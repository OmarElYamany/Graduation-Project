//includes

#include "RCC.h"

//defines

#define RCC_BaseAdd     0x40021000
#define	RCC_CFGR_SW_LENGTH	0x03

//system clock selection

#define sys_clk_HSI	0x00
#define sys_clk_HSE	0x01
#define sys_clk_PLL	0x02




//CR bits

#define RCC_CR_HSION 		BIT0_MASK
#define RCC_CR_HSIRDY 		BIT1_MASK

#define RCC_CR_HSITRIM_BIT		3
#define RCC_CR_HSITRIM_LENGTH 	0x1f

#define RCC_CR_HSICAL_BIT		8
#define RCC_CR_HSICAL_LENGTH	0xff

#define RCC_CR_HSEON	 	BIT16_MASK
#define RCC_CR_HSERDY	 	BIT17_MASK
#define RCC_CR_HSEBYP		BIT18_MASK
#define RCC_CR_CSSON	 	BIT19_MASK
#define RCC_CR_PLLON	 	BIT24_MASK
#define RCC_CR_PLLRDY		BIT25_MASK

//CFGR bits

#define RCC_CFGR_SW_BIT			0
#define	RCC_CFGR_SW_LENGTH		0x03

#define RCC_CFGR_SWS_BIT		2
#define	RCC_CFGR_SWS_LENGTH		0x03

//AHB prescaler
#define RCC_CFGR_HPRE_BIT 		4
#define RCC_CFGR_HPRE_LENGTH	0x0f

//APB1 prescaler
#define RCC_CFGR_PPRE1_BIT		8
#define RCC_CFGR_PPRE1_LENGTH	0x07



//APB2 prescaler
#define RCC_CFGR_PPRE2_BIT		11
#define RCC_CFGR_PPRE2_LENGTH	0x07

#define RCC_CFGR_ADCPRE_BIT		14
#define RCC_CFGR_ADCPRE_LENGTH 	0x03

#define RCC_CFGR_PLLSRC 		BIT16_MASK
#define RCC_CFGR_PLLXTPRE		BIT17_MASK

//pll multiplexer
#define RCC_CFGR_PLLMUL_BIT		18
#define RCC_CFGR_PLLMUL_LENGTH	0x0f


#define RCC_CFGR_USBPRE			BIT22_MASK

#define RCC_CFGR_MCO_BIT 		24
#define RCC_CFGR_MCO_LENGTH 	0x07


//CIR bits

#define RCC_CIR_LSIRDYF		BIT0_MASK
#define RCC_CIR_LSERDYF		BIT1_MASK
#define RCC_CIR_HSIRDYF		BIT2_MASK
#define RCC_CIR_HSERDYF		BIT3_MASK
#define RCC_CIR_PLLRDYF		BIT4_MASK
#define RCC_CIR_CSSF		BIT7_MASK
#define RCC_CIR_LSIRDYIE	BIT8_MASK
#define RCC_CIR_LSERDYIE	BIT9_MASK
#define RCC_CIR_HSIRDYIE	BIT10_MASK
#define RCC_CIR_HSERDYIE	BIT11_MASK
#define RCC_CIR_PLLRDYIE	BIT12_MASK
#define RCC_CIR_LSIRDYC		BIT16_MASK
#define RCC_CIR_LSERDYC		BIT17_MASK
#define RCC_CIR_HSIRDYC		BIT18_MASK
#define RCC_CIR_HSERDYC		BIT19_MASK
#define RCC_CIR_PLLRDYC		BIT20_MASK
#define RCC_CIR_CSSC		BIT23_MASK

//BDCR bits

#define RCC_BDCR_LSEON		BIT0_MASK
#define RCC_BDCR_LSERDY		BIT1_MASK
#define RCC_BDCR_LSEBYP		BIT2_MASK

#define RCC_BDCR_RTCSEL_BIT			8
#define RCC_BDCR_RTCSEL_LENGTH		0X03

#define RCC_BDCR_RTCEN		BIT15_MASK
#define RCC_BDCR_BDRST		BIT16_MASK

//CSR bits

#define RCC_CSR_LSION		BIT0_MASK
#define RCC_CSR_LSIRDY		BIT1_MASK
#define RCC_CSR_RMVF		BIT24_MASK
#define RCC_CSR_PINRSTF		BIT26_MASK
#define RCC_CSR_PORRSTF		BIT27_MASK
#define RCC_CSR_SFTRSTF		BIT28_MASK
#define RCC_CSR_IWDGRSTF	BIT29_MASK
#define RCC_CSR_WWDGRSTF	BIT30_MASK
#define RCC_CSR_LPWRRSTF	BIT31_MASK

//types

typedef struct
{
	volatile u32 CR;
	volatile u32 CFGR;
	volatile u32 CIR;
	volatile u32 APB2RSTR;
	volatile u32 APB1RSTR;
	volatile u32 AHBENR;
	volatile u32 APB2ENR;
	volatile u32 APB1ENR;
	volatile u32 BDCR;
	volatile u32 CSR;
}RCC_Struct;

//variables

static volatile RCC_Struct * const RCC_Ptr = (volatile RCC_Struct * const) RCC_BaseAdd;


// static functions prototypes


// interface functions implementation

