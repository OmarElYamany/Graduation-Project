/*
 * Motor.c
 *
 *  Created on: Jun 12, 2023
 *      Author: Omar El Yamany
 */
#include "Motor.h"
extern s32 distance;
s32 Motor_Speed_PWM;
u8 GlobalDataRec;
u8 CC_Mode=CC_Off;
u8 ACC_Range_UpperLimit;
u8 ACC_Range_MidLimit;
u8 ACC_Range_LowerLimit;
s32 Motor_Speed;

void Motor_ACCmode();


res_t MotorCfg(u8 Timer ,u8 GPIO_Port ,u32 GPIO_PinPWM, u32 GPIO_Pin_1 ,u32 GPIO_Pin_2 )
{
	u8 errstate = res_ERROR;
	TIMERx_config(Timer, TIMERx_ClockDiv_1, TIMERx_Mode_EdgeAlig, TIMERx_Dir_UpCounting);
	TIMERx_WritePSC(Timer, 8);
	TIMERx_WriteARR(Timer, 1500);
	TIMERx_CompareModeCFG(Timer, TIMERx_CCMRch_CC1S, TIMERx_CCMR_OCFE_Off, TIMERx_CCMR_OCPE_Off, TIMERx_CCMR_OCM_PWMmode1, TIMERx_CCMR_OCCE_Off);
	TIMERx_CapComchEnable(Timer, TIMERx_CCER_CapComCH1, TIMERx_CCER_Polarity_Falling);
	TIMERx_Start(Timer);
	GPIO_SetPin(GPIO_Port, GPIO_PinPWM, GPIO_Mode_OUT50, GPIO_Config_AltOUTPushPull);
	GPIO_SetPin(GPIO_Port, GPIO_Pin_1, GPIO_Mode_OUT50, GPIO_Config_GenOUTPushPull);
	GPIO_SetPin(GPIO_Port, GPIO_Pin_2, GPIO_Mode_OUT50, GPIO_Config_GenOUTPushPull);
	errstate = res_OK;
	return errstate;
}



res_t MotorsStart(u8 GPIO_Port ,u32 GPIO_ODRPin_1 ,u32 GPIO_ODRPin_2 )
{
	u8 errstate = res_ERROR;
	GPIO_SetOUTValue(GPIO_Port, GPIO_ODRPin_1, GPIO_OUTValue_High);
	GPIO_SetOUTValue(GPIO_Port, GPIO_ODRPin_2, GPIO_OUTValue_Low);

	return errstate;
}



res_t MotorsStop(u8 GPIO_Port ,u32 GPIO_ODRPin_1 ,u32 GPIO_ODRPin_2)
{
	u8 errstate = res_ERROR;
	GPIO_SetOUTValue(GPIO_Port, GPIO_ODRPin_1, GPIO_OUTValue_Low);
	GPIO_SetOUTValue(GPIO_Port, GPIO_ODRPin_2, GPIO_OUTValue_Low);

	return errstate;
}

res_t MotorSetSpeed(u8 Timer )
{
	u8 errstate = res_ERROR;
	if (distance <= danger_distance)
	{
		MotorsStop(GPIO_PortA, GPIO_ODRPin1, GPIO_ODRPin2);
		HAL_ALARM_SYSTIC_FUNC(2);

	}
	else
	{
		GPIO_SetOUTValue(GPIO_PortA, GPIO_ODRPin5, GPIO_OUTValue_Low);
		GPIO_SetOUTValue(GPIO_PortA, GPIO_ODRPin6, GPIO_OUTValue_Low);
		MotorsStart(GPIO_PortA, GPIO_ODRPin1, GPIO_ODRPin2);
		if (Motor_Speed_PWM > 1500)
		{
			Motor_Speed_PWM=1500; // to handle the case of speed_level exceeding 100%
		}
		else if (Motor_Speed_PWM < 0)
		{
			Motor_Speed_PWM=0;
		}
		TIMERx_WriteCCR(Timer, TIMERx_CCRch_1, Motor_Speed_PWM);
	}
	Motor_Speed = (Motor_Speed_PWM*48)/1500;
	return errstate;
}


//Motor modes





res_t MotorCfgSpeed(void)
{
	u8 errstate = res_ERROR;
	switch (GlobalDataRec)
	{
	case 'A':
		if (Motor_Speed_PWM <= 1500 && Motor_Speed_PWM >= 0 && CC_Mode == CC_Off)
		{
			Motor_Speed_PWM+=50;
		}
		break;
	case 'D':
		if (Motor_Speed_PWM <= 1500 && Motor_Speed_PWM >= 0)
		{
			Motor_Speed_PWM-=50;
		}
		break;
	case 'S':
		Motor_Speed_PWM = 0;
		break;

	case 'O':
		CC_Mode = CC_Off;
		break;
	case 'N':
		CC_Mode = CC_Static;
		break;
	case 'V':
		CC_Mode = CC_Adaptive;
		break;

	case 'C':
		ACC_Range_UpperLimit=60;
		ACC_Range_LowerLimit=30;

		break;
	case 'M':
		ACC_Range_UpperLimit=90;
		ACC_Range_LowerLimit=60;
		break;
	case 'L':
		ACC_Range_UpperLimit=120;
		ACC_Range_LowerLimit=90;
		break;

	default:
		if (CC_Mode == CC_Off)
		{
			Motor_Speed_PWM-=10;
		}
		break;

	}

	GlobalDataRec='Y';
	return errstate;
}






void Motor_ACCmode()
{
	if (distance > ACC_Range_UpperLimit)
	{
		Motor_Speed_PWM+=10;
	}
	else if (distance <= ACC_Range_LowerLimit && distance > danger_distance)
	{
		Motor_Speed_PWM-=10;
	}

}
