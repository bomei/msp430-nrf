#ifndef _NRF24L01_H
#define _NRF24L01_H


/*******************nRF24L01的端口定义********************/
#define NRF24L01_CE	    0
#define NRF24L01_CSN	    7
#define NRF24L01_SCLK	    3
#define NRF24L01_MOSI	    6
#define NRF24L01_MISO	    4
#define NRF24L01_IRQ	    5

#define	NRF24L01_CE_1()		P1OUT|=(1<<NRF24L01_CE)
#define	NRF24L01_CE_0()		P1OUT&=~(1<<NRF24L01_CE)
#define NRF24L01_CSN_1()	P1OUT|=(1<<NRF24L01_CSN)
#define NRF24L01_CSN_0()	P1OUT&=~(1<<NRF24L01_CSN)
#define NRF24L01_SCLK_1()	P1OUT|=(1<<NRF24L01_SCLK)
#define NRF24L01_SCLK_0()	P1OUT&=~(1<<NRF24L01_SCLK)
#define NRF24L01_MOSI_1()	P1OUT|=(1<<NRF24L01_MOSI)
#define NRF24L01_MOSI_0()	P1OUT&=~(1<<NRF24L01_MOSI)

#define NRF24L01_MISO_IN()	((P1IN&(1<<NRF24L01_MISO))>>NRF24L01_MISO)
#define NRF24L01_IRQ_IN()	((P1IN&(1<<NRF24L01_IRQ))>>NRF24L01_IRQ)

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//NRF24L01发送接收数据宽度定义
#define TX_ADR_WIDTH    5   //5字节的地址宽度
#define RX_ADR_WIDTH    5   //5字节的地址宽度
#define TX_PLOAD_WIDTH  32  //32字节的用户数据宽度
#define RX_PLOAD_WIDTH  32  //32字节的用户数据宽度



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//NRF24L01寄存器操作指令
#define NRF24L01_READ_REG        0x00  //读配置寄存器,低5位为寄存器地址
#define NRF24L01_WRITE_REG       0x20  //写配置寄存器,低5位为寄存器地址
#define NRF24L01_RD_RX_PLOAD     0x61  //读RX有效数据,1-32字节
#define NRF24L01_WR_TX_PLOAD     0xA0  //写TX有效数据,1-32字节
#define NRF24L01_FLUSH_TX        0xE1  //清除TX FIFO寄存器.发射模式下用
#define NRF24L01_FLUSH_RX        0xE2  //清除RX FIFO寄存器.接收模式下用
#define NRF24L01_REUSE_TX_PL     0xE3  //重新使用上一包数据,CE为高,数据包被不断发送.
#define NRF24L01_NOP             0xFF  //空操作,可以用来读状态寄存器	 





//////////////////////////////////////////////////////////////////////////////////////////////////////////
//NRF24L01寄存器地址
#define CONFIG          0x00  //配置寄存器地址
#define EN_AA           0x01  //使能自动应答功能  
#define EN_RXADDR       0x02  //接收地址允许
#define SETUP_AW        0x03  //设置地址宽度(所有数据通道)
#define SETUP_RETR      0x04  //建立自动重发
#define RF_CH           0x05  //RF通道频率,F0 = 2400 + RF_CH(MHz)
#define RF_SETUP        0x06  //RF寄存器
#define STATUS          0x07  //状态寄存器
#define OBSERVE_TX		0x08  //发送检测寄存器
#define CD              0x09  //载波检测寄存器
#define RX_ADDR_P0      0x0A  //数据通道0接收地址,最大长度5个字节,低字节在前(复位值：0xE7E7E7E7E7)
#define RX_ADDR_P1      0x0B  //数据通道1接收地址,最大长度5个字节,低字节在前(复位值：0xC2C2C2C2C2)
#define RX_ADDR_P2      0x0C  //数据通道2接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P3      0x0D  //数据通道3接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P4      0x0E  //数据通道4接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P5      0x0F  //数据通道5接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define TX_ADDR         0x10  //发送地址(低字节在前),ShockBurstTM模式下,RX_ADDR_P0与此地址相等
#define RX_PW_P0        0x11  //接收数据通道0有效数据宽度(1-32字节),设置为0则非法
#define RX_PW_P1        0x12  //接收数据通道1有效数据宽度(1-32字节),设置为0则非法
#define RX_PW_P2        0x13  //接收数据通道2有效数据宽度(1-32字节),设置为0则非法
#define RX_PW_P3        0x14  //接收数据通道3有效数据宽度(1-32字节),设置为0则非法
#define RX_PW_P4        0x15  //接收数据通道4有效数据宽度(1-32字节),设置为0则非法
#define RX_PW_P5        0x16  //接收数据通道5有效数据宽度(1-32字节),设置为0则非法
#define FIFO_STATUS     0x17  //FIFO状态寄存器