res_t RCC_DisableSysClk(u32 clk)
{
	u8 errstate = res_ERROR;
	if (clk == clk_HSE)
	{
		RCC_Ptr->CR &=~ RCC_CR_HSEON;
		while ((RCC_Ptr->CR & RCC_CR_HSERDY) == 1);
		errstate= res_OK;
	}
	else if (clk == clk_HSI)
	{
		RCC_Ptr->CR &=~ RCC_CR_HSION;
		while ((RCC_Ptr->CR & RCC_CR_HSIRDY) == 1);
		errstate= res_OK;
	}
	else if (clk == clk_PLL)
	{
		RCC_Ptr->CR &=~ RCC_CR_PLLON;
		while ((RCC_Ptr->CR & RCC_CR_PLLRDY) == 1);
		errstate= res_OK;
	}
	return errstate;
}
res_t RCC_EnableSysClk(u32 clk)
{
	u8 errstate = res_ERROR;
	if (clk == clk_HSE)
	{
		RCC_Ptr->CR |= RCC_CR_HSEON;
		while ((RCC_Ptr->CR & RCC_CR_HSERDY) == 0);
		errstate= res_OK;
	}
	else if (clk == clk_HSI)
	{
		RCC_Ptr->CR |= RCC_CR_HSION;
		while ((RCC_Ptr->CR & RCC_CR_HSIRDY) == 0);
		errstate= res_OK;
	}
	else if (clk == clk_PLL)
	{
		RCC_Ptr->CR |= RCC_CR_PLLON;
		while ((RCC_Ptr->CR & RCC_CR_PLLRDY) == 0);
		errstate= res_OK;
	}
	return errstate;
}
res_t RCC_SelectSysClk(u32 sys_clk)
{
	/*selecting system clock*/
	u8 errstate= res_ERROR;
	u32 temp = RCC_Ptr->CFGR;
	temp &=~ (RCC_CFGR_SW_LENGTH<<RCC_CFGR_SW_BIT);
	temp |=	 (sys_clk<<RCC_CFGR_SW_BIT);
	RCC_Ptr->CFGR=temp;
	errstate=res_OK;
	/*checking that selecting the system clock is done*/
	u32 temp2 = RCC_Ptr->CFGR;
	temp2 &= (RCC_CFGR_SWS_LENGTH<<RCC_CFGR_SWS_BIT);
	while((temp2>>RCC_CFGR_SWS_BIT) != sys_clk);

	return errstate;

}
res_t RCC_CfgPLL(u32 pll_src, u32 pllmul , u32 HSEDiv)
{
	u8 errstate = res_ERROR;
	u32 temp=RCC_Ptr->CFGR;
	if (pll_src == pll_src_HSE)
	{
		if (HSEDiv == HSEDiv_2)
		{
			temp |= RCC_CFGR_PLLXTPRE;
		}
		else if(HSEDiv == HSEDiv_0)
		{
			temp &=~ RCC_CFGR_PLLXTPRE;
		}
		temp |= RCC_CFGR_PLLSRC;
	}
	else if (pll_src == pll_src_HSI)
	{
		temp &=~ RCC_CFGR_PLLSRC;
	}
	temp &=~ (RCC_CFGR_PLLMUL_LENGTH<<RCC_CFGR_PLLMUL_BIT);
	temp |=(pllmul<<RCC_CFGR_PLLMUL_BIT);
	RCC_Ptr->CFGR = temp;
	errstate = res_OK;
	return errstate;
}

res_t RCC_EnableAHBPerClk(u32 AHBENRper_clk, u32 AHB_Pre)
{
	u8 errstate=res_ERROR;
	//AHB prescaler select
	u32 temp=RCC_Ptr->CFGR;
	temp &=~(RCC_CFGR_HPRE_LENGTH<<RCC_CFGR_HPRE_BIT);
	temp |=(AHB_Pre<<RCC_CFGR_HPRE_BIT);
	RCC_Ptr->CFGR = temp;
	//AHB peripheral enable
	RCC_Ptr->AHBENR |= AHBENRper_clk;

	errstate=res_OK;
	return errstate;
}
res_t RCC_SetAHBPrescaler( u32 AHB_Pre)
{
	u8 errstate=res_ERROR;
	//AHB prescaler select
	u32 temp=RCC_Ptr->CFGR;
	temp &=~(RCC_CFGR_HPRE_LENGTH<<RCC_CFGR_HPRE_BIT);
	temp |=(AHB_Pre<<RCC_CFGR_HPRE_BIT);
	RCC_Ptr->CFGR = temp;
	errstate=res_OK;
	return errstate;
}
res_t RCC_EnableAPB2PerClk(u32 APB2ENRper_clk , u32 APB2_Pre)
{
	//APB2 prescaler select
	u32 temp=RCC_Ptr->CFGR;
	temp &=~(RCC_CFGR_PPRE2_LENGTH<<RCC_CFGR_PPRE2_BIT);
	temp |=(APB2_Pre<<RCC_CFGR_PPRE2_BIT);
	RCC_Ptr->CFGR = temp;
	//APB2 peripheral enable
	u8 errstate=res_ERROR;
	RCC_Ptr->APB2ENR |= APB2ENRper_clk;
	errstate=res_OK;
	return errstate;
}

res_t RCC_EnableAPB1PerClk(u32 APB1ENRper_clk , u32 APB1_Pre)
{
	//APB1 prescaler select
	u32 temp=RCC_Ptr->CFGR;
	temp &=~(RCC_CFGR_PPRE1_LENGTH<<RCC_CFGR_PPRE1_BIT);
	temp |=(APB1_Pre<<RCC_CFGR_PPRE1_BIT);
	RCC_Ptr->CFGR = temp;
	//APB1 peripheral enable
	u8 errstate=res_ERROR;
	RCC_Ptr->APB1ENR |= APB1ENRper_clk;
	errstate=res_OK;
	return errstate;
}



