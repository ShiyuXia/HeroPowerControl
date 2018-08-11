#ifndef __PID_H__
#define __PID_H__

#include "sys.h"
#include "can.h"

/********����ʽ********/
typedef struct
{
	float kp;
	float ki;
	float kd;	
	float errILim;
	
	float errNow; 
	float ctrOut;
	
	float errOld;
	float errP;
	float errI;
	float errD;

	float MaxOut;
}PID_AbsoluteType;
typedef struct
{
	PID_AbsoluteType	LefUpPid;   //����pid
	PID_AbsoluteType	LefDoPid;	//����pid
	PID_AbsoluteType	RigUpPid;   //����pid
	PID_AbsoluteType	RigDoPid;   //����pid

	int16_t LimtOutValue;//���ƹ��ʺ�����е����������ܺ�
	float 	MergeFinalOutValue;//���е����������ܺ�
	int16_t LefUpFinalOutValue;		//����������ֵ
	int16_t LefDoFinalOutValue;		//����������ֵ
	int16_t RigUpFinalOutValue;		//����������ֵ
	int16_t RigDoFinalOutValue;		//����������ֵ
	
	int16_t LefUpBackSpeed; //can���߷����ٶ�
	int16_t LefDoBackSpeed;
	int16_t RigUpBackSpeed;
	int16_t	RigDoBackSpeed;
}ChassisParam_Struct;

extern ChassisParam_Struct chassisparam;;

void PID_AbsoluteMode(PID_AbsoluteType *);
void ChassisDataInit(void);
void ChassisController(void);                       //���̿���
void ChassisPwm(int16_t,int16_t,int16_t,int16_t);   //���ͺ���
void ChassisPidCtr(int16_t,int16_t,int16_t,int16_t);//����pid����

#endif
