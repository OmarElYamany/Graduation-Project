


#ifndef SYSTK_INTERFACE_H_
#define SYSTK_INTERFACE_H_
#include "../../Common/STD_Types.h"
#include "../../Common/definition.h"
#include "../../Common/util.h"
#include "../../Common/Bit_Math.h"



void SYSTK_voidInit(void);
void SYSTK_voidStart(u32 PreloadValue);
u8 SYSTK_u8ReadFlag(void);

/********provides delay in microseconds***********/
void SYSTK_voidDelay(u32 Time_Micro);
void SYSTK_voidSetCallBack(void (*ptr) (void));




#endif /* SYSTK_INTERFACE_H_ */
