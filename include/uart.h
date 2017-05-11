#ifndef _UART_H
#define _UART_H

#include <msp430.h>

#define u8 unsigned char
#define u16 unsigned int

#define UART_REC_LEN 200					//max receive bytes
#define EN_UART0_RX  1						//enable usart1 to rx

extern u8 UART0_RX_BUF[UART_REC_LEN];		//rx cache

extern u16 UART0_RX_STA;					//rx state

#define UART0_RX_LEN	  		(UART0_RX_STA&0x3f)	  //数据接收长度
#define UART0_RX_DONE           (UART0_RX_STA&0x8000)  //是否结束标志


void uart0_9600_init(void);
void uart0_send_buf(u8 *s);
void uart0_send_char(u8 ch);
#endif
