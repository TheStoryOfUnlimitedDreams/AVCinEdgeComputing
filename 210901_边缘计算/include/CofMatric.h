#if _MSC_VER > 1000
#pragma once
#endif

#if !defined(AFX__DCOFMATRIC_H__89KD15FR_58KD_43DT_83OM_WQ75C4L20632__INCLUDED_)
#define AFX__DCOFMATRIC_H__89KD15FR_58KD_43DT_83OM_WQ75C4L20632__INCLUDED_

class CMatric
{
public:
	CMatric();
	virtual ~CMatric();



	//void FundamentalMatricMemoryAllt(); //�����������ڴ����
	//void CfftMatricMemoryAllt();        //ϵ�������ڴ����
	//void UpLowMatricMemoryAllt();       //�����޾����ڴ����
	//void ObjMatricMemoryAllt();         //Ŀ�꺯�������ڴ����
	//void IterMatricMemoryAllt();        //������������ڴ����

	//void FundamentalMatricInitial();    //�����������ʼ��
	//void CfftMatricInitial();           //ϵ�������ʼ��
	//void UpLowMatricInitial();          //�����޾����ʼ��
	//void ObjMatricInitial();            //Ŀ�꺯�������ʼ��
	//void IterMatricInitial();           //������������ʼ��

	///////////////////////////////////////////////////////
 //   double *Gline;        //��·�絼
 //   double *Bline;        //��·����
 //   
	///////////////////////////////////////////////////////
 //   double **Pineq;       //�й�Լ��
 //   double **Qineq;       //�޹�Լ��
 //   double **Veq;         //����Լ��
 //   double **Veq2;        //��ѹ����Լ��
 //   double **Veq3;        //��ѹ����Լ��
 //   double **Ieq;         //����Լ��
 //   double **Pfeq;        //�ֲ�ʽ��Դ����Լ��
 //   double **Eeq;         //����ϵͳ����Լ��
	//double **Vxfrm;       //�������ѹ�����˵�ѹԼ��
	//double **Vxfrm2;      //�������ѹ�����ʴ���Լ��
 //   double **Vtrans;      //���ص�ѹ����������wj dj��ʽԼ��
 //   double **Vtrans2;     //���ص�ѹ����������wj dj����ʽԼ��
 //   double **Vtrans3;     //���ص�ѹ�����˵�ѹԼ��
 //   double **Vtrans4;     //���ص�ѹ������Vn Kmn��ʽԼ��
	//double **Vtrans5;     //���ص�ѹ�����ʴ���Լ��
 //   double **Convert;     //���������˵�ѹԼ��
	//double **Softpt;      //���������й����ʴ���Լ�� //20191127
	//double **Softeq;      //����������Ĺ����滻Լ�� //20191127
 //   double **Dcpeq;       //͹��滮Լ�������� ������ѹԼ�� 2XiXj=Yij^2+Zij^2
 //   double **Dcpeq2;      //͹��滮Լ��ƽ���� ������ѹԼ�� 2XiXj=Yij^2+Zij^2
	//double **DcpeqSop;    //͹��滮Լ�������� SOP���Լ��  SopLoss^2=Psop^2+Qsop^2 //20200902
	//double **Dcpeq2Sop;   //͹��滮Լ��ƽ���� SOP���Լ��  SopLoss^2=Psop^2+Qsop^2 //20200902

	///////////////////////////////////////////////////////
 //   double  *Pinc;        //�����й�ˮƽ Hth
	//double  *Qinc;        //�����޹�ˮƽ Hth  
 //   
 //   double  *Iequc;       //��·���������� ������ ��ʱ��

 //   double  *Eeqlc;       //���ܺɵ����������� ��ʱ��
 //   double  *Eequc;       //���ܺɵ����������� ��ʱ��

 //   double  *Vxfrmlc;     //�������ѹ�������������� ������ ��ʱ��

	//double  *Vtrans5lc;   //���ص�ѹ�������������� ������ ��ʱ��
 //
	///////////////////////////////////////////////////////
 //   double  *PDGlx;       //�ֲ�ʽ��Դ�й����� Hth
 //   double  *PDGux;       //�ֲ�ʽ��Դ�й����� Hth
 //   double  *QDGlx;       //�ֲ�ʽ��Դ�޹����� ������ ��ʱ��
 //   double  *QDGux;		  //�ֲ�ʽ��Դ�޹����� ������ ��ʱ��
 //   double  *SDGux;       //�ֲ�ʽ��Դ�������� ������ ��ʱ��
 //   
 //   double  *PStolx;      //����ϵͳ�й����� ������ ��ʱ��
 //   double  *PStoux;      //����ϵͳ�й����� ������ ��ʱ��
 //   double  *QStolx;      //����ϵͳ�޹����� ������ ��ʱ��
 //   double  *QStoux;	  //����ϵͳ�޹����� ������ ��ʱ��
 //   double  *SStoux;      //����ϵͳ�������� ������ ��ʱ��
 //   
 //   int *NCapBanklx;      //������Ͷ���������� ������ ��ʱ��
 //   int *NCapBankux;      //������Ͷ���������� ������ ��ʱ��
 //   
 //   double *QSVClx;       //��ֹ�޹��������޹����� ������ ��ʱ��
 //   double *QSVCux;       //��ֹ�޹��������޹����� ������ ��ʱ��

