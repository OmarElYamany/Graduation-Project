/*
 * Timer.c
 *
 *  Created on: Jun 2, 2023
 *      Author: Omar El Yamany
 */


// includes

#include "Timer.h"


//defines

#define DIER_DMA_INTBiteOffset	8
#define CCER_CapCom_PolarityBiteOffset	1

void (*TIM2CallBackPtr)(void)= Null;
void (*TIM3CallBackPtr)(void)= Null;
void (*TIM4CallBackPtr)(void)= Null;
void (*TIM5CallBackPtr)(void)= Null;
/************     Timers  address        *******************/
#define Timer2_BaseAdd		0x40000000
#define Timer3_BaseAdd		0x40000400
#define Timer4_BaseAdd		0x40000800
#define Timer5_BaseAdd		0x40000C00

/*************     CR1 register bits        *****************/
#define TIMERx_CR1_CEN					BIT0_MASK
#define TIMERx_CR1_UDIS					BIT1_MASK
#define TIMERx_CR1_URS					BIT2_MASK
#define TIMERx_CR1_OPM					BIT3_MASK
#define TIMERx_CR1_DIR					BIT4_MASK
#define TIMERx_CR1_APRE					BIT7_MASK

//Timer Clock Division
#define TIMERx_CKD_Length			0x03
#define TIMERx_CKD_Bit				8
//Timer Mode
#define TIMERx_CMS_Length			0x03
#define TIMERx_CMS_Bit				5

/*************    DIER register bits        *****************/
#define TIMERx_DIER_UIE						BIT0_MASK
#define TIMERx_DIER_CC1IE					BIT1_MASK
#define TIMERx_DIER_CC2IE					BIT2_MASK
#define TIMERx_DIER_CC3IE					BIT3_MASK
#define TIMERx_DIER_CC4IE					BIT4_MASK
#define TIMERx_DIER_TIE						BIT6_MASK
#define TIMERx_DIER_UDE						BIT8_MASK
#define TIMERx_DIER_CC1DE					BIT9_MASK
#define TIMERx_DIER_CC2DE					BIT10_MASK
#define TIMERx_DIER_CC3DE					BIT11_MASK
#define TIMERx_DIER_CC4DE					BIT12_MASK
#define TIMERx_DIER_TDE						BIT14_MASK

/*************    DIER register bits        *****************/
#define TIMERx_EGR_UG					BIT0_MASK
#define TIMERx_EGR_CC1G					BIT1_MASK
#define TIMERx_EGR_CC2G					BIT2_MASK
#define TIMERx_EGR_CC3G					BIT3_MASK
#define TIMERx_EGR_CC4G					BIT4_MASK
#define TIMERx_EGR_TG					BIT6_MASK

/*************    CCER register bits        *****************/
#define TIMERx_CCER_CC1E		BIT0_MASK
#define TIMERx_CCER_CC1P		BIT1_MASK
#define TIMERx_CCER_CC2E		BIT4_MASK
#define TIMERx_CCER_CC2P		BIT5_MASK
#define TIMERx_CCER_CC3E		BIT8_MASK
#define TIMERx_CCER_CC3P		BIT9_MASK
#define TIMERx_CCER_CC4E		BIT12_MASK
#define TIMERx_CCER_CC4P		BIT13_MASK


/*************    CCMR register bits        *****************/

// output or input selection
/*************Output*****************/
#define TIMERx_CCMR_CCS_Length				0x03
#define TIMERx_CCMR_RegOffset				16
#define	TIMERx_CCMR2						1
#define TIMERx_CCMR_OCFE_Bit				BIT2_MASK
#define TIMERx_CCMR_OCPE_Bit				BIT3_MASK
#define TIMERx_CCMR_OCCE_Bit				BIT7_MASK
#define TIMERx_CCMR_OCM_Length				0x07
#define TIMERx_CCMR_OCM_Bit					4

/*************Input*****************/
#define TIMERx_CCMR_ICF_Length				0xFF
#define TIMERx_CCMR_ICF_Bit					4
#define TIMERx_CCMR_ICPSC_Length			0x03
#define TIMERx_CCMR_ICPSC_Bit				2



//types

typedef struct
{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SMCR;
	volatile u32 DIER;
	volatile u32 SR;
	volatile u32 EGR;
	volatile u32 CCMR[2];
	volatile u32 CCER;
	volatile u32 CNT;
	volatile u32 PSC;
	volatile u32 ARR;
	volatile u32 RESRVED1;
	volatile u32 CCR[4];
	volatile u32 RESERVED2;
	volatile u32 DCR;
	volatile u32 DMAR;

}TIMERx_Struct;

// variables

