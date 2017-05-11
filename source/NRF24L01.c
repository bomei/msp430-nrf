#include <msp430.h>
#include "NRF24L01.h"
#include "advance.h"


unsigned char TX_ADDRESS[5]={0x34,0x43,0x10,0x10,0x01};//发送地址
unsigned char RX_ADDRESS[5]={0x34,0x43,0x10,0x10,0x01};//接收地址


/**********************************************************
*函数：SPI_Write_8bit(unsigned char dat)
*功能：SPI写8位数据;
*参数：dat(需要写入的一个字节数据，类型为unsigned char，范围为0~255);
*返回：无;
*备注：SCLK下降沿才能写入数据
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
	//SPI1_SetSpeed(SPI_BaudRatePrescaler_4); //spi?ù?è?a9Mhz￡¨24L01μ?×?′óSPIê±?ó?a10Mhz￡?   	 
	NRF24L01_Write_Str(NRF24L01_WRITE_REG+TX_ADDR,buf,5);//D′è?5??×??úμ?μ??·.	
	NRF24L01_Read_Str(TX_ADDR,buf,5); //?á3?D′è?μ?μ??·  
	//printf((char*)buf);
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//检测24l01错误	
	return 0;		 //检测到24l01
}	 	 


/**********************************************************
*函数：SPI_Read_8bit(void)
*功能：SPI接收数据;
*参数：无
*返回：读取的数据——8bit;
*备注：SCLK上升沿才能读取数据
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
*函数：NRF24L01_Write_Reg(unsigned char reg_name,unsigned char dat)
*功能：SPI向寄存器写入数据;
*参数：reg_name(需要写入的寄存器名字)
dat(需要写入的一个字节数据，类型为unsigned char，范围为0~255);
*返回：无;
**********************************************************/
void NRF24L01_Write_Reg(unsigned char reg_name,unsigned char dat)
{
  NRF24L01_CSN_0();
  SPI_Write_8bit(NRF24L01_WRITE_REG|reg_name);
  SPI_Write_8bit(dat);
  NRF24L01_CSN_1();
}





/**********************************************************
*函数：NRF24L01_Read_Reg(unsigned char reg_name)
*功能：SPI从寄存器读取数据;
*参数：reg_name(需要写入的寄存器名字，类型为unsigned char，范围为0~255)
*返回：从寄存器读回的数据;
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
*函数：NRF24L01_Write_Add(unsigned char reg_name,unsigned char *pBuf,unsigned char bytes)
*功能：SPI向寄存器写入一串数据;
*参数：reg_name(需要写入的寄存器名字)
pBuf(需要写入数据的首地址)
bytes(需要写入的数据长度，类型为unsigned char，范围为0~255);
*返回：无;
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
*函数：NRF24L01_Read_Str(unsigned char reg_name,unsigned char *pBuf,unsigned char bytes)
*功能：SPI向寄存器读取一串数据;
*参数：reg_name(需要读取的寄存器名字)
pBuf(读取数据存储位置的首地址)
bytes(需要读取的数据长度，类型为unsigned char，范围为0~255);
*返回：无;
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
*函数：NRF24L01_Read_Data(unsigned char *rx_buf)
*功能：读取nRF24L01接收的数据;
*参数：rx_buf(nRF24L01接收到的数据存储的首地址)
*返回：nRF24L01接收数据的情况(1为接收成功,0为接收失败);
*备注：清除状态寄存器中标志位的语句必须放在读数据和清除RX FIFO寄存器之前
**********************************************************/
unsigned char NRF24L01_Read_Data(unsigned char *rx_buf)
{
  unsigned char Sta=0;
  
  Sta = NRF24L01_Read_Reg(STATUS);
  NRF24L01_Write_Reg(STATUS,Sta);		//必须写在if中的两条语句之前(不知道什么原因)
  
  if(Sta & RX_DR)
  {
    NRF24L01_Read_Str(NRF24L01_RD_RX_PLOAD,rx_buf,RX_PLOAD_WIDTH);
    NRF24L01_Write_Reg(NRF24L01_FLUSH_RX,0xFF);
    NRF24L01_Write_Reg(STATUS,Sta);	//用于清除RX_DR
    return 1;
  }
  return 0;
}





