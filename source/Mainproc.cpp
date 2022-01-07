#include "math.h"//
#include "time.h"
#include "stdio.h"//standard input output
#include "string.h"//
#include "stdlib.h"//standard library
#include "iostream"//
using namespace std;


#include "GlobalVariables.h"
#include "Sys_file.h"
#include "ParType.h"
#include "ParFile.h"
#include "Optimization.h"
#include "Output.h"




//#include "../include/CofMatric.h"
//#include "../include/Output.h"

#define PROJECTFILE_NOT_EXIST  "Error: The project file <%s> does not exist!\n"

/*************************************************************************************************************
*
* Function int main(int argc, TCHAR* argv[], TCHAR* envp[])
*
* Description:	the main entry of optimization program
*
* Input:		argc --- the number of input parameters including the program name
*				argv --- an array of null-terminated strings for input parameters
*					the first string (argv[0]) is the program name,
*					and each following string is an argument passed to the program from the command line
*				envp --- a pointer to an array of environment strings
*
* Return:		0    --- success
*				1    --- failure
*
* Creator:		ZZQ
* Date:         210831
*
* Modification lists including
*	No.		Modifier			Date			Modification description
*
*************************************************************************************************************/
void ShowRights();

int main(int argc, char* argv[], char* envp[])
{
	ShowRights();

	strcpy(comment, argv[1]);
	strcpy(comment_store, comment);

	strcpy(comment, comment_store);
	strcat(comment, "/output/Error.log");

	//printf("%s", comment);

	//if ((erroLog = fopen("../output/Error.log", "w")) == NULL)
	if ((erroLog = fopen(comment, "w")) == NULL)
	{
		printf("\nCannot open errorlog data file");
		exit(1);//程序非正常退出
	}

	strcpy(comment, comment_store);
	strcat(comment, "/output/Iteration.log");
	//if ((iterLog = fopen("../output/Iteration.log", "w")) == NULL)
	if ((iterLog = fopen(comment, "w")) == NULL)
	{
		printf("\nCannot open iterationlog data file");
		exit(1);//程序非正常退出
	}

	strcpy(comment, comment_store);
	strcat(comment, "/output/Runtime.log");
	//if ((runtLog = fopen("../output/Runtime.log", "w")) == NULL)
	if ((runtLog = fopen(comment, "w")) == NULL)
	{
		printf("\nCannot open runtimelog data file");
		exit(1);//程序非正常退出
	}


	double totaltime = 0.0;
	clock_t start;
	clock_t finish;
	start = clock();

	//调用数据读入部分
	C_ParFile* pParFile = new C_ParFile();
	pParFile->GetInfor();
	delete pParFile;
	pParFile = NULL;

	//调用计算部分
	printf("\nOptimization Begin...\n");
	fprintf(iterLog, "运行优化开始...\n");

	Optimization* pOptimization = new Optimization;
	pOptimization->OptimizationProc();
	delete pOptimization;
	pOptimization = NULL;

	printf("\nOptimization End...\n");
	fprintf(iterLog, "运行优化结束...\n");

	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	fprintf(runtLog, "运行优化计算时间 %lfs\n", totaltime);

	fclose(erroLog);
	fclose(iterLog);
	fclose(runtLog);

	return 0;
}