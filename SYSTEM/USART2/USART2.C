#include "USART2.h"

//////////////////////////////////////////////////
//				串口2
//			PA2 -- TX
//			PA3 -- RX
//////////////////////////////////////////////////

u8 US2_Buf[2];
u8 USART2_Flag = 0;
u8 Finish_Flag = 0;

void USART2_Init(u32 bound)
{
	//GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART4，GPIOC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//USART4_TX   GPIOC.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PC.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化PC.10
   
  //USART4_RX	  GPIOC.11初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PC11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOC.11  

  //Usart4 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
   //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口4
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口4 
}


void USART2_IRQHandler(void)                	//串口4中断服务程序
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

