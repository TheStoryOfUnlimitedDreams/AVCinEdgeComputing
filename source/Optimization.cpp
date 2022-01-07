#include "string.h"
#include "time.h"
#include "math.h"
#include "iostream"
//#include "signal.h"


#include "GlobalVariables.h"
#include "Optimization.h"
#include "ParType.h"
#include "ParFile.h"
#include "Output.h"


Optimization::Optimization()
{

}

Optimization::~Optimization()
{
	FreeSpaceElement();

	FreeOutputElement();

	if (pOutput != NULL)
	{
		delete pOutput;
	}
}

int Optimization::OptimizationProc()
{
	pOutput = new COutput();

	if (pControl->Cloud == 1) //与云通信
	{
		CloudOptimization();//云端求解优化
	}
	else if (pControl->Cloud == 0) //不与云通信
	{
		LocalOptimization();//就地求解优化
	}
	return 1;
}

void Optimization::CloudOptimization()
{
	pOutput->WriteTitle();                        //输出Begin标识符

	//只完成转送与下发和就地运行部分

	pOutput->WriteEnd();                          //输出End标识符
	pOutput->CloseFile();                         //关闭输出文件
}

void Optimization::LocalOptimization()
{
	//判断是否支持求解器安装 0/否  1/是
	if (pControl->Solver == 0) //不支持求解器安装
	{
		IterBasedOptimization();//基于前推回代法进行求解
	}
	else if (pControl->Solver == 1) //支持求解器安装
	{
		SolverBasedOptimization();//基于求解器进行求解
	}
}

void Optimization::IterBasedOptimization()
{
	pRuntime->Hth = pControl->Npoint;//Control文件要求运行的时序点数目

	NewMatrix();//对优化过程中的矩阵进行内存分配(运算使用和输出使用)

	// 优化前
	pOutput->InitialStateGetFileOpen();
	pOutput->WriteTitle();                        //输出Begin标识符

	GenDeadComb();//生成出力组合  DG/SOP

	NodeOrder();                                  //节点排序

	pControl->Optimize = 0; //初始优化获得全网的初始状态

	BacForSweep();//前推回代法求解潮流

	pOutput->WriteResult();
	pOutput->WriteEnd();                          //输出End标识符
	pOutput->CloseFile();                         //关闭输出文件

	// 优化后
	pOutput->OptimizedStateGetFileOpen();
	pOutput->WriteTitle();                        //输出Begin标识符

	pControl->Optimize = 1; //初始优化获得全网的初始状态

	TuneCtrlDvcStrategy();//遍历整定可控设备的出力策略

	pOutput->WriteResult();
	pOutput->WriteEnd();                          //输出End标识符
	pOutput->CloseFile();                         //关闭输出文件

	ReleaseMatrix();//对优化过程中的矩阵内存进行释放(运算使用)

}

void Optimization::SolverBasedOptimization()
{
	pOutput->WriteTitle();                        //输出Begin标识符

	;//基于求解器求解

	pOutput->WriteEnd();                          //输出End标识符
	pOutput->CloseFile();                         //关闭输出文件
}