	//double *PXfrmlx;      //�������ѹ�������й����� ������ ��ʱ��
	//double *PXfrmux;      //�������ѹ�������й����� ������ ��ʱ��
	//double *QXfrmlx;      //�������ѹ�������޹����� ������ ��ʱ��
	//double *QXfrmux;      //�������ѹ�������޹����� ������ ��ʱ��
	//double *SXfrmux;      //�������ѹ�������������� ������ ��ʱ��

	//double *POLTClx;      //���ص�ѹ�������й����� ������ ��ʱ��
	//double *POLTCux;      //���ص�ѹ�������й����� ������ ��ʱ��
	//double *QOLTClx;      //���ص�ѹ�������޹����� ������ ��ʱ��
	//double *QOLTCux;      //���ص�ѹ�������޹����� ������ ��ʱ��
	//double *SOLTCux;      //���ص�ѹ�������������� ������ ��ʱ��
 //   
 //   int   *KOLTClx;       //���ص�ѹ����λ���� ������ ��ʱ��
 //   int   *KOLTCux;       //���ص�ѹ����λ���� ������ ��ʱ��
 //   
 //   double *QPWMlx;       //�����������޹����� ������ ��ʱ��
 //   double *QPWMux;       //�����������޹����� ������ ��ʱ��
 //   double *SPWMux;       //������������������ ������ ��ʱ��

 //   //20191127
	//double *PSopAlx;      //��������A�˿ڴ����й����� ������ ��ʱ��
	//double *PSopAux;      //��������A�˿ڴ����й����� ������ ��ʱ��
 //   double *PSopBlx;      //��������B�˿ڴ����й����� ������ ��ʱ��
	//double *PSopBux;      //��������B�˿ڴ����й����� ������ ��ʱ��
 //   double *PSopClx;      //��������C�˿ڴ����й����� ������ ��ʱ��
	//double *PSopCux;      //��������C�˿ڴ����й����� ������ ��ʱ��
 //   double *QSopAlx;      //��������A�˿ڷ����޹����� ������ ��ʱ��
	//double *QSopAux;      //��������A�˿ڷ����޹����� ������ ��ʱ��
 //   double *QSopBlx;      //��������B�˿ڷ����޹����� ������ ��ʱ��
	//double *QSopBux;      //��������B�˿ڷ����޹����� ������ ��ʱ��
 //   double *QSopClx;      //��������C�˿ڷ����޹����� ������ ��ʱ��
	//double *QSopCux;      //��������C�˿ڷ����޹����� ������ ��ʱ��
	//double *SSopAux;      //��������A�˿���������     ������ ��ʱ��
	//double *SSopBux;      //��������B�˿���������     ������ ��ʱ��
	//double *SSopCux;      //��������C�˿���������     ������ ��ʱ��

	///////////////////////////////////////////////////////
 //   double *PineqLoss;    //�������ϵ������
 //   double *VeqMti;		  //��ѹƫ��ϵ������
 //   double *IeqPert;	  //��·������ϵ������
 //   double *DGeqMax;	  //�ֲ�ʽ��Դ���ɵ���ϵ������
 //   double *Objmat;       //Ŀ�꺯��
	//double *ObjmatStore;  //Ŀ�꺯������

	///////////////////////////////////////////////////////
	//double **XiIter;      //͹��滮��������� ������ѹԼ��
 //   double **XjIter;
 //   double **YijIter;
 //   double **ZijIter;

	//double **PsopIter;   //͹��滮��������� SOP���Լ�� //20200902
	//double **QsopIter;
	//double **PMsopIter;

	////���ڽ���ϡ��洢����ر���
	//int a;//a,bΪ���ڶԸ�asub,aval������и�ֵ�ļ�����
	//int b;


	//int* Pineqcolnum;
	//int* Pineqaptrb;
	//int* Pineqaptre;
	//int* Pineqasub;
	//double* Pineqaval;
	//int  Pineqglobmaxnum;

	//int* Qineqcolnum;
	//int* Qineqaptrb;
	//int* Qineqaptre;
	//int* Qineqasub;
	//double* Qineqaval;
	//int  Qineqglobmaxnum;

