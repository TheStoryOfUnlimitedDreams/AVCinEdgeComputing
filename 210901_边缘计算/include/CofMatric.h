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



	//void FundamentalMatricMemoryAllt(); //基本量矩阵内存分配
	//void CfftMatricMemoryAllt();        //系数矩阵内存分配
	//void UpLowMatricMemoryAllt();       //上下限矩阵内存分配
	//void ObjMatricMemoryAllt();         //目标函数矩阵内存分配
	//void IterMatricMemoryAllt();        //迭代结果矩阵内存分配

	//void FundamentalMatricInitial();    //基本量矩阵初始化
	//void CfftMatricInitial();           //系数矩阵初始化
	//void UpLowMatricInitial();          //上下限矩阵初始化
	//void ObjMatricInitial();            //目标函数矩阵初始化
	//void IterMatricInitial();           //迭代结果矩阵初始化

	///////////////////////////////////////////////////////
 //   double *Gline;        //线路电导
 //   double *Bline;        //线路电纳
 //   
	///////////////////////////////////////////////////////
 //   double **Pineq;       //有功约束
 //   double **Qineq;       //无功约束
 //   double **Veq;         //拓扑约束
 //   double **Veq2;        //电压上限约束
 //   double **Veq3;        //电压下限约束
 //   double **Ieq;         //电流约束
 //   double **Pfeq;        //分布式电源出力约束
 //   double **Eeq;         //储能系统出力约束
	//double **Vxfrm;       //两绕组变压器两端电压约束
	//double **Vxfrm2;      //两绕组变压器功率传输约束
 //   double **Vtrans;      //有载调压器辅助变量wj dj等式约束
 //   double **Vtrans2;     //有载调压器辅助变量wj dj不等式约束
 //   double **Vtrans3;     //有载调压器两端电压约束
 //   double **Vtrans4;     //有载调压器变量Vn Kmn等式约束
	//double **Vtrans5;     //有载调压器功率传输约束
 //   double **Convert;     //换流器两端电压约束
	//double **Softpt;      //智能软开关有功功率传输约束 //20191127
	//double **Softeq;      //智能软开关损耗功率替换约束 //20191127
 //   double **Dcpeq;       //凸差规划约束线性项 潮流电压约束 2XiXj=Yij^2+Zij^2
 //   double **Dcpeq2;      //凸差规划约束平方项 潮流电压约束 2XiXj=Yij^2+Zij^2
	//double **DcpeqSop;    //凸差规划约束线性项 SOP损耗约束  SopLoss^2=Psop^2+Qsop^2 //20200902
	//double **Dcpeq2Sop;   //凸差规划约束平方项 SOP损耗约束  SopLoss^2=Psop^2+Qsop^2 //20200902

	///////////////////////////////////////////////////////
 //   double  *Pinc;        //负荷有功水平 Hth
	//double  *Qinc;        //负荷无功水平 Hth  
 //   
 //   double  *Iequc;       //线路载流量上限 单断面 总时序

 //   double  *Eeqlc;       //储能荷电量允许下限 总时序
 //   double  *Eequc;       //储能荷电量允许上限 总时序

 //   double  *Vxfrmlc;     //两绕组变压器倒送容量限制 单断面 总时序

	//double  *Vtrans5lc;   //有载调压器倒送容量限制 单断面 总时序
 //
	///////////////////////////////////////////////////////
 //   double  *PDGlx;       //分布式电源有功下限 Hth
 //   double  *PDGux;       //分布式电源有功上限 Hth
 //   double  *QDGlx;       //分布式电源无功下限 单断面 总时序
 //   double  *QDGux;		  //分布式电源无功上限 单断面 总时序
 //   double  *SDGux;       //分布式电源容量上限 单断面 总时序
 //   
 //   double  *PStolx;      //储能系统有功下限 单断面 总时序
 //   double  *PStoux;      //储能系统有功上限 单断面 总时序
 //   double  *QStolx;      //储能系统无功下限 单断面 总时序
 //   double  *QStoux;	  //储能系统无功上限 单断面 总时序
 //   double  *SStoux;      //储能系统容量上限 单断面 总时序
 //   
 //   int *NCapBanklx;      //电容器投切组数下限 单断面 总时序
 //   int *NCapBankux;      //电容器投切组数上限 单断面 总时序
 //   
 //   double *QSVClx;       //静止无功补偿器无功下限 单断面 总时序
 //   double *QSVCux;       //静止无功补偿器无功上限 单断面 总时序

	//double *PXfrmlx;      //两绕组变压器传输有功下限 单断面 总时序
	//double *PXfrmux;      //两绕组变压器传输有功上限 单断面 总时序
	//double *QXfrmlx;      //两绕组变压器传输无功下限 单断面 总时序
	//double *QXfrmux;      //两绕组变压器传输无功上限 单断面 总时序
	//double *SXfrmux;      //两绕组变压器传输容量上限 单断面 总时序

	//double *POLTClx;      //有载调压器传输有功下限 单断面 总时序
	//double *POLTCux;      //有载调压器传输有功上限 单断面 总时序
	//double *QOLTClx;      //有载调压器传输无功下限 单断面 总时序
	//double *QOLTCux;      //有载调压器传输无功上限 单断面 总时序
	//double *SOLTCux;      //有载调压器传输容量上限 单断面 总时序
 //   
 //   int   *KOLTClx;       //有载调压器档位下限 单断面 总时序
 //   int   *KOLTCux;       //有载调压器档位上限 单断面 总时序
 //   
 //   double *QPWMlx;       //换流器传输无功下限 单断面 总时序
 //   double *QPWMux;       //换流器传输无功上限 单断面 总时序
 //   double *SPWMux;       //换流器传输容量上限 单断面 总时序

 //   //20191127
	//double *PSopAlx;      //智能软开关A端口传输有功下限 单断面 总时序
	//double *PSopAux;      //智能软开关A端口传输有功上限 单断面 总时序
 //   double *PSopBlx;      //智能软开关B端口传输有功下限 单断面 总时序
	//double *PSopBux;      //智能软开关B端口传输有功上限 单断面 总时序
 //   double *PSopClx;      //智能软开关C端口传输有功下限 单断面 总时序
	//double *PSopCux;      //智能软开关C端口传输有功上限 单断面 总时序
 //   double *QSopAlx;      //智能软开关A端口发出无功下限 单断面 总时序
	//double *QSopAux;      //智能软开关A端口发出无功上限 单断面 总时序
 //   double *QSopBlx;      //智能软开关B端口发出无功下限 单断面 总时序
	//double *QSopBux;      //智能软开关B端口发出无功上限 单断面 总时序
 //   double *QSopClx;      //智能软开关C端口发出无功下限 单断面 总时序
	//double *QSopCux;      //智能软开关C端口发出无功上限 单断面 总时序
	//double *SSopAux;      //智能软开关A端口容量上限     单断面 总时序
	//double *SSopBux;      //智能软开关B端口容量上限     单断面 总时序
	//double *SSopCux;      //智能软开关C端口容量上限     单断面 总时序

	///////////////////////////////////////////////////////
 //   double *PineqLoss;    //网络损耗系数矩阵
 //   double *VeqMti;		  //电压偏差系数矩阵
 //   double *IeqPert;	  //线路载流比系数矩阵
 //   double *DGeqMax;	  //分布式电源消纳电量系数矩阵
 //   double *Objmat;       //目标函数
	//double *ObjmatStore;  //目标函数替身

	///////////////////////////////////////////////////////
	//double **XiIter;      //凸差规划结果迭代量 潮流电压约束
 //   double **XjIter;
 //   double **YijIter;
 //   double **ZijIter;

	//double **PsopIter;   //凸差规划结果迭代量 SOP损耗约束 //20200902
	//double **QsopIter;
	//double **PMsopIter;

	////用于进行稀疏存储的相关变量
	//int a;//a,b为用于对各asub,aval矩阵进行赋值的计数器
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

	////凸差规划标志位以区分凸差初始化和真正迭代的过程
	//int DcpLabel;//200816 WR_ZZQ 凸差初始化的时候不需要Dcpeq和Dcpeq2赋值 直接用socp求解

};

extern void FreeSpaceMatric();

extern CMatric *pMatric;

#endif