/**********************************************************
*函数：NRF24L01_Send_Data(void)
*功能：nRF24L01发送数据;
*参数：tx_buf(nRF24L01要发送数据的首地址)
*返回：nRF24L01发送是否成功;
*备注：清除TX FIFO寄存器语句必须放在清除状态寄存器语句之前
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
    NRF24L01_Write_Reg(NRF24L01_FLUSH_TX,0xFF);	  //必须写在NRF24L01_Write_Reg(STATUS,Sta);之前
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
*函数：NRF24L01_RX_Mode_Init(void)
*功能：nRF24L01初始化为接收模式;
*参数：无
*返回：无;
**********************************************************/
void NRF24L01_RX_Mode_Init(void)
{
  
  P1SEL = 0x00;
  P1DIR = 0xcd;  //(24l01)设置IO口方向
  
  NRF24L01_CE_1();
  NRF24L01_CSN_1();
  NRF24L01_SCLK_0();
  NRF24L01_CE_0();
  
  NRF24L01_Write_Str(RX_ADDR_P0,RX_ADDRESS,RX_ADR_WIDTH);			//写接收通道地址+有效数据+有效数据宽度
  
  NRF24L01_Write_Reg(EN_AA,ENAA_P0);    							//使能通道0的自动应答    
  NRF24L01_Write_Reg(EN_RXADDR,ERX_P0);							//使能通道0的接收地址  	 
  NRF24L01_Write_Reg(RF_CH,40);	    							//设置RF通信频率		  
  NRF24L01_Write_Reg(RX_PW_P0,RX_PLOAD_WIDTH);					//选择通道0的有效数据宽度 	    
  NRF24L01_Write_Reg(RF_SETUP,RF_DR_2Mbps|RF_PWR_0dBm|LNA_HCURR);	//设置发射功率为0db增益,传输速率为2Mbps,低噪声增益开启   
  NRF24L01_Write_Reg(CONFIG,EN_CRC|CRC_16bit|PWR_ON|PRIM_RXD);	//配置基本工作模式的参数
  
  NRF24L01_CE_1();
}



/**********************************************************
*函数：NRF24L01_TX_Mode_Init(void)
*功能：nRF24L01初始化为发送模式;
*参数：无
*返回：无;
**********************************************************/
void NRF24L01_TX_Mode_Init(void)
{
  NRF24L01_CE_1();
  NRF24L01_CSN_1();
  NRF24L01_SCLK_0();
  NRF24L01_CE_0();
  
  NRF24L01_Write_Str(TX_ADDR,TX_ADDRESS,TX_ADR_WIDTH);			//写寄存器指令+接收节点地址+地址宽度
  NRF24L01_Write_Str(RX_ADDR_P0,RX_ADDRESS,RX_ADR_WIDTH);			//为了接收设备应答信号，接收通道0地址与发送地址相同
  
  NRF24L01_Write_Reg(EN_AA,ENAA_P0);								//使能通道0的自动应答
  NRF24L01_Write_Reg(EN_RXADDR,ERX_P0);							//使能通道0的接收地址
  NRF24L01_Write_Reg(SETUP_RETR,ARD_586us|ARC_10time);			//等待586us,自动重发10次
  NRF24L01_Write_Reg(RF_CH,40);									//设置RF通信频率
  NRF24L01_Write_Reg(RF_SETUP,RF_DR_2Mbps|RF_PWR_0dBm|LNA_HCURR);	//设置发射功率为0db增益,传输速率为2Mbps,低噪声增益开启
  NRF24L01_Write_Reg(CONFIG,EN_CRC|CRC_16bit|PWR_ON|PRIM_TXD);	//配置基本工作模式的参数
  
  NRF24L01_CE_1();
}
