/*
 * EXTI.c
 *
 *  Created on: Jun 3, 2023
 *      Author: Omar El Yamany
 */
#include "EXTI.h"

void (*EXTI0CallBackPtr)(void)= Null;
void (*EXTI1CallBackPtr)(void)= Null;
#define EXTI_BaseAdd			0x40010400
#define AFIO_BaseAdd			0x40010008
#define AFIO_EXTI_Length		0x0f

typedef struct
{
	volatile u32 IMR;
	volatile u32 EMR;
	volatile u32 RTSR;
	volatile u32 FTSR;
	volatile u32 SWIER;
	volatile u32 PR;
}EXTI_Struct;

typedef struct
{
	volatile u32 EXTICR1;
	volatile u32 EXTICR2;
	volatile u32 EXTICR3;
	volatile u32 EXTICR4;

}AFIO_EXTI_Struct;

static volatile EXTI_Struct * const EXTI_Ptr = (volatile EXTI_Struct * const)EXTI_BaseAdd;
static volatile AFIO_EXTI_Struct * const AFIO_Ptr = (volatile AFIO_EXTI_Struct * const)AFIO_BaseAdd;


res_t EXTI_Config(u8 AFIO_EXTI,u16 AFIO_EXTI_Port)
{
	u8 errstate = res_ERROR;
	if ((AFIO_EXTI<=AFIO_EXTI3))
	{
		u32 temp= AFIO_Ptr->EXTICR1;
		temp &=~ (AFIO_EXTI_Length<<AFIO_EXTI);
		temp |= (AFIO_EXTI_Port<<AFIO_EXTI);
		AFIO_Ptr->EXTICR1 = temp;
	}
	else if (AFIO_EXTI>=AFIO_EXTI4 && AFIO_EXTI<=AFIO_EXTI7)
	{
		AFIO_EXTI -=16;
		u32 temp= AFIO_Ptr->EXTICR2;
		temp &=~ (AFIO_EXTI_Length<<AFIO_EXTI);
		temp |= (AFIO_EXTI_Port<<AFIO_EXTI);
		AFIO_Ptr->EXTICR2 = temp;
	}
	else if (AFIO_EXTI>=AFIO_EXTI8 && AFIO_EXTI<=AFIO_EXTI11)
	{
		AFIO_EXTI -=32;
		u32 temp= AFIO_Ptr->EXTICR3;
		temp &=~ (AFIO_EXTI_Length<<AFIO_EXTI);
		temp |= (AFIO_EXTI_Port<<AFIO_EXTI);
		AFIO_Ptr->EXTICR3 = temp;
	}
	else if (AFIO_EXTI>=AFIO_EXTI12 && AFIO_EXTI<=AFIO_EXTI15)
	{
		AFIO_EXTI -=48;
		u32 temp= AFIO_Ptr->EXTICR4;
		temp &=~ (AFIO_EXTI_Length<<AFIO_EXTI);
		temp |= (AFIO_EXTI_Port<<AFIO_EXTI);
		AFIO_Ptr->EXTICR4 = temp;
	}

	errstate = res_OK;
	return errstate;

}

res_t EXTI_EnableInt(u32 EXTI_Interrupt)
{
	u8 errstate = res_ERROR;
	EXTI_Ptr->IMR |= EXTI_Interrupt;
	errstate = res_OK;
	return errstate;
}

res_t EXTI_EnableEvent(u32 EXTI_Interrupt)
{
	u8 errstate = res_ERROR;
	EXTI_Ptr->EMR |= EXTI_Interrupt;
	errstate = res_OK;
	return errstate;
}

res_t EXTI_TriggerMode(u32 EXTI_Interrupt , u8 EXTI_TriggerMode)
{
	u8 errstate = res_ERROR;
	if(EXTI_TriggerMode == EXTI_TriggerMode_Rising)
	{
		EXTI_Ptr->RTSR |= EXTI_Interrupt;
		EXTI_Ptr->FTSR &=~ EXTI_Interrupt;
		errstate = res_OK;
	}
	else if(EXTI_TriggerMode == EXTI_TriggerMode_Falling)
	{
		EXTI_Ptr->FTSR |= EXTI_Interrupt;
		EXTI_Ptr->RTSR &=~ EXTI_Interrupt;
		errstate = res_OK;
	}
	else if(EXTI_TriggerMode == EXTI_TriggerMode_Onchange)
	{
		EXTI_Ptr->RTSR |= EXTI_Interrupt;
		EXTI_Ptr->FTSR |= EXTI_Interrupt;
		errstate = res_OK;
	}
	return errstate;
}

res_t EXTI_SetSWInt(u32 EXTI_Interrupt)
{
	u8 errstate = res_ERROR;
	EXTI_Ptr->SWIER |= EXTI_Interrupt;
	errstate = res_OK;
	return errstate;
}

res_t EXTI_ClearPending(u32 EXTI_Interrupt)
{
	u8 errstate = res_ERROR;
	EXTI_Ptr->PR |= EXTI_Interrupt;
	errstate = res_OK;
	return errstate;
}

void EXTI0_callbackFn (void (*ptr)(void))
{
	EXTI0CallBackPtr= ptr;
}

void EXTI0_IRQHandler(void)
{
	EXTI0CallBackPtr();
	EXTI_Ptr->PR |= EXTI_Interrupt0;

}


void EXTI1_callbackFn (void (*ptr)(void))
{
	EXTI1CallBackPtr= ptr;
}

void EXTI1_IRQHandler(void)
{
	EXTI1CallBackPtr();
	EXTI_Ptr->PR |= EXTI_Interrupt1;

}