void Optimization::NodeOrder()
{
	int r = 1;
	int l = 0;
	int s = 0;

	/*Queue Queue2分配内存*/
	Queue = new int* [pRuntime->maxBus + 1];
	for (int i = 0; i <= (pRuntime->maxBus + 1) - 1; i++)
	{
		Queue[i] = new int[pRuntime->maxBus];
	}
	Queue2 = new int[pRuntime->maxBus];

	/*Queue Queue2初始化*/
	for (int i = 0; i <= (pRuntime->maxBus + 1) - 1; i++)
	{
		for (int j = 0; j <= pRuntime->maxBus - 1; j++)
		{
			Queue[i][j] = 0;
		}
	}
	for (int i = 0; i <= pRuntime->maxBus - 1; i++)
	{
		Queue2[i] = 0;
	}

	for (int i = 0; i <= pRuntime->maxBus - 1; i++)//ACBus+DCBus
	{
		if (pBus[i].Symb == 1)
		{
			Queue[0][l] = pBus[i].Id_Bus;//Queue第一行存储平衡节点编号
			l++;
			Queue2[s] = pBus[i].Id_Bus;
			s++;
		}
	}

	//printf("l=%d   s=%d\n", l,s);
	//for (int i = 0; i <= (pRuntime->maxBus + 1) - 1; i++)
	//{
	//	for (int j = 0; j <= pRuntime->maxBus - 1; j++)
	//	{
	//		//printf("Queue[%d][%d] = %d", i ,j ,Queue[i][j]);
	//		printf("%d   ", Queue[i][j]);
	//	}
	//	printf("\n");
	//}

	//printf("*******************************************\n");
	//for (int j = 0; j <= pRuntime->maxBus - 1; j++)
	//{
	//	//printf("Queue[%d][%d] = %d", i ,j ,Queue[i][j]);
	//	printf("%d   ", Queue2[j]);
	//}
	//printf("\n");

	//printf("s = %d   \n", s);
	//printf("pRuntime->maxBus = %d   \n", pRuntime->maxBus);

	for (int j = 0; j <= pRuntime->maxBus - 1; j++)//Queue行
	{
		l = 0;

		//printf("*Queue[j]=%d   j=%d\n", *Queue[j], j);

		if (*Queue[j] != 0)
		{
			for (int i = 0; i <= pRuntime->maxBus - 1; i++)//Queue列
			{
				//printf("s = %d\n", s);

				if (Queue[j][i] != 0)
				{
					//因为存在等效线路 所以原拓扑连接关系发生变化 需要使用真实元件的连接关系进行判断
					for (int k = 0; k <= pRuntime->maxLine - 1; k++)//ACline("L"-"S")
					{
						int st = 0;
						//当线路为真实线路
						if (strcmp(pLine[k].Type_Line, "L") == 0)
						{
							if (pLine[k].BegNod == Queue[j][i])//找到首节点是该节点的线路
							{
								for (int k2 = 0; k2 <= s - 1; k2++)
								{
									if (pLine[k].EndNod == Queue2[k2])
									{
										st = 1;
									}
								}
								if (st == 0)
								{
									Queue[r][l] = pLine[k].EndNod;//Queue从第二行开始存放和该节点（首节点）位于同一条线路上的尾节点
									l++;
									Queue2[s] = pLine[k].EndNod;
									s++;
									//printf("s = %d\n", s);
								}
							}

							if (pLine[k].EndNod == Queue[j][i])//找到尾节点是该节点的线路
							{
								for (int k2 = 0; k2 <= s - 1; k2++)
								{
									if (pLine[k].BegNod == Queue2[k2])
									{
										st = 1;
									}
								}
								if (st == 0)
								{
									Queue[r][l] = pLine[k].BegNod;//Queue从第二行开始存放和该节点（尾节点）位于同一条线路上的首节点
									l++;
									Queue2[s] = pLine[k].BegNod;
									s++;
								}
							}
						}

						//当线路是联络开关等效线路
						if (strcmp(pLine[k].Type_Line, "S") == 0)
						{
							for (int t = 0; t <= pRuntime->maxSwitch - 1; t++)
							{
								if (pSwitch[t].BegNod == Queue[j][i])
								{
									for (int k2 = 0; k2 <= s - 1; k2++)
									{
										if (pSwitch[t].EndNod == Queue2[k2])
										{
											st = 1;
										}
									}
									if (st == 0)
									{
										Queue[r][l] = pSwitch[t].EndNod;
										l++;
										Queue2[s] = pSwitch[t].EndNod;
										s++;
									}

								}

								if (pSwitch[t].EndNod == Queue[j][i])
								{
									for (int k2 = 0; k2 <= s - 1; k2++)
									{
										if (pSwitch[t].BegNod == Queue2[k2])
										{
											st = 1;
										}
									}
									if (st == 0)
									{
										Queue[r][l] = pSwitch[t].BegNod;
										l++;
										Queue2[s] = pSwitch[t].BegNod;
										s++;
									}
								}
							}
						}
					}
				}
			}
			r++;
		}
	}

	//for (int i = 0; i <= (pRuntime->maxBus + 1) - 1; i++)
	//{
	//	for (int j = 0; j <= pRuntime->maxBus - 1; j++)
	//	{
	//		//printf("Queue[%d][%d] = %d", i ,j ,Queue[i][j]);
	//		printf("%d   ", Queue[i][j]);
	//	}
	//	printf("\n");
	//}

	//printf("*******************************************\n");
	//for (int j = 0; j <= pRuntime->maxBus - 1; j++)
	//{
	//	//printf("Queue[%d][%d] = %d", i ,j ,Queue[i][j]);
	//	printf("%d   ", Queue2[j]);
	//}
	//printf("\n");


	//printf("s = %d\n", s);


	int k2 = 0;
	int k3 = 0;
	for (int k = 0; k <= pRuntime->maxLine - 1; k++)
	{
		if (strcmp(pLine[k].Type_Line, "L") == 0)
		{
			for (int i = 0; i <= pRuntime->maxBus - 1; i++)
			{
				for (int j = 0; j <= pRuntime->maxBus - 1; j++)
				{
					if (Queue[i][j] == pLine[k].BegNod)
					{
						k2 = i;
					}
					if (Queue[i][j] == pLine[k].EndNod)
					{
						k3 = i;
					}
				}
			}
			if (k2 > k3)
			{
				int temp;
				temp = pLine[k].BegNod;
				pLine[k].BegNod = pLine[k].EndNod;
				pLine[k].EndNod = temp;

				for (int i = 0; i < pRuntime->maxBus; i++)
				{
					if (pLine[k].BegNod == pBus[i].Id_Bus)
					{
						pLine[k].BVt = pBus[i].V;
					}
					if (pLine[k].EndNod == pBus[i].Id_Bus)
					{
						pLine[k].EVt = pBus[i].V;
					}
				}
			}
		}
		if (strcmp(pLine[k].Type_Line, "S") == 0)
		{
			for (int t = 0; t <= pRuntime->maxSwitch - 1; t++)
			{
				for (int i = 0; i <= pRuntime->maxBus - 1; i++)
				{
					for (int j = 0; j <= pRuntime->maxBus - 1; j++)
					{
						if (Queue[i][j] == pSwitch[t].BegNod)
						{
							k2 = i;
						}
						if (Queue[i][j] == pSwitch[t].EndNod)
						{
							k3 = i;
						}
					}
				}
				if (k2 > k3)
				{
					if (pSwitch[t].FakeId == pLine[k].Id_Line)
					{
						int temp;
						temp = pSwitch[t].BegNod;
						pSwitch[t].BegNod = pSwitch[t].EndNod;
						pSwitch[t].EndNod = temp;
						for (int i = 0; i < pRuntime->maxBus; i++)
						{
							if (pSwitch[t].BegNod == pBus[i].Id_Bus)
							{
								pSwitch[t].BVt = pBus[i].V;
							}
							if (pSwitch[t].EndNod == pBus[i].Id_Bus)
							{
								pSwitch[t].EVt = pBus[i].V;
							}
						}

						pLine[k].BegNod = pSwitch[t].BegNod;
						pLine[k].EndNod = pSwitch[t].EndNod;
						pLine[k].BVt = pSwitch[t].BVt;
						pLine[k].EVt = pSwitch[t].EVt;
					}
				}
			}
		}
	}


}

void Optimization::GenDeadComb()//生成出力组合  DG/SOP
{
	int numPoint = 21;
	//分布式死区组合列表
	DeadZooomPoint = new double[numPoint];
	for (int i = 0; i < numPoint; i++)
	{
		DeadZooomPoint[i] = 0.9 + i * 0.01;
	}

	//构建分布式死区组合列表
	DeadZoomCombnum = 0;
	for (int i = 0; i < numPoint; i++)
	{
		for (int j = i; j < numPoint; j++)
		{
			DeadZoomCombnum++;
		}
	}

	DeadZooomCombs = new double* [DeadZoomCombnum];
	for (int i = 0; i < DeadZoomCombnum; i++)
	{
		DeadZooomCombs[i] = new double[2];
	}
	for (int i = 0; i < DeadZoomCombnum; i++)
	{
		DeadZooomCombs[i][0] = 0;
		DeadZooomCombs[i][1] = 0;
	}


	DeadZoomCombnum = 0;

	for (int i = 0; i < numPoint; i++)
	{
		Vlow = DeadZooomPoint[i];
		for (int j = i; j < numPoint; j++)
		{
			Vup = DeadZooomPoint[j];
			DeadZooomCombs[DeadZoomCombnum][0] = Vlow;
			DeadZooomCombs[DeadZoomCombnum][1] = Vup;
			DeadZoomCombnum++;
		}
	}

	//for (int i = 0; i < DeadZoomCombnum; i++)
	//{
	//	printf("%2.3lf / %2.3lf\n", DeadZooomCombs[i][0], DeadZooomCombs[i][1]);
	//}



}

