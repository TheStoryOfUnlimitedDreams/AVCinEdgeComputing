
#if _MSC_VER > 1000
#pragma once
#endif

#if !defined(AFX__DPARFILE_H__B8F05F04_23A9_4020_B88F_ED1C66C40632__INCLUDED_)
#define AFX__PARFILE_H__B8F05F04_23A9_4020_B88F_ED1C66C40632__INCLUDED_

#include "string.h"
#include "stdio.h"  
#include "stdlib.h"
#include "../include/Sys_file.h"

#define  max(a,b)    ((a)>(b) ? (a):(b))
#define  min(a,b)    ((a)<(b) ? (a):(b))

class C_ParFile  
{
public:
	C_ParFile();         //构造函数声明
	virtual ~C_ParFile();//析构函数声明

	int  GetParFileName();
	void GetInfor();
	
	CReadFile *pFcase;
	CReadFile *pFcontr;
	CReadFile *pFcurve;
	FILE *FileCtrl;//使用fscanf函数读取Control文件数据 

	char CaseFileName[1000];
	char ControlFileName[1000];
	char CurveFileName[1000];

private:
	int  GetCtrlFileParInfor();

	int  GetCaseFileElementCnt();
	int  GetCaseFileMemoryAllt();
	int  GetCaseFileParInfor();

	int  GetCurveFileElementCnt();
	int  GetCurveFileMemoryAllt();
	int  GetCurveFileParInfor();
	
	int Id_Bus_R;

	double V_R;
	int Symb_R;

	int ACDC_R;

	int DGPosSym_R;
	int DGPosCurve_R;		
	double DGPosCap_R;	
	int ESSPosSym_R;		
	double ESSPosIvtCap_R;
	double ESSPosBtyCap_R;

	int Id_Line_R;
	int BegNod_R;
	int EndNod_R;
	int State_R;
	double R_R;
	double X_R;
	double Imax_R;

	int Id_Load_R;
	int ConNod_Load_R;
	double PLoad_R;
	double QLoad_R;
	int Curve_Load_R;

	int Id_DG_R;
	int ConNod_DG_R;
	double Porg_R;
	double Qorg_R;
	double Pmin_R;
	double Pmax_R;
	double Qmin_R;
	double Qmax_R;
	double Smax_R;
	double Pf_R;
	int Type_DG_R;
	int Curve_DG_R;
	int TakePart_R;

	int Id_Sto_R;
	int ConNod_Sto_R;
	double Emin_R;
	double Emax_R;
	double E0_R;



	int Id_Switch_R;

	int Id_PWM_R;
	int Mode_R;
	double LossFactor_R;
	double Modulation_R;

	int Id_SOP_R;                    
	int NodSop_R;
		   
                
	int Id_Curve_R;
	int Tpot_R;

};

#endif