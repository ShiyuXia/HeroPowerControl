#ifndef _TASK_H__
#define _TASK_H__

#include "sys.h"
#include "includes.h"

/*---------------------------------------------------------*/
//�������ȼ�
#define START_TASK_PRIO		3
//�����ջ��С	
#define START_STK_SIZE 		256

void start_task(void *p_arg);
void start_Task_Create(void);
/*---------------------------------------------------------*/
//�������ȼ�
#define CONTROL_TASK_PRIO		4
//�����ջ��С
#define CONTROL_STK_SIZE 		512

extern OS_TCB ControlTaskTCB;

void control_task(void *p_arg);
void control_task_create(void);
/*---------------------------------------------------------*/
//�������ȼ�
#define CAN2_TASK_PRIO		7
//�����ջ��С
#define CAN2_STK_SIZE 		256

void can2_task(void *p_arg);
void can2_task_create(void);
/*---------------------------------------------------------*/
//�������ȼ�
#define USART2_TASK_PRIO		8
//�����ջ��С
#define USART2_STK_SIZE 		256

void usart2_task(void *p_arg);
void usart2_task_create(void);
/*---------------------------------------------------------*/
//�������ȼ�
#define MONITOR_TASK_PRIO		10
//�����ջ��С	
#define MONITOR_STK_SIZE 		256

void monitor_task(void *p_arg);
void monitor_task_create(void);
/*---------------------------------------------------------*/
//�������ȼ�
#define LED_TASK_PRIO		11
//�����ջ��С	
#define LED_STK_SIZE 		128

extern OS_TCB LedTaskTCB;

void led_task(void *p_arg);
void led_task_create(void);
/*---------------------------------------------------------*/
//�������ȼ�
#define PRINT_TASK_PRIO		12
//�����ջ��С	
#define PRINT_STK_SIZE 		512

void print_task(void *p_arg);
void print_task_create(void);
/*---------------------------------------------------------*/

#endif