void Optimization::BacForSweep()
{
	// 潮流计算中的节点功率计算变量
	double Ploadtime = 0;
	double Qloadtime = 0;
	double PDGtime = 0;
	double QDGtime = 0;
	double PSOPtime = 0;
	double QSOPtime = 0;

	// 潮流计算中的误差等辅助变量
	int Endnum;        //线路末节点编号
	int Startnum;      //线路首节点编号
	double Ploss = 0;
	double Qloss = 0;
	double DU = 0;
	double dU = 0;
	double LastU = 0;
	double maxerror = 0;   //最大电压迭代误差
	double* error;

	error = new double[pRuntime->Hth];
	for (int j = 0; j < pRuntime->Hth; j++)//优化时段
	{
		error[j] = 0;
	}

	// 初始化
	for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
	{
		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		{
			NodePowerP[i][j] = 0;
			NodePowerQ[i][j] = 0;
			NodePowerP_iter[i][j] = 0;
			NodePowerQ_iter[i][j] = 0;
		}
	}
	for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
	{
		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		{
			NodeVoltAmp[i][j] = pControl->InitialV;
		}
	}

	// Load 
	for (int h = 0; h < pRuntime->Hth; h++)
	{
		for (int i = 0; i < pRuntime->maxLoad; i++)
		{
			Ploadtime = 0.0;
			Qloadtime = 0.0;

			for (int j = 0; j < pRuntime->maxCurve; j++)
			{
				if (pLoad[i].Curve_Load == pCurve[j].Id_Curve)
				{
					Ploadtime = pLoad[i].PLoad * pCurve[j].TimSeq[h];
					Qloadtime = pLoad[i].QLoad * pCurve[j].TimSeq[h];
				}
			}
			for (int k = 0; k < pRuntime->maxBus; k++)
			{
				if (pLoad[i].ConNod_Load == pBus[k].Id_Bus)
				{
					NodePowerP[k][h] += Ploadtime;
					NodePowerQ[k][h] += Qloadtime;
				}
			}
		}
	}

	// DG
	for (int h = 0; h < pRuntime->Hth; h++)
	{
		for (int i = 0; i < pRuntime->maxDG; i++)
		{
			PDGtime = 0.0;
			QDGtime = 0.0;

			if (pControl->Optimize == 0)
			{
				PDGtime = DGData[i][h].P0;
				QDGtime = DGData[i][h].Q0;

			}
			if (pControl->Optimize == 1)
			{
				PDGtime = DGData[i][h].P;
				QDGtime = DGData[i][h].Q;
			}

			for (int k = 0; k < pRuntime->maxBus; k++)
			{
				if (pDG[i].ConNod_DG == pBus[k].Id_Bus)
				{
					NodePowerP[k][h] -= PDGtime;
					NodePowerQ[k][h] -= QDGtime;
				}
			}
		}
	}

	// SOP
	for (int h = 0; h < pRuntime->Hth; h++)
	{
		for (int i = 0; i < pRuntime->maxSOP; i++)
		{
			PSOPtime = 0.0;
			QSOPtime = 0.0;

			if (pControl->Optimize == 0)
			{
				PSOPtime = SOPData[i][h].P0;
				QSOPtime = SOPData[i][h].Q0;

			}
			if (pControl->Optimize == 1)
			{
				PSOPtime = SOPData[i][h].P;
				QSOPtime = SOPData[i][h].Q;
			}

			for (int k = 0; k < pRuntime->maxBus; k++)
			{
				if (pSOP[i].ConNod_SOP == pBus[k].Id_Bus)
				{
					NodePowerP[k][h] -= PSOPtime;
					NodePowerQ[k][h] -= QSOPtime;
				}
			}
		}
	}

	//if (pControl->test == 1) //初始优化获得全网的初始状态)
	//{
	//	for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
	//	{
	//		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
	//		{
	//			printf("NodePowerP[%d][%d] = %lf      NodePowerQ[%d][%d] = %lf\n", i, j, NodePowerP[i][j], i, j, NodePowerQ[i][j]);
	//		}
	//	}
	//}

	//fprintf(pF, "------------------------------NodePowerP\n");
	//for (int i = 0; i < pRuntime->maxBus; i++)
	//{
	//	for (int j = 0; j < pRuntime->Hth; j++)//优化时段
	//	{
	//		fprintf(pF, "%20.7lf\t", 1000 * NodePowerP[i][j]);
	//	}
	//}
	//fprintf(pF, "\n");




	// 标幺化
	for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
	{
		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		{
			NodePowerP[i][j] = NodePowerP[i][j] / pControl->BaseVe;
			NodePowerQ[i][j] = NodePowerQ[i][j] / pControl->BaseVe;
		}
	}

	// 迭代功率赋初值
	for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
	{
		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		{
			NodePowerP_iter[i][j] = NodePowerP[i][j];
			NodePowerQ_iter[i][j] = NodePowerQ[i][j];
		}
	}

	for (int i = 0; i < pRuntime->maxLine; i++)//ACBus+DCBus
	{
		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		{
			LineP[i][j] = 0;
			LineQ[i][j] = 0;

			LinePloss[i][j] = 0;
			LineQloss[i][j] = 0;

			LineI[i][j] = 0;
		}
	}


	//fprintf(pF, "------------------------------NodePowerP_iter\n");
	//for (int i = 0; i < pRuntime->maxBus; i++)
	//{
	//	for (int j = 0; j < pRuntime->Hth; j++)//优化时段
	//	{
	//		fprintf(pF, "%20.7lf\t", 1000 * NodePowerP_iter[i][j]);
	//	}
	//}
	//fprintf(pF, "\n");


	//if (pControl->test == 1) //初始优化获得全网的初始状态)
	//{
	//	for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
	//	{
	//		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
	//		{
	//			printf("NodePowerP_iter[%d][%d] = %lf      NodePowerP_iter[%d][%d] = %lf\n", i, j, NodePowerP_iter[i][j], i, j, NodePowerP_iter[i][j]);
	//		}
	//	}
	//	printf("--------------------------------------------------------------------------------\n");
	//}


	//int t = 0;
	//fprintf(pF, "------------------------------LineP\n");

	// 前推回代法主体
	do {

		for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
		{
			for (int j = 0; j < pRuntime->Hth; j++)//优化时段
			{
				NodePowerP_iter[i][j] = NodePowerP[i][j];
				NodePowerQ_iter[i][j] = NodePowerQ[i][j];
			}
		}
		for (int i = 0; i < pRuntime->maxLine; i++)//ACBus+DCBus
		{
			for (int j = 0; j < pRuntime->Hth; j++)//优化时段
			{
				LineP[i][j] = 0;
				LineQ[i][j] = 0;

				LinePloss[i][j] = 0;
				LineQloss[i][j] = 0;

				LineI[i][j] = 0;
			}
		}
		//误差置零
		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		{
			error[j] = 0;
		}
		maxerror = 0;


		//前推功率
		for (int i = pRuntime->maxBus - 1; i > 0; i--)//ACBus+DCBus
		{
			for (int j = 0; j < pRuntime->maxBus; j++)
			{
				if (Queue[i][j] != 0)
				{
					Endnum = Queue[i][j];

					for (int k = 0; k < pRuntime->maxLine; k++)//遍历线路
					{
						if (pLine[k].EndNod == Endnum)
						{
							Startnum = pLine[k].BegNod;

							for (int h = 0; h < pRuntime->Hth; h++)
							{
								Ploss = (NodePowerP_iter[Endnum - 1][h] * NodePowerP_iter[Endnum - 1][h]
									+ NodePowerQ_iter[Endnum - 1][h] * NodePowerQ_iter[Endnum - 1][h])
									* (pLine[k].R / (pow(pBus[j].V, 2.0) / pControl->BaseVe * 1000))
									/ (NodeVoltAmp[Endnum - 1][h] * NodeVoltAmp[Endnum - 1][h]);

								Qloss = (NodePowerP_iter[Endnum - 1][h] * NodePowerP_iter[Endnum - 1][h]
									+ NodePowerQ_iter[Endnum - 1][h] * NodePowerQ_iter[Endnum - 1][h])
									* (pLine[k].X / (pow(pBus[j].V, 2.0) / pControl->BaseVe * 1000))
									/ (NodeVoltAmp[Endnum - 1][h] * NodeVoltAmp[Endnum - 1][h]);

								NodePowerP_iter[Startnum - 1][h] += NodePowerP_iter[Endnum - 1][h];
								NodePowerQ_iter[Startnum - 1][h] += NodePowerQ_iter[Endnum - 1][h];

								NodePowerP_iter[Startnum - 1][h] += Ploss;
								NodePowerQ_iter[Startnum - 1][h] += Qloss;

								LineP[k][h] = Ploss + NodePowerP_iter[Endnum - 1][h];
								LineQ[k][h] = Qloss + NodePowerQ_iter[Endnum - 1][h];

								LinePloss[k][h] = Ploss;
								LineQloss[k][h] = Qloss;
							}
						}
					}
				}
				else
					break;
			}
		}


		//for (int ii = 0; ii < pRuntime->maxBus; ii++)//ACBus+DCBus
		//{
		//	for (int jj = 0; jj < pRuntime->Hth; jj++)//优化时段
		//	{
		//		printf("NodePowerP_iter[%d][%d] = %lf	", ii, jj, NodePowerP_iter[ii][jj]);
		//		printf("NodePowerQ_iter[%d][%d] = %lf \n", ii, jj, NodePowerQ_iter[ii][jj]);
		//	}
		//}

		//for (int ii = 0; ii < pRuntime->maxLine; ii++)//ACBus+DCBus
		//{
		//	for (int jj = 0; jj < pRuntime->Hth; jj++)//优化时段
		//	{
		//		printf("LineP[%d][%d] = %lf	", ii, jj, LineP[ii][jj]);
		//		printf("LineQ[%d][%d] = %lf\n", ii, jj, LineQ[ii][jj]);
		//	}
		//}

				//////////////////////////////////////////////////////
		//t = t + 1;

		//fprintf(pF, "+++++++++++++++++++%d++++++++++++++++++++\n", t);

		//for (int i = 0; i < pRuntime->maxLine; i++)
		//{
		//	for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		//	{
		//		fprintf(pF, "%20.7lf\t", 1000 * LineP[i][j]);
		//	}
		//}
		//fprintf(pF, "\n");


		//回推电压
		for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
		{
			for (int j = 0; j < pRuntime->maxBus; j++)
			{
				if (Queue[i][j] != 0)
				{
					Startnum = Queue[i][j];

					for (int k = 0; k < pRuntime->maxLine; k++)//遍历线路
					{
						if (pLine[k].BegNod == Startnum)
						{
							Endnum = pLine[k].EndNod;

							for (int h = 0; h < pRuntime->Hth; h++)
							{
								DU = (LineP[k][h] * (pLine[k].R / (pow(pBus[j].V, 2.0) / pControl->BaseVe * 1000)) + LineQ[k][h] * (pLine[k].X / (pow(pBus[j].V, 2.0) / pControl->BaseVe * 1000))) / NodeVoltAmp[Startnum - 1][h];
								dU = (LineP[k][h] * (pLine[k].X / (pow(pBus[j].V, 2.0) / pControl->BaseVe * 1000)) - LineQ[k][h] * (pLine[k].R / (pow(pBus[j].V, 2.0) / pControl->BaseVe * 1000))) / NodeVoltAmp[Startnum - 1][h];

								LastU = NodeVoltAmp[Endnum - 1][h];

								NodeVoltAmp[Endnum - 1][h] = sqrt(pow((NodeVoltAmp[Startnum - 1][h] - DU), 2) + pow(dU, 2));

								if (error[h] < abs(LastU - NodeVoltAmp[Endnum - 1][h]))
								{
									error[h] = abs(LastU - NodeVoltAmp[Endnum - 1][h]);
								}
							}
						}
					}
				}
				else
					break;
			}
		}

		//printf("V\n");
		//for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
		//{
		//	for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		//	{
		//		printf("NodeVoltAmp[%d][%d] = %lf\n", i, j, NodeVoltAmp[i][j]);
		//	}
		//}
		//printf("**********************************************************************\n");


		//printf("------------------------------LOSS\n");
		//for (int i = 0; i < pRuntime->maxLine; i++)
		//{
		//	for (int j = 0; j < pRuntime->Hth; j++)
		//	{
		//		printf("%lf\t", LinePloss[i][j]);
		//		printf("%lf\n", LineQloss[i][j]);
		//	}
		//}


		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		{
			if (maxerror < error[j])
			{
				maxerror = error[j];
			}
		}



	} while (maxerror > pControl->MaxPre);


	// 计算线路电流
	for (int i = 0; i < pRuntime->maxLine; i++)
	{
		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		{
			LineI[i][j] = sqrt((pow(LineP[i][j], 2.0) + pow(LineQ[i][j], 2.0)) /
				pow(NodeVoltAmp[pLine[i].BegNod][j], 2.0)) *
				pControl->BaseVe / pControl->BaseV;		//线路电流
		}
	}

	//fprintf(pF, "------------------------------LineP\n");
	//for (int i = 0; i < pRuntime->maxLine; i++)
	//{
	//	for (int j = 0; j < pRuntime->Hth; j++)//优化时段
	//	{
	//		fprintf(pF,"%20.7lf\t", 1000*LineP[i][j]);
	//	}
	//}
	//fprintf(pF, "\n");

	

	// 结果整理
	if (pControl->Optimize == 0)
	{
		for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
		{
			for (int j = 0; j < pRuntime->Hth; j++)//优化时段
			{
				VoltData[i][j].V0 = NodeVoltAmp[i][j];//节点初始电压
			}
		}
		for (int i = 0; i < pRuntime->maxLine; i++)
		{
			for (int j = 0; j < pRuntime->Hth; j++)//优化时段
			{
				LineData[i][j].P0 = LineP[i][j];					//线路有功功率 kW
				LineData[i][j].Q0 = LineQ[i][j];					//线路无功功率 kVar
				LineData[i][j].PLoss0 = LinePloss[i][j];			//损耗有功功率 kW
				LineData[i][j].QLoss0 = LineQloss[i][j];			//损耗无功功率 kVar
				LineData[i][j].I0 = LineI[i][j];					//线路电流
			}
		}

		// 损耗置零
		for (int h = 0; h < pRuntime->Hth; h++)
		{
			Obj[h].ObjmatPLoss0 = 0;
			Obj[h].ObjmatVDev0 = 0;
			Obj[h].ObjmatIcay0 = 0;
			Obj[h].Objmat0 = 0;
			Obj[h].maxIcay0 = 0;
			Obj[h].maxV0 = 0;
			Obj[h].minV0 = 1;
		}

		for (int h = 0; h < pRuntime->Hth; h++)
		{
			for (int j = 0; j < pRuntime->maxLine; j++)
			{
				Obj[h].ObjmatPLoss0 += LineData[j][h].PLoss0;
				Obj[h].ObjmatIcay0 += pow((LineData[j][h].I0 / pLine[j].Imax), 2);
			}
			for (int j = 0; j < pRuntime->maxBus; j++)
			{
				Obj[h].ObjmatVDev0 += abs(pow(VoltData[j][h].V0, 2) - 1);
			}
			Obj[h].Objmat0 = Obj[h].ObjmatPLoss0 * pControl->WeightA +
				Obj[h].ObjmatVDev0 * pControl->WeightB +
				Obj[h].ObjmatIcay0 * pControl->WeightC;

			for (int j = 0; j < pRuntime->maxBus; j++)
			{
				if (Obj[h].maxV0 < VoltData[j][h].V0)
					Obj[h].maxV0 = VoltData[j][h].V0;
				if (Obj[h].minV0 > VoltData[j][h].V0)
					Obj[h].minV0 = VoltData[j][h].V0;
			}
			for (int j = 0; j < pRuntime->maxLine; j++)
			{
				if (Obj[h].maxIcay0 < pow((LineData[j][h].I0 / pLine[j].Imax), 2))
				{
					Obj[h].maxIcay0 = pow((LineData[j][h].I0 / pLine[j].Imax), 2);
				}
			}
		}
	}

	if (pControl->Optimize == 1)
	{
		for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
		{
			for (int j = 0; j < pRuntime->Hth; j++)//优化时段
			{
				VoltData[i][j].V = NodeVoltAmp[i][j];//节点优化后电压
			}
		}
		for (int i = 0; i < pRuntime->maxLine; i++)
		{
			for (int j = 0; j < pRuntime->Hth; j++)//优化时段
			{
				LineData[i][j].P = LineP[i][j];					//线路有功功率 kW
				LineData[i][j].Q = LineQ[i][j];					//线路无功功率 kVar
				LineData[i][j].PLoss = LinePloss[i][j];			//损耗有功功率 kW
				LineData[i][j].QLoss = LineQloss[i][j];			//损耗无功功率 kVar
				LineData[i][j].I = LineI[i][j];					//线路电流 A
			}
		}

		// 损耗置零
		for (int h = 0; h < pRuntime->Hth; h++)
		{
			Obj[h].ObjmatPLoss = 0;
			Obj[h].ObjmatVDev = 0;
			Obj[h].ObjmatIcay = 0;
			Obj[h].Objmat = 0;
			Obj[h].maxIcay = 0;
			Obj[h].maxV = 0;
			Obj[h].minV = 1;
		}

		for (int h = 0; h < pRuntime->Hth; h++)
		{
			for (int j = 0; j < pRuntime->maxLine; j++)
			{
				Obj[h].ObjmatPLoss += LineData[j][h].PLoss;
				Obj[h].ObjmatIcay += pow((LineData[j][h].I / pLine[j].Imax), 2);
			}
			for (int j = 0; j < pRuntime->maxBus; j++)
			{
				Obj[h].ObjmatVDev += abs(pow(VoltData[j][h].V, 2) - 1);
			}
			Obj[h].Objmat =
				Obj[h].ObjmatPLoss * pControl->WeightA +
				Obj[h].ObjmatVDev * pControl->WeightB +
				Obj[h].ObjmatIcay * pControl->WeightC;

			for (int j = 0; j < pRuntime->maxBus; j++)
			{
				if (Obj[h].maxV < VoltData[j][h].V)
					Obj[h].maxV = VoltData[j][h].V;
				if (Obj[h].minV > VoltData[j][h].V)
					Obj[h].minV = VoltData[j][h].V;
			}
			for (int j = 0; j < pRuntime->maxLine; j++)
			{
				if (Obj[h].maxIcay < pow((LineData[j][h].I / pLine[j].Imax), 2))
				{
					Obj[h].maxIcay = pow((LineData[j][h].I / pLine[j].Imax), 2);
				}
			}
		}
	}

	//for (int i = 0; i < pRuntime->maxBus; i++)
	//{
	//	for (int j = 0; j < pRuntime->Hth; j++)
	//	{
	//		printf("%lf\t", NodePowerP[i][j]);
	//	}
	//	printf("\n");
	//}
	//printf("*****************************************\n");
	//for (int i = 0; i < pRuntime->maxBus; i++)
	//{
	//	for (int j = 0; j < pRuntime->Hth; j++)
	//	{
	//		printf("%lf\t", NodePowerQ[i][j]);
	//	}
	//	printf("\n");
	//}

	delete[]error;

}