static volatile TIMERx_Struct * const Timer2_Ptr =  (volatile TIMERx_Struct * const) Timer2_BaseAdd;
static volatile TIMERx_Struct * const Timer3_Ptr =  (volatile TIMERx_Struct * const) Timer3_BaseAdd;
static volatile TIMERx_Struct * const Timer4_Ptr =  (volatile TIMERx_Struct * const) Timer4_BaseAdd;
static volatile TIMERx_Struct * const Timer5_Ptr =  (volatile TIMERx_Struct * const) Timer5_BaseAdd;







//interface functions implementation


res_t TIMERx_config(u8 Timer , u32 TIMERx_ClockDiv , u32 TIMERx_Mode , u32 TIMERx_Dir )
{
	u8 errstate = res_ERROR;
	u32 temp = 0;
	switch (Timer)
	{
	case Timer2:
		temp = Timer2_Ptr->CR1;
		//Clock division
		temp &=~ (TIMERx_CKD_Length<<TIMERx_CKD_Bit);
		temp |= (TIMERx_ClockDiv<<TIMERx_CKD_Bit);
		//Mode selection
		temp &=~ (TIMERx_CMS_Length<<TIMERx_CMS_Bit);
		temp |= (TIMERx_Mode<<TIMERx_CMS_Bit);

		//Timer Direction
		if (TIMERx_Dir == TIMERx_Dir_DownCounting)
		{
			temp |= TIMERx_CR1_DIR;
		}
		else if (TIMERx_Dir == TIMERx_Dir_UpCounting)
		{
			temp &=~ TIMERx_CR1_DIR;
		}
		Timer2_Ptr->CR1 = temp;
		break;


	case Timer3:
		temp = Timer3_Ptr->CR1;
		//Clock division
		temp &=~ (TIMERx_CKD_Length<<TIMERx_CKD_Bit);
		temp |= (TIMERx_ClockDiv<<TIMERx_CKD_Bit);
		//Mode selection
		temp &=~ (TIMERx_CMS_Length<<TIMERx_CMS_Bit);
		temp |= (TIMERx_Mode<<TIMERx_CMS_Bit);

		//Timer Direction
		if (TIMERx_Dir == TIMERx_Dir_DownCounting)
		{
			temp |= TIMERx_CR1_DIR;
		}
		else if (TIMERx_Dir == TIMERx_Dir_UpCounting)
		{
			temp &=~ TIMERx_CR1_DIR;
		}
		Timer3_Ptr->CR1 = temp;
		break;


	case Timer4:
		temp = Timer4_Ptr->CR1;
		//Clock division
		temp &=~ (TIMERx_CKD_Length<<TIMERx_CKD_Bit);
		temp |= (TIMERx_ClockDiv<<TIMERx_CKD_Bit);
		//Mode selection
		temp &=~ (TIMERx_CMS_Length<<TIMERx_CMS_Bit);
		temp |= (TIMERx_Mode<<TIMERx_CMS_Bit);

		//Timer Direction
		if (TIMERx_Dir == TIMERx_Dir_DownCounting)
		{
			temp |= TIMERx_CR1_DIR;
		}
		else if (TIMERx_Dir == TIMERx_Dir_UpCounting)
		{
			temp &=~ TIMERx_CR1_DIR;
		}
		Timer4_Ptr->CR1 = temp;
		break;


	case Timer5:
		temp = Timer5_Ptr->CR1;
		//Clock division
		temp &=~ (TIMERx_CKD_Length<<TIMERx_CKD_Bit);
		temp |= (TIMERx_ClockDiv<<TIMERx_CKD_Bit);
		//Mode selection
		temp &=~ (TIMERx_CMS_Length<<TIMERx_CMS_Bit);
		temp |= (TIMERx_Mode<<TIMERx_CMS_Bit);

		//Timer Direction
		if (TIMERx_Dir == TIMERx_Dir_DownCounting)
		{
			temp |= TIMERx_CR1_DIR;
		}
		else if (TIMERx_Dir == TIMERx_Dir_UpCounting)
		{
			temp &=~ TIMERx_CR1_DIR;
		}
		Timer5_Ptr->CR1 = temp;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_AutoRelconfig(u8 Timer  ,u32 TIMERx_AutoRel)
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		//Preload selection
		if (TIMERx_AutoRel == TIMERx_AutoRel_On)
		{
			Timer2_Ptr->CR1 |= TIMERx_CR1_APRE;
		}
		else if (TIMERx_AutoRel == TIMERx_AutoRel_Off)
		{
			Timer2_Ptr->CR1 &=~ TIMERx_CR1_APRE;
		}
		break;

	case Timer3:
		//Preload selection
		if (TIMERx_AutoRel == TIMERx_AutoRel_On)
		{
			Timer3_Ptr->CR1 |= TIMERx_CR1_APRE;
		}
		else if (TIMERx_AutoRel == TIMERx_AutoRel_Off)
		{
			Timer3_Ptr->CR1 &=~ TIMERx_CR1_APRE;
		}
		break;


	case Timer4:
		//Preload selection
		if (TIMERx_AutoRel == TIMERx_AutoRel_On)
		{
			Timer4_Ptr->CR1 |= TIMERx_CR1_APRE;
		}
		else if (TIMERx_AutoRel == TIMERx_AutoRel_Off)
		{
			Timer4_Ptr->CR1 &=~ TIMERx_CR1_APRE;
		}
		break;


	case Timer5:
		//Preload selection
		if (TIMERx_AutoRel == TIMERx_AutoRel_On)
		{
			Timer5_Ptr->CR1 |= TIMERx_CR1_APRE;
		}
		else if (TIMERx_AutoRel == TIMERx_AutoRel_Off)
		{
			Timer5_Ptr->CR1 &=~ TIMERx_CR1_APRE;
		}
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_OPMconfig(u8 Timer ,u32 TIMERx_OnePulseMode )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		//One-pulse mode selection
		if (TIMERx_OnePulseMode == TIMERx_OnePulseMode_On)
		{
			Timer2_Ptr->CR1 |= TIMERx_CR1_OPM;
		}
		else if (TIMERx_OnePulseMode == TIMERx_OnePulseMode_Off)
		{
			Timer2_Ptr->CR1 &=~ TIMERx_CR1_OPM;
		}
		break;


	case Timer3:
		//One-pulse mode selection
		if (TIMERx_OnePulseMode == TIMERx_OnePulseMode_On)
		{
			Timer3_Ptr->CR1 |= TIMERx_CR1_OPM;
		}
		else if (TIMERx_OnePulseMode == TIMERx_OnePulseMode_Off)
		{
			Timer3_Ptr->CR1 &=~ TIMERx_CR1_OPM;
		}
		break;


	case Timer4:
		//One-pulse mode selection
		if (TIMERx_OnePulseMode == TIMERx_OnePulseMode_On)
		{
			Timer4_Ptr->CR1 |= TIMERx_CR1_OPM;
		}
		else if (TIMERx_OnePulseMode == TIMERx_OnePulseMode_Off)
		{
			Timer4_Ptr->CR1 &=~ TIMERx_CR1_OPM;
		}
		break;


	case Timer5:
		//One-pulse mode selection
		if (TIMERx_OnePulseMode == TIMERx_OnePulseMode_On)
		{
			Timer5_Ptr->CR1 |= TIMERx_CR1_OPM;
		}
		else if (TIMERx_OnePulseMode == TIMERx_OnePulseMode_Off)
		{
			Timer5_Ptr->CR1 &=~ TIMERx_CR1_OPM;
		}
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_UEVsrc(u8 Timer , u32 TIMERx_UpdateReqSrc )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		//Update Event source
		if (TIMERx_UpdateReqSrc == TIMERx_UpdateReqSrc_OverUnderFlow)
		{
			Timer2_Ptr->CR1 |= TIMERx_CR1_URS;
		}
		else if (TIMERx_UpdateReqSrc == TIMERx_UpdateReqSrc_All)
		{
			Timer2_Ptr->CR1 &=~ TIMERx_CR1_URS;
		}
		break;


	case Timer3:
		//Update Event source
		if (TIMERx_UpdateReqSrc == TIMERx_UpdateReqSrc_OverUnderFlow)
		{
			Timer3_Ptr->CR1 |= TIMERx_CR1_URS;
		}
		else if (TIMERx_UpdateReqSrc == TIMERx_UpdateReqSrc_All)
		{
			Timer3_Ptr->CR1 &=~ TIMERx_CR1_URS;
		}
		break;


	case Timer4:
		//Update Event source
		if (TIMERx_UpdateReqSrc == TIMERx_UpdateReqSrc_OverUnderFlow)
		{
			Timer4_Ptr->CR1 |= TIMERx_CR1_URS;
		}
		else if (TIMERx_UpdateReqSrc == TIMERx_UpdateReqSrc_All)
		{
			Timer4_Ptr->CR1 &=~ TIMERx_CR1_URS;
		}
		break;


	case Timer5:
		if (TIMERx_UpdateReqSrc == TIMERx_UpdateReqSrc_OverUnderFlow)
		{
			Timer5_Ptr->CR1 |= TIMERx_CR1_URS;
		}
		else if (TIMERx_UpdateReqSrc == TIMERx_UpdateReqSrc_All)
		{
			Timer5_Ptr->CR1 &=~ TIMERx_CR1_URS;
		}
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_UEVconfig(u8 Timer , u32 TIMERx_UpdateEv )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		//Update Event Selection
		if (TIMERx_UpdateEv == TIMERx_UpdateEv_Off)
		{
			Timer2_Ptr->CR1 |= TIMERx_CR1_UDIS;
		}
		else if (TIMERx_UpdateEv == TIMERx_UpdateEv_On)
		{
			Timer2_Ptr->CR1 &=~ TIMERx_CR1_UDIS;
		}
		break;

	case Timer3:
		//Update Event Selection
		if (TIMERx_UpdateEv == TIMERx_UpdateEv_Off)
		{
			Timer3_Ptr->CR1 |= TIMERx_CR1_UDIS;
		}
		else if (TIMERx_UpdateEv == TIMERx_UpdateEv_On)
		{
			Timer3_Ptr->CR1 &=~ TIMERx_CR1_UDIS;
		}
		break;

	case Timer4:
		//Update Event Selection
		if (TIMERx_UpdateEv == TIMERx_UpdateEv_Off)
		{
			Timer4_Ptr->CR1 |= TIMERx_CR1_UDIS;
		}
		else if (TIMERx_UpdateEv == TIMERx_UpdateEv_On)
		{
			Timer4_Ptr->CR1 &=~ TIMERx_CR1_UDIS;
		}
		break;

	case Timer5:
		//Update Event Selection
		if (TIMERx_UpdateEv == TIMERx_UpdateEv_Off)
		{
			Timer5_Ptr->CR1 |= TIMERx_CR1_UDIS;
		}
		else if (TIMERx_UpdateEv == TIMERx_UpdateEv_On)
		{
			Timer5_Ptr->CR1 &=~ TIMERx_CR1_UDIS;
		}
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_Start(u8 Timer )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->CR1 |= TIMERx_CR1_CEN;
		break;

	case Timer3:
		Timer3_Ptr->CR1 |= TIMERx_CR1_CEN;
		break;

	case Timer4:
		Timer4_Ptr->CR1 |= TIMERx_CR1_CEN;
		break;

	case Timer5:
		Timer5_Ptr->CR1 |= TIMERx_CR1_CEN;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_Stop(u8 Timer )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->CR1 &=~ TIMERx_CR1_CEN;
		break;

	case Timer3:
		Timer3_Ptr->CR1 &=~ TIMERx_CR1_CEN;
		break;

	case Timer4:
		Timer4_Ptr->CR1 &=~ TIMERx_CR1_CEN;
		break;

	case Timer5:
		Timer5_Ptr->CR1 &=~ TIMERx_CR1_CEN;
		break;
	}
	errstate = res_OK;
	return errstate;
}


