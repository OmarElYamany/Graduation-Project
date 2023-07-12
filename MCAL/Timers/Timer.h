/*
 * Timer.h
 *
 *  Created on: Jun 2, 2023
 *      Author: Omar El Yamany
 */

#ifndef TIMERS_TIMER_H_
#define TIMERS_TIMER_H_
#include "../../Common/Bit_Math.h"
#include "../../Common/util.h"
#include "../../Common/definition.h"
#include "../../Common/STD_Types.h"

//defines
/***************************Timer Configuration options******************************/
//Timer Selection
#define Timer2		0
#define Timer3		1
#define Timer4		2
#define Timer5		3


//Clock Division : Ratio between timer clk frequency and sampling clock used by the  (Tsamp = x * Tclk)
#define TIMERx_ClockDiv_1				0x00
#define TIMERx_ClockDiv_2				0x01
#define TIMERx_ClockDiv_4				0x02


//Auto-reload preload enable/disable
#define TIMERx_AutoRel_On		0
#define TIMERx_AutoRel_Off		1


//Counter mode selection
/*
 * 1-Edge aligned = The counter counts up or down depending on the direction bit
 * 2-CenterAliMode1 = Output compare flags are set only when counting down
 * 3-CenterAliMode2 = Output compare flags are set only when counting up
 * 4-CenterAliMode3 = Output compare flags are set both when counting down or counting up
 */

#define TIMERx_Mode_EdgeAlig				0x00
#define TIMERx_Mode_CenterAlig1				0x01
#define TIMERx_Mode_CenterAlig2				0x02
#define TIMERx_Mode_CenterAlig3				0x03


//Timer Direction
#define TIMERx_Dir_UpCounting				0
#define TIMERx_Dir_DownCounting				1


//Timer One-pulse mode enable/disable
#define TIMERx_OnePulseMode_On		0
#define TIMERx_OnePulseMode_Off		1

//Timer Update Event Sorce
#define TIMERx_UpdateReqSrc_All 					0
#define TIMERx_UpdateReqSrc_OverUnderFlow 			1

//Timer Update Event enable/disable
#define TIMERx_UpdateEv_On		0
#define TIMERx_UpdateEv_Off		1

//DMA/Interrupt capture/compare channels
#define TIMERx_CapComCH_1	BIT1_MASK
#define TIMERx_CapComCH_2	BIT2_MASK
#define TIMERx_CapComCH_3	BIT3_MASK
#define TIMERx_CapComCH_4	BIT4_MASK

/**************Timer capture/compare channels configuration****************/
//Channel selection from 1 to 4
#define TIMERx_CCMRch_CC1S					0
#define TIMERx_CCMRch_CC2S					8
#define TIMERx_CCMRch_CC3S					16
#define TIMERx_CCMRch_CC4S					24
//Channel mode
#define TIMERx_CCMRMode_Compare					0x00
#define TIMERx_CCMRMode_Capture_TI1				0x01
#define TIMERx_CCMRMode_Capture_TI2				0x02
#define TIMERx_CCMRMode_Capture_TRC				0x03
/*********Output Mode (compare)******/
//Output compare mode fast enable
#define TIMERx_CCMR_OCFE_On			0
#define TIMERx_CCMR_OCFE_Off		1
//Output compare mode preload enable
#define TIMERx_CCMR_OCPE_On			0
#define TIMERx_CCMR_OCPE_Off		1
//Counter compare mode selection
/*
 * 1-Frozen = The comparison between the output compare register TIMx_CCR1 and the counter TIMx_CNT has no effect on the outputs.
 * 2-ActiveLVL =  active level on match (OC1REF signal is forced high when the counter TIMx_CNT matches the capture/compare register 1 (TIMx_CCR1)).
 * 3-InactiveLVL = inactive level on match (OC1REF signal is forced low when the counter TIMx_CNT matches the capture/compare register 1 (TIMx_CCR1)).
 * 4-Toggle = OC1REF toggles when TIMx_CNT=TIMx_CCR1.
 * 5-ForceInactiveLVL = OC1REF is forced low.
 * 6-ForceActiveLVL = OC1REF is forced high.
 * 7-PWMmode1 = In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0) as long as TIMx_CNT>TIMx_CCR1 else active (OC1REF=1).
 * 8-PWMmode2 = In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1 else active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else inactive.
 */
