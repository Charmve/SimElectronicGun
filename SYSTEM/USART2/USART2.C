#include "USART2.h"

//////////////////////////////////////////////////
//				����2
//			PA2 -- TX
//			PA3 -- RX
//////////////////////////////////////////////////

u8 US2_Buf[2];
u8 USART2_Flag = 0;
u8 Finish_Flag = 0;

void USART2_Init(u32 bound)
{
	//GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//ʹ��USART4��GPIOCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//USART4_TX   GPIOC.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PC.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��PC.10
   
  //USART4_RX	  GPIOC.11��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PC11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOC.11  

  //Usart4 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
   //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); //��ʼ������4
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���4 
}


void USART2_IRQHandler(void)                	//����4�жϷ������
{
	u8 Res;
	static u8 count,last_data,last_last_data;
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
	{
		Res = USART2->DR; 
		if(USART2_Flag == 0)
		{
			if(last_data==0xF2 && last_last_data==0xC8)
				USART2_Flag=1;
			count=0;
			Finish_Flag = 0;
		}
		if(USART2_Flag == 1)
		{
			US2_Buf[count]=Res;
			count++;
			if(count==2) 
			{
				USART2_Flag=0;
				Finish_Flag=1;
			}
		}
		last_last_data=last_data;
		last_data=Res;
  }
}