res_t TIMERx_DMAchEnable(u8 Timer , u32 TIMERx_CapComCH )
{
	u8 errstate = res_ERROR;
	TIMERx_CapComCH = TIMERx_CapComCH <<DIER_DMA_INTBiteOffset;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->DIER |= TIMERx_CapComCH;
		break;

	case Timer3:
		Timer3_Ptr->DIER |= TIMERx_CapComCH;
		break;

	case Timer4:
		Timer4_Ptr->DIER |= TIMERx_CapComCH;
		break;

	case Timer5:
		Timer5_Ptr->DIER |= TIMERx_CapComCH;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_DMAchDisable(u8 Timer , u32 TIMERx_CapComCH )
{
	u8 errstate = res_ERROR;
	TIMERx_CapComCH = TIMERx_CapComCH <<DIER_DMA_INTBiteOffset;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->DIER &=~ TIMERx_CapComCH;
		break;

	case Timer3:
		Timer3_Ptr->DIER &=~ TIMERx_CapComCH;
		break;

	case Timer4:
		Timer4_Ptr->DIER &=~ TIMERx_CapComCH;
		break;

	case Timer5:
		Timer5_Ptr->DIER &=~ TIMERx_CapComCH;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_DMAUpdateEnable(u8 Timer  )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->DIER |= TIMERx_DIER_UDE;
		break;

	case Timer3:
		Timer3_Ptr->DIER |= TIMERx_DIER_UDE;
		break;

	case Timer4:
		Timer4_Ptr->DIER |= TIMERx_DIER_UDE;
		break;

	case Timer5:
		Timer5_Ptr->DIER |= TIMERx_DIER_UDE;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_DMAUpdateDisable(u8 Timer )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->DIER &=~ TIMERx_DIER_UDE;
		break;

	case Timer3:
		Timer3_Ptr->DIER &=~ TIMERx_DIER_UDE;
		break;

	case Timer4:
		Timer4_Ptr->DIER &=~ TIMERx_DIER_UDE;
		break;

	case Timer5:
		Timer5_Ptr->DIER &=~ TIMERx_DIER_UDE;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_DMATriggerEnable(u8 Timer  )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->DIER |= TIMERx_DIER_TDE;
		break;

	case Timer3:
		Timer3_Ptr->DIER |= TIMERx_DIER_TDE;
		break;

	case Timer4:
		Timer4_Ptr->DIER |= TIMERx_DIER_TDE;
		break;

	case Timer5:
		Timer5_Ptr->DIER |= TIMERx_DIER_TDE;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_DMATriggerDisable(u8 Timer )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->DIER &=~ TIMERx_DIER_TDE;
		break;

	case Timer3:
		Timer3_Ptr->DIER &=~ TIMERx_DIER_TDE;
		break;

	case Timer4:
		Timer4_Ptr->DIER &=~ TIMERx_DIER_TDE;
		break;

	case Timer5:
		Timer5_Ptr->DIER &=~ TIMERx_DIER_TDE;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_INTchEnable(u8 Timer , u32 TIMERx_CapComCH )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->DIER |= TIMERx_CapComCH;
		break;

	case Timer3:
		Timer3_Ptr->DIER |= TIMERx_CapComCH;
		break;

	case Timer4:
		Timer4_Ptr->DIER |= TIMERx_CapComCH;
		break;

	case Timer5:
		Timer5_Ptr->DIER |= TIMERx_CapComCH;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_INTchDisable(u8 Timer , u32 TIMERx_CapComCH )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->DIER &=~ TIMERx_CapComCH;
		break;

	case Timer3:
		Timer3_Ptr->DIER &=~ TIMERx_CapComCH;
		break;

	case Timer4:
		Timer4_Ptr->DIER &=~ TIMERx_CapComCH;
		break;

	case Timer5:
		Timer5_Ptr->DIER &=~ TIMERx_CapComCH;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_INTUpdateEnable(u8 Timer  )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->DIER |= TIMERx_DIER_UIE;
		break;

	case Timer3:
		Timer3_Ptr->DIER |= TIMERx_DIER_UIE;
		break;

	case Timer4:
		Timer4_Ptr->DIER |= TIMERx_DIER_UIE;
		break;

	case Timer5:
		Timer5_Ptr->DIER |= TIMERx_DIER_UIE;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_INTUpdateDisable(u8 Timer )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->DIER &=~ TIMERx_DIER_UIE;
		break;

	case Timer3:
		Timer3_Ptr->DIER &=~ TIMERx_DIER_UIE;
		break;

	case Timer4:
		Timer4_Ptr->DIER &=~ TIMERx_DIER_UIE;
		break;

	case Timer5:
		Timer5_Ptr->DIER &=~ TIMERx_DIER_UIE;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_INTTriggerEnable(u8 Timer  )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->DIER |= TIMERx_DIER_TIE;
		break;

	case Timer3:
		Timer3_Ptr->DIER |= TIMERx_DIER_TIE;
		break;

	case Timer4:
		Timer4_Ptr->DIER |= TIMERx_DIER_TIE;
		break;

	case Timer5:
		Timer5_Ptr->DIER |= TIMERx_DIER_TIE;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_INTTriggerDisable(u8 Timer )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->DIER &=~ TIMERx_DIER_TIE;
		break;

	case Timer3:
		Timer3_Ptr->DIER &=~ TIMERx_DIER_TIE;
		break;

	case Timer4:
		Timer4_Ptr->DIER &=~ TIMERx_DIER_TIE;
		break;

	case Timer5:
		Timer5_Ptr->DIER &=~ TIMERx_DIER_TIE;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_TriggerEventchEnable(u8 Timer , u32 TIMERx_CapComCH )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->EGR |= TIMERx_CapComCH;
		break;

	case Timer3:
		Timer3_Ptr->EGR |= TIMERx_CapComCH;
		break;

	case Timer4:
		Timer4_Ptr->EGR |= TIMERx_CapComCH;
		break;

	case Timer5:
		Timer5_Ptr->EGR |= TIMERx_CapComCH;
		break;
	}
	errstate = res_OK;
	return errstate;
}


