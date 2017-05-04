#ifndef _NRF24L01_H
#define _NRF24L01_H


/*******************nRF24L01�Ķ˿ڶ���********************/
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
//NRF24L01���ͽ������ݿ�ȶ���
#define TX_ADR_WIDTH    5   //5�ֽڵĵ�ַ���
#define RX_ADR_WIDTH    5   //5�ֽڵĵ�ַ���
#define TX_PLOAD_WIDTH  32  //32�ֽڵ��û����ݿ��
#define RX_PLOAD_WIDTH  32  //32�ֽڵ��û����ݿ��



//////////////////////////////////////////////////////////////////////////////////////////////////////////
//NRF24L01�Ĵ�������ָ��
#define NRF24L01_READ_REG        0x00  //�����üĴ���,��5λΪ�Ĵ�����ַ
#define NRF24L01_WRITE_REG       0x20  //д���üĴ���,��5λΪ�Ĵ�����ַ
#define NRF24L01_RD_RX_PLOAD     0x61  //��RX��Ч����,1-32�ֽ�
#define NRF24L01_WR_TX_PLOAD     0xA0  //дTX��Ч����,1-32�ֽ�
#define NRF24L01_FLUSH_TX        0xE1  //���TX FIFO�Ĵ���.����ģʽ����
#define NRF24L01_FLUSH_RX        0xE2  //���RX FIFO�Ĵ���.����ģʽ����
#define NRF24L01_REUSE_TX_PL     0xE3  //����ʹ����һ������,CEΪ��,���ݰ������Ϸ���.
#define NRF24L01_NOP             0xFF  //�ղ���,����������״̬�Ĵ���	 





//////////////////////////////////////////////////////////////////////////////////////////////////////////
//NRF24L01�Ĵ�����ַ
#define CONFIG          0x00  //���üĴ�����ַ
#define EN_AA           0x01  //ʹ���Զ�Ӧ����  
#define EN_RXADDR       0x02  //���յ�ַ����
#define SETUP_AW        0x03  //���õ�ַ���(��������ͨ��)
#define SETUP_RETR      0x04  //�����Զ��ط�
#define RF_CH           0x05  //RFͨ��Ƶ��,F0 = 2400 + RF_CH(MHz)
#define RF_SETUP        0x06  //RF�Ĵ���
#define STATUS          0x07  //״̬�Ĵ���
#define OBSERVE_TX		0x08  //���ͼ��Ĵ���
#define CD              0x09  //�ز����Ĵ���
#define RX_ADDR_P0      0x0A  //����ͨ��0���յ�ַ,��󳤶�5���ֽ�,���ֽ���ǰ(��λֵ��0xE7E7E7E7E7)
#define RX_ADDR_P1      0x0B  //����ͨ��1���յ�ַ,��󳤶�5���ֽ�,���ֽ���ǰ(��λֵ��0xC2C2C2C2C2)
#define RX_ADDR_P2      0x0C  //����ͨ��2���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define RX_ADDR_P3      0x0D  //����ͨ��3���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define RX_ADDR_P4      0x0E  //����ͨ��4���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define RX_ADDR_P5      0x0F  //����ͨ��5���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define TX_ADDR         0x10  //���͵�ַ(���ֽ���ǰ),ShockBurstTMģʽ��,RX_ADDR_P0��˵�ַ���
#define RX_PW_P0        0x11  //��������ͨ��0��Ч���ݿ��(1-32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P1        0x12  //��������ͨ��1��Ч���ݿ��(1-32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P2        0x13  //��������ͨ��2��Ч���ݿ��(1-32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P3        0x14  //��������ͨ��3��Ч���ݿ��(1-32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P4        0x15  //��������ͨ��4��Ч���ݿ��(1-32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P5        0x16  //��������ͨ��5��Ч���ݿ��(1-32�ֽ�),����Ϊ0��Ƿ�
#define FIFO_STATUS     0x17  //FIFO״̬�Ĵ���






//////////////////////////////////////////////////////////////////////////////////////////////////////////
//NRF24L01�Ĵ���λ����


