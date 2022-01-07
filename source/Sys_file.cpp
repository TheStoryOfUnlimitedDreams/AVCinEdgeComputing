
# include "Sys_file.h"

# include "math.h"
# include "string.h"
# include "ctype.h"
# include "stdlib.h"

# define DEDatGenBG  "DGEN"
# define DEDatGenED  "EDATA"

CReadFile::CReadFile(char *sFileName)
{
	ml_FileSize=0;

	ml_BeginPos=0;
	if ( (mt_File = fopen(sFileName, "rt")) == NULL)
	{
		//Message(sFileName,"File can't opened");
		ml_FileSize=-1;
		return;
	}
	fseek(mt_File, 0, SEEK_END);
	ml_FileSize=ftell(mt_File);

	strcpy(ms_Str,"");
	ml_LastPos=0;
	ml_Pos=0;
	mi_StrSz=0;
	mi_LeftPos=0;
	mi_RightPos=0;
	mc_ReadBus=0;
	mc_ReadPtiGen=0;
	mc_ReadBra=0;

}//end construction CReadFile(char *,int)

CReadFile::~CReadFile()
{
	fclose(mt_File);
}

int CReadFile::StrFindStr(char ch[],int n)//return the first position of the string in bufer ms_Str
{
	int i,j;
	for(i=0;i<=mi_StrSz-n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(ms_Str[i+j]!=ch[j]) break;
		}
		if(j==n) 
		{
			return i;
		}
	}
	return -1; ////not find string//
}////

//wangdan_2008_07_26
int  CReadFile::StrFindFristStr(char ch[],int n)
{
	int i,j;
	for(i=0;i<=mi_StrSz-n;i++)
	{
		if (ms_Str[i]!=' '&&ms_Str[i]!=ch[0])
		{
			return -1;
		}
		for(j=0;j<n;j++)
		{
			if(ms_Str[i+j]!=ch[j]) break;
		}
		if(j==n) 
		{
			return i;
		}
	}
	return -1; ////not find string//
	
}
//wangdan_2008_07_26

// +++ add by gaoyi
int CReadFile::IsVacantLine() 
{
	if ( mi_StrSz == 0 )
		return 1;
	else 
		return 0;
}

void CReadFile::StrReplace(char chFrom,char chTo)
{
	int i;
	for(i=0;i<=mi_StrSz;i++)
	{
		if(ms_Str[i]==chFrom) 
		{
			ms_Str[i]=chTo;
		}
	}
}


int CReadFile::StrFindCh(char ch,int nBgn)//return the position of a "char" in bufer ms_Str, modified by gaoyi
{        
	int i;
	for(i=nBgn;i<mi_StrSz;i++)
	{
		if(ms_Str[i]==ch) return i;
	}
	return -1;
}
int CReadFile::StrFindNotCh(char ch,int nBgn) // +++ by gaoyi, as same as up
{
	int i = 0;
	for ( i = nBgn; i < mi_StrSz; i ++ )
	{
		if ( ms_Str[i] != ch )
			return i;
	}
	return -1;
}

long CReadFile::GetFilePos()
{
	return ftell(mt_File);
}//end get mt_File position


long CReadFile::GetStrFilePos(char ch[],int n,long fm,long fe)
{
	ml_LastPos=0;
	ml_Pos=fm;
	MoveToFilePos(fm);

	while(!IsEnd())////ml_Pos!=ml_LastPos)//IsEnd()
	{
		FGetLine();
		if( StrFindStr(ch,n)!=-1 )
		{
			ml_LastPos=ml_Pos;
			ml_Pos=GetFilePos();
			return ml_Pos;
		}
	}

	return -1;
}//end fet strpos

void CReadFile::MoveToFilePos( long fp)
{
	ml_Pos=fp;
	fseek(mt_File,ml_Pos,SEEK_SET);
}


int CReadFile::IsEnd()
{
	int ri=feof(mt_File);
	return ri;////feof(mt_File); ??????
}

void CReadFile::FGetLine()
{
	int i;
	strcpy(ms_Str,"");
//	ms_Str[0] = '\0';
	fgets(ms_Str,990,mt_File);

	mi_StrSz=strlen(ms_Str);
	for(i=mi_StrSz-1; i>=0; i--)
	{
		if(ms_Str[i]!=' ' && ms_Str[i]!='\n' && ms_Str[i]!=10) break;
		if(ms_Str[i]==' ' || ms_Str[i]=='\n' || ms_Str[i]==10) ms_Str[i]=0;
		mi_StrSz=i;
	}
}//////

void CReadFile::GoBegin()
{
	MoveToFilePos(ml_BeginPos);
}

