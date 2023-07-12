/*
 * RCC_Private1.h
 *
 *  Created on: May 21, 2023
 *      Author: Omar El Yamany
 */

#ifndef RCC_RCC_H_
#define RCC_RCC_H_
#include "../../Common/STD_Types.h"
#include "../../Common/definition.h"
#include "../../Common/util.h"

//clock selection for enabling and disabling
#define clk_HSI		0
#define clk_HSE		1
#define clk_PLL		2

//System clock source
#define sys_clk_HSI	0x00
#define sys_clk_HSE	0x01
#define sys_clk_PLL	0x02

//PLL source
#define pll_src_HSI	0
#define pll_src_HSE	1

//PLL multiplexer
#define pllmul_2	0x00
#define pllmul_3	0x01
#define pllmul_4	0x02
#define pllmul_5	0x03
#define pllmul_6	0x04
#define pllmul_7	0x05
#define pllmul_8	0x06
#define pllmul_9	0x07
#define pllmul_10	0x08
#define pllmul_11	0x09
#define pllmul_12	0x0a
#define pllmul_13	0x0b
#define pllmul_14	0x0c
#define pllmul_15	0x0d
#define pllmul_16	0x0e

//HSE scaler
#define HSEDiv_0	0
#define HSEDiv_2	2

//AHB prescaler
#define AHB_Pre_1				0x00
#define AHB_Pre_2				0x08
#define AHB_Pre_4				0x09


//AHB peripherals enable
#define AHBENRper_clk_RCC_DMA1EN	BIT0_MASK
#define AHBENRper_clk_RCC_DMA2EN  	BIT1_MASK
#define AHBENRper_clk_RCC_SRAMEN  	BIT2_MASK
#define AHBENRper_clk_RCC_FLITFEN 	BIT4_MASK
#define AHBENRper_clk_RCC_CRCEN   	BIT6_MASK
#define AHBENRper_clk_RCC_FSMCEN  	BIT8_MASK
#define AHBENRper_clk_RCC_SDIOEN  	BIT10_MASK



//APB2 prescaler
#define APB2_Pre_1				0x00
#define APB2_Pre_2				0x04
#define APB2_Pre_4				0x05
#define APB2_Pre_8				0x06
#define APB2_Pre_16				0x07

//APB2 Bus bits
#define APB2ENRper_clk_RCC_AFIOEN	  	BIT0_MASK
#define APB2ENRper_clk_RCC_IOPAEN	  	BIT2_MASK
#define APB2ENRper_clk_RCC_IOPBEN  		BIT3_MASK
#define APB2ENRper_clk_RCC_IOPCEN  		BIT4_MASK
#define APB2ENRper_clk_RCC_IOPDEN  		BIT5_MASK
#define APB2ENRper_clk_RCC_IOPEEN  		BIT6_MASK
#define APB2ENRper_clk_RCC_IOPFEN 		BIT7_MASK
#define APB2ENRper_clk_RCC_IOPGEN		BIT8_MASK
#define APB2ENRper_clk_RCC_ADC1EN	  	BIT9_MASK
#define APB2ENRper_clk_RCC_ADC2EN		BIT10_MASK
#define APB2ENRper_clk_RCC_TIM1EN		BIT11_MASK
#define APB2ENRper_clk_RCC_SPI1EN		BIT12_MASK
#define APB2ENRper_clk_RCC_TIM8EN		BIT13_MASK
#define APB2ENRper_clk_RCC_USART1EN  	BIT14_MASK
#define APB2ENRper_clk_RCC_ADC3EN		BIT15_MASK
#define APB2ENRper_clk_RCC_TIM9EN		BIT19_MASK
#define APB2ENRper_clk_RCC_TIM10EN		BIT20_MASK
#define APB2ENRper_clk_RCC_TIM11EN		BIT21_MASK

//APB1 prescaler
#define APB1_Pre_1				0x00
#define APB1_Pre_2				0x04
#define APB1_Pre_4				0x05
#define APB1_Pre_8				0x06
#define APB1_Pre_16				0x07

//APB1 Bus bits
#define APB1ENRper_clk_RCC_TIM2EN		BIT0_MASK
#define APB1ENRper_clk_RCC_TIM3EN		BIT1_MASK
#define APB1ENRper_clk_RCC_TIM4EN		BIT2_MASK
#define APB1ENRper_clk_RCC_TIM5EN		BIT3_MASK
#define APB1ENRper_clk_RCC_TIM6EN		BIT4_MASK
#define APB1ENRper_clk_RCC_TIM7EN		BIT5_MASK
#define APB1ENRper_clk_RCC_TIM12EN		BIT6_MASK
#define APB1ENRper_clk_RCC_TIM13EN		BIT7_MASK
#define APB1ENRper_clk_RCC_TIM14EN		BIT8_MASK
#define APB1ENRper_clk_RCC_WWDGEN		BIT11_MASK
#define APB1ENRper_clk_RCC_SPI2EN  		BIT14_MASK
#define APB1ENRper_clk_RCC_SPI3EN		BIT15_MASK
#define APB1ENRper_clk_RCC_USART2EN		BIT17_MASK
#define APB1ENRper_clk_RCC_USART3EN		BIT18_MASK
#define APB1ENRper_clk_RCC_USART4EN		BIT19_MASK
#define APB1ENRper_clk_RCC_USART5EN		BIT20_MASK
#define APB1ENRper_clk_RCC_I2C1EN		BIT21_MASK
#define APB1ENRper_clk_RCC_I2C2EN		BIT22_MASK
#define APB1ENRper_clk_RCC_USBEN		BIT23_MASK
#define APB1ENRper_clk_RCC_CANEN 		BIT25_MASK
#define APB1ENRper_clk_RCC_BKPEN		BIT27_MASK
#define APB1ENRper_clk_RCC_PWREN 		BIT28_MASK
#define APB1ENRper_clk_RCC_DACEN		BIT29_MASK







res_t RCC_EnableSysClk(u32 clk);
res_t RCC_DisableSysClk(u32 clk);
res_t RCC_SelectSysClk(u32 sys_clk);
res_t RCC_CfgPLL(u32 pll_src, u32 pllmul , u32 HSEDiv);
res_t RCC_EnableAHBPerClk(u32 AHBENRper_clk, u32 AHB_Pre);
res_t RCC_SetAHBPrescaler( u32 AHB_Pre);
res_t RCC_EnableAPB2PerClk(u32 APB2ENRper_clk , u32 APB2_Pre);
res_t RCC_EnableAPB1PerClk(u32 APB1ENRper_clk , u32 APB1_Pre);


#endif /* RCC_RCC_H_ */
