#include "../HAL/SYS_CONFIG/SYS_CFG.h"


extern u8 CC_Mode;
extern s32 distance;
extern s32 Motor_Speed;
void main(void)
{


	SYSCfg_init();

	while (1)
	{
		Ultrasonic_measure_distance(Timer3, GPIO_PortA, GPIO_ODRPin4, GPIO_IDRPin3);
		MotorCfgSpeed();
		MotorSetSpeed(Timer2);
		SYSTK_voidDelay(10000);
		if (CC_Mode == CC_Adaptive)
		{
			Motor_ACCmode();
		}

			USART_sendString(Motor_Speed);
			USART_sendData((u8*)"d");
			USART_sendString(distance);
			USART_sendData((u8*)"\n");



	}
}
