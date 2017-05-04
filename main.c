//发送模式
#include <msp430.h>
#include "NRF24L01.h"
#include "string.h"
#include "advance.h"

int cnt;
long long t;
unsigned char temp_buf[32]="SWITCH+ONCE";

#define P1_1_1()        P1OUT|=(1<<1)
#define P1_1_0()        P1OUT&=~(1<<1)

#define P2_1_1()        P2OUT|=(1<<1)
#define P2_1_0()        P2OUT&=~(1<<1)

void main(void)
{


  WDTCTL = WDTPW + WDTHOLD;        // 关闭看门狗
  BCSCTL1 = CALBC1_1MHZ;            //设置DCO频率
  DCOCTL =  CALDCO_1MHZ;             //设置DCO频率
//  t=10000*50;
//  while(t-->0);
P1SEL = 0x00;
P1DIR = 0xce;  //24l01设置IO口方向。P1.1用来看一次发射需要的时间
  /*
  P1IES = 0x00;                     // P1.0设为上升沿中断
  P1IE  |= BIT0;                    // 允许P1.0中断
  P1IFG &=~BIT0;
  _EINT();*/
  P1_1_0();
  P1_1_1();
  while(NRF24L01_Check());
NRF24L01_TX_Mode_Init();          // nRF24L01初始化为发送模式
NRF24L01_Send_Data(temp_buf);
nrf24l01_powerdown();
//  P1DIR = 0;
//  P1_1_0();
//  LPM4;

  while(1){

    /*cnt++;
    if(cnt%10000==0){
        P1DIR = 0xce;
        nrf24l01_activate_tx();
        NRF24L01_Send_Data("IN MAIN LOOP");
        nrf24l01_powerdown();
        P1_1_0();
    }
    */
      P1_1_0();
      for(cnt=5;cnt>0;--cnt){
        t=1000;
        while(t-->0);
      }
      P1_1_1();
      for(cnt=5;cnt>0;--cnt){
        t=1000;
        while(t-->0);
      }

  }
}
/*
#pragma vector = PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
  if((P1IFG | 0xfe)==0xff){
    P1DIR = 0xce;
    P1_1_1();

    nrf24l01_activate_tx();

    if(count==0){
      strcpy((char*)temp_buf,"P");
    }
    else{
        strcpy((char*)temp_buf,"O");
    }
    count=1-count;

    //NRF24L01_Send_Data("");
    NRF24L01_Send_Data(temp_buf);
    nrf24l01_powerdown();
    P1_1_0();
    t=999*5;
    while(t-->0);
    //P1DIR = 0;
    P1IFG &=~BIT0;
  }
}
*/
