#include <msp430.h>
#include "NRF24L01.h"
#include "advance.h"


unsigned char TX_ADDRESS[5]={0x34,0x43,0x10,0x10,0x01};//���͵�ַ
unsigned char RX_ADDRESS[5]={0x34,0x43,0x10,0x10,0x01};//���յ�ַ


/**********************************************************
*������SPI_Write_8bit(unsigned char dat)
*���ܣ�SPIд8λ����;
*������dat(��Ҫд���һ���ֽ����ݣ�����Ϊunsigned char����ΧΪ0~255);
*���أ���;
*��ע��SCLK�½��ز���д������
**********************************************************/
void SPI_Write_8bit(unsigned char dat)
{
  unsigned char i;
  
  for(i=0;i<8;i++)
  {
    if(dat&0x80)
    {
      NRF24L01_MOSI_1();
    }
    else
    {
      NRF24L01_MOSI_0();
    }
    NRF24L01_SCLK_1();
    NRF24L01_SCLK_0();
    dat = dat<<1;
  }
}


int NRF24L01_Check(void)
{
	unsigned char buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	unsigned char i;
	//SPI1_SetSpeed(SPI_BaudRatePrescaler_4); //spi?��?��?a9Mhz�ꡧ24L01��?��?�䨮SPI����?��?a10Mhz��?   	 
	NRF24L01_Write_Str(NRF24L01_WRITE_REG+TX_ADDR,buf,5);//D�䨨?5??��??����?��??��.	
	NRF24L01_Read_Str(TX_ADDR,buf,5); //?��3?D�䨨?��?��??��  
	//printf((char*)buf);
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//���24l01����	
	return 0;		 //��⵽24l01
}	 	 


/**********************************************************
*������SPI_Read_8bit(void)
*���ܣ�SPI��������;
*��������
*���أ���ȡ�����ݡ���8bit;
*��ע��SCLK�����ز��ܶ�ȡ����
**********************************************************/
unsigned char SPI_Read_8bit(void)
{
  unsigned char i,inData=0x00;
  
  NRF24L01_SCLK_0();
  for(i=0;i<8;i++)
  {
    inData  = inData<<1;
    NRF24L01_SCLK_0();
    NRF24L01_SCLK_1();
    inData |= NRF24L01_MISO_IN();
  }
  
  return inData;
}




/**********************************************************
*������NRF24L01_Write_Reg(unsigned char reg_name,unsigned char dat)
*���ܣ�SPI��Ĵ���д������;
*������reg_name(��Ҫд��ļĴ�������)
dat(��Ҫд���һ���ֽ����ݣ�����Ϊunsigned char����ΧΪ0~255);
*���أ���;
**********************************************************/
void NRF24L01_Write_Reg(unsigned char reg_name,unsigned char dat)
{
  NRF24L01_CSN_0();
  SPI_Write_8bit(NRF24L01_WRITE_REG|reg_name);
  SPI_Write_8bit(dat);
  NRF24L01_CSN_1();
}





/**********************************************************
*������NRF24L01_Read_Reg(unsigned char reg_name)
*���ܣ�SPI�ӼĴ�����ȡ����;
*������reg_name(��Ҫд��ļĴ������֣�����Ϊunsigned char����ΧΪ0~255)
*���أ��ӼĴ������ص�����;
**********************************************************/
unsigned char NRF24L01_Read_Reg(unsigned char reg_name)
{
  unsigned char inData;
  
  NRF24L01_CSN_0();
  SPI_Write_8bit(NRF24L01_READ_REG|reg_name);
  inData = SPI_Read_8bit();
  NRF24L01_CSN_1();
  
  return inData;
}




