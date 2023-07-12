/*
 * NVIC.h
 *
 *  Created on: May 27, 2023
 *      Author: Omar El Yamany
 */

#ifndef NVIC_NVIC_H_
#define NVIC_NVIC_H_
#include "../../Common/STD_Types.h"
#include "../../Common/definition.h"
#include "../../Common/util.h"

/********************************Interrupt number***********************************/
//ISER0
#define NVIC_Int_0     		0
#define NVIC_Int_1     		1
#define NVIC_Int_2     		2
#define NVIC_Int_3     		3
#define NVIC_Int_4     		4
#define NVIC_Int_5     		5
#define NVIC_Int_6    		6
#define NVIC_Int_7     		7
#define NVIC_Int_8     		8
#define NVIC_Int_9     		9
#define NVIC_Int_10     	10
#define NVIC_Int_11			11
#define NVIC_Int_12     	12
#define NVIC_Int_13     	13
#define NVIC_Int_14     	14
#define NVIC_Int_15     	15
#define NVIC_Int_16     	16
#define NVIC_Int_17     	17
#define NVIC_Int_18     	18
#define NVIC_Int_19     	19
#define NVIC_Int_20     	20
#define NVIC_Int_21     	21
#define NVIC_Int_22     	22
#define NVIC_Int_23     	23
#define NVIC_Int_24     	24
#define NVIC_Int_25     	25
#define NVIC_Int_26     	26
#define NVIC_Int_27     	27
#define NVIC_Int_28     	28
#define NVIC_Int_29     	29
#define NVIC_Int_30     	30
#define NVIC_Int_31     	31

//ISER1
#define NVIC_Int_32    		32
#define NVIC_Int_33    		33
#define NVIC_Int_34    		34
#define NVIC_Int_35    		35
#define NVIC_Int_36    		36
#define NVIC_Int_37    		37
#define NVIC_Int_38    		38
#define NVIC_Int_39    		39
#define NVIC_Int_40     	40
#define NVIC_Int_41     	41
#define NVIC_Int_42     	42
#define NVIC_Int_43			43
#define NVIC_Int_44      	44
#define NVIC_Int_45      	45
#define NVIC_Int_46      	46
#define NVIC_Int_47      	47
#define NVIC_Int_48      	48
#define NVIC_Int_49      	49
#define NVIC_Int_50      	50
#define NVIC_Int_51      	51
#define NVIC_Int_52      	52
#define NVIC_Int_53      	53
#define NVIC_Int_54      	54
#define NVIC_Int_55       	55
#define NVIC_Int_56       	56
#define NVIC_Int_57       	57
#define NVIC_Int_58       	58
#define NVIC_Int_59       	59
#define NVIC_Int_60       	60
#define NVIC_Int_61       	61
#define NVIC_Int_62       	62
#define NVIC_Int_63       	63
//ISER2
#define NVIC_Int_64         64
#define NVIC_Int_65         65
#define NVIC_Int_66         66
#define NVIC_Int_67         67


//Software Interrupt

#define NVIC_Software_Int(n)		n


//NVIC Groups + subgroups
#define SCB_AIRCR_PRIGROUP_16G0S		0x03
#define SCB_AIRCR_PRIGROUP_8G2S			0x04
#define SCB_AIRCR_PRIGROUP_4G4S			0x05
#define SCB_AIRCR_PRIGROUP_2G8S			0x06
#define SCB_AIRCR_PRIGROUP_0G16S		0x07


//priorities
/*********************16 groups***************************/
#define 	NVIC_Priority_16G0S_G0S0		0x00
#define 	NVIC_Priority_16G0S_G1S0		0x10
#define 	NVIC_Priority_16G0S_G2S0		0x20
#define 	NVIC_Priority_16G0S_G3S0		0x30
#define 	NVIC_Priority_16G0S_G4S0		0x40
#define 	NVIC_Priority_16G0S_G5S0		0x50
#define 	NVIC_Priority_16G0S_G6S0		0x60
#define 	NVIC_Priority_16G0S_G7S0		0x70
#define 	NVIC_Priority_16G0S_G8S0		0x80
#define 	NVIC_Priority_16G0S_G9S0		0x90
#define 	NVIC_Priority_16G0S_G10S0		0xA0
#define 	NVIC_Priority_16G0S_G11S0		0xB0
#define 	NVIC_Priority_16G0S_G12S0		0xC0
#define 	NVIC_Priority_16G0S_G13S0		0xD0
#define 	NVIC_Priority_16G0S_G14S0		0xE0
#define 	NVIC_Priority_16G0S_G15S0		0xF0



