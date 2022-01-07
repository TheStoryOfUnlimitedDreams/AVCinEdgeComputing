
#include "math.h"
#include "../include/Sys_file.h"
#include "../include/GlobalVariables.h"
#include "../include/ParFile.h"
#include "../include/ParType.h"


C_ParFile::C_ParFile()//���캯������
{
	GetParFileName();//����GetParFileName()
}
C_ParFile::~C_ParFile()//������������
{
}

int C_ParFile::GetParFileName()
{
	strcpy(comment, comment_store);
	strcat(comment, "/data/Case");
	strcpy(CaseFileName, comment);
	//strcpy(CaseFileName, "../data/Case");

	strcpy(comment,comment_store);
	strcat(comment,"/data/Control");
	strcpy(ControlFileName, comment);
	//strcpy(CaseFileName, "../data/Control");

	strcpy(comment,comment_store);
	strcat(comment,"/data/Curve");
	strcpy(CurveFileName, comment);
	//strcpy(CaseFileName, "../data/Curve");

	return 1;
}

void C_ParFile::GetInfor()
{	
	pFcontr = new CReadFile(ControlFileName);
    pFcase  = new CReadFile(CaseFileName);
	pFcurve = new CReadFile(CurveFileName);

 	if ((FileCtrl = fopen(ControlFileName, "r")) == NULL)
 	printf("Cannot open optimization control file");
 
	pControl = new CContrData;
	pRuntime = new CRunData;
	
	pControl->BaseVe        = 100;
	pControl->BaseV         = 12.66;
	pControl->Step          = 1.0;
	pControl->Npoint        = 1;
	pControl->Vu            = 1.1;
	pControl->Vb            = 0.9;
	pControl->Vqu           = 1.01;
	pControl->Vqb           = 0.99;         
  


      
	pControl->WeightA       = 1.0;     
	pControl->WeightB       = 1.0;     
	pControl->WeightC       = 1.0;     
     

        
	pControl->Optimize      = 0;       
 
     
	pControl->MaxPre        = 1e-5;      
     


    pControl->EnablePV      = 0;
    pControl->EnableWT      = 0;
    pControl->EnableSto     = 0;
    pControl->EnableCapBank = 0;

    pControl->EnableSwitch  = 0;


	pRuntime->nCurve        = 0;
	pRuntime->nBus          = 0;

	pRuntime->nBa           = 0;
	pRuntime->nLine         = 0;

	pRuntime->nLoad         = 0;
	pRuntime->nPV           = 0;
	pRuntime->nWT           = 0;
	pRuntime->nDG           = 0;


	pRuntime->nSwitch       = 0;

	pRuntime->nSOP          = 0;

	pRuntime->maxCurve      = 0;
	pRuntime->maxBus        = 0;
	pRuntime->maxACBus      = 0;

	pRuntime->maxBa         = 0;
	pRuntime->maxLine       = 0;
	pRuntime->maxACLine     = 0;

	pRuntime->maxLoad       = 0;
	pRuntime->maxPV         = 0;
	pRuntime->maxWT         = 0;
	pRuntime->maxDG         = 0;

	pRuntime->maxSwitch     = 0;
	pRuntime->maxSOP        = 0;

	pRuntime->Hth           = 0;

	pRuntime->GapIter       = 0;
	pRuntime->GapPre        = 1.0;

	if(GetCtrlFileParInfor() == 0)    //��ȡControl�ļ��п�����Ϣ
	{
		Message("Get Control File parameter infor defeated.","error_Sys_ParFile:");
		fprintf(erroLog,"����[Input]���޷��򿪿��Ʋ��������ļ�Control���ж�ȡ.\n");  //TidyErrLog
		exit(0);//���������˳�
	}
	if(GetCaseFileElementCnt() == 0)  //��Case�ļ���Ԫ������
	{
		Message("Get Case File parameter infor defeated.","error_Sys_ParFile:");
		fprintf(erroLog,"����[Input]���޷���Ԫ�����������ļ�Case���ж�ȡ.\n");  //TidyErrLog
		exit(0);
	}
	if(GetCaseFileMemoryAllt() == 0) //��Case�ļ���Ԫ�������ڴ�
	{
		Message("Get Case File parameter infor defeated.","error_Sys_ParFile:");
		fprintf(erroLog,"����[Input]���޷���Ԫ�����������ļ�Case���ж�ȡ.\n");  //TidyErrLog
		exit(0);
	}
	if(GetCaseFileParInfor() == 0)   //��ȡCase�ļ���Ԫ������
	{
		Message("Get Case File parameter infor defeated.","error_Sys_ParFile:");
		fprintf(erroLog,"����[Input]���޷���Ԫ�����������ļ�Case���ж�ȡ.\n");  //TidyErrLog
		exit(0);
	}
	if(GetCurveFileElementCnt() == 0)//��Curve�ļ�������ʱ��ֵ����
	{
		Message("Get Curve File parameter infor defeated.","error_Sys_ParFile:");
		fprintf(erroLog,"����[Input]���޷���ʱ����������ļ�Curve���ж�ȡ.\n");  //TidyErrLog
		exit(0);
	}
	if(GetCurveFileMemoryAllt() == 0) //��Curve�ļ������߷����ڴ�
	{
		Message("Get Curve File parameter infor defeated.","error_Sys_ParFile:");
		fprintf(erroLog,"����[Input]���޷���ʱ����������ļ�Curve���ж�ȡ.\n");  //TidyErrLog
		exit(0);
	}
	if(GetCurveFileParInfor() == 0)  //��ȡCurve�ļ�������ʱ��ֵ
	{
		Message("Get Curve File parameter infor defeated.","error_Sys_ParFile:");
		fprintf(erroLog,"����[Input]���޷���ʱ����������ļ�Curve���ж�ȡ.\n");  //TidyErrLog
		exit(0);
	}
}

