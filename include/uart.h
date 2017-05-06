#ifndef _UART_H
#define _UART_H

#include <msp430.h>

void uart_init(void);
void uart_send_buf(char *s);
__interrupt void USCI0RX_ISR(void);