/**********************************************************
*������NRF24L01_Write_Add(unsigned char reg_name,unsigned char *pBuf,unsigned char bytes)
*���ܣ�SPI��Ĵ���д��һ������;
*������reg_name(��Ҫд��ļĴ�������)
pBuf(��Ҫд�����ݵ��׵�ַ)
bytes(��Ҫд������ݳ��ȣ�����Ϊunsigned char����ΧΪ0~255);
*���أ���;
**********************************************************/
void NRF24L01_Write_Str(unsigned char reg_name,unsigned char *pBuf,unsigned char bytes)
{
  unsigned char i;
  
  NRF24L01_CSN_0();
  SPI_Write_8bit(NRF24L01_WRITE_REG|reg_name);
  for(i=0;i<bytes;i++)
  {
    SPI_Write_8bit(pBuf[i]);
  }
  NRF24L01_CSN_1();
}




/**********************************************************
*������NRF24L01_Read_Str(unsigned char reg_name,unsigned char *pBuf,unsigned char bytes)
*���ܣ�SPI��Ĵ�����ȡһ������;
*������reg_name(��Ҫ��ȡ�ļĴ�������)
pBuf(��ȡ���ݴ洢λ�õ��׵�ַ)
bytes(��Ҫ��ȡ�����ݳ��ȣ�����Ϊunsigned char����ΧΪ0~255);
*���أ���;
**********************************************************/
void NRF24L01_Read_Str(unsigned char reg_name,unsigned char *pBuf,unsigned char bytes)
{
  unsigned char i;
  
  NRF24L01_CSN_0();
  SPI_Write_8bit(NRF24L01_WRITE_REG|reg_name);
  for(i=0;i<bytes;i++)
  {
    pBuf[i] = SPI_Read_8bit();
  }
  NRF24L01_CSN_1();
}




/**********************************************************
*������NRF24L01_Read_Data(unsigned char *rx_buf)
*���ܣ���ȡnRF24L01���յ�����;
*������rx_buf(nRF24L01���յ������ݴ洢���׵�ַ)
*���أ�nRF24L01�������ݵ����(1Ϊ���ճɹ�,0Ϊ����ʧ��);
*��ע�����״̬�Ĵ����б�־λ����������ڶ����ݺ����RX FIFO�Ĵ���֮ǰ
**********************************************************/
unsigned char NRF24L01_Read_Data(unsigned char *rx_buf)
{
  unsigned char Sta=0;
  
  Sta = NRF24L01_Read_Reg(STATUS);
  NRF24L01_Write_Reg(STATUS,Sta);		//����д��if�е��������֮ǰ(��֪��ʲôԭ��)
  
  if(Sta & RX_DR)
  {
    NRF24L01_Read_Str(NRF24L01_RD_RX_PLOAD,rx_buf,RX_PLOAD_WIDTH);
    NRF24L01_Write_Reg(NRF24L01_FLUSH_RX,0xFF);
    NRF24L01_Write_Reg(STATUS,Sta);	//�������RX_DR
    return 1;
  }
  return 0;
}





/**********************************************************
*������NRF24L01_Send_Data(void)
*���ܣ�nRF24L01��������;
*������tx_buf(nRF24L01Ҫ�������ݵ��׵�ַ)
*���أ�nRF24L01�����Ƿ�ɹ�;
*��ע�����TX FIFO�Ĵ���������������״̬�Ĵ������֮ǰ
**********************************************************/
unsigned char NRF24L01_Send_Data(unsigned char *tx_buf)
{
  unsigned char Sta;
  
  NRF24L01_CE_0();
  NRF24L01_Write_Str(NRF24L01_WR_TX_PLOAD,tx_buf,TX_PLOAD_WIDTH);	
  NRF24L01_Write_Reg(CONFIG,0x0E);
  NRF24L01_CE_1();
  
  while(NRF24L01_IRQ_IN());
  Sta = NRF24L01_Read_Reg(STATUS);
  
  if(Sta & MAX_RT)
  {
    NRF24L01_Write_Reg(NRF24L01_FLUSH_TX,0xFF);	  //����д��NRF24L01_Write_Reg(STATUS,Sta);֮ǰ
    NRF24L01_Write_Reg(STATUS,Sta);
    return MAX_RT;
  }
  if(Sta & TX_DS)
  {
    return TX_DS;
  }
  flush_tx();
  return 0xFF;
}