res_t TIMERx_TriggerEventchDisable(u8 Timer , u32 TIMERx_CapComCH )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->EGR &=~ TIMERx_CapComCH;
		break;

	case Timer3:
		Timer3_Ptr->EGR &=~ TIMERx_CapComCH;
		break;

	case Timer4:
		Timer4_Ptr->EGR &=~ TIMERx_CapComCH;
		break;

	case Timer5:
		Timer5_Ptr->EGR &=~ TIMERx_CapComCH;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_TriggerEventUpdateGen(u8 Timer  )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->EGR |= TIMERx_EGR_UG;
		break;

	case Timer3:
		Timer3_Ptr->EGR |= TIMERx_EGR_UG;
		break;

	case Timer4:
		Timer4_Ptr->EGR |= TIMERx_EGR_UG;
		break;

	case Timer5:
		Timer5_Ptr->EGR |= TIMERx_EGR_UG;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_TriggerEventGen(u8 Timer  )
{
	u8 errstate = res_ERROR;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->EGR |= TIMERx_EGR_TG;
		break;

	case Timer3:
		Timer3_Ptr->EGR |= TIMERx_EGR_TG;
		break;

	case Timer4:
		Timer4_Ptr->EGR |= TIMERx_EGR_TG;
		break;

	case Timer5:
		Timer5_Ptr->EGR |= TIMERx_EGR_TG;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_CapComchEnable(u8 Timer , u32 TIMERx_CCER_CapComCH , u32 TIMERx_CCER_Polarity )
{
	u8 errstate = res_ERROR;
	u32 TIMERx_CCER_Polarity_Bit = TIMERx_CCER_CapComCH <<CCER_CapCom_PolarityBiteOffset;
	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->CCER |= TIMERx_CCER_CapComCH;
		if (TIMERx_CCER_Polarity == TIMERx_CCER_Polarity_Rising)
		{
			Timer2_Ptr->CCER |= TIMERx_CCER_Polarity_Bit;
		}
		else if (TIMERx_CCER_Polarity == TIMERx_CCER_Polarity_Falling)
		{
			Timer2_Ptr->CCER &=~ TIMERx_CCER_Polarity_Bit;
		}
		break;

	case Timer3:
		Timer3_Ptr->CCER |= TIMERx_CCER_CapComCH;
		if (TIMERx_CCER_Polarity == TIMERx_CCER_Polarity_Rising)
		{
			Timer3_Ptr->CCER |= TIMERx_CCER_Polarity_Bit;
		}
		else if (TIMERx_CCER_Polarity == TIMERx_CCER_Polarity_Falling)
		{
			Timer3_Ptr->CCER &=~ TIMERx_CCER_Polarity_Bit;
		}
		break;

	case Timer4:
		Timer4_Ptr->CCER |= TIMERx_CCER_CapComCH;
		if (TIMERx_CCER_Polarity == TIMERx_CCER_Polarity_Rising)
		{
			Timer4_Ptr->CCER |= TIMERx_CCER_Polarity_Bit;
		}
		else if (TIMERx_CCER_Polarity == TIMERx_CCER_Polarity_Falling)
		{
			Timer4_Ptr->CCER &=~ TIMERx_CCER_Polarity_Bit;
		}
		break;

	case Timer5:
		Timer5_Ptr->CCER |= TIMERx_CCER_CapComCH;
		if (TIMERx_CCER_Polarity == TIMERx_CCER_Polarity_Rising)
		{
			Timer5_Ptr->CCER |= TIMERx_CCER_Polarity_Bit;
		}
		else if (TIMERx_CCER_Polarity == TIMERx_CCER_Polarity_Falling)
		{
			Timer5_Ptr->CCER &=~ TIMERx_CCER_Polarity_Bit;
		}
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_CapComchDisable(u8 Timer , u32 TIMERx_CCER_CapComCH )
{
	u8 errstate = res_ERROR;

	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->CCER &=~ TIMERx_CCER_CapComCH;
		break;

	case Timer3:
		Timer3_Ptr->CCER &=~ TIMERx_CCER_CapComCH;
		break;

	case Timer4:
		Timer4_Ptr->CCER &=~ TIMERx_CCER_CapComCH;
		break;

	case Timer5:
		Timer5_Ptr->CCER &=~ TIMERx_CCER_CapComCH;
		break;
	}
	errstate = res_OK;
	return errstate;
}

u16 TIMERx_ReadCNT(u8 Timer )
{
	volatile u16 TimerValue = 0;

	switch (Timer)
	{
	case Timer2:
		TimerValue = Timer2_Ptr->CNT;
		break;

	case Timer3:
		TimerValue = Timer3_Ptr->CNT;
		break;

	case Timer4:
		TimerValue = Timer4_Ptr->CNT;
		break;

	case Timer5:
		TimerValue = Timer5_Ptr->CNT;
		break;
	}
	return TimerValue;

}

res_t TIMERx_WriteCNT(u8 Timer , u16 TIMERx_CNTValue )
{
	u8 errstate = res_ERROR;
	TIMERx_Stop(Timer);

	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->CNT = TIMERx_CNTValue;
		break;

	case Timer3:
		Timer3_Ptr->CNT = TIMERx_CNTValue;
		break;

	case Timer4:
		Timer4_Ptr->CNT = TIMERx_CNTValue;
		break;

	case Timer5:
		Timer5_Ptr->CNT = TIMERx_CNTValue;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_WritePSC(u8 Timer , u16 TIMERx_PSCValue )
{
	u8 errstate = res_ERROR;

	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->PSC = TIMERx_PSCValue;
		break;

	case Timer3:
		Timer3_Ptr->PSC = TIMERx_PSCValue;
		break;

	case Timer4:
		Timer4_Ptr->PSC = TIMERx_PSCValue;
		break;

	case Timer5:
		Timer5_Ptr->PSC = TIMERx_PSCValue;
		break;
	}

	errstate = res_OK;
	return errstate;
}

res_t TIMERx_WriteARR(u8 Timer , u16 TIMERx_ARRValue )
{
	u8 errstate = res_ERROR;

	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->ARR = TIMERx_ARRValue;
		break;

	case Timer3:
		Timer3_Ptr->ARR = TIMERx_ARRValue;
		break;

	case Timer4:
		Timer4_Ptr->ARR = TIMERx_ARRValue;
		break;

	case Timer5:
		Timer5_Ptr->ARR = TIMERx_ARRValue;
		break;
	}

	errstate = res_OK;
	return errstate;
}

