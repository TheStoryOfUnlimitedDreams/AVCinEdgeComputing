
#if _MSC_VER > 1000
#pragma once
#endif

#if !defined(AFX_DISPPARTYPE_H__BEA163A0_6F37_484C_BD78_13AC401D0FA8__INCLUDED_)
#define AFX_DISPPARTYPE_H__BEA163A0_6F37_484C_BD78_13AC401D0FA8__INCLUDED_
//如果XXX_H__XX没有定义过 证明这个头文件没有被包含过
//因为XXX_H__XX是一个比较唯一的宏名 其长度保证其唯一性
//如果XXX_H__XX被定义过 即该头文件被包含过 则整个#if #endif之间的变量就不会被重复定义

class CContrData
{
public:
	CContrData();
	virtual ~CContrData();

	char CaseName[100];       //算例名称
	double BaseVe;            //基准容量 kVA
	double BaseV;             //基准电压 kV
	double Step;              //运行时步//规划时步 h
	int Npoint;               //运行周期//规划周期
	double Vu;                //电压允许上限 p.u.
	double Vb;                //电压允许下限 p.u.
	double Vqu;               //电压合格上限 p.u.
	double Vqb;               //电压合格下限 p.u.

	double WeightA;           //网络损耗最小权重系数
	double WeightB;           //电压偏差最小权重系数
	double WeightC;           //线路载流比最小权重系数

	char Devise[3];           //可调控设备 [xxx]-[光伏 风机 电容器组]

	int Optimize;             //优化标志位 0：优化前 1：优化后

	double MaxPre;            //允许精度//凸差规划锥约束gap值允许精度

	double PSOPintvl;		  //SOP有功的优化间隔，不对用户开放

	int Cloud;                //指示是否与云边通信
	int Solver;               //指示是否有可用求解器

	double InitialV;		  //源节点初始电压


    int EnablePV;             //光伏参与调节
    int EnableWT;			  //风机参与调节
    int EnableSto;			  //储能参与调节
    int EnableCapBank;		  //电容器组参与调节

    int EnableSwitch;		  //联络开关参与调节

	int EnableSOP;			  //智能软开关参与调节
};

class CCurveData
{
public:
	CCurveData();
	~CCurveData();

	int Id_Curve;             //曲线名称
	int Tpot;                 //时间断面数
	double *TimSeq;           //曲线时序值 .p.u
	int Play;                 //是否使用 1：使用 0：不使用
};

//交流母线
class CBusData
{
public:
	CBusData();
	~CBusData();

	int Id_Bus;                //母线编号
	double P;				   //连接在该母线上负荷有功功率 kW
	double Q;				   //连接在该母线上负荷无功功率 kVar
	double V;                  //母线额定电压 kV
	int Symb;				   //母线平衡节点标志位 1：是平衡节点 0：不是平衡节点
	int ACDC;                  //母线交直流标志位 1：交流母线 0：直流母线
	int Curve_Load;			   //连接在该母线上负荷时序曲线编号
};

//交流线路
class CLineData
{
public:
	CLineData();
	~CLineData();

	int Id_Line;                //线路编号
	int BegNod;					//线路首节点编号
	int EndNod;					//线路尾节点编号
	int State;					//线路标志位 1：表示使用中 0：表示开路或停用
	char Type_Line[10];			//线路类型 L：交流线路和直流线路 X：两绕组变压器 T：有载调压器 S：联络开关
	int ACDC;                   //线路交直流标志位 1：交流线路 0：直流线路
	double R;					//线路电阻 Ω
	double X;					//线路电抗 Ω
	double Imax;				//线路最大载流量 A
	double BVt;				    //线路首节点电压
	double EVt;				    //线路末节点电压
	int TakePart;               //参与调节类型 0：不参与 3：综合调节
};							

//负荷
class CLoadData
{
public:
	CLoadData();
	~CLoadData();
	
	int Id_Load;                //负荷编号
	int ConNod_Load;		    //负荷连接节点编号
	int ACDC;				    //负荷交直流标志位 1：交流负荷 0：直流负荷 
	double PLoad;			    //负荷额定有功功率 kW
	double QLoad;			    //负荷额定无功功率 kVar
	int Curve_Load;			    //负荷时序曲线编号
};

//分布式电源
class CDGData
{
public:
	CDGData();
	~CDGData();

	int Id_DG;                   //分布式电源编号 
	int ConNod_DG;				 //分布式电源连接节点编号
	double Porg;                 //原始输出有功功率 kW
	double Qorg;                 //原始输出无功功率 kVar
	double Pmin;				 //输出有功功率下限 kW
	double Pmax;				 //输出有功功率上限 kW
	double Qmin;				 //输出无功功率下限 kVar
	double Qmax;				 //输出无功功率上限 kVar
	double Smax;				 //输出视在功率上限 kVA
	int Type_DG;				 //分布式电源类型 1：光伏 2：风机
	int Curve_DG;				 //分布式电源时序曲线编号
	int TakePart;                //参与调节类型 0：不参与 1：参与调节
};								 

//联络开关
class CSwitchData
{
public:
	CSwitchData();
	~CSwitchData();