/**********************************************************
*������NRF24L01_RX_Mode_Init(void)
*���ܣ�nRF24L01��ʼ��Ϊ����ģʽ;
*��������
*���أ���;
**********************************************************/
void NRF24L01_RX_Mode_Init(void)
{
  
  P1SEL = 0x00;
  P1DIR = 0xcd;  //(24l01)����IO�ڷ���
  
  NRF24L01_CE_1();
  NRF24L01_CSN_1();
  NRF24L01_SCLK_0();
  NRF24L01_CE_0();
  
  NRF24L01_Write_Str(RX_ADDR_P0,RX_ADDRESS,RX_ADR_WIDTH);			//д����ͨ����ַ+��Ч����+��Ч���ݿ��
  
  NRF24L01_Write_Reg(EN_AA,ENAA_P0);    							//ʹ��ͨ��0���Զ�Ӧ��    
  NRF24L01_Write_Reg(EN_RXADDR,ERX_P0);							//ʹ��ͨ��0�Ľ��յ�ַ  	 
  NRF24L01_Write_Reg(RF_CH,40);	    							//����RFͨ��Ƶ��		  
  NRF24L01_Write_Reg(RX_PW_P0,RX_PLOAD_WIDTH);					//ѡ��ͨ��0����Ч���ݿ�� 	    
  NRF24L01_Write_Reg(RF_SETUP,RF_DR_2Mbps|RF_PWR_0dBm|LNA_HCURR);	//���÷��书��Ϊ0db����,��������Ϊ2Mbps,���������濪��   
  NRF24L01_Write_Reg(CONFIG,EN_CRC|CRC_16bit|PWR_ON|PRIM_RXD);	//���û�������ģʽ�Ĳ���
  
  NRF24L01_CE_1();
}



/**********************************************************
*������NRF24L01_TX_Mode_Init(void)
*���ܣ�nRF24L01��ʼ��Ϊ����ģʽ;
*��������
*���أ���;
**********************************************************/
void NRF24L01_TX_Mode_Init(void)
{
  NRF24L01_CE_1();
  NRF24L01_CSN_1();
  NRF24L01_SCLK_0();
  NRF24L01_CE_0();
  
  NRF24L01_Write_Str(TX_ADDR,TX_ADDRESS,TX_ADR_WIDTH);			//д�Ĵ���ָ��+���սڵ��ַ+��ַ���
  NRF24L01_Write_Str(RX_ADDR_P0,RX_ADDRESS,RX_ADR_WIDTH);			//Ϊ�˽����豸Ӧ���źţ�����ͨ��0��ַ�뷢�͵�ַ��ͬ
  
  NRF24L01_Write_Reg(EN_AA,ENAA_P0);								//ʹ��ͨ��0���Զ�Ӧ��
  NRF24L01_Write_Reg(EN_RXADDR,ERX_P0);							//ʹ��ͨ��0�Ľ��յ�ַ
  NRF24L01_Write_Reg(SETUP_RETR,ARD_586us|ARC_10time);			//�ȴ�586us,�Զ��ط�10��
  NRF24L01_Write_Reg(RF_CH,40);									//����RFͨ��Ƶ��
  NRF24L01_Write_Reg(RF_SETUP,RF_DR_2Mbps|RF_PWR_0dBm|LNA_HCURR);	//���÷��书��Ϊ0db����,��������Ϊ2Mbps,���������濪��
  NRF24L01_Write_Reg(CONFIG,EN_CRC|CRC_16bit|PWR_ON|PRIM_TXD);	//���û�������ģʽ�Ĳ���
  
  NRF24L01_CE_1();
}
