#include "advance.h"
#include "nrf24l01.h"
void flush_tx(){
    NRF24L01_CE_0();
	SPI_Write_8bit(RF24_FLUSH_TX);
	NRF24L01_CE_1();
}

void flush_rx(){
    NRF24L01_CE_0();
	SPI_Write_8bit(RF24_FLUSH_RX);
	NRF24L01_CE_1(); 
}

void pulse_ce(){
    long long t=100;
    NRF24L01_CE_0();
	while(t-->0);
	NRF24L01_CE_1(); 
}

void nrf24l01_powerdown(){
  NRF24L01_CE_1();
  NRF24L01_Write_Reg(STATUS,MASK_IRQ_ALL);
  NRF24L01_Write_Reg(CONFIG,0);
}

void nrf24l01_standby(){
  char state=NRF24L01_Read_Reg(CONFIG);
  if(state == RF24_STATE_NOTPRESENT || state == RF24_STATE_STANDBY_I)
	return;
  NRF24L01_CE_1();
  NRF24L01_Write_Reg(CONFIG,PWR_UP);
  if(state == RF24_STATE_POWERDOWN){
  	long long t=99*5;
	while(t-->0);
  }
}

void nrf24l01_activate_tx(){
  nrf24l01_standby();
  NRF24L01_Write_Reg(STATUS,EN_IT_TX_DR|EN_IT_MAX_RT);
  pulse_ce();
}

void nrf24l01_activate_rx(){
  nrf24l01_standby();
  flush_rx();
  NRF24L01_Write_Reg(STATUS,EN_IT_RX_DR);
  NRF24L01_Write_Reg(CONFIG,PWR_UP|PRIM_RX);
  NRF24L01_CE_0();
}