int CReadFile::FileStrToFloat()
{
	int i;
	int ikf;
	short cState; //lable can atof or not
	cState=10;

	ikf=0;
	for(i=0;i<mi_StrSz;i++)
	{
		if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
		   ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')//||
		  )
		{
			mf_AtoF[ikf]=(double)atof(&ms_Str[i]); ikf++;
			cState=0;
			if(ikf>=200) return ikf;
		}
		if(ms_Str[i]==' '||ms_Str[i]==',') cState=10;
	}//for end in str

	return ikf;
}//filestrtofloat function end//

/////////////////////////////////////////////////////////////////////////////////
int mi_iPosBus[13]={12,0, 6, 8, 17, 26,  35, 44, 47, 56, 67, 77, 84};
int mi_iPosGen[19]={18,0, 6, 8, 17, 26,  35, 44, 52, 58, 66, 74, 82, 90, 98, 106, 108, 114, 122};
int mi_iPosBra1[17]={16,0, 6, 13, 16, 26, 34, 42, 50, 58, 65, 66, 69, 79, 89,  99,  109};
int mi_iPosBra2[17]={16,0, 6, 13, 16, 26, 34, 42, 50, 58, 66, 74, 83, 93, 103, 113, 123};
int mi_iPosCons[8]={7,0,10,20,30,40,50,60};
/////////////////////////////////////////////////////////////////////////////////