res_t TIMERx_WriteDMAadd(u8 Timer , u16 TIMERx_DMAadd )

{
	u8 errstate = res_ERROR;

	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->DMAR = TIMERx_DMAadd;
		break;

	case Timer3:
		Timer3_Ptr->DMAR = TIMERx_DMAadd;
		break;

	case Timer4:
		Timer4_Ptr->DMAR = TIMERx_DMAadd;
		break;

	case Timer5:
		Timer5_Ptr->DMAR = TIMERx_DMAadd;
		break;
	}

	errstate = res_OK;
	return errstate;
}

res_t TIMERx_CompareModeCFG(u8 Timer , u8 TIMERx_CCMRch , u8 TIMERx_CCMR_OCFE , u8 TIMERx_CCMR_OCPE , u8 TIMERx_CCMR_OCM , u8 TIMERx_CCMR_OCCE)
{
	u8 errstate = res_ERROR;
	u8 LocalArrIndex = TIMERx_CCMRch/TIMERx_CCMR_RegOffset;
	//Channel selection in for each register
	if ( LocalArrIndex == TIMERx_CCMR2)
	{
		TIMERx_CCMRch -= TIMERx_CCMR_RegOffset;
	}
	u16 temp = 0;
	switch (Timer)
	{
	case Timer2:
		temp = Timer2_Ptr->CCMR[LocalArrIndex];
		break;

	case Timer3:
		temp = Timer3_Ptr->CCMR[LocalArrIndex];
		break;

	case Timer4:
		temp = Timer4_Ptr->CCMR[LocalArrIndex] ;
		break;

	case Timer5:
		temp = Timer5_Ptr->CCMR[LocalArrIndex] ;
		break;
	}

	temp &=~ (TIMERx_CCMR_CCS_Length << TIMERx_CCMRch);
	temp |= (TIMERx_CCMRMode_Compare<< TIMERx_CCMRch);

	//Output compare mode preload enable
	if (TIMERx_CCMR_OCPE == TIMERx_CCMR_OCPE_On)
	{
		temp |= (TIMERx_CCMR_OCPE_Bit<<TIMERx_CCMRch);

	}
	else if (TIMERx_CCMR_OCPE == TIMERx_CCMR_OCPE_Off)
	{
		temp &=~ (TIMERx_CCMR_OCPE_Bit<<TIMERx_CCMRch);
	}
	//Counter compare mode selection
	temp &=~ (TIMERx_CCMR_OCM_Length << (TIMERx_CCMR_OCM_Bit + TIMERx_CCMRch));
	temp |= (TIMERx_CCMR_OCM<< (TIMERx_CCMR_OCM_Bit + TIMERx_CCMRch));
	//Output compare mode fast enable
	if (TIMERx_CCMR_OCFE == TIMERx_CCMR_OCFE_On)
	{
		temp |= (TIMERx_CCMR_OCFE_Bit<<TIMERx_CCMRch);

	}
	else if (TIMERx_CCMR_OCFE == TIMERx_CCMR_OCFE_Off)
	{
		temp &=~ (TIMERx_CCMR_OCFE_Bit<<TIMERx_CCMRch);
	}
	//Output compare clear enable
	if (TIMERx_CCMR_OCCE == TIMERx_CCMR_OCCE_On)
	{
		temp |= (TIMERx_CCMR_OCCE_Bit<<TIMERx_CCMRch);

	}
	else if (TIMERx_CCMR_OCCE == TIMERx_CCMR_OCCE_Off)
	{
		temp &=~ (TIMERx_CCMR_OCCE_Bit<<TIMERx_CCMRch);
	}

	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->CCMR[LocalArrIndex] = temp;
		break;

	case Timer3:
		Timer3_Ptr->CCMR[LocalArrIndex] = temp;
		break;

	case Timer4:
		Timer4_Ptr->CCMR[LocalArrIndex] = temp ;
		break;

	case Timer5:
		Timer5_Ptr->CCMR[LocalArrIndex]  = temp;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_CaptureModeCFG(u8 Timer , u8 TIMERx_CCMRch , u8 TIMERx_CCMRMode , u8 TIMERx_CCMR_ICF , u8 TIMERx_CCMR_ICPSC )
{
	u8 errstate = res_ERROR;
	u8 LocalArrIndex = TIMERx_CCMRch/TIMERx_CCMR_RegOffset;
	//Channel selection in for each register
	if ( LocalArrIndex == TIMERx_CCMR2)
	{
		TIMERx_CCMRch -= TIMERx_CCMR_RegOffset;
	}
	u16 temp = 0;
	switch (Timer)
	{
	case Timer2:
		temp = Timer2_Ptr->CCMR[LocalArrIndex];
		break;

	case Timer3:
		temp = Timer3_Ptr->CCMR[LocalArrIndex];
		break;

	case Timer4:
		temp = Timer4_Ptr->CCMR[LocalArrIndex] ;
		break;

	case Timer5:
		temp = Timer5_Ptr->CCMR[LocalArrIndex] ;
		break;
	}
	//Channel mode
	temp &=~ (TIMERx_CCMR_CCS_Length << TIMERx_CCMRch);
	temp |= (TIMERx_CCMRMode<< TIMERx_CCMRch);
	//Input capture filter
	temp &=~ (TIMERx_CCMR_ICF_Length << (TIMERx_CCMR_ICF_Bit + TIMERx_CCMRch));
	temp |= (TIMERx_CCMR_ICF<< (TIMERx_CCMR_ICF_Bit + TIMERx_CCMRch));
	//Input capture prescaler
	temp &=~ (TIMERx_CCMR_ICPSC_Length << (TIMERx_CCMR_ICPSC_Bit + TIMERx_CCMRch));
	temp |= (TIMERx_CCMR_ICPSC<< (TIMERx_CCMR_ICPSC_Bit + TIMERx_CCMRch));


	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->CCMR[LocalArrIndex] = temp;
		break;

	case Timer3:
		Timer3_Ptr->CCMR[LocalArrIndex] = temp;
		break;

	case Timer4:
		Timer4_Ptr->CCMR[LocalArrIndex] = temp ;
		break;

	case Timer5:
		Timer5_Ptr->CCMR[LocalArrIndex]  = temp;
		break;
	}
	errstate = res_OK;
	return errstate;
}