int C_ParFile::GetCtrlFileParInfor()
{
	/*��ȡControl�ļ�*/
	pFcontr->GoBegin();//ʹ��fscanf���� ����ҪEND��������Ϊֹͣ�����ı�־
	fscanf(FileCtrl,"%s%lf%lf%lf%d%lf%lf%lf%lf%lf%s%lf%d%d%lf",
		&pControl->CaseName,
		&pControl->BaseVe,
		&pControl->BaseV,
		&pControl->Step,
		&pControl->Npoint,
		&pControl->Vu,
		&pControl->Vb,
		&pControl->WeightA,
		&pControl->WeightB,
		&pControl->WeightC,
		&pControl->Devise,
		&pControl->MaxPre,
		&pControl->Cloud,
		&pControl->Solver,
		&pControl->InitialV);


	if(pControl->Devise[0] == '1') pControl->EnablePV       = 1;
	if(pControl->Devise[1] == '1') pControl->EnableWT       = 1;
	if(pControl->Devise[2] == '1') pControl->EnableCapBank  = 1;

	pControl->PSOPintvl = 200;//SOP�й��Ż�����������û�����

	return 1;
}

int C_ParFile::GetCaseFileElementCnt()
{
	/*��ȡCase�ļ�*/
	/*���ȶ�ȡ��Ԫ����ĳ��� Ϊ����ľ��󿪱���Ӧ��С���ڴ�ռ�*/
	int DataRead = 0;

	pFcase->GoBegin();
	pFcase->FGetLine();
	while (pFcase->ms_Str[0] != 'E') //����ע����
	{
		pFcase->FGetLine();
	}

	//��������ĸ��
	pFcase->FGetLine();
	while (pFcase->ms_Str[0] != 'E')
	{
		DataRead = sscanf(pFcase->ms_Str, "%d%lf%d%d%d%lf%d%lf%lf", 
			&Id_Bus_R, &V_R, &Symb_R,								
			&DGPosSym_R, &DGPosCurve_R, &DGPosCap_R,
			&ESSPosSym_R, &ESSPosIvtCap_R, &ESSPosBtyCap_R);
		if (Symb_R == 1)
		{
			pRuntime->maxBa++;//����ƽ��ڵ�
		}
		pRuntime->maxACBus++;
		pFcase->FGetLine();
	}
	if (pRuntime->maxBa == 0)
	{
		fprintf(erroLog, "����[Case]������ϵͳ��ȱ���ⲿ����.\n"); //TidyErrLog
	}

	//����������·
		pFcase->FGetLine();
		while (pFcase->ms_Str[0] != 'E')
		{
			DataRead = sscanf(pFcase->ms_Str, "%d%d%d%d%lf%lf%lf",
				&Id_Line_R, &BegNod_R, &EndNod_R, &State_R, &R_R, &X_R, &Imax_R);
			if (State_R == 1)
			{
				pRuntime->maxACLine++;
			}
			pFcase->FGetLine();
		}


		//��������
		pFcase->FGetLine();
		while (pFcase->ms_Str[0] != 'E')
		{
			pRuntime->maxLoad++;
			pFcase->FGetLine();
		}

		//�����ֲ�ʽ��Դ
		pFcase->FGetLine();
		while (pFcase->ms_Str[0] != 'E')
		{
			DataRead = sscanf(pFcase->ms_Str, "%d%d%lf%lf%lf%lf%lf%lf%lf%lf%d%d%d",
				&Id_DG_R, &ConNod_DG_R, &Porg_R, &Qorg_R,
				&Pmin_R, &Pmax_R, &Qmin_R, &Qmax_R, &Smax_R, &Pf_R,
				&Type_DG_R, &Curve_DG_R, &TakePart_R);

			if (Type_DG_R == 1)//�������
			{
				pRuntime->maxPV++;
			}
			if (Type_DG_R == 2)//�������
			{
				pRuntime->maxWT++;
			}

			pRuntime->maxDG++;//NDG=NPV+NWind
			pFcase->FGetLine();
		}



		//�������翪��
		pFcase->FGetLine();
		while (pFcase->ms_Str[0] != 'E')
		{
			DataRead = sscanf(pFcase->ms_Str, "%d%d%d%lf%lf%lf%d%d",
				&Id_Switch_R, &BegNod_R, &EndNod_R, &R_R, &X_R, &Imax_R, &State_R, &TakePart_R);
			if (State_R == 1)
			{
				pRuntime->maxSwitch++;
			}
			pFcase->FGetLine();
		}


		//������������
		pFcase->FGetLine();
		while (pFcase->ms_Str[0] != 'E')
		{
			pRuntime->maxSOP++;
			pFcase->FGetLine();
		}

		pRuntime->maxBus = pRuntime->maxACBus;    //������ʵĸ�ߺ͵�Чĸ��֮��
		pRuntime->maxLine = pRuntime->maxACLine //������ʵ��·�͵�Ч��·֮��
			+ pRuntime->maxSwitch;

		if (pControl->EnablePV == 1 && pRuntime->maxPV == 0)
		{
			//fprintf(erroLog,"DSIM_ERRO_DEV_01: There is none PhotoVoltaic exists in this electrial net.\n");  //TidyErrLog
			fprintf(erroLog, "����[Case]������ϵͳ�в����ڹ�����޷���Ϊ���ڷ�ʽ.\n");
		}
		if (pControl->EnableWT == 1 && pRuntime->maxWT == 0)
		{
			//fprintf(erroLog,"DSIM_ERRO_DEV_02: There is none WindTurbine exists in this electrial net.\n");
			fprintf(erroLog, "����[Case]������ϵͳ�в����ڷ�����޷���Ϊ���ڷ�ʽ.\n");
		}

		if (pControl->EnableSwitch == 1 && pRuntime->maxSwitch == 0)
		{
			//fprintf(erroLog,"DSIM_ERRO_DEV_07: There is none TieSwitch exists in this electrial net.\n");
			fprintf(erroLog, "����[Case]������ϵͳ�в��������翪�أ��޷���Ϊ���ڷ�ʽ.\n");
		}
		if (pControl->EnableSOP == 1 && pRuntime->maxSOP == 0)
		{
			//fprintf(erroLog,"DSIM_ERRO_DEV_09: There is none SoftOpenPoint exists in this electrial net.\n");
			fprintf(erroLog, "����[Case]������ϵͳ�в������������أ��޷���Ϊ���ڷ�ʽ.\n");
		}

		return 1;
	};