/*************���üĴ���CONFIGλ����(Ĭ�ϣ�08H)*************/
#define MASK_RX_DR		0x40  // �������ж�RX_RD��1����IRQ���Ų���ʾRX_RD�жϣ�0����RX_RD�жϲ���ʱIRQ���ŵ�ƽΪ��
#define MASK_TX_DR		0x20  // �������ж�TX_RD��1����IRQ���Ų���ʾTX_RD�жϣ�0����TX_RD�жϲ���ʱIRQ���ŵ�ƽΪ��
#define MASK_MAX_RT		0x10  // �������ж�MAX_RT,1����IRQ���Ų���ʾMAX_RT�ж�,0����MAX_RT�жϲ���ʱIRQ���ŵ�ƽΪ��
#define EN_CRC			0x08  // CRCʹ��,���EN_AA������һλΪ����EN_CRCǿ��Ϊ��
#define CRCO			0x04  // CRCģʽ,0����8λCRCУ�飬1����16λCRCУ��
#define PWR_UP			0x02  // 1�����ϵ磬0��������
#define PRIM_RX 		0x01  // 1��������ģʽ��0��������ģʽ
#define MASK_IRQ_ALL    0x70

#define DIS_IT_RX_DR	0x40  // IRQ���Ų���ʾRX_RD�ж�
#define EN_IT_RX_DR		0x00  // RX_RD�жϲ���ʱIRQ���ŵ�ƽΪ��

#define DIS_IT_TX_DR	0x20  // IRQ���Ų���ʾTX_RD�ж�
#define EN_IT_TX_DR		0x00  // TX_RD�жϲ���ʱIRQ���ŵ�ƽΪ��

#define DIS_IT_MAX_RT	0x10  // IRQ���Ų���ʾMAX_RT�ж�
#define EN_IT_MAX_RT	0x00  // MAX_RT�жϲ���ʱIRQ���ŵ�ƽΪ��

#define EN_CRC			0x08  // ʹ��CRCУ��
#define DIS_CRC			0x00  // �ر�CRCУ��

#define CRC_16bit		0x04  // 16λCRCУ��
#define CRC_8bit		0x00  // 8λCRCУ��

#define PWR_ON			0x02  // �ϵ�
#define PWR_OFF			0x00  // ����

#define PRIM_RXD		0x01  // ����ģʽ
#define PRIM_TXD		0x00  // ����ģʽ




/*************ʹ��"�Զ�Ӧ��"���ܼĴ���EN_AAλ����(Ĭ�ϣ�3FH)*************/
#define ENAA_P5 		0x20  // ����ͨ��5�Զ�Ӧ������
#define ENAA_P4 		0x10  // ����ͨ��4�Զ�Ӧ������
#define ENAA_P3 		0x08  // ����ͨ��3�Զ�Ӧ������
#define ENAA_P2 		0x04  // ����ͨ��2�Զ�Ӧ������
#define ENAA_P1 		0x02  // ����ͨ��1�Զ�Ӧ������
#define ENAA_P0 		0x01  // ����ͨ��0�Զ�Ӧ������




/*************���յ�ַ����Ĵ���EN_RXADDRλ����(Ĭ�ϣ�03H)*************/
#define ERX_P5			0x20  // ��������ͨ��5����
#define ERX_P4			0x10  // ��������ͨ��4����
#define ERX_P3			0x08  // ��������ͨ��3����
#define ERX_P2			0x04  // ��������ͨ��2����
#define ERX_P1			0x02  // ��������ͨ��1����
#define ERX_P0			0x01  // ��������ͨ��0���� 




/*************���õ�ַ��ȼĴ���SETUP_AWλ����(Ĭ�ϣ�03H)*************/
#define AW		        0x03  // ����/�����ַ���

#define AW_NA			0x00  // ��Ч
#define AW_3byte		0x01  // 3�ֽڿ��
#define AW_4byte		0x02  // 4�ֽڿ��
#define AW_5byte		0x03  // 5�ֽڿ�� 				




/*************�����Զ��ط��Ĵ���SETUP_RETRλ����(Ĭ�ϣ�03H)*************/
#define ARD		        0xF0  // �Զ��ط���ʱ
#define ARC       	        0x0F  // �Զ��ط�����
 
#define ARD_336us		0x00  // �ȴ�336us
#define ARD_586us		0x10  // �ȴ�586us
#define ARD_836us		0x20  // �ȴ�836us
#define ARD_1086us		0x30  // �ȴ�1086us
#define ARD_1336us		0x40  // �ȴ�1336us
#define ARD_1586us		0x50  // �ȴ�1586us
#define ARD_1836us		0x60  // �ȴ�1836us
#define ARD_2086us		0x70  // �ȴ�2086us
#define ARD_2336us		0x80  // �ȴ�2336us
#define ARD_2586us		0x90  // �ȴ�2586us
#define ARD_2836us		0xA0  // �ȴ�2836us
#define ARD_3086us		0xB0  // �ȴ�3086us
#define ARD_3336us		0xC0  // �ȴ�3336us
#define ARD_3586us		0xD0  // �ȴ�3586us
#define ARD_3836us		0xE0  // �ȴ�3836us
#define ARD_4086us		0xF0  // �ȴ�4086us