#define TIMERx_CCMR_OCM_Frozen					0x00
#define TIMERx_CCMR_OCM_ActiveLVL				0x01
#define TIMERx_CCMR_OCM_InactiveLVL				0x02
#define TIMERx_CCMR_OCM_Toggle					0x03
#define TIMERx_CCMR_OCM_ForceInactiveLVL		0x04
#define TIMERx_CCMR_OCM_ForceActiveLVL			0x05
#define TIMERx_CCMR_OCM_PWMmode1				0x06
#define TIMERx_CCMR_OCM_PWMmode2				0x07

//Output compare clear enable
#define TIMERx_CCMR_OCCE_On			0
#define TIMERx_CCMR_OCCE_Off		1



//Timer capture/compare channels enable and polarity
#define TIMERx_CCER_Polarity_Rising			0
#define TIMERx_CCER_Polarity_Falling		1
#define TIMERx_CCER_CapComCH1				BIT0_MASK
#define TIMERx_CCER_CapComCH2				BIT4_MASK
#define TIMERx_CCER_CapComCH3				BIT8_MASK
#define TIMERx_CCER_CapComCH4				BIT12_MASK


/*********Input Mode (capture)******/
//Input capture filter
/*
 * 1- No filter, sampling is done at fDTS
 * 2- fSAMPLING=fCK_INT, N=2
 * 3- fSAMPLING=fCK_INT, N=4
 * 4- fSAMPLING=fCK_INT, N=8
 * 5- fSAMPLING=fDTS/2, N=6
 * 6- fSAMPLING=fDTS/2, N=8
 * 7- fSAMPLING=fDTS/4, N=6
 * 8- fSAMPLING=fDTS/4, N=8
 * 9- fSAMPLING=fDTS/8, N=6
 * 10-fSAMPLING=fDTS/8, N=8
 * 11-fSAMPLING=fDTS/16, N=5
 * 12-fSAMPLING=fDTS/16, N=6
 * 13-fSAMPLING=fDTS/16, N=8
 * 14-fSAMPLING=fDTS/32, N=5
 * 15-fSAMPLING=fDTS/32, N=6
 * 16-fSAMPLING=fDTS/32, N=8
 */
#define TIMERx_CCMR_ICF_1		0x00
#define TIMERx_CCMR_ICF_2		0x01
#define TIMERx_CCMR_ICF_3		0x02
#define TIMERx_CCMR_ICF_4		0x03
#define TIMERx_CCMR_ICF_5		0x04
#define TIMERx_CCMR_ICF_6		0x05
#define TIMERx_CCMR_ICF_7		0x06
#define TIMERx_CCMR_ICF_8		0x07
#define TIMERx_CCMR_ICF_9		0x08
#define TIMERx_CCMR_ICF_10		0x09
#define TIMERx_CCMR_ICF_11		0x0A
#define TIMERx_CCMR_ICF_12		0x0B
#define TIMERx_CCMR_ICF_13		0x0C
#define TIMERx_CCMR_ICF_14		0x0D
#define TIMERx_CCMR_ICF_15		0x0E
#define TIMERx_CCMR_ICF_16		0x0F
//Input capture prescaler
/*
 * 1- no prescaler, capture is done each time an edge is detected on the capture input
 * 2- capture is done once every 2 events
 * 3- capture is done once every 4 events
 * 4- capture is done once every 8 events
 */
#define TIMERx_CCMR_ICPSC_1		0x00
#define TIMERx_CCMR_ICPSC_2		0x01
#define TIMERx_CCMR_ICPSC_3		0x02
#define TIMERx_CCMR_ICPSC_4		0x03

