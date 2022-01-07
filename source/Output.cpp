#include "math.h"

#include "..\include\GlobalVariables.h"
#include "..\include\ParType.h"
#include "..\include\Output.h"

COutput::COutput()
{
};
COutput::~COutput()
{
};

void COutput::WriteTitle()
{
	fprintf(pFVoltage, "%9s%9s%21s\n", "Tpot", "Id", "V(p.u.)");
	if (pControl->Optimize == 0) fprintf(pFVoltage, "%s\n", "BEGIN V");
	if (pControl->Optimize == 1) fprintf(pFVoltage, "%s\n", "BEGIN V1");

	fprintf(pFLineData, "%9s%9s%9s%9s%21s%21s%21s%21s\n", "Tpot", "Id", "BegNod", "EndNod", "P(kW)", "Q(kvar)", "PLoss(kW)", "I(A)");
	if (pControl->Optimize == 0) fprintf(pFLineData, "%s\n", "BEGIN LineData");
	if (pControl->Optimize == 1) fprintf(pFLineData, "%s\n", "BEGIN LineData1");

	fprintf(pFDistGen, "%9s%9s%9s%9s%21s%21s%21s%21s\n", "Tpot", "Id", "Type", "ConNod", "P(kW)", "Q(kvar)", "Vlow(p.u.)", "Vup(p.u.)");
	if (pControl->Optimize == 0) fprintf(pFDistGen, "%s\n", "BEGIN DG");
	if (pControl->Optimize == 1) fprintf(pFDistGen, "%s\n", "BEGIN DG1");

	fprintf(pFSOP, "%9s%9s%9s%9s%21s%21s%21s%21s\n", "Tpot", "Id", "Type", "ConNod", "P(kW)", "Q(kvar)", "Vlow(p.u.)", "Vup(p.u.)");
	if (pControl->Optimize == 0) fprintf(pFSOP, "%s\n", "BEGIN SOP");
	if (pControl->Optimize == 1) fprintf(pFSOP, "%s\n", "BEGIN SOP1");

	fprintf(pFObject, "%9s%21s%21s%21s%21s\n", "Tpot", "Loss(kWh)", "maxV(p.u.)", "minV(p.u.)", "maxIcay(%)");
	if (pControl->Optimize == 0) fprintf(pFObject, "%s\n", "BEGIN Obj");
	if (pControl->Optimize == 1) fprintf(pFObject, "%s\n", "BEGIN Obj1");

	if (pControl->Optimize == 0) fprintf(pFSumInfo, "%s\n", "BEGIN SumInfo");
	if (pControl->Optimize == 1) fprintf(pFSumInfo, "%s\n", "BEGIN SumInfo1");
}

void COutput::WriteEnd()
{
	fprintf(pFVoltage, "%s", "END");
	fprintf(pFLineData, "%s", "END");
	fprintf(pFDistGen, "%s", "END");
	fprintf(pFSOP, "%s", "END");
	fprintf(pFObject, "%s", "END");
	fprintf(pFSumInfo, "%s", "END");
}

void COutput::WriteResult()
{
	PrintVoltage();
	PrintLineData();
	PrintDistGen();
	PrintSOP();
	PrintObject();
	PrintSumInfo();
}

void COutput::InitialStateGetFileOpen()
{
	strcpy(comment, comment_store);
	strcat(comment, "/output/V.out");
	if ((pFVoltage = fopen(comment, "w")) == NULL)
	{
		printf("\nCannot open Voltage data file");
		exit(1);
	}

	strcpy(comment, comment_store);
	strcat(comment, "/output/LineData.out");
	if ((pFLineData = fopen(comment, "w")) == NULL)
	{
		printf("\nCannot open LinePower data file");
		exit(1);
	}

	strcpy(comment, comment_store);
	strcat(comment, "/output/DG.out");
	if ((pFDistGen = fopen(comment, "w")) == NULL)
	{
		printf("\nCannot open DistGen data file");
		exit(1);
	}

	strcpy(comment, comment_store);
	strcat(comment, "/output/SOP.out");
	if ((pFSOP = fopen(comment, "w")) == NULL)
	{
		printf("\nCannot open SOP data file");
		exit(1);
	}

	strcpy(comment, comment_store);
	strcat(comment, "/output/Obj.out");
	if ((pFObject = fopen(comment, "w")) == NULL)
	{
		printf("\nCannot open Object data file");
		exit(1);
	}

	strcpy(comment, comment_store);
	strcat(comment, "/output/SumInfo.out");
	if ((pFSumInfo = fopen(comment, "w")) == NULL)
	{
		printf("\nCannot open SumInfo data file");
		exit(1);
	}

}