#define ARC_DISABLE		0x00  // ��ֹ�Զ��ط� 
#define ARC_1time		0x01  // �Զ��ط�1��
#define ARC_2time		0x02  // �Զ��ط�2��
#define ARC_3time		0x03  // �Զ��ط�3��
#define ARC_4time		0x04  // �Զ��ط�4��
#define ARC_5time		0x05  // �Զ��ط�5��
#define ARC_6time		0x06  // �Զ��ط�6��
#define ARC_7time		0x07  // �Զ��ط�7��
#define ARC_8time		0x08  // �Զ��ط�8��
#define ARC_9time		0x09  // �Զ��ط�9��
#define ARC_10time		0x0A  // �Զ��ط�10��
#define ARC_11time		0x0B  // �Զ��ط�11��
#define ARC_12time		0x0C  // �Զ��ط�12��
#define ARC_13time		0x0D  // �Զ��ط�13��
#define ARC_14time		0x0E  // �Զ��ط�14��
#define ARC_15time		0x0F  // �Զ��ط�15�� 




/*************��Ƶ�Ĵ���RF_SETUPλ����(Ĭ�ϣ�0FH)*************/
#define PLL_LOCK		0x10  // PLL_LOCK������Ӧ���ڲ���ģʽ
#define RF_DR			0x08  // ���ݴ������ʣ�0����1Mbps��1����2Mbps
#define RF_PWR			0x06  // ���书��
#define LNA_HCURR		0x01  // �������Ŵ�������


#define RF_DR_1Mbps		0x00  // ���ݴ�������Ϊ1Mbps
#define RF_DR_2Mbps		0x08  // ���ݴ�������Ϊ2Mbps

#define RF_PWR__18dBm	0x00  // ���书��Ϊ-18dBm
#define RF_PWR__12dBm	0x02  // ���书��Ϊ-12dBm
#define RF_PWR__6dBm	0x04  // ���书��Ϊ-6dBm
#define RF_PWR_0dBm		0x06  // ���书��Ϊ0dBm




/*************״̬�Ĵ���STATUSλ����(Ĭ�ϣ�0EH)*************/
#define RX_DR			0x40  // ���������жϱ�־λ
#define TX_DS			0x20  // ���ݷ�������жϱ�־λ
#define MAX_RT			0x10  // �ﵽ�����ط��жϱ�־λ,���MAX_RT�жϲ�������������ϵͳ���ܽ���ͨѶ
#define RX_P_NO			0x0E  // ��������ͨ����(ֻ��)
#define TX_FULL			0x01  // TX FIFO�Ĵ�������־(ֻ��)

#define RX_P_NO_0		0x00  // ��������ͨ��0
#define RX_P_NO_1		0x02  // ��������ͨ��1
#define RX_P_NO_2		0x04  // ��������ͨ��2
#define RX_P_NO_3		0x06  // ��������ͨ��3
#define RX_P_NO_4		0x08  // ��������ͨ��4
#define RX_P_NO_5		0x0A  // ��������ͨ��5




/*************���ͼ��Ĵ���OBSERVE_TXλ����(Ĭ�ϣ�00H)*************/
#define PLOS_CNT		0xF0  // ���ݰ���ʧ������(ֻ��)
#define ARC_CNT			0x0F  // �ط�������,���������ݰ�ʱ�˼Ĵ�����λ(ֻ��)




/*************FIFO״̬�Ĵ���FIFO_STATUSλ����(Ĭ�ϣ�00H)*************/
#define TX_REUSE		0x40  // ��TX_REUSE=1��CEλ�ߵ�ƽ״̬ʱ���Ϸ�����һ���ݰ�
//#define	TX_FULL			0x20  // TX FIFO�Ĵ�������־(ֻ��),1����TX FIFO�Ĵ�����
#define TX_EMPTY		0x10  // TX FIFO�Ĵ����ձ�־(ֻ��),1����TX FIFO�Ĵ�����
#define RX_FULL			0x02  // RX FIFO�Ĵ�������־(ֻ��),1����RX FIFO�Ĵ�����
#define RX_EMPTY		0x10  // RX FIFO�Ĵ����ձ�־(ֻ��),1����RX FIFO�Ĵ�����
#define RF24_FLUSH_TX      0xE1
#define RF24_FLUSH_RX      0xE2





/***************** �������� ****************/
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