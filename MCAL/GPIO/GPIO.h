
/*
 * GPIO.h
 *
 *  Created on: May 26, 2023
 *      Author: Omar El Yamany
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

#include "../../Common/STD_Types.h"
#include "../../Common/definition.h"
#include "../../Common/util.h"

#define GPIO_PortA	0
#define GPIO_PortB	1
#define GPIO_PortC	2



#define GPIO_Pin0		0
#define GPIO_Pin1		4
#define GPIO_Pin2		8
#define GPIO_Pin3		12
#define GPIO_Pin4		16
#define GPIO_Pin5		20
#define GPIO_Pin6		24
#define GPIO_Pin7		28
#define GPIO_Pin8		32
#define GPIO_Pin9		36
#define GPIO_Pin10		40
#define GPIO_Pin11		44
#define GPIO_Pin12		48
#define GPIO_Pin13		52
#define GPIO_Pin14		56
#define GPIO_Pin15		60


#define GPIO_ODRPin0	 BIT0_MASK
#define GPIO_ODRPin1	 BIT1_MASK
#define GPIO_ODRPin2	 BIT2_MASK
#define GPIO_ODRPin3	 BIT3_MASK
#define GPIO_ODRPin4	 BIT4_MASK
#define GPIO_ODRPin5	 BIT5_MASK
#define GPIO_ODRPin6	 BIT6_MASK
#define GPIO_ODRPin7	 BIT7_MASK
#define GPIO_ODRPin8	 BIT8_MASK
#define GPIO_ODRPin9	 BIT9_MASK
#define GPIO_ODRPin10	 BIT10_MASK
#define GPIO_ODRPin11	 BIT11_MASK
#define GPIO_ODRPin12	 BIT12_MASK
#define GPIO_ODRPin13	 BIT13_MASK
#define GPIO_ODRPin14	 BIT14_MASK
#define GPIO_ODRPin15	 BIT15_MASK


#define GPIO_IDRPin0	0
#define GPIO_IDRPin1	1
#define GPIO_IDRPin2	2
#define GPIO_IDRPin3	3
#define GPIO_IDRPin4	4
#define GPIO_IDRPin5	5
#define GPIO_IDRPin6	6
#define GPIO_IDRPin7	7
#define GPIO_IDRPin8	8
#define GPIO_IDRPin9	9
#define GPIO_IDRPin10	10
#define GPIO_IDRPin11	11
#define GPIO_IDRPin12	12
#define GPIO_IDRPin13	13
#define GPIO_IDRPin14	14
#define GPIO_IDRPin15	15

#define GPIO_Config_GenOUTPushPull	0x00
#define GPIO_Config_GenOUTOpenDrain	0x01
#define GPIO_Config_AltOUTPushPull	0x02
#define GPIO_Config_AltOUTOpenDrain	0x03

#define GPIO_Config_INPAnalog			0x00
#define GPIO_Config_INPFloating			0x01
#define GPIO_Config_INPPullUpDown		0x02


#define GPIO_Mode_IN		0x00
#define GPIO_Mode_OUT10		0x01
#define GPIO_Mode_OUT2		0x02
#define GPIO_Mode_OUT50		0x03

#define GPIO_OUTValue_Low	0x00
#define GPIO_OUTValue_High	0x01



res_t GPIO_SetPin(u8 GPIO_Port,u32 GPIO_Pin, u8 GPIO_Mode , u8 GPIO_Config);
res_t GPIO_SetOUTValue(u8 GPIO_Port,u32 GPIO_ODRPin, u8 GPIO_OUTValue);
u8 GPIO_ReadPin(u8 GPIO_Port,u32 GPIO_IDRPin);


#endif /* GPIO_GPIO_H_ */