int C_ParFile::GetCaseFileMemoryAllt()
{
    pBus       = new CBusData       [pRuntime->maxBus];    
    pLine      = new CLineData      [pRuntime->maxLine];
	pLoad      = new CLoadData      [pRuntime->maxLoad]; 
    pDG        = new CDGData        [pRuntime->maxDG];     

    pSwitch    = new CSwitchData    [pRuntime->maxSwitch]; 
	pSOP       = new CSOPData       [pRuntime->maxSOP];

	return 1;
}

int C_ParFile::GetCaseFileParInfor()
{
	int DataRead  = 0;
	int IdBusmax  = 0;
	int IdLinemax = 0;

	pFcase->GoBegin();
	pFcase->FGetLine();
    while (pFcase->ms_Str[0] != 'E') //����ע����
	{
		pFcase->FGetLine();
    }

	//¼�뽻��ĸ��
	pFcase->FGetLine();
	while (pFcase->ms_Str[0] != 'E') 
	{
		DataRead = sscanf(pFcase->ms_Str, "%d%lf%d",
			&Id_Bus_R, &V_R, &Symb_R);						

		pBus[pRuntime->nBus].Id_Bus = Id_Bus_R;
		pBus[pRuntime->nBus].P = 0.0; 
		pBus[pRuntime->nBus].Q = 0.0; 
		pBus[pRuntime->nBus].V = V_R;
		pBus[pRuntime->nBus].Symb = Symb_R;
		pBus[pRuntime->nBus].ACDC = 1;//ACBus
		pBus[pRuntime->nBus].Curve_Load = 0; 



		//��¼ĸ������� Ϊ��Чĸ�߱�Ÿ�ֵʹ��
		if(Id_Bus_R >= IdBusmax)
		{
			IdBusmax = Id_Bus_R;
		}

		pRuntime->nBus++;
		pFcase->FGetLine();
	}

	//¼�뽻����·
	pFcase->FGetLine();
	while (pFcase->ms_Str[0] != 'E') 
	{
		DataRead = sscanf(pFcase->ms_Str, "%d%d%d%d%lf%lf%lf%d",
			&Id_Line_R, &BegNod_R, &EndNod_R, &State_R, &R_R, &X_R, &Imax_R, &TakePart_R);
		if(State_R == 1) 
		{
			pLine[pRuntime->nLine].Id_Line = Id_Line_R;
			pLine[pRuntime->nLine].BegNod = BegNod_R;
			pLine[pRuntime->nLine].EndNod = EndNod_R;
			pLine[pRuntime->nLine].State = State_R;
			pLine[pRuntime->nLine].ACDC = 1;//ACline
			strcpy(pLine[pRuntime->nLine].Type_Line, "L");
			pLine[pRuntime->nLine].R = R_R;
			pLine[pRuntime->nLine].X = X_R;
			pLine[pRuntime->nLine].Imax = Imax_R;
			pLine[pRuntime->nLine].TakePart = TakePart_R;

			for(int i=0; i<pRuntime->maxBus; i++)
			{
				if(pLine[pRuntime->nLine].BegNod == pBus[i].Id_Bus)
				{
					pLine[pRuntime->nLine].BVt = pBus[i].V;
				}
				if(pLine[pRuntime->nLine].EndNod == pBus[i].Id_Bus)
				{
					pLine[pRuntime->nLine].EVt = pBus[i].V;
				}
			}

			pRuntime->nLine++;
		}

		//��¼��·����� Ϊ��Ч��·��Ÿ�ֵʹ��
		if(Id_Line_R >= IdLinemax)
		{
			IdLinemax = Id_Line_R;
		}

		pFcase->FGetLine();
	}


	//¼�븺��
	pFcase->FGetLine();
	while (pFcase->ms_Str[0] != 'E') 
	{
		DataRead = sscanf(pFcase->ms_Str, "%d%d%d%lf%lf%d",
			&Id_Load_R, &ConNod_Load_R, &ACDC_R, &PLoad_R, &QLoad_R, &Curve_Load_R);

		pLoad[pRuntime->nLoad].Id_Load = Id_Load_R;
		pLoad[pRuntime->nLoad].ConNod_Load = ConNod_Load_R;
		pLoad[pRuntime->nLoad].ACDC = ACDC_R;
		pLoad[pRuntime->nLoad].PLoad = PLoad_R;
		pLoad[pRuntime->nLoad].QLoad = QLoad_R;
		pLoad[pRuntime->nLoad].Curve_Load = Curve_Load_R;

		pRuntime->nLoad++;
		pFcase->FGetLine();
	}

	//¼��ֲ�ʽ��Դ
	pFcase->FGetLine();
	while (pFcase->ms_Str[0] != 'E') 
	{
		DataRead = sscanf(pFcase->ms_Str, "%d%d%lf%lf%lf%lf%lf%lf%lf%lf%d%d%d",
			&Id_DG_R, &ConNod_DG_R, &Porg_R, &Qorg_R,
			&Pmin_R, &Pmax_R, &Qmin_R, &Qmax_R, &Smax_R, &Pf_R,
			&Type_DG_R, &Curve_DG_R, &TakePart_R);

		pDG[pRuntime->nDG].Id_DG = Id_DG_R;
		pDG[pRuntime->nDG].ConNod_DG = ConNod_DG_R;
		pDG[pRuntime->nDG].Porg = Porg_R;
		pDG[pRuntime->nDG].Qorg = Qorg_R;
		pDG[pRuntime->nDG].Pmin = Pmin_R;
		pDG[pRuntime->nDG].Pmax = Pmax_R;
		pDG[pRuntime->nDG].Qmin = Qmin_R;
		pDG[pRuntime->nDG].Qmax = Qmax_R;
		pDG[pRuntime->nDG].Smax = Smax_R;
		pDG[pRuntime->nDG].Pf = Pf_R;
		pDG[pRuntime->nDG].Type_DG = Type_DG_R;
		pDG[pRuntime->nDG].Curve_DG = Curve_DG_R;
		pDG[pRuntime->nDG].TakePart = TakePart_R;

		pRuntime->nDG++;
		pFcase->FGetLine();
	}

	//¼�����翪��
	pFcase->FGetLine();
	while (pFcase->ms_Str[0] != 'E')
	{
		DataRead = sscanf(pFcase->ms_Str, "%d%d%d%lf%lf%lf%d%d",
			&Id_Switch_R, &BegNod_R, &EndNod_R, &R_R, &X_R, &Imax_R, &State_R, &TakePart_R);
		if(State_R == 1)
		{
			pSwitch[pRuntime->nSwitch].Id_Switch = Id_Switch_R;
			pSwitch[pRuntime->nSwitch].FakeId = ++IdLinemax;
			pSwitch[pRuntime->nSwitch].BegNod = BegNod_R;
			pSwitch[pRuntime->nSwitch].EndNod = EndNod_R;
			pSwitch[pRuntime->nSwitch].R = R_R;
			pSwitch[pRuntime->nSwitch].X = X_R;
			pSwitch[pRuntime->nSwitch].Imax = Imax_R;
			pSwitch[pRuntime->nSwitch].State = State_R;			
			pSwitch[pRuntime->nSwitch].TakePart = TakePart_R;

			for(int i=0; i<pRuntime->maxBus; i++)
			{
				if(pSwitch[pRuntime->nSwitch].BegNod == pBus[i].Id_Bus)
				{
					pSwitch[pRuntime->nSwitch].BVt = pBus[i].V;
				}
				if(pSwitch[pRuntime->nSwitch].EndNod == pBus[i].Id_Bus)
				{
					pSwitch[pRuntime->nSwitch].EVt = pBus[i].V;
				}
			}

			pLine[pRuntime->nLine].Id_Line = pSwitch[pRuntime->nSwitch].FakeId;//��Ч��·���
			pLine[pRuntime->nLine].BegNod = pSwitch[pRuntime->nSwitch].BegNod;
			pLine[pRuntime->nLine].EndNod = pSwitch[pRuntime->nSwitch].EndNod;
			pLine[pRuntime->nLine].State = State_R;
			pLine[pRuntime->nLine].ACDC = 1;//ACline
			strcpy(pLine[pRuntime->nLine].Type_Line, "S");
			pLine[pRuntime->nLine].R = R_R;
			pLine[pRuntime->nLine].X = X_R;
			pLine[pRuntime->nLine].Imax = Imax_R;
			pLine[pRuntime->nLine].TakePart = 0;
		    pLine[pRuntime->nLine].BVt = pSwitch[pRuntime->nSwitch].BVt;
		    pLine[pRuntime->nLine].EVt = pSwitch[pRuntime->nSwitch].BVt;

			pRuntime->nSwitch++;
		    pRuntime->nLine++;
		}		

		pFcase->FGetLine();
	}

	//¼����������
	pFcase->FGetLine();
	while (pFcase->ms_Str[0] != 'E')
	{
		DataRead = sscanf(pFcase->ms_Str, "%d%d%lf%lf%lf%lf%lf%lf%lf%d",
			&Id_SOP_R, &NodSop_R, &Porg_R, &Qorg_R,
			&Pmin_R, &Pmax_R, &Qmin_R, &Qmax_R, &Smax_R,
			&TakePart_R);

		pSOP[pRuntime->nSOP].Id_SOP = Id_SOP_R;
		pSOP[pRuntime->nSOP].ConNod_SOP = NodSop_R;
		pSOP[pRuntime->nSOP].Porg = Porg_R;
		pSOP[pRuntime->nSOP].Qorg = Qorg_R;
		pSOP[pRuntime->nSOP].Pmin = Pmin_R;
		pSOP[pRuntime->nSOP].Pmax = Pmax_R;
		pSOP[pRuntime->nSOP].Qmin = Qmin_R;
		pSOP[pRuntime->nSOP].Qmax = Qmax_R;
		pSOP[pRuntime->nSOP].Smax = Smax_R;
		pSOP[pRuntime->nSOP].TakePart = TakePart_R;

		pRuntime->nSOP++;
		pFcase->FGetLine();
	}

	return 1;
}

