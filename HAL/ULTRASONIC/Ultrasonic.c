/*
 * Ultrasonic.c
 *
 *  Created on: Jun 9, 2023
 *      Author: Omar El Yamany
 */


// Ultrasonic sensor parameters
#include "Ultrasonic.h"
#define SPEED_OF_SOUND 343 // meters per second
#define TIMER_CLOCK_FREQ 1000
s32 distance=100;
void Ultrasonic_init(u8 GPIO_Port,u32 GPIO_PinEcho ,u8 GPIO_ModeEcho,u8 GPIO_ConfigEcho,u32 GPIO_PinTrig,  u8 GPIO_ModeTrig,u8  GPIO_ConfigTrig)
{
	GPIO_SetPin(GPIO_Port, GPIO_PinEcho, GPIO_ModeEcho, GPIO_ConfigEcho);
	GPIO_SetPin(GPIO_Port, GPIO_PinTrig, GPIO_ModeTrig, GPIO_ConfigTrig);
}




void Ultrasonic_measure_distance(u8 Timer , u8 GPIO_Port, u32 GPIO_ODRPinTrig, u32 GPIO_IDRPinEcho)
{
	TIMERx_WritePSC(Timer, 72);
	TIMERx_WriteCNT(Timer, 0);
	// Send a trigger pulse to start the measurement
	GPIO_SetOUTValue(GPIO_Port, GPIO_ODRPinTrig, GPIO_OUTValue_High);
	SYSTK_voidDelay(15);
	GPIO_SetOUTValue(GPIO_Port, GPIO_ODRPinTrig, GPIO_OUTValue_Low);

	// Wait for the echo pulse to start
	while (GPIO_ReadPin(GPIO_Port, GPIO_IDRPinEcho) == 0);

	TIMERx_Start(Timer);
	// Measure the pulse width of the echo pulse
	u32 pulse_width = 0;
	while (GPIO_ReadPin(GPIO_Port, GPIO_IDRPinEcho)  == 1)
	{
		pulse_width = TIMERx_ReadCNT(Timer);
	}

	// Convert the pulse width to distance in centimeters
	distance = ((f32)pulse_width * SPEED_OF_SOUND) / (TIMER_CLOCK_FREQ * 2);


}