	//int* Veqcolnum;
	//int* Veqaptrb;
	//int* Veqaptre;
	//int* Veqasub;
	//double* Veqaval;
	//int  Veqglobmaxnum;

	//int* Veq2colnum;
	//int* Veq2aptrb;
	//int* Veq2aptre;
	//int* Veq2asub;
	//double* Veq2aval;
	//int  Veq2globmaxnum;

	//int* Veq3colnum;
	//int* Veq3aptrb;
	//int* Veq3aptre;
	//int* Veq3asub;
	//double* Veq3aval;
	//int  Veq3globmaxnum;

	//int* Ieqcolnum;
	//int* Ieqaptrb;
	//int* Ieqaptre;
	//int* Ieqasub;
	//double* Ieqaval;
	//int  Ieqglobmaxnum;

	//int* Pfeqcolnum;
	//int* Pfeqaptrb;
	//int* Pfeqaptre;
	//int* Pfeqasub;
	//double* Pfeqaval;
	//int  Pfeqglobmaxnum;

	//int* Eeqcolnum;
	//int* Eeqaptrb;
	//int* Eeqaptre;
	//int* Eeqasub;
	//double* Eeqaval;
	//int  Eeqglobmaxnum;

	//int* Vxfrmcolnum;
	//int* Vxfrmaptrb;
	//int* Vxfrmaptre;
	//int* Vxfrmasub;
	//double* Vxfrmaval;
	//int  Vxfrmglobmaxnum;

	//int* Vxfrm2colnum;
	//int* Vxfrm2aptrb;
	//int* Vxfrm2aptre;
	//int* Vxfrm2asub;
	//double* Vxfrm2aval;
	//int  Vxfrm2globmaxnum;

	//int* Vtranscolnum;
	//int* Vtransaptrb;
	//int* Vtransaptre;
	//int* Vtransasub;
	//double* Vtransaval;
	//int  Vtransglobmaxnum;

	//int* Vtrans2colnum;
	//int* Vtrans2aptrb;
	//int* Vtrans2aptre;
	//int* Vtrans2asub;
	//double* Vtrans2aval;
	//int  Vtrans2globmaxnum;

	//int* Vtrans3colnum;
	//int* Vtrans3aptrb;
	//int* Vtrans3aptre;
	//int* Vtrans3asub;
	//double* Vtrans3aval;
	//int  Vtrans3globmaxnum;

	//int* Vtrans4colnum;
	//int* Vtrans4aptrb;
	//int* Vtrans4aptre;
	//int* Vtrans4asub;
	//double* Vtrans4aval;
	//int  Vtrans4globmaxnum;

	//int* Vtrans5colnum;
	//int* Vtrans5aptrb;
	//int* Vtrans5aptre;
	//int* Vtrans5asub;
	//double* Vtrans5aval;
	//int  Vtrans5globmaxnum;

	//int* Convertcolnum;
	//int* Convertaptrb;
	//int* Convertaptre;
	//int* Convertasub;
	//double* Convertaval;
	//int  Convertglobmaxnum;

	//int* Softptcolnum;
	//int* Softptaptrb;
	//int* Softptaptre;
	//int* Softptasub;
	//double* Softptaval;
	//int  Softptglobmaxnum;

	//int* Softeqcolnum;
	//int* Softeqaptrb;
	//int* Softeqaptre;
	//int* Softeqasub;
	//double* Softeqaval;
	//int  Softeqglobmaxnum;

	//int* Dcpeqcolnum;
	//int* Dcpeqaptrb;
	//int* Dcpeqaptre;
	//int* Dcpeqasub;
	//double* Dcpeqaval;
	//int  Dcpeqglobmaxnum;

	//int* Dcpeq2colnum;
	//int* Dcpeq2aptrb;
	//int* Dcpeq2aptre;
	//int* Dcpeq2asub;
	//double* Dcpeq2aval;
	//int  Dcpeq2globmaxnum;

	//int* DcpeqSopcolnum;
	//int* DcpeqSopaptrb;
	//int* DcpeqSopaptre;
	//int* DcpeqSopasub;
	//double* DcpeqSopaval;
	//int  DcpeqSopglobmaxnum;

	//int* Dcpeq2Sopcolnum;
	//int* Dcpeq2Sopaptrb;
	//int* Dcpeq2Sopaptre;
	//int* Dcpeq2Sopasub;
	//double* Dcpeq2Sopaval;
	//int  Dcpeq2Sopglobmaxnum;

	////͹��滮��־λ������͹���ʼ�������������Ĺ���
	//int DcpLabel;//200816 WR_ZZQ ͹���ʼ����ʱ����ҪDcpeq��Dcpeq2��ֵ ֱ����socp���

};

extern void FreeSpaceMatric();

extern CMatric *pMatric;

#endif