void Optimization::TuneCtrlDvcStrategy()//遍历整定可控设备的出力策略
{
	double G = 0;
	numOptmz = 0;// 用于存储总优化变量数
	DGnumOptmz = 0;// 用于存储DG优化变量数
	SOPnumOptmz = 0;// 用于存储SOP优化变量数
	numOptmzstorg = 0; // 用于存储优化结果的存储位置

	if (pRuntime->maxDG > 0 && pRuntime->maxSOP > 0)
	{
		DGnumOptmz = DeadZoomCombnum;
		SOPnumOptmz = DeadZoomCombnum;
		numOptmz = DeadZoomCombnum * DeadZoomCombnum;
	}
	if (pRuntime->maxDG > 0 && pRuntime->maxSOP == 0)
	{
		DGnumOptmz = DeadZoomCombnum;
		SOPnumOptmz = 1;
		numOptmz = DGnumOptmz;
	}
	if (pRuntime->maxDG == 0 && pRuntime->maxSOP > 0)
	{
		DGnumOptmz = 1;
		SOPnumOptmz = DeadZoomCombnum;
		numOptmz = SOPnumOptmz;
	}
	if (pRuntime->maxDG == 0 && pRuntime->maxSOP == 0)
	{
		DGnumOptmz = 1;
		SOPnumOptmz = 1;
		numOptmz = 0;
	}

	//printf("numOptmz = %d\n", numOptmz);
	//printf("DeadZoomCombnum = %d\n", DeadZoomCombnum);
	//printf("SOPnumOptmz = %d\n", SOPnumOptmz);
	//printf("DGnumOptmz = %d\n", DGnumOptmz);

	ObjmatPLoss = new double[numOptmz];   //用于描述网损目标函数
	ObjmatVDev = new double[numOptmz];    //用于描述电压偏差目标函数
	ObjmatIcay = new double[numOptmz];    //用于描述负载均衡目标函数
	Objmat = new double[numOptmz];        //用于描述总目标函数

	for (int i = 0; i < numOptmz; i++)
	{
		ObjmatPLoss[i] = 0;
		ObjmatVDev[i] = 0;
		ObjmatIcay[i] = 0;
		Objmat[i] = 0;
	}

	for (int iQDG = 0; iQDG < DGnumOptmz; iQDG++)
	{
		if (DGnumOptmz != 1)
		{
			// 分布式电源出力策略
			Vlow = DeadZooomCombs[iQDG][0];
			Vup = DeadZooomCombs[iQDG][1];

			for (int j = 0; j < pRuntime->maxDG; j++)
			{
				for (int h = 0; h < pRuntime->Hth; h++)
				{
					Qbase = sqrt(pow(pDG[j].Smax, 2) - pow(DGData[j][h].P, 2));

					for (int k = 0; k < pRuntime->maxBus; k++)
					{
						if (pDG[j].ConNod_DG == pBus[k].Id_Bus)
						{
							G = GetGValue(VoltData[k][h].V0, Vlow, Vup);
						}
					}
					DGData[j][h].Q = Qbase * G;

					//越限则置于限上

					if (pDG[j].TakePart == 1)
					{
						if (DGData[j][h].Q > pDG[j].Qmax)
						{
							DGData[j][h].Q = pDG[j].Qmax;
						}
						if (DGData[j][h].Q < pDG[j].Qmin)
						{
							DGData[j][h].Q = pDG[j].Qmin;
						}
					}
					if (pDG[j].TakePart == 0)
					{
						DGData[j][h].Q = DGData[j][h].Q0;
					}
				}
			}

		}
		for (int iQSOP = 0; iQSOP < SOPnumOptmz; iQSOP++)
		{
			if (SOPnumOptmz != 1)
			{
				// SOP出力策略
				Vlow = DeadZooomCombs[iQSOP][0];
				Vup = DeadZooomCombs[iQSOP][1];

				for (int j = 0; j < pRuntime->maxSOP; j++)
				{
					for (int h = 0; h < pRuntime->Hth; h++)
					{
						//计算无功最大容量
						Qbase = sqrt(pow(pSOP[j].Smax, 2) - pow(SOPData[j][h].P, 2));

						for (int k = 0; k < pRuntime->maxBus; k++)
						{
							if (pSOP[j].ConNod_SOP == pBus[k].Id_Bus)
							{
								G = GetGValue(VoltData[k][h].V0, Vlow, Vup);
							}
						}

						SOPData[j][h].Q = Qbase * G;

						//越限则置于限上
						if (SOPData[j][h].P > pSOP[j].Pmax)
						{
							SOPData[j][h].P = pSOP[j].Pmax;
						}
						if (SOPData[j][h].P < pSOP[j].Pmin)
						{
							SOPData[j][h].P = pSOP[j].Pmin;
						}

						if (pSOP[j].TakePart == 1)
						{
							if (SOPData[j][h].Q > pSOP[j].Qmax)
							{
								SOPData[j][h].Q = pSOP[j].Qmax;
							}
							if (SOPData[j][h].Q < pSOP[j].Qmin)
							{
								SOPData[j][h].Q = pSOP[j].Qmin;
							}
						}
						if (pSOP[j].TakePart == 0)
						{
							SOPData[j][h].Q = SOPData[j][h].Q0;
						}
					}
				}
			}

			pControl->Optimize = 1; //初始优化获得全网的初始状态

			BacForSweep();//前推回代法求解潮流

			for (int h = 0; h < pRuntime->Hth; h++)
			{
				for (int j = 0; j < pRuntime->maxLine; j++)
				{
					ObjmatPLoss[numOptmzstorg] += LineData[j][h].PLoss;
					ObjmatIcay[numOptmzstorg] += pow((LineData[j][h].I / pLine[j].Imax), 2);
				}
				for (int j = 0; j < pRuntime->maxBus; j++)
				{
					ObjmatVDev[numOptmzstorg] += abs(pow(VoltData[j][h].V, 2) - 1);
				}
			}
			Objmat[numOptmzstorg] =
				ObjmatPLoss[numOptmzstorg] * pControl->WeightA +
				ObjmatVDev[numOptmzstorg] * pControl->WeightB +
				ObjmatIcay[numOptmzstorg] * pControl->WeightC;

			numOptmzstorg = numOptmzstorg + 1;
		}
	}

	//for (int i = 0; i < numOptmz; i++)
	//{
	//	printf("Objmat[%d] = %lf\n", i, Objmat[i]);
	//}

	//printf("numOptmzstorg = %d\n", numOptmzstorg);



	int num = 0;
	double minObj = 100;

	for (int i = 0; i < numOptmz; i++)
	{
		if (minObj >= Objmat[i])
		{
			minObj = Objmat[i];
			num = i;
		}
	}

	// printf("num = %d\n", num);

	// 反解对应的 SOP 与 DG 的出力死区
	// 刷新最终的电压
	int numDG = 0;
	int numSOP = 0;

	if (pRuntime->maxDG == 0 && pRuntime->maxSOP > 0)
	{
		numSOP = num;
	}
	if (pRuntime->maxDG > 0 && pRuntime->maxSOP == 0)
	{
		numDG = num;
	}
	if (pRuntime->maxDG > 0 && pRuntime->maxSOP > 0)
	{
		numSOP = num % DeadZoomCombnum;
		numDG = num / DeadZoomCombnum;
	}


	//printf("numSOP = %d\n", numSOP);
	//printf("numDG = %d\n", numDG);


	// DG 刷新
	Vlow = DeadZooomCombs[numDG][0];
	Vup = DeadZooomCombs[numDG][1];

	for (int i = 0; i < pRuntime->maxDG; i++)
	{
		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		{
			DGData[i][j].Vlow = Vlow;	//控制曲线死区下限
			DGData[i][j].Vup = Vup;	//控制曲线死区上限
		}
	}

	for (int j = 0; j < pRuntime->maxDG; j++)
	{
		for (int h = 0; h < pRuntime->Hth; h++)
		{
			Qbase = sqrt(pow(pDG[j].Smax, 2) - pow(DGData[j][h].P, 2));

			for (int k = 0; k < pRuntime->maxBus; k++)
			{
				if (pDG[j].ConNod_DG == pBus[k].Id_Bus)
				{
					G = GetGValue(VoltData[k][h].V0, Vlow, Vup);
				}
			}
			if (pDG[j].TakePart == 1)
			{
				DGData[j][h].Q = Qbase * G;
			}
			if (pDG[j].TakePart == 0)
			{
				DGData[j][h].Q = DGData[j][h].Q0;
			}

			//越限则置于限上
			if (DGData[j][h].P > pDG[j].Pmax)
			{
				DGData[j][h].P = pDG[j].Pmax;
			}
			if (DGData[j][h].P < pDG[j].Pmin)
			{
				DGData[j][h].P = pDG[j].Pmin;
			}
			if (DGData[j][h].Q > pDG[j].Qmax)
			{
				DGData[j][h].Q = pDG[j].Qmax;
			}
			if (DGData[j][h].Q < pDG[j].Qmin)
			{
				DGData[j][h].Q = pDG[j].Qmin;
			}
		}

	}


	// SOP 刷新
	Vlow = DeadZooomCombs[numSOP][0];
	Vup = DeadZooomCombs[numSOP][1];

	for (int i = 0; i < pRuntime->maxSOP; i++)
	{
		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		{
			SOPData[i][j].Vlow = Vlow;	//控制曲线死区下限
			SOPData[i][j].Vup = Vup;		//控制曲线死区上限
		}
	}

	for (int j = 0; j < pRuntime->maxSOP; j++)
	{
		for (int h = 0; h < pRuntime->Hth; h++)
		{
			//计算无功最大容量
			Qbase = sqrt(pow(pSOP[j].Smax, 2) - pow(SOPData[j][h].P, 2));

			for (int k = 0; k < pRuntime->maxBus; k++)
			{
				if (pSOP[j].ConNod_SOP == pBus[k].Id_Bus)
				{
					G = GetGValue(VoltData[k][h].V0, Vlow, Vup);
				}
			}

			SOPData[j][h].Q = Qbase * G;

			//越限则置于限上
			if (SOPData[j][h].P > pSOP[j].Pmax)
			{
				SOPData[j][h].P = pSOP[j].Pmax;
			}
			if (SOPData[j][h].Q > pSOP[j].Qmax)
			{
				SOPData[j][h].Q = pSOP[j].Qmax;
			}
			if (SOPData[j][h].P < pSOP[j].Pmin)
			{
				SOPData[j][h].P = pSOP[j].Pmin;
			}
			if (SOPData[j][h].Q < pSOP[j].Qmin)
			{
				SOPData[j][h].Q = pSOP[j].Qmin;
			}
		}
	}

	pControl->Optimize = 1; //初始优化获得全网的初始状态

	BacForSweep();//前推回代法求解潮流

}