res_t TIMERx_WriteCCR(u8 Timer , u8 TIMERx_CCRch , u16 TIMERx_CCRValue )
{
	u8 errstate = res_ERROR;

	switch (Timer)
	{
	case Timer2:
		Timer2_Ptr->CCR[TIMERx_CCRch] = TIMERx_CCRValue;
		break;

	case Timer3:
		Timer3_Ptr->CCR[TIMERx_CCRch] = TIMERx_CCRValue;
		break;

	case Timer4:
		Timer4_Ptr->CCR[TIMERx_CCRch] = TIMERx_CCRValue;
		break;

	case Timer5:
		Timer5_Ptr->CCR[TIMERx_CCRch] = TIMERx_CCRValue;
		break;
	}

	errstate = res_OK;
	return errstate;
}

u16 TIMERx_ReadCCR(u8 Timer ,u8 TIMERx_CCRch  )
{
	volatile u16 CCRValue = 0;

	switch (Timer)
	{
	case Timer2:
		CCRValue = Timer2_Ptr->CCR[TIMERx_CCRch];
		break;

	case Timer3:
		CCRValue = Timer3_Ptr->CCR[TIMERx_CCRch];
		break;

	case Timer4:
		CCRValue = Timer4_Ptr->CCR[TIMERx_CCRch];
		break;

	case Timer5:
		CCRValue = Timer5_Ptr->CCR[TIMERx_CCRch];
		break;
	}
	return CCRValue;

}



