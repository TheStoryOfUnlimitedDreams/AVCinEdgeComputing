
#if _MSC_VER > 1000
#pragma once
#endif

#if !defined(AFX_DISPPARTYPE_H__BEA163A0_6F37_484C_BD78_13AC401D0FA8__INCLUDED_)
#define AFX_DISPPARTYPE_H__BEA163A0_6F37_484C_BD78_13AC401D0FA8__INCLUDED_
//���XXX_H__XXû�ж���� ֤�����ͷ�ļ�û�б�������
//��ΪXXX_H__XX��һ���Ƚ�Ψһ�ĺ��� �䳤�ȱ�֤��Ψһ��
//���XXX_H__XX������� ����ͷ�ļ��������� ������#if #endif֮��ı����Ͳ��ᱻ�ظ�����

class CContrData
{
public:
	CContrData();
	virtual ~CContrData();

	char CaseName[100];       //��������
	double BaseVe;            //��׼���� kVA
	double BaseV;             //��׼��ѹ kV
	double Step;              //����ʱ��//�滮ʱ�� h
	int Npoint;               //��������//�滮����
	double Vu;                //��ѹ�������� p.u.
	double Vb;                //��ѹ�������� p.u.
	double Vqu;               //��ѹ�ϸ����� p.u.
	double Vqb;               //��ѹ�ϸ����� p.u.

	double WeightA;           //���������СȨ��ϵ��
	double WeightB;           //��ѹƫ����СȨ��ϵ��
	double WeightC;           //��·��������СȨ��ϵ��

	char Devise[3];           //�ɵ����豸 [xxx]-[��� ��� ��������]

	int Optimize;             //�Ż���־λ 0���Ż�ǰ 1���Ż���

	double MaxPre;            //������//͹��滮׶Լ��gapֵ������

	double PSOPintvl;		  //SOP�й����Ż�����������û�����

	int Cloud;                //ָʾ�Ƿ����Ʊ�ͨ��
	int Solver;               //ָʾ�Ƿ��п��������

	double InitialV;		  //Դ�ڵ��ʼ��ѹ


    int EnablePV;             //����������
    int EnableWT;			  //����������
    int EnableSto;			  //���ܲ������
    int EnableCapBank;		  //��������������

    int EnableSwitch;		  //���翪�ز������

	int EnableSOP;			  //�������ز������
};

class CCurveData
{
public:
	CCurveData();
	~CCurveData();

	int Id_Curve;             //��������
	int Tpot;                 //ʱ�������
	double *TimSeq;           //����ʱ��ֵ .p.u
	int Play;                 //�Ƿ�ʹ�� 1��ʹ�� 0����ʹ��
};

//����ĸ��
class CBusData
{
public:
	CBusData();
	~CBusData();

	int Id_Bus;                //ĸ�߱��
	double P;				   //�����ڸ�ĸ���ϸ����й����� kW
	double Q;				   //�����ڸ�ĸ���ϸ����޹����� kVar
	double V;                  //ĸ�߶��ѹ kV
	int Symb;				   //ĸ��ƽ��ڵ��־λ 1����ƽ��ڵ� 0������ƽ��ڵ�
	int ACDC;                  //ĸ�߽�ֱ����־λ 1������ĸ�� 0��ֱ��ĸ��
	int Curve_Load;			   //�����ڸ�ĸ���ϸ���ʱ�����߱��
};

//������·
class CLineData
{
public:
	CLineData();
	~CLineData();

	int Id_Line;                //��·���
	int BegNod;					//��·�׽ڵ���
	int EndNod;					//��·β�ڵ���
	int State;					//��·��־λ 1����ʾʹ���� 0����ʾ��·��ͣ��
	char Type_Line[10];			//��·���� L��������·��ֱ����· X���������ѹ�� T�����ص�ѹ�� S�����翪��
	int ACDC;                   //��·��ֱ����־λ 1��������· 0��ֱ����·
	double R;					//��·���� ��
	double X;					//��·�翹 ��
	double Imax;				//��·��������� A
	double BVt;				    //��·�׽ڵ��ѹ
	double EVt;				    //��·ĩ�ڵ��ѹ
	int TakePart;               //����������� 0�������� 3���ۺϵ���
};							

