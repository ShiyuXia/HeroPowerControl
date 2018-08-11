#include "led.h"

/**
  * @brief  LED��ʼ��
  * @param  ��
  * @retval ��
 **/
void Led_Configuration(void)
{
  GPIO_InitTypeDef gpio;
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOE,ENABLE);
	
	gpio.GPIO_Pin = GPIO_Pin_9 ;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&gpio);
	gpio.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOE,&gpio);
	
	LED0 = 1;
	LASER = 1;
}