	int Id_Switch;                 //联络开关编号
	int FakeId;                    //联络开关等效线路编号
	int BegNod;					   //联络开关首节点编号
	int EndNod;					   //联络开关尾节点编号
	double BVt;					   //联络开关首端电压 kV
	double EVt;					   //联络开关末端电压 kV
	double R;                      //联络开关支路电阻 Ω
	double X;					   //联络开关支路电抗 Ω
	int State;					   //联络开关标志位 1：表示使用中 0：表示开路或停用
	double Imax;				   //联络开关最大载流量 A
	int TakePart;                  //参与调节类型[0 3]
};

//智能软开关
class CSOPData
{
public:
	CSOPData();
	~CSOPData();
	
	int Id_SOP;                   //SOP编号 
	int ConNod_SOP;				 //SOP连接节点编号
	double Porg;                 //SOP原始输出有功功率 kW
	double Qorg;                 //SOP原始输出无功功率 kVar
	double Pmin;				 //SOP输出有功功率下限 kW
	double Pmax;				 //SOP输出有功功率上限 kW
	double Qmin;				 //SOP输出无功功率下限 kVar
	double Qmax;				 //SOP输出无功功率上限 kVar
	double Smax;				 //SOP输出视在功率上限 kVA
	int TakePart;                //参与调节类型 0：不参与 2：无功调节

	//VSC1控制方式     VSC2控制方式      节点类型       适用场景
	//PQ控制           UdcQ控制		     PQ-PQ节点      正常运行
	//PQ控制           UdcUac控制        PQ-PV节点      正常运行
	//PUac控制         UdcQ控制		     PV-PQ节点      正常运行
	//PUac控制         UdcUac控制        PV-PV节点      正常运行
	//Uacθ控制        UdcQ控制          Vθ-PQ节点     VSC1交流侧故障
	//Uacθ控制        UdcUac控制        Vθ-PV节点     VSC1交流侧故障
	//UdcQ控制         Uacθ控制         PQ-Vθ节点     VSC2交流侧故障
	//UdcUac控制       Uacθ控制         PV-Vθ节点     VSC2交流侧故障
};	

class CRunData						
{									
public:								
	CRunData();						
	~CRunData();

	//计数量
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

	//总数量
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

//输出类
class Output_VoltData //节点电压
{
public:
	Output_VoltData();
	~Output_VoltData();

	int Id_Bus;                //母线编号
	double V0;				   //节点初始电压
	double V;				   //节点优化后电压
};

class Output_LineData //Line
{
public:
	Output_LineData();
	~Output_LineData();

	int Id_Line;                //线路编号
	int BegNod;					//线路首节点编号
	int EndNod;					//线路尾节点编号
	double P0;                  //原始线路有功功率 kW
	double Q0;                  //原始线路无功功率 kVar
	double PLoss0;              //原始损耗有功功率 kW
	double QLoss0;              //原始损耗无功功率 kVar
	double I0;					//原始线路电流 A
	double P;                   //线路有功功率 kW
	double Q;                   //线路无功功率 kVar
	double PLoss;               //损耗有功功率 kW
	double QLoss;               //损耗无功功率 kVar
	double I;					//线路电流 A
};

class Output_DGData //DG
{
public:
	Output_DGData();
	~Output_DGData();

	int Id_DG;                //分布式电源编号 
	int ConNod_DG;			  //分布式电源连接节点编号
	double P0;                //原始输出有功功率 kW
	double Q0;                //原始输出无功功率 kVar
	double P;                 //输出有功功率 kW
	double Q;                 //输出无功功率 kVar
	double Vlow;			  //控制曲线死区下限
	double Vup ;			  //控制曲线死区上限
};

class Output_SOPData //SOP
{
public:
	Output_SOPData();
	~Output_SOPData();

	int Id_SOP;					//SOP编号 
	int ConNod_SOP;				//SOP连接节点编号
	double P0;					//端口原始输出有功功率 kW
	double Q0;					//端口原始输出无功功率 kVar
	double P;					//端口优化后输出有功功率 kW
	double Q;					//端口优化后输出无功功率 kVar
	double Vlow;				//端口控制曲线死区下限
	double Vup;					//端口控制曲线死区上限
};

class Output_Obj //目标函数
{
public:
	Output_Obj();
	~Output_Obj();

	double ObjmatPLoss0;  //用于描述优化前网损目标函数
	double ObjmatVDev0;   //用于描述优化前电压偏差目标函数
	double ObjmatIcay0;   //用于描述优化前负载均衡目标函数
	double Objmat0;       //用于描述优化前总目标函数
	double maxIcay0;	  //用于描述最大负载均衡指标
	double maxV0;		  //用于描述最大节点电压
	double minV0;		  //用于描述最小节点电压
	double ObjmatPLoss;   //用于描述网损目标函数
	double ObjmatVDev;    //用于描述电压偏差目标函数
	double ObjmatIcay;	  //用于描述负载均衡目标函数
	double Objmat;        //用于描述总目标函数
	double maxIcay;		  //用于描述最大负载均衡指标
	double maxV;		  //用于描述最大节点电压
	double minV;		  //用于描述最小节点电压


};


//声明子函数
extern void FreeSpaceElement();
extern void FreeOutputElement();

extern void Message(const char *sText,const char* sTitle);

//声明各元件类为全局变量
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