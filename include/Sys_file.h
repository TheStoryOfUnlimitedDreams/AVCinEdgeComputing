/***************************** TJUee ESPDG ******************************  
* FileName: 		Sys_file.h
*
* Author: 			Wangdan
*
* Data: 			2009.12.17
*
* Description:		read functions class  
*
* Attention:        Copyright (C) 2007-2009 EE&A, all rights reserved by ESPDG group
*
***************************** TJUee ESPDG *****************************/
# ifndef def_SYS_file_h
# define def_SYS_file_h

# include "stdio.h"

class CReadFile
{
private:
	long   ml_BeginPos;
	short  mc_ReadBus;
	short  mc_ReadPtiGen;
	short  mc_ReadBra;

public:
	char   ms_StrBK[200];
	char   ms_Str[1000];
	double  mf_AtoF[200];

	char *mp_Str;
	int  mi_StrSz;///to delete
	int  mi_LeftPos,mi_RightPos;
	long ml_LastPos;
	long ml_Pos;
	long ml_FileSize;

	FILE *mt_File;

	int  StrFindStr(char ch[],int n);
	int  StrFindFristStr(char ch[],int n);  //wangdan_2008_07_26
	int  StrFindCh(char ch, int nBgn = 0);   // +++ modified by gaoyi
	
	int StrFindNotCh(char ch, int nBgn = 0);  // +++ by gaoyi
	int IsVacantLine();  // +++ by gaoyi

	void StrReplace(char chFrom,char chTo);
	void  FGetLine(); //return the lenghth of the string

	long GetFilePos();
	long GetStrFilePos(char ch[],int n,long frompos,long topos);
	void MoveToFilePos( long fp);
	int  IsEnd();

public:
	CReadFile(char *filename);
	~CReadFile();
public:
	int  FileStrToFloat();
	////int  FileStrToFloat(int iPos[]);
	char ms_BusName[13];
	char ms_Id[2];
	int  FileStrToBusData();
	int  FileStrToLoadData();     // gjc_07_07_16
	int  FileStrToGenData();
	int  FileStrToBraData();
	int  FileStrToTransformerData();
	int  FileStrToInsData();

// +++++++++++++++++++++++++ For reading Covdc load flow, Add by wangdan
	char ms_CovDcName[13];
	int  FileStrToDcCovDataLine();
// +++++++++++++++++++++++++ End : add

// +++++++++++++++++++++++++ For reading Area Interchange, Add by Gaoyi
	char ms_ArName[13];
	int  FileStrToAreaInterchange();
	char ms_Rmidnt[13];
	int  FileStrToSwtShnt();
	int  FileStrToTrsfImpdc();
	char mc_MultSctLnId;
	int FileStrToMultSctLn();
	char ms_ZoneName[13];
	int FileStrToZone();
// +++++++++++++++++++++++++ End : add
	
// +++++++++++++++++++++++++ For reading dc2 load flow, Add by Gaoyi
	char mc_Meter;
	int  FileStrToDc2DataLine1();
	int  FileStrToDc2DataLine2();
	int  FileStrToDc2DataLine3();
// +++++++++++++++++++++++++ End : add
	
// +++++++++++++++++++++++++ For reading dcm load flow, Add by Gaoyi
	char mc_DcBrId;
	char ms_DcBusName[13];
	int  FileStrToDcmDataLine();

// +++++++++++++++++++++++++ End : add

// +++++++++++++++++++++++++ For reading vscdc load flow, Add by Gaoyi
	char ms_VscDcName[13];
	int  FileStrToDcVscDataLine();
// +++++++++++++++++++++++++ End : add
	
	////for DAT File
	int  DatParemeter(char paraID[], int n,long fp);    //  / gjc
	int  DATStrToGenData();
	int  FormatDATStrToGenData();
	int  UnFormatDATStrToGenData();

	void GoBegin();
};
# endif