//����
class CLoadData
{
public:
	CLoadData();
	~CLoadData();
	
	int Id_Load;                //���ɱ��
	int ConNod_Load;		    //�������ӽڵ���
	int ACDC;				    //���ɽ�ֱ����־λ 1���������� 0��ֱ������ 
	double PLoad;			    //���ɶ�й����� kW
	double QLoad;			    //���ɶ�޹����� kVar
	int Curve_Load;			    //����ʱ�����߱��
};

//�ֲ�ʽ��Դ
class CDGData
{
public:
	CDGData();
	~CDGData();

	int Id_DG;                   //�ֲ�ʽ��Դ��� 
	int ConNod_DG;				 //�ֲ�ʽ��Դ���ӽڵ���
	double Porg;                 //ԭʼ����й����� kW
	double Qorg;                 //ԭʼ����޹����� kVar
	double Pmin;				 //����й��������� kW
	double Pmax;				 //����й��������� kW
	double Qmin;				 //����޹��������� kVar
	double Qmax;				 //����޹��������� kVar
	double Smax;				 //������ڹ������� kVA
	int Type_DG;				 //�ֲ�ʽ��Դ���� 1����� 2�����
	int Curve_DG;				 //�ֲ�ʽ��Դʱ�����߱��
	int TakePart;                //����������� 0�������� 1���������
};								 

//���翪��
class CSwitchData
{
public:
	CSwitchData();
	~CSwitchData();

	int Id_Switch;                 //���翪�ر��
	int FakeId;                    //���翪�ص�Ч��·���
	int BegNod;					   //���翪���׽ڵ���
	int EndNod;					   //���翪��β�ڵ���
	double BVt;					   //���翪���׶˵�ѹ kV
	double EVt;					   //���翪��ĩ�˵�ѹ kV
	double R;                      //���翪��֧·���� ��
	double X;					   //���翪��֧·�翹 ��
	int State;					   //���翪�ر�־λ 1����ʾʹ���� 0����ʾ��·��ͣ��
	double Imax;				   //���翪����������� A
	int TakePart;                  //�����������[0 3]
};

//��������
class CSOPData
{
public:
	CSOPData();
	~CSOPData();
	
	int Id_SOP;                   //SOP��� 
	int ConNod_SOP;				 //SOP���ӽڵ���
	double Porg;                 //SOPԭʼ����й����� kW
	double Qorg;                 //SOPԭʼ����޹����� kVar
	double Pmin;				 //SOP����й��������� kW
	double Pmax;				 //SOP����й��������� kW
	double Qmin;				 //SOP����޹��������� kVar
	double Qmax;				 //SOP����޹��������� kVar
	double Smax;				 //SOP������ڹ������� kVA
	int TakePart;                //����������� 0�������� 2���޹�����

	//VSC1���Ʒ�ʽ     VSC2���Ʒ�ʽ      �ڵ�����       ���ó���
	//PQ����           UdcQ����		     PQ-PQ�ڵ�      ��������
	//PQ����           UdcUac����        PQ-PV�ڵ�      ��������
	//PUac����         UdcQ����		     PV-PQ�ڵ�      ��������
	//PUac����         UdcUac����        PV-PV�ڵ�      ��������
	//Uac�ȿ���        UdcQ����          V��-PQ�ڵ�     VSC1���������
	//Uac�ȿ���        UdcUac����        V��-PV�ڵ�     VSC1���������
	//UdcQ����         Uac�ȿ���         PQ-V�Ƚڵ�     VSC2���������
	//UdcUac����       Uac�ȿ���         PV-V�Ƚڵ�     VSC2���������
};	

class CRunData						
{									
public:								
	CRunData();						
	~CRunData();

	//������
	int nCurve;
	int nBus;                     
	int nBa;
	int nLine;
	int nLoad;
	int nPV;
	int nWT;
	int nDG;
	int nSwitch;
	int nSOP;

	//������
	int maxCurve;
	int maxBus;
	int maxACBus;
	int maxBa;
	int maxLine;
	int maxACLine;
	int maxPV;
	int maxWT;
	int maxLoad;
	int maxDG;
	int maxSwitch;
	int maxSOP;