//////////////////////////////////////////////////////////////////////////////////////////////////////////
//NRF24L01寄存器位操作


/*************配置寄存器CONFIG位定义(默认：08H)*************/
#define MASK_RX_DR		0x40  // 可屏蔽中断RX_RD，1——IRQ引脚不显示RX_RD中断，0——RX_RD中断产生时IRQ引脚电平为低
#define MASK_TX_DR		0x20  // 可屏蔽中断TX_RD，1——IRQ引脚不显示TX_RD中断，0——TX_RD中断产生时IRQ引脚电平为低
#define MASK_MAX_RT		0x10  // 可屏蔽中断MAX_RT,1——IRQ引脚不显示MAX_RT中断,0——MAX_RT中断产生时IRQ引脚电平为低
#define EN_CRC			0x08  // CRC使能,如果EN_AA中任意一位为高则EN_CRC强迫为高
#define CRCO			0x04  // CRC模式,0——8位CRC校验，1——16位CRC校验
#define PWR_UP			0x02  // 1——上电，0——掉电
#define PRIM_RX 		0x01  // 1——接收模式，0——发射模式
#define MASK_IRQ_ALL    0x70

#define DIS_IT_RX_DR	0x40  // IRQ引脚不显示RX_RD中断
#define EN_IT_RX_DR		0x00  // RX_RD中断产生时IRQ引脚电平为低

#define DIS_IT_TX_DR	0x20  // IRQ引脚不显示TX_RD中断
#define EN_IT_TX_DR		0x00  // TX_RD中断产生时IRQ引脚电平为低

#define DIS_IT_MAX_RT	0x10  // IRQ引脚不显示MAX_RT中断
#define EN_IT_MAX_RT	0x00  // MAX_RT中断产生时IRQ引脚电平为低

#define EN_CRC			0x08  // 使能CRC校验
#define DIS_CRC			0x00  // 关闭CRC校验

#define CRC_16bit		0x04  // 16位CRC校验
#define CRC_8bit		0x00  // 8位CRC校验

#define PWR_ON			0x02  // 上电
#define PWR_OFF			0x00  // 掉电

#define PRIM_RXD		0x01  // 接收模式
#define PRIM_TXD		0x00  // 发射模式




/*************使能"自动应答"功能寄存器EN_AA位定义(默认：3FH)*************/
#define ENAA_P5 		0x20  // 数据通道5自动应答允许
#define ENAA_P4 		0x10  // 数据通道4自动应答允许
#define ENAA_P3 		0x08  // 数据通道3自动应答允许
#define ENAA_P2 		0x04  // 数据通道2自动应答允许
#define ENAA_P1 		0x02  // 数据通道1自动应答允许
#define ENAA_P0 		0x01  // 数据通道0自动应答允许




/*************接收地址允许寄存器EN_RXADDR位定义(默认：03H)*************/
#define ERX_P5			0x20  // 接收数据通道5允许
#define ERX_P4			0x10  // 接收数据通道4允许
#define ERX_P3			0x08  // 接收数据通道3允许
#define ERX_P2			0x04  // 接收数据通道2允许
#define ERX_P1			0x02  // 接收数据通道1允许
#define ERX_P0			0x01  // 接收数据通道0允许 




/*************设置地址宽度寄存器SETUP_AW位定义(默认：03H)*************/
#define AW		        0x03  // 接收/发射地址宽度

#define AW_NA			0x00  // 无效
#define AW_3byte		0x01  // 3字节宽度
#define AW_4byte		0x02  // 4字节宽度
#define AW_5byte		0x03  // 5字节宽度 				




/*************建立自动重发寄存器SETUP_RETR位定义(默认：03H)*************/
#define ARD		        0xF0  // 自动重发延时
#define ARC       	        0x0F  // 自动重发计数
 
#define ARD_336us		0x00  // 等待336us
#define ARD_586us		0x10  // 等待586us
#define ARD_836us		0x20  // 等待836us
#define ARD_1086us		0x30  // 等待1086us
#define ARD_1336us		0x40  // 等待1336us
#define ARD_1586us		0x50  // 等待1586us
#define ARD_1836us		0x60  // 等待1836us
#define ARD_2086us		0x70  // 等待2086us
#define ARD_2336us		0x80  // 等待2336us
#define ARD_2586us		0x90  // 等待2586us
#define ARD_2836us		0xA0  // 等待2836us
#define ARD_3086us		0xB0  // 等待3086us
#define ARD_3336us		0xC0  // 等待3336us
#define ARD_3586us		0xD0  // 等待3586us
#define ARD_3836us		0xE0  // 等待3836us
#define ARD_4086us		0xF0  // 等待4086us

