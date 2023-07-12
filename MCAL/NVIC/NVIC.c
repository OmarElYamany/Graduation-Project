/*
 * NVIC.c
 *
 *  Created on: May 27, 2023
 *      Author: Omar El Yamany
 */


#include "NVIC.h"

#define NVIC_BaseAdd			0xE000E100




#define SCB_AIRCR	(*(volatile u32*)0xE000ED0C)
#define SCB_AIRCR_PRIGROUP_Length		0x07
#define SCB_AIRCR_PRIGROUP_Bit			8
#define SCB_AIRCR_VECTKEY_Length		0xFFFF
#define SCB_AIRCR_VECTKEY_Bit			16

#define NVIC_IPRx_Length				0xF0
#define NVIC_IPRx_Bit					4


typedef struct
{
	volatile u32 ISER[3];
	volatile u32 Reserved0[29];
	volatile u32 ICER[3];
	volatile u32 Reserved1[29];
	volatile u32 ISPR[3];
	volatile u32 Reserved2[29];
	volatile u32 ICPR[3];
	volatile u32 Reserved3[29];
	volatile u32 IABR[3];
	volatile u32 Reserved4[61];
	volatile u8 IPR[80];
	volatile u32 Reserved5[695];
	volatile u32 STIR;

}NVIC_Struct;


static volatile NVIC_Struct * const NVIC_Ptr = (volatile NVIC_Struct * const)NVIC_BaseAdd;


res_t NVICEnableInt(u8 NVIC_Int)
{
	u8 errstate = res_ERROR;
	u8 localArrIndex = NVIC_Int/32;
	NVIC_Ptr->ISER[localArrIndex] |= (1<<(NVIC_Int%32));
	errstate = res_OK;
	return errstate;
}

res_t NVICDisableInt(u8 NVIC_Int)
{
	u8 errstate = res_ERROR;
	u8 localArrIndex = NVIC_Int/32;
	NVIC_Ptr->ICER[localArrIndex] |= (1<<(NVIC_Int%32));
	errstate = res_OK;
	return errstate;
}

res_t NVICSetPend(u8 NVIC_Int)
{
	u8 errstate = res_ERROR;
	u8 localArrIndex = NVIC_Int/32;
	NVIC_Ptr->ISPR[localArrIndex] |= (1<<(NVIC_Int%32));
	errstate = res_OK;
	return errstate;
}

res_t NVICClearPend(u8 NVIC_Int)
{
	u8 errstate = res_ERROR;
	u8 localArrIndex = NVIC_Int/32;
		NVIC_Ptr->ICPR[localArrIndex] |= (1<<(NVIC_Int%32));
	errstate = res_OK;
	return errstate;
}

res_t NVICSetSFWInt(u8 NVIC_Software_Int)
{
	u8 errstate = res_ERROR;
	NVIC_Ptr->STIR |= NVIC_Software_Int;
	errstate = res_OK;
	return errstate;
}

res_t SCBSetPriority(u8 SCB_AIRCR_PRIGROUP)
{
	u8 errstate = res_ERROR;
	SCB_AIRCR =  (0x05FA<<SCB_AIRCR_VECTKEY_Bit);
	u32 temp = SCB_AIRCR;
	temp &=~ (SCB_AIRCR_PRIGROUP_Length<<SCB_AIRCR_PRIGROUP_Bit);
	temp |= (SCB_AIRCR_PRIGROUP<<SCB_AIRCR_PRIGROUP_Bit);
	SCB_AIRCR = temp;
	errstate = res_OK;
	return errstate;
}

res_t NVICSetPriority(u8 NVIC_Priority , u8  NVIC_Int)
{
	u8 errstate = res_ERROR;
	u32 temp = NVIC_Ptr->IPR[NVIC_Int];
	temp &=~ NVIC_IPRx_Length;
	temp |= NVIC_Priority;
	NVIC_Ptr->IPR[NVIC_Int] = temp;
	errstate = res_OK;
	return errstate;
}