	int Hth;

	int GapIter;
	double GapPre;
};

//�����
class Output_VoltData //�ڵ��ѹ
{
public:
	Output_VoltData();
	~Output_VoltData();

	int Id_Bus;                //ĸ�߱��
	double V0;				   //�ڵ��ʼ��ѹ
	double V;				   //�ڵ��Ż����ѹ
};

class Output_LineData //Line
{
public:
	Output_LineData();
	~Output_LineData();

	int Id_Line;                //��·���
	int BegNod;					//��·�׽ڵ���
	int EndNod;					//��·β�ڵ���
	double P0;                  //ԭʼ��·�й����� kW
	double Q0;                  //ԭʼ��·�޹����� kVar
	double PLoss0;              //ԭʼ����й����� kW
	double QLoss0;              //ԭʼ����޹����� kVar
	double I0;					//ԭʼ��·���� A
	double P;                   //��·�й����� kW
	double Q;                   //��·�޹����� kVar
	double PLoss;               //����й����� kW
	double QLoss;               //����޹����� kVar
	double I;					//��·���� A
};

class Output_DGData //DG
{
public:
	Output_DGData();
	~Output_DGData();

	int Id_DG;                //�ֲ�ʽ��Դ��� 
	int ConNod_DG;			  //�ֲ�ʽ��Դ���ӽڵ���
	double P0;                //ԭʼ����й����� kW
	double Q0;                //ԭʼ����޹����� kVar
	double P;                 //����й����� kW
	double Q;                 //����޹����� kVar
	double Vlow;			  //����������������
	double Vup ;			  //����������������
};

class Output_SOPData //SOP
{
public:
	Output_SOPData();
	~Output_SOPData();

	int Id_SOP;					//SOP��� 
	int ConNod_SOP;				//SOP���ӽڵ���
	double P0;					//�˿�ԭʼ����й����� kW
	double Q0;					//�˿�ԭʼ����޹����� kVar
	double P;					//�˿��Ż�������й����� kW
	double Q;					//�˿��Ż�������޹����� kVar
	double Vlow;				//�˿ڿ���������������
	double Vup;					//�˿ڿ���������������
};

class Output_Obj //Ŀ�꺯��
{
public:
	Output_Obj();
	~Output_Obj();

	double ObjmatPLoss0;  //���������Ż�ǰ����Ŀ�꺯��
	double ObjmatVDev0;   //���������Ż�ǰ��ѹƫ��Ŀ�꺯��
	double ObjmatIcay0;   //���������Ż�ǰ���ؾ���Ŀ�꺯��
	double Objmat0;       //���������Ż�ǰ��Ŀ�꺯��
	double maxIcay0;	  //������������ؾ���ָ��
	double maxV0;		  //�����������ڵ��ѹ
	double minV0;		  //����������С�ڵ��ѹ
	double ObjmatPLoss;   //������������Ŀ�꺯��
	double ObjmatVDev;    //����������ѹƫ��Ŀ�꺯��
	double ObjmatIcay;	  //�����������ؾ���Ŀ�꺯��
	double Objmat;        //����������Ŀ�꺯��
	double maxIcay;		  //������������ؾ���ָ��
	double maxV;		  //�����������ڵ��ѹ
	double minV;		  //����������С�ڵ��ѹ


};


//�����Ӻ���
extern void FreeSpaceElement();
extern void FreeOutputElement();

extern void Message(const char *sText,const char* sTitle);

//������Ԫ����Ϊȫ�ֱ���
extern CContrData     *pControl;
extern CCurveData     *pCurve;
extern CBusData       *pBus;
extern CLineData      *pLine;
extern CLoadData      *pLoad;
extern CDGData        *pDG;
extern CSwitchData    *pSwitch;
extern CSOPData       *pSOP;

extern CRunData       *pRuntime;

extern Output_VoltData **VoltData;
extern Output_DGData   **DGData;
extern Output_SOPData  **SOPData;
extern Output_LineData **LineData;
extern Output_Obj      *Obj;

#endif