void TIM2_callbackFn (void (*ptr)(void))
{
	TIM2CallBackPtr= ptr;
}

void TIM2_IRQHandler(void)
{
	TIM2CallBackPtr();

}


void TIM3_callbackFn (void (*ptr)(void))
{
	TIM3CallBackPtr= ptr;
}

void TIM3_IRQHandler(void)
{
	TIM3CallBackPtr();

}

void TIM4_callbackFn (void (*ptr)(void))
{
	TIM4CallBackPtr= ptr;
}

void TIM4_IRQHandler(void)
{
	TIM4CallBackPtr();

}


void TIM5_callbackFn (void (*ptr)(void))
{
	TIM5CallBackPtr= ptr;
}

void TIM5_IRQHandler(void)
{
	TIM5CallBackPtr();

}

/*

void delay_us(uint32_t us)
{
    // Configure the timer for a delay of us microseconds
    TIM2->PSC = TIMER_PRESCALER;
    TIM2->ARR = us * (TIMER_CLOCK_FREQ / 1000000) - 1;

    // Start the timer
    TIM2->CNT = 0;
    TIM2->CR1 |= TIM_CR1_CEN;

    // Wait until the timer counts down to zero
    while ((TIM2->SR & TIM_SR_UIF) == 0);

    // Stop the timer
    TIM2->CR1 &= ~TIM_CR1_CEN;
    TIM2->SR &= ~TIM_SR_UIF;
}
/*/