//CCR channel selection
#define TIMERx_CCRch_1		0
#define TIMERx_CCRch_2		1
#define TIMERx_CCRch_3		2
#define TIMERx_CCRch_4		3




//Clock config
res_t TIMERx_config(u8 Timer , u32 TIMERx_ClockDiv , u32 TIMERx_Mode , u32 TIMERx_Dir );
res_t TIMERx_AutoRelconfig(u8 Timer  ,u32 TIMERx_AutoRel);
res_t TIMERx_OPMconfig(u8 Timer ,u32 TIMERx_OnePulseMode );
res_t TIMERx_UEVsrc(u8 Timer , u32 TIMERx_UpdateReqSrc );
res_t TIMERx_UEVconfig(u8 Timer , u32 TIMERx_UpdateEv );
res_t TIMERx_Start(u8 Timer );
res_t TIMERx_Stop(u8 Timer );
//DMA Config
res_t TIMERx_DMAchEnable(u8 Timer , u32 TIMERx_CapComCH );
res_t TIMERx_DMAchDisable(u8 Timer , u32 TIMERx_CapComCH );
res_t TIMERx_DMAUpdateEnable(u8 Timer  );
res_t TIMERx_DMAUpdateDisable(u8 Timer );
res_t TIMERx_DMATriggerEnable(u8 Timer  );
res_t TIMERx_DMATriggerDisable(u8 Timer );
//Interrupt Config
res_t TIMERx_INTchEnable(u8 Timer , u32 TIMERx_CapComCH );
res_t TIMERx_INTchDisable(u8 Timer , u32 TIMERx_CapComCH );
res_t TIMERx_INTUpdateEnable(u8 Timer  );
res_t TIMERx_INTUpdateDisable(u8 Timer );
res_t TIMERx_INTTriggerEnable(u8 Timer  );
res_t TIMERx_INTTriggerDisable(u8 Timer );
/**********not tested*****************/
//Event triggering config
res_t TIMERx_TriggerEventchEnable(u8 Timer , u32 TIMERx_CapComCH );
res_t TIMERx_TriggerEventchDisable(u8 Timer , u32 TIMERx_CapComCH );
res_t TIMERx_TriggerEventUpdateGen(u8 Timer  );
res_t TIMERx_TriggerEventGen(u8 Timer  );
/************************************/
//Capture/compare channels config
res_t TIMERx_CapComchEnable(u8 Timer , u32 TIMERx_CCER_CapComCH , u32 TIMERx_CCER_Polarity );
res_t TIMERx_CapComchDisable(u8 Timer , u32 TIMERx_CCER_CapComCH );

//Timer capture/compare channels configuration
res_t TIMERx_CompareModeCFG(u8 Timer , u8 TIMERx_CCMRch , u8 TIMERx_CCMR_OCFE , u8 TIMERx_CCMR_OCPE , u8 TIMERx_CCMR_OCM , u8 TIMERx_CCMR_OCCE);
res_t TIMERx_CaptureModeCFG(u8 Timer , u8 TIMERx_CCMRch , u8 TIMERx_CCMRMode , u8 TIMERx_CCMR_ICF , u8 TIMERx_CCMR_ICPSC );

//CNT read/write value
u16 TIMERx_ReadCNT(u8 Timer );
res_t TIMERx_WriteCNT(u8 Timer , u16 TIMERx_CNTValue );
//Prescaler value setting
res_t TIMERx_WritePSC(u8 Timer , u16 TIMERx_PSCValue );
//ARR value setting
res_t TIMERx_WriteARR(u8 Timer , u16 TIMERx_ARRValue );
//DMA address setting
res_t TIMERx_WriteDMAadd(u8 Timer , u16 TIMERx_DMAadd );
//CCR read/write value
res_t TIMERx_WriteCCR(u8 Timer , u8 TIMERx_CCRch , u16 TIMERx_CCRValue );
u16 TIMERx_ReadCCR(u8 Timer ,u8 TIMERx_CCRch  );










#endif /* TIMERS_TIMER_H_ */
