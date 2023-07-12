#ifndef __ALARM_H__
#define __ALARM_H__

#include "../../MCAL/GPIO/GPIO.h"
#include "../../Common/STD_Types.h"

/***************************for_BUZZER***********************/
#define 	port1    GPIO_PORTA
#define 	pin1  	 GPIO_PIN0
/***************************for_LED***********************/
#define 	port2    GPIO_PORTA
#define 	pin2  	 GPIO_PIN1





void HAL_ALARM_SYSTIC_FUNC(u8 sec);



#endif
