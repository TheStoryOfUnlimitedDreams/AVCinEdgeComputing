#if _MSC_VER > 1000
#pragma once
#endif

#if !defined(AFX__OUTPUT_H__76YGV09_12OLEB6_1225UHD_0EQMSK_56PL3__INCLUDED_)
#define AFX__OUTPUT_H__76YGV09_12OLEB6_1225UHD_0EQMSK_56PL3__INCLUDED_

#include "string.h"
#include "stdio.h"  
#include "stdlib.h"
#include "../include/Sys_file.h"

class COutput
{
public:
	COutput();
	virtual ~COutput();

	void WriteTitle();
	void InitialStateGetFileOpen();
    void OptimizedStateGetFileOpen();

	void WriteResult();
	void PrintVoltage();
	void PrintLineData();

	void PrintDistGen();
	void PrintSOP();

	void PrintObject();
	void PrintSumInfo();


	void WriteEnd();
	void CloseFile();


	double *xx;

private:
	FILE *pFVoltage;
	FILE *pFLineData;
	FILE *pFDistGen;
	FILE *pFSOP;
	FILE *pFObject;
	FILE *pFSumInfo;

};


#endif