/*********************8 groups 2 subs***************************/
#define 	NVIC_Priority_8G2S_G0S0		0x00
#define 	NVIC_Priority_8G2S_G1S0		0x20
#define 	NVIC_Priority_8G2S_G2S0		0x40
#define 	NVIC_Priority_8G2S_G3S0		0x60
#define 	NVIC_Priority_8G2S_G4S0		0x80
#define 	NVIC_Priority_8G2S_G5S0		0xA0
#define 	NVIC_Priority_8G2S_G6S0		0xC0
#define 	NVIC_Priority_8G2S_G7S0		0xE0
#define 	NVIC_Priority_8G2S_G0S1		0x10
#define 	NVIC_Priority_8G2S_G1S1		0x30
#define 	NVIC_Priority_8G2S_G2S1		0x50
#define 	NVIC_Priority_8G2S_G3S1		0x70
#define 	NVIC_Priority_8G2S_G4S1		0x90
#define 	NVIC_Priority_8G2S_G5S1		0xB0
#define 	NVIC_Priority_8G2S_G6S1		0xD0
#define 	NVIC_Priority_8G2S_G7S1		0xF0

/*********************4 groups 4 subs***************************/
#define 	NVIC_Priority_4G4S_G0S0		0x00
#define 	NVIC_Priority_4G4S_G0S1		0x10
#define 	NVIC_Priority_4G4S_G0S2		0x20
#define 	NVIC_Priority_4G4S_G0S3		0x30
#define 	NVIC_Priority_4G4S_G1S0		0x40
#define 	NVIC_Priority_4G4S_G1S1		0x50
#define 	NVIC_Priority_4G4S_G1S2		0x60
#define 	NVIC_Priority_4G4S_G1S3		0x70
#define 	NVIC_Priority_4G4S_G2S0		0x80
#define 	NVIC_Priority_4G4S_G2S1		0x90
#define 	NVIC_Priority_4G4S_G2S2		0xA0
#define 	NVIC_Priority_4G4S_G2S3		0xB0
#define 	NVIC_Priority_4G4S_G3S0		0xC0
#define 	NVIC_Priority_4G4S_G3S1		0xD0
#define 	NVIC_Priority_4G4S_G3S2		0xE0
#define 	NVIC_Priority_4G4S_G3S3		0xF0

/*********************2 groups 8 subs***************************/
#define 	NVIC_Priority_2G8S_G0S0		0x00
#define 	NVIC_Priority_2G8S_G0S1		0x10
#define 	NVIC_Priority_2G8S_G0S2		0x20
#define 	NVIC_Priority_2G8S_G0S3		0x30
#define 	NVIC_Priority_2G8S_G0S4		0x40
#define 	NVIC_Priority_2G8S_G0S5		0x50
#define 	NVIC_Priority_2G8S_G0S6		0x60
#define 	NVIC_Priority_2G8S_G0S7		0x70
#define 	NVIC_Priority_2G8S_G1S0		0x80
#define 	NVIC_Priority_2G8S_G1S1		0x90
#define 	NVIC_Priority_2G8S_G1S2		0xA0
#define 	NVIC_Priority_2G8S_G1S3		0xB0
#define 	NVIC_Priority_2G8S_G1S4		0xC0
#define 	NVIC_Priority_2G8S_G1S5		0xD0
#define 	NVIC_Priority_2G8S_G1S6		0xE0
#define 	NVIC_Priority_2G8S_G1S7		0xF0

/*********************0 groups 16 subs***************************/
#define 	NVIC_Priority_0G16S_G0S0		0x00
#define 	NVIC_Priority_0G16S_G0S1		0x10
#define 	NVIC_Priority_0G16S_G0S2		0x20
#define 	NVIC_Priority_0G16S_G0S3		0x30
#define 	NVIC_Priority_0G16S_G0S4		0x40
#define 	NVIC_Priority_0G16S_G0S5		0x50
#define 	NVIC_Priority_0G16S_G0S6		0x60
#define 	NVIC_Priority_0G16S_G0S7		0x70
#define 	NVIC_Priority_0G16S_G0S8		0x80
#define 	NVIC_Priority_0G16S_G0S9		0x90
#define 	NVIC_Priority_0G16S_G0S10		0xA0
#define 	NVIC_Priority_0G16S_G0S11		0xB0
#define 	NVIC_Priority_0G16S_G0S12		0xC0
#define 	NVIC_Priority_0G16S_G0S13		0xD0
#define 	NVIC_Priority_0G16S_G0S14		0xE0
#define 	NVIC_Priority_0G16S_G0S15		0xF0




res_t NVICEnableInt(u8 NVIC_Int);
res_t NVICDisableInt(u8 NVIC_Int);
res_t NVICSetPend(u8 NVIC_Int);
res_t NVICClearPend(u8 NVIC_Int);
res_t NVICSetSFWInt(u8 NVIC_Software_Int);
res_t SCBSetPriority(u8 SCB_AIRCR_PRIGROUP);
res_t NVICSetPriority(u8 NVIC_Priority , u8  NVIC_Int);



#endif /* NVIC_NVIC_H_ */
