#include "uart.h"


unsigned char rx_buffer;

#if EN_UART0_RX
	u8 UART0_RX_BUF[UART_REC_LEN];
	u16 UART0_RX_STA=0;

	void uart0_init(void)
	{
		P1SEL |= BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
		P1SEL2 |= BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD

		UCA0CTL1 = UCSWRST;
		UCA0CTL1 |= UCSSEL_2;                     // uart时钟: SMCLK=1MHz
		UCA0BR0 = 104;                            // 设置波特率:9600
		UCA0BR1 = 0;                              // 设置波特率:9600
		UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
		UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

		IE2 |= UCA0RXIE+UCA0TXIE;                 // Enable USCI_A0 RX and TX interrupt
	}

	void uart0_send_char(u8 ch){
		while ((IFG2&UCA0TXIFG)==0);
		UCA0TXBUF=ch;
	}

	void uart0_send_buf(char *s)
	{
	  while(*s)
	  {
	    uart_send_char(*s);
	    s++;
	  }
	}

	//  uart串口RX接收到一个字符,产生中断处理
	#pragma vector=USCIAB0RX_VECTOR
	__interrupt void USCI0RX_ISR(void)
	{
		u8 Res;
		while((IFG2&UCA0RXIFG)==0);
		Res=UCA0RXBUF;

		if((UART0_RX_STA&0x8000)==0){					//rx unfinish
			if((UART0_RX_STA&0x4000)){					//rx 0x0d
				if(Res!=0x0a)
					UART0_RX_STA=0;
				else{
					UART0_RX_STA|=0x8000;
					UART0_RX_BUF[UART0_RX_LEN]='\0';
				}
		}
		else{
			if(Res == 0x0d){
				UART0_RX_STA |= 0x4000;
			}
			else{
				UART0_RX_BUF[UART0_RX_STA&0x3fff]=Res;
				UART0_RX_STA++;
				if(UART0_RX_STA>(UART_REC_LEN-1))
					UART0_RX_STA=0;						//rx error, restart
			}
		}

	}
#endif