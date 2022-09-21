#include "ButtonArray.h"

void ButtonArray_Init(void)
{
	//Row
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	//Col
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_7;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}

u8 ButtonArray_Scan(void)
{
	u8 code;
	u8 Num = 0;
	Row_Out();
	Row1 = 1;Row2 = 1;Row3 = 1;Row4 = 1;
	Col_In();
	code = GPIOC->IDR;
	if(code == 0x55) return 0;
	else
	{
		switch(code)
		{
			case 0xd5:
				Num = 0x01;
				break;
			case 0x75:
				Num = 0x02;
				break;
			case 0x5d:
				Num = 0x03;
				break;
			case 0x57:
				Num = 0x04;
				break;
			default:
				return 0;
		}
	}
	Row1 = 0;Row2 = 0;Row3 = 0;Row4 = 0;
	Col_Out();
	Col1 = 1;Col2 = 1;Col3 = 1;Col4 = 1;
	Row_In();
	code = GPIOC->IDR;
	if(code == 0xaa) return 0;
	else
	{
		switch(code)
		{
			case 0xea:
				Num |= 0x10;
				break;
			case 0xba:
				Num |= 0x20;
				break;
			case 0xae:
				Num |= 0x30;
				break;
			case 0xab:
				Num |= 0x40;
				break;
			default:
				return 0;
		}
	}
	Col1 = 0;Col2 = 0;Col3 = 0;Col4 = 0;
	return Num;
}

u8 ButtonArray_KeyPress(void)
{
	u8 key = ButtonArray_Scan();
	switch(key)
	{
		case 0x11:
			return 1;
		case 0x12:
			return 2;
		case 0x13:
			return 3;
		case 0x21:
			return 4;
		case 0x22:
			return 5;
		case 0x23:
			return 6;
		case 0x31:
			return 7;
		case 0x32:
			return 8;
		case 0x33:
			return 9;
		default:
			return 0;
	}
}