double Optimization::GetGValue(double U0, double Ulow, double Uup) //计算分布式电源的无功出力
{
	double G = 0;

	if (U0 >= 0 && U0 < pControl->Vb)
	{
		G = 1;
	}
	if (U0 >= pControl->Vb && U0 < Ulow)
	{
		G = (1 / (pControl->Vb - Ulow)) * U0 + (1 / (Ulow - pControl->Vb)) * Ulow;
	}
	if (U0 >= Ulow && U0 < Uup)
	{
		G = 0;
	}
	if (U0 >= Uup && U0 < pControl->Vu)
	{
		G = (1 / (Uup - pControl->Vu)) * U0 + (1 / (pControl->Vu - Uup)) * Uup;
	}
	if (U0 >= pControl->Vu && U0 < 1.2)
	{
		G = -1;
	}

	return G;
}

void Optimization::NewMatrix()//对优化过程中的矩阵进行内存分配(运算使用和输出使用)
{
	//节点电压
	VoltData = new Output_VoltData * [pRuntime->maxBus];
	for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
	{
		VoltData[i] = new Output_VoltData[pRuntime->Hth];
	}
	for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
	{
		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		{
			VoltData[i][j].Id_Bus = pBus[i].Id_Bus;//母线编号
			VoltData[i][j].V0 = 0;//节点初始电压
			VoltData[i][j].V = 0;//节点优化后电压
		}
	}


	//线路功率
	LineData = new Output_LineData * [pRuntime->maxLine];
	for (int i = 0; i < pRuntime->maxLine; i++)
	{
		LineData[i] = new Output_LineData[pRuntime->Hth];
	}

	for (int i = 0; i < pRuntime->maxLine; i++)
	{
		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		{
			LineData[i][j].Id_Line = pLine[i].Id_Line;			//线路编号
			LineData[i][j].BegNod = pLine[i].BegNod;			//线路首节点编号
			LineData[i][j].EndNod = pLine[i].EndNod;			//线路尾节点编号
			LineData[i][j].P0 = 0;								//原始线路有功功率 kW
			LineData[i][j].Q0 = 0;								//原始线路无功功率 kVar
			LineData[i][j].PLoss0 = 0;							//原始损耗有功功率 kW
			LineData[i][j].QLoss0 = 0;							//原始损耗无功功率 kVar
			LineData[i][j].P = 0;								//线路有功功率 kW
			LineData[i][j].Q = 0;								//线路无功功率 kVar
			LineData[i][j].PLoss = 0;							//损耗有功功率 kW
			LineData[i][j].QLoss = 0;							//损耗无功功率 kVar
			LineData[i][j].I = 0;								//线路电流 A
		}
	}

	//节点分布式电源的出力
	DGData = new Output_DGData * [pRuntime->maxDG];
	for (int i = 0; i < pRuntime->maxDG; i++)
	{
		DGData[i] = new Output_DGData[pRuntime->Hth];
	}
	for (int i = 0; i < pRuntime->maxDG; i++)
	{
		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		{
			DGData[i][j].Id_DG = pDG[i].Id_DG;//母线编号
			DGData[i][j].ConNod_DG = pDG[i].ConNod_DG;//母线编号
			DGData[i][j].P0 = 0;//原始输出有功功率 kW
			DGData[i][j].Q0 = 0;//原始输出无功功率 kVar
			DGData[i][j].P = 0;//输出有功功率 kW
			DGData[i][j].Q = 0;//输出无功功率 kVar
			DGData[i][j].Vlow = 0;//控制曲线死区下限
			DGData[i][j].Vup = 0;//控制曲线死区上限
		}
	}
	for (int h = 0; h < pRuntime->Hth; h++)
	{
		for (int j = 0; j < pRuntime->maxDG; j++)
		{
			for (int k = 0; k < pRuntime->maxCurve; k++)
			{
				if (pDG[j].Curve_DG == pCurve[k].Id_Curve)
				{
					DGData[j][h].P0 = pDG[j].Porg * pCurve[k].TimSeq[h];
					DGData[j][h].Q0 = pDG[j].Qorg * pCurve[k].TimSeq[h];
					DGData[j][h].P = pDG[j].Porg * pCurve[k].TimSeq[h];
				}
			}

			//越限则置于限上
			if (DGData[j][h].P0 > pDG[j].Pmax)
			{
				DGData[j][h].P0 = pDG[j].Pmax;
			}
			if (DGData[j][h].P0 < pDG[j].Pmin)
			{
				DGData[j][h].P0 = pDG[j].Pmin;
			}

			if (DGData[j][h].P > pDG[j].Pmax)
			{
				DGData[j][h].P = pDG[j].Pmax;
			}
			if (DGData[j][h].P < pDG[j].Pmin)
			{
				DGData[j][h].P = pDG[j].Pmin;
			}

			if (DGData[j][h].Q0 > pDG[j].Qmax)
			{
				DGData[j][h].Q0 = pDG[j].Qmax;
			}
			if (DGData[j][h].Q0 < pDG[j].Qmin)
			{
				DGData[j][h].Q0 = pDG[j].Qmin;
			}

		}
	}

	//SOP的出力
	SOPData = new Output_SOPData * [pRuntime->maxSOP];
	for (int i = 0; i < pRuntime->maxSOP; i++)
	{
		SOPData[i] = new Output_SOPData[pRuntime->Hth];
	}
	for (int i = 0; i < pRuntime->maxSOP; i++)
	{
		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		{
			SOPData[i][j].Id_SOP = pSOP[i].Id_SOP;//母线编号
			SOPData[i][j].ConNod_SOP = pSOP[i].ConNod_SOP;//母线编号
			SOPData[i][j].P0 = pSOP[i].Porg;//端口原始输出有功功率 kW
			SOPData[i][j].Q0 = pSOP[i].Qorg;//端口原始输出无功功率 kVar
			SOPData[i][j].P = pSOP[i].Porg;//端口优化后输出有功功率 kW
			SOPData[i][j].Q = 0;//端口优化后输出无功功率 kVar
			SOPData[i][j].Vlow = 0;//端口控制曲线死区下限
			SOPData[i][j].Vup = 0;//端口控制曲线死区上限

		}
	}

	//目标函数
	Obj = new Output_Obj[pRuntime->Hth];
	for (int h = 0; h < pRuntime->Hth; h++)
	{
		Obj[h].ObjmatPLoss0 = 0;
		Obj[h].ObjmatVDev0 = 0;
		Obj[h].ObjmatIcay0 = 0;
		Obj[h].Objmat0 = 0;
		Obj[h].ObjmatPLoss = 0;
		Obj[h].ObjmatVDev = 0;
		Obj[h].ObjmatIcay = 0;
		Obj[h].Objmat = 0;
	}


	//节点的净功率注入
	NodePowerP = new double* [pRuntime->maxBus];
	NodePowerQ = new double* [pRuntime->maxBus];
	for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
	{
		NodePowerP[i] = new double[pRuntime->Hth];
		NodePowerQ[i] = new double[pRuntime->Hth];
	}

	for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
	{
		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		{
			NodePowerP[i][j] = 0;
			NodePowerQ[i][j] = 0;
		}
	}

	//迭代时的节点功率
	NodePowerP_iter = new double* [pRuntime->maxBus];
	NodePowerQ_iter = new double* [pRuntime->maxBus];
	for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
	{
		NodePowerP_iter[i] = new double[pRuntime->Hth];
		NodePowerQ_iter[i] = new double[pRuntime->Hth];
	}
	for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
	{
		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		{
			NodePowerP_iter[i][j] = 0;
			NodePowerQ_iter[i][j] = 0;
		}
	}

	//线路首端功率
	LineP = new double* [pRuntime->maxLine];
	LineQ = new double* [pRuntime->maxLine];
	LinePloss = new double* [pRuntime->maxLine];
	LineQloss = new double* [pRuntime->maxLine];
	LineI = new double* [pRuntime->maxLine];

	for (int i = 0; i < pRuntime->maxLine; i++)//ACBus+DCBus
	{
		LineP[i] = new double[pRuntime->Hth];
		LineQ[i] = new double[pRuntime->Hth];
		LinePloss[i] = new double[pRuntime->Hth];
		LineQloss[i] = new double[pRuntime->Hth];
		LineI[i] = new double[pRuntime->Hth];

	}
	for (int i = 0; i < pRuntime->maxLine; i++)//ACBus+DCBus
	{
		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		{
			LineP[i][j] = 0;
			LineQ[i][j] = 0;
			LinePloss[i][j] = 0;
			LineQloss[i][j] = 0;
			LineI[i][j] = 0;
		}
	}

	//节点电压的幅值
	NodeVoltAmp = new double* [pRuntime->maxBus];
	for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
	{
		NodeVoltAmp[i] = new double[pRuntime->Hth];
	}
	for (int i = 0; i < pRuntime->maxBus; i++)//ACBus+DCBus
	{
		for (int j = 0; j < pRuntime->Hth; j++)//优化时段
		{
			NodeVoltAmp[i][j] = pControl->InitialV;
		}
	}
}

