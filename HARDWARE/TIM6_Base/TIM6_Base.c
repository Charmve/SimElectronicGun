#include "TIM6_Base.h"

void TIM6_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	//基本定时器配置
	//Parameter:
	//TIM6 = (arr+1)(psc+1)/72MHz
	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	//其他两个CounterMode和ClockDivision基础定时器不需要设置
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);
	//中断配置
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//清除更新标志位
	TIM_ClearFlag(TIM6,TIM_FLAG_Update);
	//使能定时器6的更新中断
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	
	//开启定时器6
	TIM_Cmd(TIM6,ENABLE);
}


