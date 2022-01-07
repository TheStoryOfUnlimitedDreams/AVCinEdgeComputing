#include "stdio.h"
#include "../include/ParType.h"

//定义各元件类的构造函数
CContrData::CContrData()
{
}
CCurveData::CCurveData()
{
}
CBusData::CBusData()
{
}
CLineData::CLineData()
{
}
CLoadData::CLoadData() 
{
}
CDGData::CDGData()      
{
}
CSwitchData::CSwitchData()
{
}
CSOPData::CSOPData()
{
}
CRunData::CRunData()
{
}
//定义各元件类的析构函数
CContrData::~CContrData()
{
}
CCurveData::~CCurveData()
{
}
CBusData::~CBusData()
{
}
CLineData::~CLineData()
{
}
CLoadData::~CLoadData()     
{
}
CDGData::~CDGData()      
{
}
CSwitchData::~CSwitchData()
{
}
CSOPData::~CSOPData()
{
}
CRunData::~CRunData()
{
}


//输出类
Output_VoltData::Output_VoltData()
{
}
Output_VoltData::~Output_VoltData()
{
}
Output_LineData::Output_LineData()
{
}
Output_LineData::~Output_LineData()
{
}
Output_DGData::Output_DGData()
{
}
Output_DGData::~Output_DGData()
{
}
Output_SOPData::Output_SOPData()
{
}
Output_SOPData::~Output_SOPData()
{
}
Output_Obj::Output_Obj()
{
}
Output_Obj::~Output_Obj()
{
}


//释放各元件类内存
void FreeSpaceElement()
{
	if(pRuntime->maxBus >0)
	{
		delete []pBus;
		pBus = NULL;
	}

	if(pRuntime->maxLine >0)
	{
		delete []pLine;
		pLine = NULL;
	}

	if(pRuntime->maxLoad >0)
	{
		delete []pLoad;
		pLoad = NULL;
	}
	if(pRuntime->maxDG >0)
	{
		delete []pDG;
		pDG = NULL;
	}
	if(pRuntime->maxSwitch >0)
	{
		delete []pSwitch;
		pSwitch = NULL;
	}

	if(pRuntime->maxSOP >0)
	{
		delete []pSOP;
		pSOP = NULL;
	}	

	if (pRuntime->maxCurve > 0)
	{
		delete[]pCurve;
		pCurve = NULL;
	}
}

void FreeOutputElement()
{
	//节点电压
	for (int i = 0; i < pRuntime->maxBus; i++)
	{
		delete[]VoltData[i];
	}
	delete[]VoltData;
	VoltData = NULL;

	//线路功率
	for (int i = 0; i < pRuntime->maxLine; i++)
	{
		delete[]LineData[i];
	}
	delete[]LineData;
	LineData = NULL;

	//节点分布式电源的出力
	for (int i = 0; i < pRuntime->maxDG; i++)
	{
		delete[]DGData[i];
	}
	delete[]DGData;
	DGData = NULL;

	for (int i = 0; i < pRuntime->maxSOP; i++)
	{
		delete[]SOPData[i];
	}
	delete[]SOPData;
	SOPData = NULL;

	//目标函数
	delete[]Obj;

}

void Message(const char *sText,const char* sTitle)//显示系统平台文件组织错误信息
{
	fprintf(stderr,"\n%s %s \n",sText,sTitle);//printf("\n%s %s \n",sText,sTitle);
	//stderr无缓存输出 默认输出到显示器
}

//定义各元件类并初始化
CContrData    *pControl  = NULL;
CCurveData    *pCurve    = NULL;
CBusData      *pBus      = NULL;

CLineData     *pLine     = NULL;

CLoadData     *pLoad     = NULL;
CDGData		  *pDG       = NULL;

CSwitchData   *pSwitch   = NULL;
CSOPData      *pSOP      = NULL;
CRunData      *pRuntime  = NULL;

Output_VoltData **VoltData = NULL;
Output_DGData   **DGData   = NULL;
Output_SOPData  **SOPData = NULL;
Output_LineData **LineData = NULL;
Output_Obj      *Obj	   = NULL;
