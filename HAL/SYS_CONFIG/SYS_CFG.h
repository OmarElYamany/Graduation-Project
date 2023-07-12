/*
 * SYS_CFG.h
 *
 *  Created on: Jun 23, 2023
 *      Author: Omar El Yamany
 */

#ifndef SYS_CONFIG_SYS_CFG_H_
#define SYS_CONFIG_SYS_CFG_H_

#include "../../MCAL/RCC/RCC.h"
#include "../../MCAL/NVIC/NVIC.h"
#include "../../MCAL/EXTI/EXTI.h"
#include "../../MCAL/Timers/Timer.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../../HAL/ULTRASONIC/Ultrasonic.h"
#include "../../HAL/MOTOR/Motor.h"
#include "../../MCAL/SYSTK/SYSTK.h"

void SYSCfg_init(void);

#endif /* SYS_CONFIG_SYS_CFG_H_ */
