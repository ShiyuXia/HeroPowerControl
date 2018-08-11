#include "bsp_init.h"
#include "task.h"
#include "pid.h"
#include "remote.h"
#include "sys.h"
#include "includes.h"


int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	
	RemoteDataInit();
	ChassisDataInit();
	BSP_Init();
	
	OSInit(&err);		//��ʼ��UCOSIII
	OS_CRITICAL_ENTER();//�����ٽ���
	start_Task_Create();	//������ʼ����
	OS_CRITICAL_EXIT();	//�˳��ٽ���	 
	OSStart(&err);  //����UCOSIII
	while(1);
}
