#if _MSC_VER > 1000
#pragma once
#endif

#if !defined(AFX__DOPTIMIZATION_H__22SF47IDV_LW53K_8UK0T_2M0PB_264YA5C64E__INCLUDED_)
#define AFX__DOPTIMIZATION_H__22SF47IDV_LW53K_8UK0T_2M0PB_264YA5C64E__INCLUDED_

#include "../include/Output.h"

class Optimization
{
public:
	Optimization();
	virtual ~Optimization();

	int OptimizationProc();                        //ͳ���Ż�����
	void NodeOrder();                              //�ڵ�����
	void LocalOptimization();                      //�͵��Ż�����
	void CloudOptimization();                      //�ƶ��Ż�����
	void IterBasedOptimization();                  //���ڵ������Ż�����
	void SolverBasedOptimization();                //������������Ż�����
	void GenDeadComb();                            //���ɷֲ�ʽ��Դ�������
	void NewMatrix();							   //���Ż������еľ�������ڴ����(����ʹ�ú����ʹ��)
	void ReleaseMatrix();						   //���Ż������еľ����ڴ�����ͷ�(����ʹ��)

	void BacForSweep();                            //����ǰ�ƻش����⳱��
	void TuneCtrlDvcStrategy();							   //���������ɿ��豸�ĳ�������
	double GetGValue(double U0, double Ulow, double Uup);	  //����ֲ�ʽ��Դ���޹�����

private:

	int **Queue;
	int  *Queue2;

	double** DeadZooomCombs;
	double* DeadZooomPoint; //�ֲ�ʽ��������б�

	//�ڵ��ע�빦��
	double** NodePowerP;
	double** NodePowerQ;

	//���������еĽڵ㹦��
	double** NodePowerP_iter;
	double** NodePowerQ_iter;

	//�ڵ��ѹ
	double** NodeVoltAmp;//��ֵ

	//��·����
	double** LineP;		  //��·�й�
	double** LineQ;		  //��·�޹�

	double** LinePloss;		  //��·�й����
	double** LineQloss;		  //��·�޹����

	double** LineI;		  //��·����
	

	int DeadZoomCombnum ; //�������������������
	int numOptmz;// ���ڴ洢���Ż�������
	int DGnumOptmz;// ���ڴ洢DG�Ż�������
	int SOPnumOptmz;// ���ڴ洢SOP�Ż�������
	int numOptmzstorg; // ���ڴ洢�Ż�����Ĵ洢λ��
	double Vlow;
	double Vup;
	double Qbase;

	double* ObjmatPLoss;  //������������Ŀ�꺯��
	double* ObjmatVDev;   //����������ѹƫ��Ŀ�꺯��
	double* ObjmatIcay;   //�����������ؾ���Ŀ�꺯��
	double* Objmat;       //����������Ŀ�꺯��

	COutput *pOutput;

	//FILE* pF ;  //���ʹ��


};






#endif