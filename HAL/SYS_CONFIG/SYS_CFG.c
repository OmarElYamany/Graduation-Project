/*
 * SYS_CFG.c
 *
 *  Created on: Jun 23, 2023
 *      Author: Omar El Yamany
 */

#include "SYS_CFG.h"


void SYSCfg_init(void)
{
	RCC_EnableSysClk(clk_HSI);

	RCC_SelectSysClk(sys_clk_HSI);
	RCC_SetAHBPrescaler(AHB_Pre_1);

	RCC_EnableAPB2PerClk(APB2ENRper_clk_RCC_IOPAEN, APB2_Pre_1);
	RCC_EnableAPB1PerClk(APB1ENRper_clk_RCC_TIM2EN, APB1_Pre_1);
	RCC_EnableAPB1PerClk(APB1ENRper_clk_RCC_TIM3EN, APB1_Pre_1);
	RCC_EnableAPB2PerClk(APB2ENRper_clk_RCC_USART1EN, APB2_Pre_1);
	Ultrasonic_init(GPIO_PortA, GPIO_Pin3, GPIO_Mode_IN, GPIO_Config_INPPullUpDown, GPIO_Pin4, GPIO_Mode_OUT10, GPIO_Config_GenOUTPushPull);
	USART_init(USART1, 9600, 8000000, bits_8, STOP_1bit);
	USART_RXInterruptEnable();
	TIMERx_config(Timer2, TIMERx_ClockDiv_1, TIMERx_Mode_EdgeAlig, TIMERx_Dir_UpCounting);

	MotorCfg(Timer2, GPIO_PortA, GPIO_Pin0, GPIO_Pin1, GPIO_Pin2);

}
