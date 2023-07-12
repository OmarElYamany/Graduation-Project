
#include "SYSTK.h"


#define SYSTK_Base_Address	(0xE000E010)
#define SYSTK	((SYSTKR_t *)(SYSTK_Base_Address))

typedef enum
{
	ENABLE,
	TICKINT,
	CLKSRC,
	COUNTFLAG
}Ctrl_t;



typedef enum
{
	DIS,
	EN
}INTst_t;




typedef struct
{
	u32 volatile CTRL;
	u32 volatile LOAD;
	u32 volatile VAL;
	u32 volatile CALIB;
}SYSTKR_t;




void (*SYSTK_CallBack) (void)= Null;




void SYSTK_voidInit(void)
{
	/* [Enable Systick Interrupt - clock = AHB/8 - Stop Systick]*/

	CLR_BIT(SYSTK -> CTRL ,0);
	SET_BIT(SYSTK -> CTRL ,1);
	CLR_BIT(SYSTK -> CTRL ,2);

}





void SYSTK_voidStart(u32 PreloadValue)
{


	//Step 1: Load Value

	SYSTK -> LOAD = PreloadValue;

	//Step 2: Clear Val Reg

	SYSTK -> VAL = 0;

	//Step 3: Enable Systick

	SET_BIT(SYSTK -> CTRL ,0);

}








void SYSTK_voidDelay(u32 Time_Micro)
{
	//Step 1 : Init Systick

	SYSTK_voidInit();

	//Step 2 : Disable INT

	CLR_BIT(SYSTK -> CTRL,1);

	//Step 3 : Start Systick( Time in micro seconds )

	SYSTK_voidStart(Time_Micro * 2);

	//Step 4 : Waiting on the Flag

	while(GET_BIT(SYSTK -> CTRL , 16) == 0);

}


void SYSTK_voidSetCallBack(void (*ptr) (void))
{
	SYSTK_CallBack = ptr ;

}
void SysTick_Handler(void)
{
	// Execute CallBack Function
	if (SYSTK_CallBack!= Null)
	{
		SYSTK_CallBack() ;
	}
}





























