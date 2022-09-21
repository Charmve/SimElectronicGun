#include "TIM6_Base.h"

void TIM6_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	//������ʱ������
	//Parameter:
	//TIM6 = (arr+1)(psc+1)/72MHz
	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	//��������CounterMode��ClockDivision������ʱ������Ҫ����
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitStructure);
	//�ж�����
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//������±�־λ
	TIM_ClearFlag(TIM6,TIM_FLAG_Update);
	//ʹ�ܶ�ʱ��6�ĸ����ж�
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	
	//������ʱ��6
	TIM_Cmd(TIM6,ENABLE);
}