int CReadFile::FileStrToBusData()   // +++ consider ',' and ' ' simultaneously, modified by gaoyi
{                                   // about reading bus name 
	int i;
	int j = 0;
	int ikf;
	int iComma=0;
	short cState; //lable can atof or not

	for(i = 0; i<200; i++)    // gjc_07_07_16
	{
		mf_AtoF[i] = 0;
	}

	cState=10;
	ikf=0;
	iComma=0;

	if ( StrFindCh(',') == -1 )
	{
		for(i=0;i<mi_StrSz;i++)
		{
			if(ms_Str[i]=='\'' && ikf == 1 && cState == 10)
			{
				iComma++;
				j = 0;

				while(ms_Str[i+1+j]!='\'')
				{
					j++;
					if ( j >= 13 )
						break;
				}
				if ( j >= 13 )
					memset(ms_BusName,0,13);
				else
				{
					memcpy(ms_BusName,&ms_Str[i+1],j);
					ms_BusName[j]=0;
				}
				i = i+1+j;
				cState=0;
				ikf++;	

			}//get bus name//

			if( cState>0 && ikf != 1 && 
				(
				  (ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
				  (ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
				  (ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
				  (ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
				  (ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
				)
			  )
			{
				mf_AtoF[ikf]=(double)atof(&ms_Str[i]); 
				ikf++;
				cState=0;
				if(ikf>=200) return ikf;
			}

			if( cState == 0 && ms_Str[i]==' ' )
			{
				cState = 10;
			}
		}
	}
	else
	{
		for(i=0;i<mi_StrSz;i++)
		{
			if(ms_Str[i]=='\'' && ikf == 1 && cState == 10)
			{
				iComma++;
				j = 0;

				while(ms_Str[i+1+j]!='\'')
				{
					j++;
					if ( j >= 13 )
						break;
				}
				if ( j >= 13 )
					memset(ms_BusName,0,13);
				else
				{
					memcpy(ms_BusName,&ms_Str[i+1],j);
					ms_BusName[j]=0;
				}
				i = i+1+j;
				cState=0;
				ikf++;				
			}//get bus name//

			if( cState>0 && ikf != 1 && 
				(
				  (ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
				  (ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
				  (ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
				  (ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
				  (ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
				)
			  )
			{
				mf_AtoF[ikf]=(double)atof(&ms_Str[i]); 
				ikf++;
				cState=0;
				if(ikf>=200) return ikf;
			}

			if( cState == 0 && ms_Str[i]==',' )
			{
				cState = 10;
			}
			else if ( cState == 10 && ms_Str[i]==',' )
			{
				if ( ikf == 1 )
				{
					memset(ms_BusName,0,9);
				}
				else if(ikf ==3 || ikf==6 || ikf==7 || ikf==8)
				{
					mf_AtoF[ikf] = 1;
				}
				else
				{
					mf_AtoF[ikf] = 0;
				}
				ikf++;
			}
		}		
	}


	return ikf;
}//filestrtobus function end//

int CReadFile::FileStrToLoadData()
{
	int i;
	int j = 0;
	int ikf;
	short cState; //lable can atof or not

	StrReplace('\'',' ');

	for(i = 0; i<200; i++)    // gjc_07_07_16
	{
		mf_AtoF[i] = 0;
	}

	cState=10;
	ikf=0;

	if ( StrFindCh(',') == -1 )
	{
		for(i=0;i<mi_StrSz;i++)
		{
			if(cState ==10 && ikf == 1)
			{
				for(j=i; j<mi_StrSz; j++)
				{
					if ( ms_Str[j] != ' ' )
					{
						memcpy(ms_Id,&ms_Str[j],2);
						ms_Id[2] = 0;
						ikf ++;
						cState = 0;
						i = j+1;
						break;
					}
				}
				if ( j == mi_StrSz )
				{
					memset(ms_Id,0,3);
					cState = 0;
					i = j;
				}
			}
			if( cState>0 && ikf != 1 && 
				(
				  (ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
				  (ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
				  (ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
				  (ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
				  (ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
				)
			  )
			{
				mf_AtoF[ikf]=(double)atof(&ms_Str[i]); 
				ikf++;
				cState=0;
				if(ikf>=200) return ikf;
			}
			if( cState == 0 && ms_Str[i]==' ' )
			{
				cState = 10;
			}
		}
	}
	else
	{
		for(i=0;i<mi_StrSz;i++)
		{
			if(cState ==10 && ikf == 1)
			{
				for(j=i; j<mi_StrSz; j++)
				{
					if ( ms_Str[j] != ' ' )
					{
						memcpy(ms_Id,&ms_Str[j],2);
						ms_Id[2] = 0;
						ikf ++;
						cState = 0;
						i = j+1;
						break;
					}
				}
				if ( j == mi_StrSz )
				{
					memset(ms_Id,0,3);
					cState = 0;
					i = j;
				}
			}
			if( cState>0 && ikf != 1 && 
				(
				  (ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
				  (ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
				  (ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
				  (ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
				  (ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
				)
			  )
			{
				mf_AtoF[ikf]=(double)atof(&ms_Str[i]); 
				ikf++;
				cState=0;
				if(ikf>=200) return ikf;
			}
			if( cState == 0 && ms_Str[i]==',' )
			{
				cState = 10;
			}
			else if ( cState == 10 && ms_Str[i]==',' )
			{
				if ( ikf == 1 )
				{
					ms_Id[0] = '1';
					ms_Id[1] = 0;
				}
				else if( ikf==2)
				{
					mf_AtoF[ikf] = 1;
				}
				else
				{
					mf_AtoF[ikf] = 0;
				}
				ikf++;
			}
		}
	}


	return ikf;
}//filestrtoload function end//


int CReadFile::FileStrToGenData()
{
	int i;
	int j;
	int ikf;
	short cState; //lable can atof or not

	for(i = 0; i<200; i++)    // gjc_07_07_16
	{
		mf_AtoF[i] = 0;
	}

	StrReplace('\'',' ');
//	StrReplace(',',' ');

	cState=10;
	ikf=0;
	if(StrFindCh(',') == -1)   // space
	{
		for(i=0;i<mi_StrSz;i++)
		{
			if( ikf == 1 && cState == 10 )
			{
				for(j=i; j<mi_StrSz; j++)
				{
					if ( ms_Str[j] != ' ' )
					{
						memcpy(ms_Id,&ms_Str[j],2);
						ms_Id[2] = 0;
						ikf ++;
						cState = 0;
						i = j+1;
						break;
					}
				}
				if ( j == mi_StrSz )
				{
					memset(ms_Id,0,3);
					cState = 0;
					i = j;
				}
			}//find gen lable
			if( cState>0 && ikf != 1 && 
				(
				  (ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
				  (ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
				  (ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
				  (ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
				  (ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
				)
			  )
			{
				mf_AtoF[ikf]=(double)atof(&ms_Str[i]); 
				ikf++;
				cState=0;
				if(ikf>=200) return ikf;
			}
			if( cState == 0 && ms_Str[i]==' ' ) 
				cState=10;
		}//for end in str
	}
	else   // ',' seperate data
	{
		for(i=0;i<mi_StrSz;i++)
		{
			if( ikf == 1 && cState == 10 )
			{
				for(j=i; j<mi_StrSz; j++)
				{
					if ( ms_Str[j] != ' ' )
					{
						memcpy(ms_Id,&ms_Str[j],2);
						ms_Id[2] = 0;
						ikf ++;
						cState = 0;
						i = j+1;
						break;
					}
				}
				if ( j == mi_StrSz )
				{
					memset(ms_Id,0,3);
					cState = 0;
					i = j;
				}
			}//find gen lable
			if( cState>0 && ikf != 1 && 
				(
				  (ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
				  (ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
				  (ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
				  (ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
				  (ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
				)
			  )
			{
				mf_AtoF[ikf]=(double)atof(&ms_Str[i]); 
				ikf++;
				cState=0;
				if(ikf>=200) return ikf;
			}
			if(ms_Str[i]==',')
			{
				if(cState == 0)
				{
					cState=10;
				}
				else
				{
					if ( ikf == 1 )
					{
						memset(ms_Id,0,3);
					}
					else if(ikf ==6 || ikf ==13 || ikf == 14)
					{
						mf_AtoF[ikf] = 1;
					}
					else if(ikf == 4 || ikf == 16)
					{
						mf_AtoF[ikf] = 9999.0;
					}
					else if(ikf == 5 || ikf ==17)
					{
						mf_AtoF[ikf] = -9999.0;
					}
					else if(ikf == 8)
					{
						mf_AtoF[ikf] = -1;
					}
					else if(ikf == 15)
					{
						mf_AtoF[ikf] = 100;
					}
					else
					{
						mf_AtoF[ikf] = 0;
					}
					ikf++;
				}
			}
		}//for end in str
	}

	return ikf;
}//filestrtofloat function end//


int CReadFile::FileStrToBraData()
{
	int i;
//	int j;
	int ikf;
	short cState; //lable can atof or not
//	int iT100L0=100;

	for(i = 0; i<200; i++)    // gjc_07_07_16
	{
		mf_AtoF[i] = 0;
	}

	cState=10;
	ikf=0;
	if(StrFindCh(',') == -1)   // space
	{
		for(i=0;i<mi_StrSz;i++)
		{
/*			if(ikf == -1)
			{
				for(j=i;j<mi_StrSz;j++)
				{
					if(ms_Str[j]==' ' && ms_Str[j+1]!=' ')
					{
						if(ms_Str[j+2]!=' ')
						{
							mf_AtoF[ikf]=double( int(ms_Str[j+1])*256+int(ms_Str[j+2]) );
							ikf++;
						}
						else
						{
							mf_AtoF[ikf]=double(int(ms_Str[j+1]));
							ikf++;
						}

						i=j+1;
						cState=0;
						break;
					}
				}
			}//find bra lable
*/
/*			if(ms_Str[i]==',' && ikf == 9) ////set non tra K and cita//
			{
				iT100L0=0;
				mf_AtoF[ikf]=1.0;
				ikf++;
				mf_AtoF[ikf]=0.0;
				ikf++; 
				cState=0;
			}
*/
			if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
			  ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
			  ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
			  ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
			  ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
			 )
			{
				mf_AtoF[ikf]=(double)atof(&ms_Str[i]); 
				ikf++;
				cState=0;
				if(ikf>=200) return ikf;
			}
			if(ms_Str[i]==' ') cState=10;
		}//for end in str
	}
	else // ',' sperate data
	{
		for(i = 0; i<mi_StrSz; i++)
		{
			if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
			  ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
			  ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
			  ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
			  ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
			 )
			{
				mf_AtoF[ikf]=(double)atof(&ms_Str[i]); 
				ikf++;
				cState=0;
				if(ikf>=200) return ikf;
			}
			if(ms_Str[i]==',') 
			{
				if(cState == 0)
				{
					cState=10;
				}
				else
				{
					if(ikf == 2 || ikf == 13)
					{
						mf_AtoF[ikf] = 1;
					}
					else mf_AtoF[ikf] = 0;
					ikf++;
				}
			}
		}
	}

//	if(fabs(mf_AtoF[9])<=0.01) mf_AtoF[9]=1.0;
	mf_AtoF[0]=(double)fabs(mf_AtoF[0]);
	mf_AtoF[1]=(double)fabs(mf_AtoF[1]);

	return ikf;  //+iT100L0;
}//filestrtofloat function end//

//
int CReadFile::FileStrToTransformerData()
{
	int i;
//	int j;
	int ikf;
	short cState; //lable can atof or not

	for(i = 0; i<200; i++)    // gjc_07_07_16
	{
		mf_AtoF[i] = 0;
	}

	cState=10;
	ikf=0;
	if(StrFindCh(',') == -1)   // space
	{
		for(i=0;i<mi_StrSz;i++)
		{

			if(ms_Str[i] == '\'')
			{
				mf_AtoF[ikf] = 0;
				ikf++;
			}
			if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
			  ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
			  ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
			  ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
			  ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
			 )
			{
				mf_AtoF[ikf]=(double)atof(&ms_Str[i]); 
				ikf++;
				cState=0;
				if(ikf>=200) return ikf;
			}
			if(ms_Str[i]==' ') cState=10;
		}//for end in str
	}
	else // ',' sperate data
	{
		for(i = 0; i<mi_StrSz; i++)
		{
			if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
			  ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
			  ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
			  ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
			  ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
			 )
			{
				mf_AtoF[ikf]=(double)atof(&ms_Str[i]); 
				ikf++;
				cState=0;
				if(ikf>=200) return ikf;
			}
			if(ms_Str[i]==',') 
			{
				if(cState == 0)
				{
					cState=10;
				}
				else
				{
					mf_AtoF[ikf] = 0;
					ikf++;
				}
			}
		}
	}

	return ikf;
}

// ++++++++++++++++++++++ For reading covDc pti-data, add by wangdan
int CReadFile::FileStrToDcCovDataLine()
{
	int i,j;
	int ikf;

	short cState; //lable can atof or not

	cState=10;
	ikf=0;
	int lab_flag=0;
	for(i=0;i<mi_StrSz;i++)
	{
		if ( ikf == 1 && cState > 0 && ms_Str[i] == '\'')  // Get DcCoverter Lab
		{
		
			for(j=i; j<mi_StrSz; j++)
				{
					if ( ms_Str[j] != ' ' )
					{
						memcpy(ms_Id,&ms_Str[j],2);
						ms_Id[2] = 0;
						ikf ++;
						cState = 0;
						i = j+1;
						break;
					}
				}
				if ( j == mi_StrSz )
				{
					memset(ms_Id,0,3);
					cState = 0;
					i = j;
				}
		}
			

		if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
		   ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
		  )
		{
			mf_AtoF[ikf]=(double)atof(&ms_Str[i]); ikf++;
			cState=0;
			if(ikf>=200) return ikf;
		}
		if(ms_Str[i]==' ' || ms_Str[i]==',') cState=10;
	}//for end in str

	return ikf;
}
// ++++++++++++++++++++++ For reading covDc pti-data, add by wangdan

/*
int CReadFile::FileStrToBusData()
{
	int i;
	int ikf;
	int iComma=0;
	short cState; //lable can atof or not

	cState=10;
	ikf=0;
	iComma=0;
	for(i=0;i<mi_StrSz;i++)
	{
		if(ms_Str[i]=='\'')
		{
			iComma++;
			if(iComma==1) 
			{
				memcpy(ms_BusName,&ms_Str[i+1],8);
				ms_BusName[8]=0;
				cState=0;
				ikf++;
			}
		}//get bus name//

		if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
		   ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
		  )
		{
			mf_AtoF[ikf]=(double)atof(&ms_Str[i]); ikf++;
			cState=0;
			if(ikf>=200) return ikf;
		}
		if(ms_Str[i]==' ' && iComma!=1) cState=10;
	}//for end in str

	return ikf;
}//filestrtofloat function end//


int CReadFile::FileStrToGenData()
{
	int i;
	int j;
	int ikf;
	short cState; //lable can atof or not

	cState=10;
	ikf=0;
	for(i=0;i<mi_StrSz;i++)
	{
		if(ikf == 1)
		{
			for(j=i;j<mi_StrSz;j++)
			{
				if(ms_Str[j]==' ' && ms_Str[j+1]!=' ')
				{
					mf_AtoF[ikf]=double(int(ms_Str[j+1]));
					ikf++;
					i=j+1;
					cState=0;
					break;
				}
			}
		}//find gen lable
		if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
		   ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
		  )
		{
			mf_AtoF[ikf]=(double)atof(&ms_Str[i]); 
			ikf++;
			cState=0;
			if(ikf>=200) return ikf;
		}
		if(ms_Str[i]==' ') cState=10;
	}//for end in str

	return ikf;
}//filestrtofloat function end//


int CReadFile::FileStrToBraData()
{
	int i;
	int j;
	int ikf;
	short cState; //lable can atof or not
	int iT100L0=100;

	cState=10;
	ikf=0;
	for(i=0;i<mi_StrSz;i++)
	{
		if(ikf == -1)
		{
			for(j=i;j<mi_StrSz;j++)
			{
				if(ms_Str[j]==' ' && ms_Str[j+1]!=' ')
				{
					if(ms_Str[j+2]!=' ')
					{
						mf_AtoF[ikf]=double( int(ms_Str[j+1])*256+int(ms_Str[j+2]) );
						ikf++;
					}
					else
					{
						mf_AtoF[ikf]=double(int(ms_Str[j+1]));
						ikf++;
					}

					i=j+1;
					cState=0;
					break;
				}
			}
		}//find bra lable

		if(ms_Str[i]==',' && ikf == 9) ////set non tra K and cita//
		{
			iT100L0=0;
			mf_AtoF[ikf]=1.0;
			ikf++;
			mf_AtoF[ikf]=0.0;
			ikf++; 
			cState=0;
		}

		if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
		   ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
		  )
		{
			mf_AtoF[ikf]=(double)atof(&ms_Str[i]); 
			ikf++;
			cState=0;
			if(ikf>=200) return ikf;
		}
		if(ms_Str[i]==' ') cState=10;
	}//for end in str

	if(fabs(mf_AtoF[9])<=0.01) mf_AtoF[9]=1.0;
	mf_AtoF[0]=(double)fabs(mf_AtoF[0]);
	mf_AtoF[1]=(double)fabs(mf_AtoF[1]);

	return ikf+iT100L0;
}//filestrtofloat function end//
*/

/****************************************/

///////////////////////////////////////
///// if( there is '.' && '0'<=( right of '.' ||left of '.')<='9') use f10.5 format function
///// else use no format function
/////
/////if(this line iNum>=3 && Next Line iNum>=12) GenData Begin
///////////////////////////////////////
int CReadFile::DATStrToGenData()
{
	int iNum;

	//DEDatGenED
	if( StrFindStr(DEDatGenED,strlen(DEDatGenED)) >=0 ) return -1;

	if(strpbrk(".",ms_Str))
	{
		iNum=FormatDATStrToGenData();
	}
	else
	{
		iNum=UnFormatDATStrToGenData();
	}
	
	if(iNum!=12) memcpy(ms_StrBK,ms_Str,199);

	return iNum;
}////


int CReadFile::FormatDATStrToGenData()
{
	int i;
	int iNum=0;
	int idformat=10;
	char sAu[13];

	iNum=0;
	for(i=0;i<mi_StrSz;i=i+idformat)
	{
		////mf_AtoF[iNum]=(double)atof(&ms_Str[i]);

		sAu[0]=0;
		strncpy(sAu,&ms_Str[i],10);
		sAu[10]=0;
		mf_AtoF[iNum]=(double)atof(sAu);

		iNum++;
	}//for end in str
	
	return iNum;
}//filestrtofloat function end//

int CReadFile::UnFormatDATStrToGenData()
{
	int i;
	int iNum;
	short cState; //lable can atof or not

	iNum=0;
	cState=10;
	for(i=0;i<mi_StrSz;i++)
	{
		if( cState>0 && 
			( (ms_Str[i]>='0'&&ms_Str[i]<='9') 
			  || (ms_Str[i]=='-' && ms_Str[i+1]>='0' && ms_Str[i+1]<='9')
			  || (ms_Str[i]=='.' && ms_Str[i+1]>='0' && ms_Str[i+1]<='9')
			)
		  ) 
		{
			mf_AtoF[iNum]=(double)atof(&ms_Str[i]); iNum++;
			cState=0;
			if(iNum>=200) return iNum;
		}
		if(ms_Str[i]==' '||ms_Str[i]==9) cState=10;
	}//for end in str
	return iNum;
}//filestrtofloat function end//

int CReadFile::FileStrToInsData()
{
	int i;
	int iNum;

	if(FileStrToFloat()==0) return 0;
	iNum=mi_iPosCons[0];

	for(i=0;i<iNum;i++)
	{
		if(mi_StrSz>=mi_iPosCons[i+1])
		{
			mf_AtoF[i]=(double)atof(&ms_Str[mi_iPosCons[i+1]]);
		}
		else
		{
			mf_AtoF[i]=0; 
		}
	}//for end in str

	if(ms_Str[50]==' ' && ms_Str[51]==' ') mf_AtoF[5]=1;  // double(' ');   // gjc_070807
	else mf_AtoF[5]=(double)atof(&ms_Str[50]);
//	else if(ms_Str[50]==' ' && ms_Str[51]!=' ') mf_AtoF[5]=double(ms_Str[51]);
//	else if(ms_Str[50]!=' ' && ms_Str[51]==' ') mf_AtoF[5]=double(ms_Str[50]);
//	else mf_AtoF[5]=double( int(ms_Str[50])*256+int(ms_Str[51]) );

	return iNum;
}//filestrtofloat function end//

// gjc
int  CReadFile::DatParemeter(char paraID[], int n,long fp)
{
//	int i;
	int strPos;
//	int comstrPos;
	char cTemp[1000];
	MoveToFilePos(fp);
	FGetLine();
/*	comstrPos = StrFindStr("'",1);
	strPos = StrFindStr(paraID, n);
	if(comstrPos>strPos)
	{
		for(i=0; i<=comstrPos;i++)
		{
			ms_Str[i] = ' ';
		}
	}
	strPos = StrFindStr("'",1);
	for(i=0; i<=strPos;i++)
	{
		ms_Str[i] = ' ';
	}
	strPos = StrFindStr(paraID, n);
	strncpy(cTemp, &ms_Str[strPos+n], (mi_StrSz-strPos-n));
	cTemp[mi_StrSz-strPos-n+1] = 0;
*/
	strncpy(cTemp, &ms_Str[0], mi_StrSz);
	cTemp[mi_StrSz] = ' ';
	cTemp[mi_StrSz+1] = 0;
	while(StrFindCh('/') == -1)
	{
		FGetLine();
		ms_Str[mi_StrSz+1] = 0;
		strncat(cTemp, ms_Str, mi_StrSz);
	}
	// deal
	strncpy(ms_Str, cTemp, strlen(cTemp));
	ms_Str[strlen(cTemp)+1] = 0;
	mi_StrSz = strlen(ms_Str);
	strPos = StrFindCh('/');
	ms_Str[strPos] = 0;
	mi_StrSz = strlen(ms_Str);
	return FileStrToFloat();
}

int CReadFile::FileStrToAreaInterchange()
{
	int i;
	int ikf;

	short cState; //lable can atof or not

	cState=10;
	ikf=0;


	for(i=0;i<mi_StrSz;i++)
	{
		if ( ikf == 4 && cState > 0 && ms_Str[i] == '\'' )  // Get meter
		{
			int j = 1;
			while ( ms_Str[j+i] != '\'' )
			{
				ms_ArName[j-1] = ms_Str[j+i];
				j ++;
			}
			ms_ArName[j-1] = 0;
			i += j + 1;
			ikf ++, cState = 0;
		}
		if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
		   ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
		  )
		{
			mf_AtoF[ikf]=(double)atof(&ms_Str[i]); ikf++;
			cState=0;
			if(ikf>=200) return ikf;
		}
		if(ms_Str[i]==' ' || ms_Str[i]==',') cState=10;
	}//for end in str

	return ikf;
}
int CReadFile::FileStrToSwtShnt()
{
	int i;
	int ikf;

	short cState; //lable can atof or not

	cState=10;
	ikf=0;


	for(i=0;i<mi_StrSz;i++)
	{
		if ( ikf == 5 && cState > 0 && ms_Str[i] == '\'' )  // Get meter
		{
			int j = 1;
			while ( ms_Str[j+i] != '\'' )
			{
				ms_Rmidnt[j-1] = ms_Str[j+i];
				j ++;
			}
			ms_Rmidnt[j-1] = 0;
			i += j + 1;
			ikf ++, cState = 0;
		}
		if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
		   ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
		  )
		{
			mf_AtoF[ikf]=(double)atof(&ms_Str[i]); ikf++;
			cState=0;
			if(ikf>=200) return ikf;
		}
		if(ms_Str[i]==' ' || ms_Str[i]==',') cState=10;
	}//for end in str

	return ikf;
}

int CReadFile::FileStrToTrsfImpdc()
{
	int i;
	int ikf;

	short cState; //lable can atof or not

	cState=10;
	ikf=0;


	for(i=0;i<mi_StrSz;i++)
	{
		if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
		   ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
		  )
		{
			mf_AtoF[ikf]=(double)atof(&ms_Str[i]); ikf++;
			cState=0;
			if(ikf>=200) return ikf;
		}
		if(ms_Str[i]==' ' || ms_Str[i]==',') cState=10;
	}//for end in str

	return ikf;
}
int CReadFile::FileStrToMultSctLn()
{
	int i;
	int ikf;

	short cState; //lable can atof or not

	cState=10;
	ikf=0;


	for(i=0;i<mi_StrSz;i++)
	{
		if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
		   ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
		  )
		{
			mf_AtoF[ikf]=(double)atof(&ms_Str[i]); ikf++;
			cState=0;
			if(ikf>=200) return ikf;
		}
		if(ms_Str[i]==' ' || ms_Str[i]==',') cState=10;
	}//for end in str

	return ikf;
}
int CReadFile::FileStrToZone()
{
	int i;
	int ikf;

	short cState; //lable can atof or not

	cState=10;
	ikf=0;


	for(i=0;i<mi_StrSz;i++)
	{
		if ( ikf == 1 && cState > 0 && ms_Str[i] == '\'' )  // Get meter
		{
			int j = 1;
			while ( ms_Str[j+i] != '\'' )
			{
				ms_Rmidnt[j-1] = ms_Str[j+i];
				j ++;
			}
			ms_Rmidnt[j-1] = 0;
			i += j + 1;
			ikf ++, cState = 0;
		}
		if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
		   ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
		  )
		{
			mf_AtoF[ikf]=(double)atof(&ms_Str[i]); ikf++;
			cState=0;
			if(ikf>=200) return ikf;
		}
		if(ms_Str[i]==' ' || ms_Str[i]==',') cState=10;
	}//for end in str

	return ikf;
}
// ++++++++++++++++++++++ For reading Dc2 pti-data, add by Gaoyi
int CReadFile::FileStrToDc2DataLine1()
{
	int i;
	int ikf;

	short cState; //lable can atof or not

	cState=10;
	ikf=0;

	for(i=0;i<mi_StrSz;i++)
	{
		if ( (ikf == 8) && (cState > 0) )  // Get meter
		{
			if (ms_Str[i] == 'R' || ms_Str[i] == 'I')
			{
				mc_Meter = ms_Str[i];
			}
		}

		if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
		   ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
		  )
		{
			mf_AtoF[ikf]=(double)atof(&ms_Str[i]); ikf++;
			cState=0;
			if(ikf>=200) return ikf;
		}
		if(ms_Str[i]==' ' || ms_Str[i]==',') cState=10;
	}//for end in str

	return ikf;
}
int CReadFile::FileStrToDc2DataLine2()
{
	int i;
	int ikf;

	short cState; //lable can atof or not

	cState=10;
	ikf=0;

	for(i=0;i<mi_StrSz;i++)
	{
		if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
		   ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
		  )
		{
			mf_AtoF[ikf]=(double)atof(&ms_Str[i]); ikf++;
			cState=0;
			if(ikf>=200) return ikf;
		}
		if(ms_Str[i]==' ' || ms_Str[i]==',') cState=10;
	}//for end in str

	return ikf;
}
int CReadFile::FileStrToDc2DataLine3()
{
	int i;
	int ikf;

	short cState; //lable can atof or not

	cState=10;
	ikf=0;

	for(i=0;i<mi_StrSz;i++)
	{
		if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
		   ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
		  )
		{
			mf_AtoF[ikf]=(double)atof(&ms_Str[i]); ikf++;
			cState=0;
			if(ikf>=200) return ikf;
		}
		if(ms_Str[i]==' ' || ms_Str[i]==',') cState=10;
	}//for end in str

	return ikf;
}
// ++++++++++++++++++++++ For reading Dc2 pti-data, add by Gaoyi


// ++++++++++++++++++++++ For reading Dcm pti-data, add by Gaoyi
int CReadFile::FileStrToDcmDataLine()
{
	int i;
	int ikf;

	short cState; //lable can atof or not

	cState=10;
	ikf=0;

	for(i=0;i<mi_StrSz;i++)
	{
		if ( ikf == 4 && cState > 0 && ms_Str[i] == '\'' )  // Get meter
		{
			int j = 1;
			while ( ms_Str[j+i] != '\'' )
			{
				ms_DcBusName[j-1] = ms_Str[j+i];
				j ++;
			}
			ms_DcBusName[j-1] = 0;
			i += j + 1;
			ikf ++, cState = 0;
		}
		else if ( ikf == 2 && cState > 0 && ms_Str[i] == '\'' )
		{
			mc_DcBrId = ms_Str[i+1];
			i = i + 3;
			ikf ++, cState = 0;
		}
		if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
		   ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
		  )
		{
			mf_AtoF[ikf]=(double)atof(&ms_Str[i]); ikf++;
			cState=0;
			if(ikf>=200) return ikf;
		}
		if(ms_Str[i]==' ' || ms_Str[i]==',') cState=10;
	}//for end in str

	return ikf;
}
// ++++++++++++++++++++++ For reading Dcm pti-data, add by Gaoyi


// ++++++++++++++++++++++ For reading vscDc pti-data, add by Gaoyi
int CReadFile::FileStrToDcVscDataLine()
{
	int i;
	int ikf;

	short cState; //lable can atof or not

	cState=10;
	ikf=0;

	for(i=0;i<mi_StrSz;i++)
	{
		if ( ikf == 0 && cState > 0 && ms_Str[i] == '\'' )  // Get meter
		{
			int j = 1;
			while ( ms_Str[j+i] != '\'' )
			{
				ms_VscDcName[j-1] = ms_Str[j+i];
				j ++;
			}
			ms_DcBusName[j-1] = 0;
			i += j + 1;
			ikf ++, cState = 0;
		}

		if(( cState>0 && ms_Str[i]>='0' && ms_Str[i]<='9' ) ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='-') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='.') ||
		   ( cState>0 && ms_Str[i+1]>='0' && ms_Str[i+1]<='9' && ms_Str[i]=='+') ||
		   ( cState>0 && ms_Str[i+2]>='0' && ms_Str[i+2]<='9' && ms_Str[i+1]<='.' && ms_Str[i]=='-')
		  )
		{
			mf_AtoF[ikf]=(double)atof(&ms_Str[i]); ikf++;
			cState=0;
			if(ikf>=200) return ikf;
		}
		if(ms_Str[i]==' ' || ms_Str[i]==',') cState=10;
	}//for end in str

	return ikf;
}
// ++++++++++++++++++++++ For reading vscDc pti-data, add by Gaoyi




