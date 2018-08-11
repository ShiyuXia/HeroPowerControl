#include "bsp_init.h"
#include "control.h"
#include "remote.h"

/**
  * @brief  �ײ�������ʼ��
  * @param  ��
  * @retval ��
 **/
void BSP_Init(void)
{
	delay_init(168);       //��ʱ��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�жϷ�������
	#if IS_OPEN_CAN2_TASK
	CAN2_Configuration();
	#endif
	delay_ms(100);
	
	Led_Configuration();    //LED��ʼ��
	USART1_Configuration();
	delay_ms(50);
	#if IS_OPEN_USART2_TASK
	USART2_Configuration();
	delay_ms(50);
	#endif
	TIM6_Configuration();
	delay_ms(4300);
	TIM6_Start();
}
