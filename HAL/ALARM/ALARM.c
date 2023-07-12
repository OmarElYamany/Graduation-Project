
#include "ALARM.h"











void HAL_ALARM_SYSTIC_FUNC(u8 sec) // ALARM Func
{

	static int c=0;
	//MGPIO_voidSetPinModeOutPut(port1,pin1,OUT_PUSH_PULL); //set port DIRECTION
	//MGPIO_voidSetPinModeOutPut(port2,pin2,OUT_PUSH_PULL);
	GPIO_SetPin(GPIO_PortA, GPIO_Pin5, GPIO_Mode_OUT2, GPIO_Config_GenOUTPushPull);
	GPIO_SetPin(GPIO_PortA, GPIO_Pin6, GPIO_Mode_OUT2, GPIO_Config_GenOUTPushPull);
	c++;
	if(c==sec)
	{
	//MGPIO_voidSetPin(port1,pin1); // set pin value 1
	//MGPIO_voidSetPin(port2,pin2);
		GPIO_SetOUTValue(GPIO_PortA, GPIO_ODRPin5, GPIO_OUTValue_High);
		GPIO_SetOUTValue(GPIO_PortA, GPIO_ODRPin6, GPIO_OUTValue_High);

	}
	else if(c==2*sec)
	{
		//MGPIO_voidResetPin(port1,pin1);  // set pin value to 0
		//MGPIO_voidResetPin(port2,pin2);
		GPIO_SetOUTValue(GPIO_PortA, GPIO_ODRPin5, GPIO_OUTValue_Low);
		GPIO_SetOUTValue(GPIO_PortA, GPIO_ODRPin6, GPIO_OUTValue_Low);
	c=0;

	}
	else
	{
		;;
	}

}
