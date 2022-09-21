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

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTCʱ��

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
	//up
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;//PC12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó����룬Ĭ������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC12
	//down
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PA5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó����룬Ĭ������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA5
	//left
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13;//PC13
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó����룬Ĭ������	  
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC13
	//right
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//PA4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA4
	//mid
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//PA1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA1
	//startstop
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;//PA6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA6
#ifdef NVIC_SCAN
	EXTIX_Init();
#endif
} 

/*****************************************************************************
												����KEY_Scan�������
*****************************************************************************/
#ifdef KEY_SCAN 
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//����ֵ��
//0��û���κΰ�������
//ע��˺�������Ӧ���ȼ�
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode) key_up=1;  //֧������		  
	if(key_up&&(UP==0||DOWN==0||LEFT==0||RIGHT==0||MID==0||START==0))
	{
		delay_ms(2);//ȥ���� 
		key_up=0;
		if(UP==0)return UP_PRES;
		else if(DOWN==0)return DOWN_PRES;
		else if(LEFT==0)return LEFT_PRES;
		else if(RIGHT==0)return RIGHT_PRES;
		else if(MID==0)return MID_PRES;
		else if(START==0)return START_PRES;
	}else if(UP==1&&DOWN==1&&LEFT==1&&RIGHT==1&&MID==1&&START==1) key_up=1;
	return 0;// �ް�������
}
#endif

/*****************************************************************************
												ͨ���ⲿ�жϼ�ⰴ��
*****************************************************************************/
#ifdef NVIC_SCAN 
void EXTIX_Init(void)
{
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��
  //Up -- PC12
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource12);
  EXTI_InitStructure.EXTI_Line = EXTI_Line12;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;						//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);
  //Down -- PA5
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource5);
  EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;						//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);
	//Left -- PC13
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
  EXTI_InitStructure.EXTI_Line=EXTI_Line13;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;						//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);
	//Right -- PA4
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);
  EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;						//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);
	//Mid -- PA1
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;						//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);
	//Startstop -- PA6
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6);
  EXTI_InitStructure.EXTI_Line = EXTI_Line6;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;  					//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
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



