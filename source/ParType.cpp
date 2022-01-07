#include "stdio.h"
#include "../include/ParType.h"

//�����Ԫ����Ĺ��캯��
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
//�����Ԫ�������������
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


//�����
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


//�ͷŸ�Ԫ�����ڴ�
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
	//�ڵ��ѹ
	for (int i = 0; i < pRuntime->maxBus; i++)
	{
		delete[]VoltData[i];
	}
	delete[]VoltData;
	VoltData = NULL;

	//��·����
	for (int i = 0; i < pRuntime->maxLine; i++)
	{
		delete[]LineData[i];
	}
	delete[]LineData;
	LineData = NULL;

	//�ڵ�ֲ�ʽ��Դ�ĳ���
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

	//Ŀ�꺯��
	delete[]Obj;

}

void Message(const char *sText,const char* sTitle)//��ʾϵͳƽ̨�ļ���֯������Ϣ
{
	fprintf(stderr,"\n%s %s \n",sText,sTitle);//printf("\n%s %s \n",sText,sTitle);
	//stderr�޻������ Ĭ���������ʾ��
}

//�����Ԫ���ಢ��ʼ��
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
