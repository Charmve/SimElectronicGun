#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

/*
两种方法实现按键扫描
一种需要在主函数中调用
一种通过外部中断来触发
*/

#define KEY_SCAN
//#define NVIC_SCAN

#define UP  	 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)//读取按键PC12
#define DOWN   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5) //读取按键PA5
#define LEFT   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)//读取按键PC13
#define RIGHT  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) //读取按键PA4
#define MID    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) //读取按键PA1
#define START  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6) //读取按键PA6

#define NO_PRES    0
#define UP_PRES	   1 
#define DOWN_PRES	 2
#define LEFT_PRES	 3
#define RIGHT_PRES 4
#define MID_PRES   5
#define START_PRES 6

void KEY_Init(void);		//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数    扫描方法
void EXTIX_Init(void);		//中断处理方法
void Key_Operation(u8 Press);

#endif
