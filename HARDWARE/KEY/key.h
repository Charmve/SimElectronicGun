#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

/*
���ַ���ʵ�ְ���ɨ��
һ����Ҫ���������е���
һ��ͨ���ⲿ�ж�������
*/

#define KEY_SCAN
//#define NVIC_SCAN

#define UP  	 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)//��ȡ����PC12
#define DOWN   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) //��ȡ����PA5
#define LEFT   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)//��ȡ����PC13
#define RIGHT  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) //��ȡ����PA4
#define MID    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) //��ȡ����PA1
#define START  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6) //��ȡ����PA6

#define NO_PRES    0
#define UP_PRES	   1 
#define DOWN_PRES	 2
#define LEFT_PRES	 3
#define RIGHT_PRES 4
#define MID_PRES   5
#define START_PRES 6

void KEY_Init(void);		//IO��ʼ��
u8 KEY_Scan(u8 mode);  	//����ɨ�躯��    ɨ�跽��
void EXTIX_Init(void);		//�жϴ�����
void Key_Operation(u8 Press);

#endif
