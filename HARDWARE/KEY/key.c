#include "key.h"
#include "delay.h"
#include "usart.h"
#include "OLED.h"

//Up        --    PC12
//Down      --    PA5
//Left      --    PC13
//Right     --    PA4
//Mid       --    PA1
//Startstop --    PA6

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTC时钟

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
	//up
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;//PC12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成输入，默认下拉
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC12
	//down
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PA5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成输入，默认下拉
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA5
	//left
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;//PC13
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成输入，默认下拉	  
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC13
	//right
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//PA4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA4
	//mid
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//PA1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA1
	//startstop
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;//PA6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA6
#ifdef NVIC_SCAN
	EXTIX_Init();
#endif
} 

/*****************************************************************************
												调用KEY_Scan函数检测
*****************************************************************************/
#ifdef KEY_SCAN 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//返回值：
//0，没有任何按键按下
//注意此函数有响应优先级
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode) key_up=1;  //支持连按		  
	if(key_up&&(UP==0||DOWN==0||LEFT==0||RIGHT==0||MID==0||START==0))
	{
		delay_ms(2);//去抖动 
		key_up=0;
		if(UP==0)return UP_PRES;
		else if(DOWN==0)return DOWN_PRES;
		else if(LEFT==0)return LEFT_PRES;
		else if(RIGHT==0)return RIGHT_PRES;
		else if(MID==0)return MID_PRES;
		else if(START==0)return START_PRES;
	}else if(UP==1&&DOWN==1&&LEFT==1&&RIGHT==1&&MID==1&&START==1) key_up=1;
	return 0;// 无按键按下
}
#endif

/*****************************************************************************
												通过外部中断检测按键
*****************************************************************************/
#ifdef NVIC_SCAN 
void EXTIX_Init(void)
{
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
  //Up -- PC12
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource12);
  EXTI_InitStructure.EXTI_Line = EXTI_Line12;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;						//使能按键所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);
  //Down -- PA5
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource5);
  EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;						//使能按键所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);
	//Left -- PC13
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
  EXTI_InitStructure.EXTI_Line=EXTI_Line13;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;						//使能按键所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);
	//Right -- PA4
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);
  EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;						//使能按键所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);
	//Mid -- PA1
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;						//使能按键所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);
	//Startstop -- PA6
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6);
  EXTI_InitStructure.EXTI_Line = EXTI_Line6;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;  					//使能按键所在的外部中断通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);
}
//MID
void EXTI1_IRQHandler(void)
{
	delay_ms(10);
	if(MID==0)
	{
		Key_Operation(MID_PRES);
	}
	EXTI_ClearITPendingBit(EXTI_Line1);
}
//UP LEFT
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);
	if(UP==0)
	{
		Key_Operation(UP_PRES);
	}
	if(LEFT==0)
	{
		Key_Operation(LEFT_PRES);
	}
	EXTI_ClearITPendingBit(EXTI_Line12);
	EXTI_ClearITPendingBit(EXTI_Line13);
}
//DOWN
void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);
	if(DOWN==0)
	{
		Key_Operation(DOWN_PRES);
	}
	if(START==0)
	{
		Key_Operation(START_PRES);
	}
	EXTI_ClearITPendingBit(EXTI_Line5);
	EXTI_ClearITPendingBit(EXTI_Line6);
}
//RIGHT
void EXTI4_IRQHandler(void)
{
	delay_ms(10);
	if(RIGHT==0)
	{
		Key_Operation(RIGHT_PRES);
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}
#endif

void Key_Operation(u8 Press)
{
	switch(Press)
	{
		case UP_PRES:
			printf("UP");
			break;
		case DOWN_PRES:
			printf("DOWN");
			break;
		case LEFT_PRES:
			printf("LEFT");
			break;
		case RIGHT_PRES:
			printf("RIGHT");
			break;
		case MID_PRES:
			printf("MID");
			break;
		case START_PRES:
			printf("START");
			break;
		default:
			break;
	}
}



