/*
 * Motor.h
 *
 *  Created on: Jun 12, 2023
 *      Author: Omar El Yamany
 */

#ifndef MOTOR_MOTOR_H_
#define MOTOR_MOTOR_H_

#define CC_Static		0
#define CC_Adaptive		1
#define CC_Off			2

#include "../../Common/STD_Types.h"
#include "../../Common/definition.h"
#include "../../Common/util.h"
#include "../../Common/Bit_Math.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../../MCAL/Timers/Timer.h"
#include "../../MCAL/USART/USART_int.h"
#include "../../MCAL/SYSTK/SYSTK.h"
#include "../HAL/ALARM/ALARM.h"



#define danger_distance 20
res_t MotorCfg(u8 Timer ,u8 GPIO_Port ,u32 GPIO_PinPWM, u32 GPIO_Pin_1 ,u32 GPIO_Pin_2 );
res_t MotorsStart(u8 GPIO_Port ,u32 GPIO_ODRPin_1 ,u32 GPIO_ODRPin_2 );
res_t MotorsStop(u8 GPIO_Port ,u32 GPIO_ODRPin_1 ,u32 GPIO_ODRPin_2 );
res_t MotorSetSpeed(u8 Timer );
res_t MotorCfgSpeed(void);
void Motor_ACCmode();
#endif /* MOTOR_MOTOR_H_ */
