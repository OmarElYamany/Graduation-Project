/*
 * GPIO.c
 *
 *  Created on: May 26, 2023
 *      Author: Omar El Yamany
 */

//includes
#include "GPIO.h"

#include "../../MCAL/RCC/RCC.h"






//defines

#define GPIOA_BaseAdd     (0x40010800)
#define GPIOB_BaseAdd     (0x40010C00)
#define GPIOC_BaseAdd     (0x40011000)
#define CRLRegShift		    0x02
#define GPIO_CRL_LENGTH		0x03





//types

typedef struct
{
	volatile u32 CRL;
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCKR;
}GPIOx_Struct;

//variables


static volatile GPIOx_Struct * const GPIOA_Ptr = (volatile GPIOx_Struct * const) GPIOA_BaseAdd;
static volatile GPIOx_Struct * const GPIOB_Ptr = (volatile GPIOx_Struct * const) GPIOB_BaseAdd;
static volatile GPIOx_Struct * const GPIOC_Ptr = (volatile GPIOx_Struct * const) GPIOC_BaseAdd;

//static functions implementation




// interface functions implementation
res_t GPIO_SetPin(u8 GPIO_Port,u32 GPIO_Pin, u8 GPIO_Mode , u8 GPIO_Config)
{
	u8 errstate = res_ERROR;
	u32 temp;
	switch (GPIO_Port){
	case GPIO_PortA:
		if (GPIO_Pin == GPIO_Pin0 || GPIO_Pin == GPIO_Pin1 || GPIO_Pin == GPIO_Pin2 || GPIO_Pin == GPIO_Pin3 || GPIO_Pin == GPIO_Pin4 || GPIO_Pin == GPIO_Pin5 || GPIO_Pin == GPIO_Pin6 || GPIO_Pin == GPIO_Pin7 )
		{
			temp=GPIOA_Ptr->CRL;
			temp &=~(GPIO_CRL_LENGTH<<(CRLRegShift+GPIO_Pin));
			temp |=(GPIO_Config<<(CRLRegShift+GPIO_Pin));
			temp &=~(GPIO_CRL_LENGTH<<(GPIO_Pin));
			temp |=(GPIO_Mode<<(GPIO_Pin));
			GPIOA_Ptr->CRL=temp;
		}
		else
		{
			GPIO_Pin -= 32;
			temp=GPIOA_Ptr->CRH;
			temp &=~(GPIO_CRL_LENGTH<<(CRLRegShift+GPIO_Pin));
			temp |=(GPIO_Config<<(CRLRegShift+GPIO_Pin));
			temp &=~(GPIO_CRL_LENGTH<<(GPIO_Pin));
			temp |=(GPIO_Mode<<(GPIO_Pin));
			GPIOA_Ptr->CRH=temp;
		}
		break;
	case GPIO_PortB:
		if (GPIO_Pin == GPIO_Pin0 || GPIO_Pin == GPIO_Pin1 || GPIO_Pin == GPIO_Pin2 || GPIO_Pin == GPIO_Pin3 || GPIO_Pin == GPIO_Pin4 || GPIO_Pin == GPIO_Pin5 || GPIO_Pin == GPIO_Pin6 || GPIO_Pin == GPIO_Pin7 )
		{
			temp=GPIOB_Ptr->CRL;
			temp &=~(GPIO_CRL_LENGTH<<(CRLRegShift+GPIO_Pin));
			temp |=(GPIO_Config<<(CRLRegShift+GPIO_Pin));
			temp &=~(GPIO_CRL_LENGTH<<(GPIO_Pin));
			temp |=(GPIO_Mode<<(GPIO_Pin));
			GPIOB_Ptr->CRL=temp;
		}
		else
		{
			GPIO_Pin -= 32;
			temp=GPIOB_Ptr->CRH;
			temp &=~(GPIO_CRL_LENGTH<<(CRLRegShift+GPIO_Pin));
			temp |=(GPIO_Config<<(CRLRegShift+GPIO_Pin));
			temp &=~(GPIO_CRL_LENGTH<<(GPIO_Pin));
			temp |=(GPIO_Mode<<(GPIO_Pin));
			GPIOB_Ptr->CRH=temp;
		}
		break;
	case GPIO_PortC:
		if (GPIO_Pin == GPIO_Pin0 || GPIO_Pin == GPIO_Pin1 || GPIO_Pin == GPIO_Pin2 || GPIO_Pin == GPIO_Pin3 || GPIO_Pin == GPIO_Pin4 || GPIO_Pin == GPIO_Pin5 || GPIO_Pin == GPIO_Pin6 || GPIO_Pin == GPIO_Pin7 )
		{
			temp=GPIOC_Ptr->CRL;
			temp &=~(GPIO_CRL_LENGTH<<(CRLRegShift+GPIO_Pin));
			temp |=(GPIO_Config<<(CRLRegShift+GPIO_Pin));
			temp &=~(GPIO_CRL_LENGTH<<(GPIO_Pin));
			temp |=(GPIO_Mode<<(GPIO_Pin));
			GPIOC_Ptr->CRL=temp;
		}
		else
		{
			GPIO_Pin -= 32;
			temp=GPIOC_Ptr->CRH;
			temp &=~(GPIO_CRL_LENGTH<<(CRLRegShift+GPIO_Pin));
			temp |=(GPIO_Config<<(CRLRegShift+GPIO_Pin));
			temp &=~(GPIO_CRL_LENGTH<<(GPIO_Pin));
			temp |=(GPIO_Mode<<(GPIO_Pin));
			GPIOC_Ptr->CRH=temp;
		}
		break;
	}

	errstate = res_OK;
	return errstate;

}

res_t GPIO_SetOUTValue(u8 GPIO_Port,u32 GPIO_ODRPin, u8 GPIO_OUTValue)
{
	u8 errstate = res_ERROR;
	u32 temp;
	switch (GPIO_Port)
	{
	case GPIO_PortA:
		temp=GPIOA_Ptr->ODR;
		temp &=~GPIO_ODRPin;
		if (GPIO_OUTValue == GPIO_OUTValue_High)
		{
			temp |=(GPIO_ODRPin);
		}
		GPIOA_Ptr->ODR=temp;
		break;
	case GPIO_PortB:
		temp=GPIOB_Ptr->ODR;
		temp &=~GPIO_ODRPin;
		if (GPIO_OUTValue == GPIO_OUTValue_High)
		{
			temp |=(GPIO_ODRPin);
		}
		GPIOB_Ptr->ODR=temp;
		break;
	case GPIO_PortC:
		temp=GPIOC_Ptr->ODR;
		temp &=~GPIO_ODRPin;
		if (GPIO_OUTValue == GPIO_OUTValue_High)
		{
			temp |=(GPIO_ODRPin);
		}
		GPIOC_Ptr->ODR=temp;
		break;
	}

	errstate=res_OK;
	return errstate;
}

u8 GPIO_ReadPin(u8 GPIO_Port,u32 GPIO_IDRPin)
{
	u8 temp=0;
	switch (GPIO_Port)
		{
		case GPIO_PortA:
			temp=((GPIOA_Ptr->IDR >>GPIO_IDRPin)&0x01);
			break;
		case GPIO_PortB:
			temp=((GPIOB_Ptr->IDR >>GPIO_IDRPin)&0x01);
			break;
		case GPIO_PortC:
			temp=((GPIOC_Ptr->IDR >>GPIO_IDRPin)&0x01);
			break;
		}
	return temp;
}

