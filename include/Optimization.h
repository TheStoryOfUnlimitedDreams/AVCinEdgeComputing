#if _MSC_VER > 1000
#pragma once
#endif

#if !defined(AFX__DOPTIMIZATION_H__22SF47IDV_LW53K_8UK0T_2M0PB_264YA5C64E__INCLUDED_)
#define AFX__DOPTIMIZATION_H__22SF47IDV_LW53K_8UK0T_2M0PB_264YA5C64E__INCLUDED_

#include "../include/Output.h"

class Optimization
{
public:
	Optimization();
	virtual ~Optimization();

	int OptimizationProc();                        //统领优化过程
	void NodeOrder();                              //节点排序
	void LocalOptimization();                      //就地优化过程
	void CloudOptimization();                      //云端优化过程
	void IterBasedOptimization();                  //基于迭代的优化过程
	void SolverBasedOptimization();                //基于求解器的优化过程
	void GenDeadComb();                            //生成分布式电源死区组合
	void NewMatrix();							   //对优化过程中的矩阵进行内存分配(运算使用和输出使用)
	void ReleaseMatrix();						   //对优化过程中的矩阵内存进行释放(运算使用)

	void BacForSweep();                            //基于前推回代法解潮流
	void TuneCtrlDvcStrategy();							   //遍历整定可控设备的出力策略
	double GetGValue(double U0, double Ulow, double Uup);	  //计算分布式电源的无功出力

private:

	int **Queue;
	int  *Queue2;

	double** DeadZooomCombs;
	double* DeadZooomPoint; //分布式死区组合列表

	//节点的注入功率
	double** NodePowerP;
	double** NodePowerQ;

	//迭代过程中的节点功率
	double** NodePowerP_iter;
	double** NodePowerQ_iter;

	//节点电压
	double** NodeVoltAmp;//幅值

	//线路功率
	double** LineP;		  //线路有功
	double** LineQ;		  //线路无功

	double** LinePloss;		  //线路有功损耗
	double** LineQloss;		  //线路无功损耗

	double** LineI;		  //线路电流
	

	int DeadZoomCombnum ; //用于描述死区组合总数
	int numOptmz;// 用于存储总优化变量数
	int DGnumOptmz;// 用于存储DG优化变量数
	int SOPnumOptmz;// 用于存储SOP优化变量数
	int numOptmzstorg; // 用于存储优化结果的存储位置
	double Vlow;
	double Vup;
	double Qbase;

	double* ObjmatPLoss;  //用于描述网损目标函数
	double* ObjmatVDev;   //用于描述电压偏差目标函数
	double* ObjmatIcay;   //用于描述负载均衡目标函数
	double* Objmat;       //用于描述总目标函数

	COutput *pOutput;

	//FILE* pF ;  //检测使用


};






#endif