void Optimization::ReleaseMatrix()//对优化过程中的矩阵内存进行释放(运算使用)
{

	//释放此部分施用内存
	//死区组合
	delete[]DeadZooomPoint;

	for (int i = 0; i < DeadZoomCombnum; i++)
	{
		delete[]DeadZooomCombs[i];
	}
	delete[]DeadZooomCombs;

	//Queue Queue2内存释放
	for (int i = 0; i < pRuntime->maxBus + 1; i++)
	{
		delete[]Queue[i];
	}
	delete[]Queue;
	delete[]Queue2;

	//节点的净功率注入
	for (int i = 0; i < pRuntime->maxBus; i++)
	{
		delete[]NodePowerP[i];
		delete[]NodePowerQ[i];
	}
	delete[]NodePowerP;
	delete[]NodePowerQ;
	NodePowerP = NULL;
	NodePowerQ = NULL;

	for (int i = 0; i < pRuntime->maxBus; i++)
	{
		delete[]NodePowerP_iter[i];
		delete[]NodePowerQ_iter[i];
	}
	delete[]NodePowerP_iter;
	delete[]NodePowerQ_iter;
	NodePowerP_iter = NULL;
	NodePowerQ_iter = NULL;

	// 线路功率
	for (int i = 0; i < pRuntime->maxBus; i++)
	{
		delete[]NodeVoltAmp[i];
	}
	delete[]NodeVoltAmp;
	NodeVoltAmp = NULL;

	//节点电压的幅值
	for (int i = 0; i < pRuntime->maxLine; i++)
	{
		delete[]LineP[i];
		delete[]LineQ[i];
		delete[]LinePloss[i];
		delete[]LineQloss[i];
		delete[]LineI[i];
	}
	delete[]LineP;
	delete[]LineQ;
	delete[]LinePloss;
	delete[]LineQloss;
	delete[]LineI;
	LineP = NULL;
	LineQ = NULL;
	LinePloss = NULL;
	LineQloss = NULL;
	LineI = NULL;

	if (numOptmz != 0)
	{
		delete[]ObjmatPLoss;
		delete[]ObjmatVDev;
		delete[]ObjmatIcay;
		delete[]Objmat;
		ObjmatPLoss = NULL;
		ObjmatVDev = NULL;
		ObjmatIcay = NULL;
		Objmat = NULL;
	}

}