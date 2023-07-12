/*
 * USART.c
 *
 *  Created on: ٠٤‏/٠٦‏/٢٠٢٣
 *      Author: Mohamed Samir
 */

#include "../../Common/util.h"
#include "../../Common/definition.h"
#include "../../Common/STD_Types.h"
#include "../../Common/Bit_Math.h"
#include "../../MCAL/GPIO/GPIO.h"
#include "../MCAL/NVIC/NVIC.h"
#include "USART_int.h"

// CR1
#define RE			2
#define TE			3
#define	RXNEIE		5
#define	TCIE		6
#define	TXEIE		7
#define	Word_length	12
#define UE			13

// Status Register
#define RXNE		5
#define TC			6
#define TXE			7

#define STOP_BIT_LENGTH		0x3
#define STOP_BIT			12

//Baud rate equation
#define USARTDIV(PCLK, BAUD)							(u32) (PCLK/(16 * BAUD ))
#define USARTDIV_MUL100(PCLK, BAUD)						(u32) ( (25 * PCLK ) / (4  * BAUD ))
#define Mantissa_MUL100(PCLK, BAUD)						(u32) (USARTDIV(PCLK, BAUD) * 100)
#define Mantissa(PCLK, BAUD)							(u32) (USARTDIV(PCLK, BAUD) )
#define DIV_Fraction(PCLK, BAUD)						(u32) (((USARTDIV_MUL100(PCLK, BAUD) -  Mantissa_MUL100(PCLK, BAUD) ) * 16 ) / 100 )
#define UART_BRR_Register(PCLK, BAUD)					(( Mantissa (PCLK, BAUD) ) <<4 )|( (DIV_Fraction(PCLK, BAUD)) & 0xF )

#define USART1_BASE	0x40013800

static volatile USART_t* USART1_reg = (volatile USART_t*) USART1_BASE;

static void (*USART1_CallBack)(void) = Null;
extern u8 GlobalDataRec;
static u8 tempRef[5] ;

res_t USART_init(USART_module USARTx, u16 baud_rate, u32 freq, word_size M, stop_bits STOP)
{
	u16 temp_BRRreg = UART_BRR_Register(freq,baud_rate);
	if(USARTx==USART1)
	{
		// set Stop bits
		USART1_reg->USART_CR2 &= ~(STOP_BIT_LENGTH<<STOP_BIT);
		USART1_reg->USART_CR2 |= (STOP<<STOP_BIT);
		// set baud rate
		USART1_reg->USART_BRR = temp_BRRreg;
		// set data bits long // Transmitter enable // Receiver Enable //UART Enable
		u32 temp_CR1reg = (M<<Word_length) | (1<<TE) | (1<<RE) | (1<<UE);
		//
		USART1_reg->USART_CR1 |= temp_CR1reg;

	}
	GPIO_SetPin(GPIO_PortA, GPIO_Pin9, GPIO_Mode_OUT50, GPIO_Config_AltOUTPushPull);
	GPIO_SetPin(GPIO_PortA, GPIO_Pin10, GPIO_Mode_IN, GPIO_Config_INPFloating);
	return res_OK;
}
//Interrupt
res_t USART_RXInterruptEnable()
{
	USART1_reg->USART_CR1 |= (1<<RXNEIE);
	NVICEnableInt(37);

	return res_OK;
}
res_t USART_TXInterruptEnable()
{
	USART1_reg->USART_CR1 |= (1<<TCIE);
	NVICEnableInt(37);
	return res_OK;
}

res_t USART_sendData(u8* Data)
{
	//*Data = *Data + '0';
	if ((USART1_reg->USART_CR1 & (1<<TCIE)) == 0)
	{
		while(! (USART1_reg->USART_SR & (1<<TXE)) );
		USART1_reg->USART_DR = *Data;
		while(! (USART1_reg->USART_SR & (1<<TC)) );
		USART1_reg->USART_SR &= ~(1<<TC);
	}
	else
	{
		USART1_reg->USART_DR = *Data;
	}

	return res_OK;
}

void fromInttoStr(u32 intp)
{	u8 temp [5];

	s8 i = 0;
	s8 j = 0;
	while(intp != 0)
	{
		temp[i] = intp%10;
		intp = intp/10;
		i++;
	}
	i--;
	for ( ; i>=0; i--)
	{
		tempRef[j] = temp[i]+'0' ;
		j++;
	}
	tempRef[j] = '\r';

	//return tempRef;
}
res_t USART_sendString(u32 Data)
{
	//u8 *parsedData;
	fromInttoStr(Data);
	s8 i = 0;
	if ((USART1_reg->USART_CR1 & (1<<TCIE)) == 0)
	{
		while(! (USART1_reg->USART_SR & (1<<TXE)) );

		while( (tempRef[i]) != '\r' )
		{
			//tempRef[i] = tempRef[i] + '0';
			USART1_reg->USART_DR = tempRef[i];
			while(! (USART1_reg->USART_SR & (1<<TC)) );
			USART1_reg->USART_SR &= ~(1<<TC);
			i++;
		}

	}
	return res_OK;
}

res_t USART_receiveData(u8* Data)
{
	if ((USART1_reg->USART_CR1 & (1<<RXNEIE)) == 0)
	{
		while(!(USART1_reg->USART_SR & (1<<RXNE)));
		*Data = USART1_reg->USART_DR ;
	}
	else
	{
		*Data = USART1_reg->USART_DR ;
	}
	return res_OK;
}

res_t USART_receiveString(u8* Data,u8 max_length)
{
	if ((USART1_reg->USART_CR1 & (1<<RXNEIE)) == 0)
	{
		u8 i = 0;
		while (i < (max_length - 1)) // leave room for null terminator
		{
			while (!(USART1_reg->USART_SR & (1<<RXNE))); // wait for data to be received
			// read the received character
			u8 c = USART1_reg->USART_DR  & 0xFF;
			// end of line
			if (c == '\r' || c == '\n')
			{
				// add null terminator
				Data[i] = '\0';
				break;
			}
			else
			{
				// add the character to the buffer
				Data[i] = c;
				i++;
			}
		}
		Data[max_length - 1] = '\0'; // add null terminator in case max length is reached

	}
	else
	{
		*Data = USART1_reg->USART_DR ;
	}
	return res_OK;
}

void USART1_setCallBack(void(*ptr)(void))
{
	USART1_CallBack = ptr ;
}

void USART1_IRQHandler()
{
	USART_receiveData(&GlobalDataRec);
}

