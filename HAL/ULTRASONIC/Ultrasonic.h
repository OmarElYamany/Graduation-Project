/*
 * Ultrasonic.h
 *
 *  Created on: Jun 9, 2023
 *      Author: Omar El Yamany
 */

#ifndef ULTRASONIC_ULTRASONIC_H_
#define ULTRASONIC_ULTRASONIC_H_

#include "../../Common/STD_Types.h"
#include "../../Common/definition.h"
#include "../../Common/util.h"
#include "../../Common/Bit_Math.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../../MCAL/SYSTK/SYSTK.h"
#include "../../MCAL/Timers/Timer.h"

void Ultrasonic_init(u8 GPIO_Port,u32 GPIO_PinEcho ,u8 GPIO_ModeEcho,u8 GPIO_ConfigEcho,u32 GPIO_PinTrig,  u8 GPIO_ModeTrig,u8  GPIO_ConfigTrig);
void Ultrasonic_measure_distance(u8 Timer , u8 GPIO_Port, u32 GPIO_ODRPinTrig, u32 GPIO_IDRPinEcho);

#endif /* ULTRASONIC_ULTRASONIC_H_ */
