#include "uart.h"

void uart_init(void)
{
	P1SEL |= BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
	P1SEL2 |= BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
	UCA0CTL1 |= UCSSEL_2;                     // uart时钟: SMCLK=1MHz
	UCA0BR0 = 104;                            // 设置波特率:9600
	UCA0BR1 = 0;                              // 设置波特率:9600
	UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	IE2 |= UCA0RXIE+UCA0TXIE;                 // Enable USCI_A0 RX and TX interrupt
}

void uart_send_buf(char *s)
{
  while(*s!='\0')
  {
    UCA0TXBUF=*s;
    while((IFG2&UCA0TXIFG)==0); //查询发送是否结束
    IFG2&=~UCA0TXIFG; //清除发送一标志位
    s++;
  }
}

//  uart串口RX接收到一个字符,产生中断处理
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	while((IFG2&UCA0RXIFG)==0);
	i=UCA0RXBUF;
	uart_send_buf(i);
}