void COutput::OptimizedStateGetFileOpen()
{
	strcpy(comment, comment_store);
	strcat(comment, "/output/V1.out");
	if ((pFVoltage = fopen(comment, "w")) == NULL)
	{
		printf("\nCannot open Voltage data file");
		exit(1);
	}

	strcpy(comment, comment_store);
	strcat(comment, "/output/LineData1.out");
	if ((pFLineData = fopen(comment, "w")) == NULL)
	{
		printf("\nCannot open LinePower data file");
		exit(1);
	}

	strcpy(comment, comment_store);
	strcat(comment, "/output/DG1.out");
	if ((pFDistGen = fopen(comment, "w")) == NULL)
	{
		printf("\nCannot open DistGen data file");
		exit(1);
	}

	strcpy(comment, comment_store);
	strcat(comment, "/output/SOP1.out");
	if ((pFSOP = fopen(comment, "w")) == NULL)
	{
		printf("\nCannot open SOP data file");
		exit(1);
	}

	strcpy(comment, comment_store);
	strcat(comment, "/output/Obj1.out");
	if ((pFObject = fopen(comment, "w")) == NULL)
	{
		printf("\nCannot open Object data file");
		exit(1);
	}

	strcpy(comment, comment_store);
	strcat(comment, "/output/SumInfo1.out");
	if ((pFSumInfo = fopen(comment, "w")) == NULL)
	{
		printf("\nCannot open SumInfo data file");
		exit(1);
	}

}

void COutput::PrintVoltage()
{
	for (int h = 0; h < pRuntime->Hth; h++)
	{
		for (int i = 0; i < pRuntime->maxBus; i++)
		{

			fprintf(pFVoltage, " %8d", h + 1);
			fprintf(pFVoltage, " %8d", VoltData[i][h].Id_Bus);

			if (pControl->Optimize == 0)
				fprintf(pFVoltage, " %20.5lf", VoltData[i][h].V0);
			if (pControl->Optimize == 1)
				fprintf(pFVoltage, " %20.5lf", VoltData[i][h].V);

			fprintf(pFVoltage, "\n");
		}
		fprintf(pFVoltage, "\n");
	}
}

void COutput::PrintLineData()
{
	for (int h = 0; h < pRuntime->Hth; h++)
	{
		for (int i = 0; i < pRuntime->maxLine; i++)
		{
			fprintf(pFLineData, " %8d", h + 1);
			fprintf(pFLineData, " %8d\t%8d\t%8d", LineData[i][h].Id_Line, LineData[i][h].BegNod, LineData[i][h].EndNod);

			if (pControl->Optimize == 0)
				fprintf(pFLineData, " %20.5lf\t%20.5lf\t%20.5lf\t%20.5lf",
					pControl->BaseVe * LineData[i][h].P0, pControl->BaseVe * LineData[i][h].Q0,
					pControl->BaseVe * LineData[i][h].PLoss0,
					LineData[i][h].I0);

			if (pControl->Optimize == 1)
				fprintf(pFLineData, " %20.5lf\t%20.5lf\t%20.5lf\t%20.5lf",
					pControl->BaseVe * LineData[i][h].P, pControl->BaseVe * LineData[i][h].Q,
					pControl->BaseVe * LineData[i][h].PLoss,
					LineData[i][h].I);


			fprintf(pFLineData, "\n");
		}
		fprintf(pFLineData, "\n");
	}
}

void COutput::PrintDistGen()
{

	for (int h = 0; h < pRuntime->Hth; h++)
	{
		for (int i = 0; i < pRuntime->maxDG; i++)
		{
			fprintf(pFDistGen, " %8d", h + 1);
			fprintf(pFDistGen, " %8d", DGData[i][h].Id_DG);

			if (pDG[i].Type_DG == 1)
			{
				fprintf(pFDistGen, " %8s", "PV");
			}
			if (pDG[i].Type_DG == 2)
			{
				fprintf(pFDistGen, " %8s", "WT");
			}

			fprintf(pFDistGen, " %8d", DGData[i][h].ConNod_DG);

			if (pControl->Optimize == 0)
			{
				fprintf(pFDistGen, " %20.5lf %20.5lf", DGData[i][h].P0, DGData[i][h].Q0);
				fprintf(pFDistGen, "                      /                        /");
			}

			if (pControl->Optimize == 1)
			{
				fprintf(pFDistGen, " %20.5lf %20.5lf", DGData[i][h].P, DGData[i][h].Q);

				if (pDG[i].TakePart == 1)
				{
					fprintf(pFDistGen, " %20.5lf %20.5lf", DGData[i][h].Vlow, DGData[i][h].Vup);
				}
				if (pDG[i].TakePart == 0)
				{
					fprintf(pFDistGen, "                      /                        /");
				}

			}

			fprintf(pFDistGen, "\n");
		}
	}
}

