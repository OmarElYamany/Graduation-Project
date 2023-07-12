/*
 * EXTI.h
 *
 *  Created on: Jun 3, 2023
 *      Author: Omar El Yamany
 */

#ifndef EXTI_EXTI_H_
#define EXTI_EXTI_H_
#include "../../Common/STD_Types.h"
#include "../../Common/definition.h"
#include "../../Common/util.h"
//port selection
#define AFIO_EXTI_PortA			0x0000
#define AFIO_EXTI_PortB			0x0001
#define AFIO_EXTI_PortC			0x0002
//pin selection
#define AFIO_EXTI0			0
#define AFIO_EXTI1			4
#define AFIO_EXTI2			8
#define AFIO_EXTI3			12
#define AFIO_EXTI4			16
#define AFIO_EXTI5			20
#define AFIO_EXTI6			24
#define AFIO_EXTI7			28
#define AFIO_EXTI8			32
#define AFIO_EXTI9			36
#define AFIO_EXTI10			40
#define AFIO_EXTI11			44
#define AFIO_EXTI12			48
#define AFIO_EXTI13			52
#define AFIO_EXTI14			56
#define AFIO_EXTI15			60

//EXTI selection
#define EXTI_Interrupt0        BIT0_MASK
#define EXTI_Interrupt1        BIT1_MASK
#define EXTI_Interrupt2        BIT2_MASK
#define EXTI_Interrupt3        BIT3_MASK
#define EXTI_Interrupt4        BIT4_MASK
#define EXTI_Interrupt5        BIT5_MASK
#define EXTI_Interrupt6        BIT6_MASK
#define EXTI_Interrupt7        BIT7_MASK
#define EXTI_Interrupt8        BIT8_MASK
#define EXTI_Interrupt9        BIT9_MASK
#define EXTI_Interrupt10       BIT10_MASK
#define EXTI_Interrupt11       BIT11_MASK
#define EXTI_Interrupt12       BIT12_MASK
#define EXTI_Interrupt13       BIT13_MASK
#define EXTI_Interrupt14       BIT14_MASK
#define EXTI_Interrupt15       BIT15_MASK
#define EXTI_Interrupt16       BIT16_MASK
#define EXTI_Interrupt17       BIT17_MASK
#define EXTI_Interrupt18       BIT18_MASK
#define EXTI_Interrupt19       BIT19_MASK

//trigger mode
#define EXTI_TriggerMode_Falling	0
#define EXTI_TriggerMode_Rising		1
#define EXTI_TriggerMode_Onchange	2


res_t EXTI_Config(u8 AFIO_EXTI,u16 AFIO_EXTI_Port);

res_t EXTI_EnableInt(u32 EXTI_Interrupt);
res_t EXTI_EnableEvent(u32 EXTI_Interrupt);
res_t EXTI_TriggerMode(u32 EXTI_Interrupt , u8 EXTI_TriggerMode);
res_t EXTI_SetSWInt(u32 EXTI_Interrupt);
res_t EXTI_ClearPending(u32 EXTI_Interrupt);

void EXTI0_callbackFn (void (*ptr)(void));
void EXTI1_callbackFn (void (*ptr)(void));
#endif /* EXTI_EXTI_H_ */
