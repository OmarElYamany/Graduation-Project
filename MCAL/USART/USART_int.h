/*
 * USART_int.h
 *
 *  Created on: ٠٤‏/٠٦‏/٢٠٢٣
 *      Author: Mohamed Samir
 */

#ifndef USART_USART_INT_H_
#define USART_USART_INT_H_



typedef enum
{
	USART1,
	USART2,
	USART3,
	USART4,
	USART5,
}USART_module;

typedef enum
{
	bits_8,
	bits_9
}word_size;

typedef	enum
{
	STOP_1bit = 0,
	STOP_2bit = 2
}stop_bits;

typedef struct
{
	u32 USART_SR;
	u32 USART_DR;
	u32 USART_BRR;
	u32 USART_CR1;
	u32 USART_CR2;
	u32 USART_CR3;
	u32 USART_GTPR;
}USART_t;


/*
    USART_init :
    inputs: options from [USART:(1,2,3,4,5), baud rate, frequency in Hz, Word size:(8bit or 9bit,  stop bit:(1,2)]
    output: options from [res_OK - res_ERROR]
*/
res_t USART_init(USART_module USARTx, u16 baud_rate, u32 freq, word_size M, stop_bits STOP);

/*
    USART_sendData :
    inputs: options from [address of u8 Variable]
    output: options from [res_OK - res_ERROR]
*/
res_t USART_sendData(u8* Data);

/*
    USART_sendString :
    inputs: options from [address of u8 Array (NOTE:Last character is '\0')]
    output: options from [res_OK - res_ERROR]
*/
res_t USART_sendString(u32 Data);
/*
    USART_receiveData :
    inputs: options from [address of u8 Variable]
    output: options from [res_OK - res_ERROR]
*/
res_t USART_receiveData(u8* Data);
/*
    USART_receiveData :
    inputs: options from [address of u8 Array, max length of the received characters]
    output: options from [res_OK - res_ERROR]
*/
res_t USART_receiveString(u8* Data,u8 max_length);

/*
    USART_RXInterruptEnable : enable the interrupt of receiving
    output: options from [res_OK - res_ERROR]
*/
res_t USART_RXInterruptEnable();

/*
    USART_TXInterruptEnable : enable the interrupt of Transmitting
    output: options from [res_OK - res_ERROR]
*/
res_t USART_TXInterruptEnable();

void USART1_setCallBack(void(*ptr)(void));



#endif /* USART_USART_INT_H_ */