#define ARC_DISABLE		0x00  // 禁止自动重发 
#define ARC_1time		0x01  // 自动重发1次
#define ARC_2time		0x02  // 自动重发2次
#define ARC_3time		0x03  // 自动重发3次
#define ARC_4time		0x04  // 自动重发4次
#define ARC_5time		0x05  // 自动重发5次
#define ARC_6time		0x06  // 自动重发6次
#define ARC_7time		0x07  // 自动重发7次
#define ARC_8time		0x08  // 自动重发8次
#define ARC_9time		0x09  // 自动重发9次
#define ARC_10time		0x0A  // 自动重发10次
#define ARC_11time		0x0B  // 自动重发11次
#define ARC_12time		0x0C  // 自动重发12次
#define ARC_13time		0x0D  // 自动重发13次
#define ARC_14time		0x0E  // 自动重发14次
#define ARC_15time		0x0F  // 自动重发15次 




/*************射频寄存器RF_SETUP位定义(默认：0FH)*************/
#define PLL_LOCK		0x10  // PLL_LOCK允许，仅应用于测试模式
#define RF_DR			0x08  // 数据传输速率，0——1Mbps，1——2Mbps
#define RF_PWR			0x06  // 发射功率
#define LNA_HCURR		0x01  // 低噪声放大器增益


#define RF_DR_1Mbps		0x00  // 数据传输速率为1Mbps
#define RF_DR_2Mbps		0x08  // 数据传输速率为2Mbps

#define RF_PWR__18dBm	0x00  // 发射功率为-18dBm
#define RF_PWR__12dBm	0x02  // 发射功率为-12dBm
#define RF_PWR__6dBm	0x04  // 发射功率为-6dBm
#define RF_PWR_0dBm		0x06  // 发射功率为0dBm




/*************状态寄存器STATUS位定义(默认：0EH)*************/
#define RX_DR			0x40  // 接收数据中断标志位
#define TX_DS			0x20  // 数据发送完成中断标志位
#define MAX_RT			0x10  // 达到最多次重发中断标志位,如果MAX_RT中断产生则必须清除后系统才能进行通讯
#define RX_P_NO			0x0E  // 接收数据通道号(只读)
#define TX_FULL			0x01  // TX FIFO寄存器满标志(只读)

#define RX_P_NO_0		0x00  // 接收数据通道0
#define RX_P_NO_1		0x02  // 接收数据通道1
#define RX_P_NO_2		0x04  // 接收数据通道2
#define RX_P_NO_3		0x06  // 接收数据通道3
#define RX_P_NO_4		0x08  // 接收数据通道4
#define RX_P_NO_5		0x0A  // 接收数据通道5




/*************发送检测寄存器OBSERVE_TX位定义(默认：00H)*************/
#define PLOS_CNT		0xF0  // 数据包丢失计数器(只读)
#define ARC_CNT			0x0F  // 重发计数器,发送新数据包时此寄存器复位(只读)




/*************FIFO状态寄存器FIFO_STATUS位定义(默认：00H)*************/
#define TX_REUSE		0x40  // 若TX_REUSE=1则当CE位高电平状态时不断发送上一数据包
//#define	TX_FULL			0x20  // TX FIFO寄存器满标志(只读),1——TX FIFO寄存器满
#define TX_EMPTY		0x10  // TX FIFO寄存器空标志(只读),1——TX FIFO寄存器空
#define RX_FULL			0x02  // RX FIFO寄存器满标志(只读),1——RX FIFO寄存器满
#define RX_EMPTY		0x10  // RX FIFO寄存器空标志(只读),1——RX FIFO寄存器空
#define RF24_FLUSH_TX      0xE1
#define RF24_FLUSH_RX      0xE2





/***************** 函数声明 ****************/
void SPI_Write_8bit(unsigned char dat);
unsigned char SPI_Read_8bit(void);
void NRF24L01_Write_Reg(unsigned char reg_name,unsigned char dat);
unsigned char NRF24L01_Read_Reg(unsigned char reg_name);
void NRF24L01_Write_Str(unsigned char reg_name,unsigned char *pBuf,unsigned char bytes);
void NRF24L01_Read_Str(unsigned char reg_name,unsigned char *pBuf,unsigned char bytes);
unsigned char NRF24L01_Read_Data(unsigned char *rx_buf);
unsigned char NRF24L01_Send_Data(unsigned char *tx_buf);
void NRF24L01_RX_Mode_Init(void);
void NRF24L01_TX_Mode_Init(void);
int NRF24L01_Check(void);


#endif