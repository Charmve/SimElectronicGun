#include "TIM4_PWM.h"

/****************************
TIM4
CH1 PB6/PD12
CH2 PB7/PD13
CH3 PB8/PD14
CH4 PB9/PD15
****************************/

void TIM4_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructre;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	TIM_TimeBaseStructre.TIM_Period = arr;
	TIM_TimeBaseStructre.TIM_Prescaler = psc;
	TIM_TimeBaseStructre.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructre.TIM_ClockDivision = 0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructre);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM4,&TIM_OCInitStructure);
	TIM_OC2Init(TIM4,&TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM4,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
}

void SetPWM1(int pwm1)
{
	TIM4->CCR1 = pwm1;
}

void SetPWM2(int pwm2)
{
	TIM4->CCR2 = pwm2;
}