int C_ParFile::GetCurveFileElementCnt()
{
	pFcurve->GoBegin();
	pFcase->FGetLine();
	while(pFcurve->ms_Str[0] != 'E')
	{
		pRuntime->maxCurve++;
		pFcurve->FGetLine();
		while(pFcurve->ms_Str[0] != 'C')
		{
			pFcurve->FGetLine();
		}
		pFcurve->FGetLine();
	}
	
	return 1;
}

int C_ParFile::GetCurveFileMemoryAllt()
{
	pCurve = new CCurveData [pRuntime->maxCurve];

	return 1;
}

int C_ParFile::GetCurveFileParInfor()
{
	int DataRead = 0;
	double OneLine[24];

	pFcurve->GoBegin();
	pFcurve->FGetLine();
	while(pFcurve->ms_Str[0] != 'E')
	{
		DataRead=sscanf(pFcurve->ms_Str,"%d%d",&Id_Curve_R, &Tpot_R);

		pCurve[pRuntime->nCurve].Id_Curve = Id_Curve_R;
		pCurve[pRuntime->nCurve].Tpot = Tpot_R;
		//pCurve[pRuntime->nCurve].DGPlanCst = DGPlanCst_R;
		//pCurve[pRuntime->nCurve].DGPlanDvc = DGPlanDvc_R;

		pCurve[pRuntime->nCurve].TimSeq = new double[Tpot_R];//��ʱ�����
		for(int i=0; i<Tpot_R; i++)
		{
			pCurve[pRuntime->nCurve].TimSeq[i] = 0.0;
		}

		int tk = 0;
		pFcurve->FGetLine();
		while(pFcurve->ms_Str[0] != 'C')
		{
			DataRead=sscanf(pFcurve->ms_Str,"%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",
						&OneLine[0],&OneLine[1],&OneLine[2],&OneLine[3],&OneLine[4],&OneLine[5],
						&OneLine[6],&OneLine[7],&OneLine[8],&OneLine[9],&OneLine[10],&OneLine[11],
						&OneLine[12],&OneLine[13],&OneLine[14],&OneLine[15],&OneLine[16],&OneLine[17],
						&OneLine[18],&OneLine[19],&OneLine[20],&OneLine[21],&OneLine[22],&OneLine[23]);

			for(int i=0; i<min(Tpot_R, DataRead); i++)
			{
				pCurve[pRuntime->nCurve].TimSeq[tk*24+i] = OneLine[i];
			}
			pFcurve->FGetLine();
		    tk++;
		}


		pCurve[pRuntime->nCurve].Play = 0;
		for(int i=0; i<pRuntime->maxLoad; i++)
		{
			if(pLoad[i].Curve_Load == Id_Curve_R)
			{
				pCurve[pRuntime->nCurve].Play = 1;
			}
		}
		for(int i=0; i<pRuntime->maxDG; i++)
		{
			if(pDG[i].Curve_DG == Id_Curve_R)
			{
				pCurve[pRuntime->nCurve].Play = 1;
			}
		}

		pRuntime->nCurve++;
		pFcurve->FGetLine();
	}


	return 1;
}