void COutput::PrintSOP()
{
	for (int h = 0; h < pRuntime->Hth; h++)
	{
		for (int i = 0; i < pRuntime->maxSOP; i++)
		{
			fprintf(pFSOP, " %8d", h + 1);
			fprintf(pFSOP, " %8d", SOPData[i][h].Id_SOP);

			fprintf(pFSOP, " %8d", SOPData[i][h].ConNod_SOP);

			if (pControl->Optimize == 0)
			{
				fprintf(pFSOP, " %20.5lf %20.5lf", SOPData[i][h].P0, SOPData[i][h].Q0);
				fprintf(pFSOP, "                      /                        /");
			}

			if (pControl->Optimize == 1)
			{
				fprintf(pFSOP, " %20.5lf %20.5lf", SOPData[i][h].P, SOPData[i][h].Q);

				if (pSOP[i].TakePart == 1)
				{
					fprintf(pFSOP, " %20.5lf %20.5lf", SOPData[i][h].Vlow, SOPData[i][h].Vup);
				}
				if (pSOP[i].TakePart == 0)
				{
					fprintf(pFSOP, "                      /                        /");
				}
			}
			fprintf(pFSOP, "\n");
		}
	}
}

void COutput::PrintObject()
{
	for (int h = 0; h < pRuntime->Hth; h++)
	{
		fprintf(pFObject, " %8d", h + 1);

		if (pControl->Optimize == 0)
		{
			fprintf(pFObject, " %20.5lf", pControl->BaseVe * Obj[h].ObjmatPLoss0);
			fprintf(pFObject, " %20.5lf", Obj[h].maxV0);
			fprintf(pFObject, " %20.5lf", Obj[h].minV0);
			fprintf(pFObject, " %20.5lf", Obj[h].maxIcay0);
		}

		if (pControl->Optimize == 1)
		{
			fprintf(pFObject, " %20.5lf", pControl->BaseVe * Obj[h].ObjmatPLoss);
			fprintf(pFObject, " %20.5lf", Obj[h].maxV);
			fprintf(pFObject, " %20.5lf", Obj[h].minV);
			fprintf(pFObject, " %20.5lf", Obj[h].maxIcay);
		}
		fprintf(pFObject, "\n");
	}
}

void COutput::PrintSumInfo()
{
	double Slos = 0;		//系统总损耗
	double Sauxmax = 0;		//系统总电压偏差
	double Scaymax = 0;		//系统总负载均衡
	double maxIcay = 0;		//用于描述最大负载均衡指标
	double maxV = 0;		//用于描述最大节点电压
	double minV = 1;		//用于描述最小节点电压

	for (int h = 0; h < pRuntime->Hth; h++)
	{
		if (pControl->Optimize == 0)
		{
			Slos = Slos + pControl->BaseVe * Obj[h].ObjmatPLoss0;
			Sauxmax = Sauxmax + Obj[h].ObjmatVDev0;
			Scaymax = Sauxmax + Obj[h].ObjmatIcay0;

			if (maxV < Obj[h].maxV0)
				maxV = Obj[h].maxV0;
			if (minV > Obj[h].minV0)
				minV = Obj[h].minV0;
			if (maxIcay < Obj[h].maxIcay0)
				maxIcay = Obj[h].maxIcay0;

		}

		if (pControl->Optimize == 1)
		{
			Slos = Slos + pControl->BaseVe * Obj[h].ObjmatPLoss;
			Sauxmax = Sauxmax + Obj[h].ObjmatVDev;
			Scaymax = Sauxmax + Obj[h].ObjmatIcay;

			if (maxV < Obj[h].maxV)
				maxV = Obj[h].maxV;
			if (minV > Obj[h].minV)
				minV = Obj[h].minV;
			if (maxIcay < Obj[h].maxIcay)
				maxIcay = Obj[h].maxIcay;
		}
	}

	fprintf(pFSumInfo, " %-10s %20.5lf", "Slos(kWh)", Slos);
	fprintf(pFSumInfo, "\n");
	fprintf(pFSumInfo, " %-10s %20.5lf", "maxV(p.u.)", maxV);
	fprintf(pFSumInfo, "\n");
	fprintf(pFSumInfo, " %-10s %20.5lf", "minV(p.u.)", minV);
	fprintf(pFSumInfo, "\n");
	fprintf(pFSumInfo, " %-10s %20.5lf", "maxIcay(p.u.)", maxIcay);
	fprintf(pFSumInfo, "\n");

}

void COutput::CloseFile()
{
	fflush(pFVoltage);
	fflush(pFLineData);
	fflush(pFDistGen);
	fflush(pFSOP);
	fflush(pFObject);
	fflush(pFSumInfo);

	fclose(pFVoltage);
	fclose(pFLineData);
	fclose(pFDistGen);
	fclose(pFSOP);
	fclose(pFObject);
	fclose(pFSumInfo);
}