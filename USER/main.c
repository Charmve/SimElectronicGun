#include "delay.h"
#include "sys.h"
#include "math.h"
#include "usart.h"
#include "oled.h"
#include "key.h"
#include "MyVariable.h"
#include "TIM6_Base.h"
#include "TIM4_PWM.h"
#include "Menu.h"
#include "PID.h"
#include "UART4.h"
#include "AnoTc.h"
#include "USART2.h"
#include "DC_CONTROL.h"
#include "MyVariable.h"

u8 cnt = 0;
u8 i=0;
u8 TIM6_Flag = 0;

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 													 //延时函数初始化	  
	uart_init(115200);	 													 //串口初始化为115200
	USART2_Init(115200);													 //串口屏
	UART4_Init(115200);														 //OpenMV
	JTAG_Disagble();															 //JTAG
	
	Beep_Init();
	
	OLED_Init();
	OLED_Clear();
	KEY_Init();
	DC_GPIO_Init();
	
//	PID_ParaInit();
//	Set_M1_PID(0.08,0,0);
//	Set_M1_Target(176);
	
	TIM6_Init(20000-1,72-1);
	
	TIM4_PWM_Init(20000-1,72-1);
	
	//舵机归零
	SetPWM1(1760);
 	SetPWM2(1600);
	
	
	
	while(1)
	{
		if(TIM6_Flag)
		{
			if(Mode == 1)   //基础：要求1
			{
				if(Finish_Flag)
				{				
					if(US2_Buf[1] == 0xAA)
					{
						Power = 1;
						delay_ms(500);
						Shoot = 1;
						delay_ms(1000);
						Power = 0;
						Shoot = 0;
						US2_Buf[1] = 0;
					}
					Finish_Flag = 0;
				}
			}
			if(Mode == 2)
			{
				int temp_pwm = Pwm[0];
				if(count == 0)
				{
					L = 200;
					Angle = 0;
					count++;
				}
				if(confirm == 1)
				{
					for(i=0;i<21;i++)
					{
						if(Num[i] == L)
						{
							temp_pwm = Pwm[i];
							break;
						}
						else if(Num[i]<L && Num[i+1]>L)
						{
							temp_pwm = (Pwm[i]+Pwm[i+1])/2.0;
							break;
						}
					}
					SetPWM2(temp_pwm);
					confirm = 0;
				}
				if(Finish_Flag)
				{				
					if(US2_Buf[1] == 0xAA)
					{
						Power = 1;
						delay_ms(500);
						Shoot = 1;
						delay_ms(1000);
						Power = 0;
						Shoot = 0;
						US2_Buf[1] = 0;
					}
					Finish_Flag = 0;
				}
			}
			if(Mode == 3)
			{
				int temp_pwm = Pwm[0];
				int temp_angle = 1760;
				if(count == 0)
				{
					L = 200;
					Angle = 0;
					count++;
				}
				if(confirm == 1)
				{
					for(i=0;i<21;i++)
					{
						if(Num[i] == L)
						{
							temp_pwm = Pwm[i];
							break;
						}
						else if(Num[i]<L && Num[i+1]>L)
						{
							temp_pwm = (Pwm[i]+Pwm[i+1])/2.0;
							break;
						}
						else if(L>Num[20])
								temp_pwm = Pwm[20];
					}
					temp_angle = ((-Angle+23.4+90)/180*2000+500);
					SetPWM1(temp_angle);
					SetPWM2(temp_pwm);
					confirm = 0;
				}
				if(Finish_Flag)
				{				
					if(US2_Buf[1] == 0xAA)
					{
						Power = 1;
						delay_ms(500);
						Shoot = 1;
						delay_ms(1000);
						Power = 0;
						Shoot = 0;
						US2_Buf[1] = 0;
					}
					Finish_Flag = 0;
				}
			}
			if(Mode == 4)
			{
				if(count == 0)
				{
					SetPWM2(1600);
					int temp_pwm = Pwm[0];
					int pwm0 = 2093;
					Get_Pos();
					SetPWM1(pwm0);
					//找目标
					while(Pos == 253 || (Pos!=253 && ((Pos-155)>2 || (Pos-155)<-2)))
					{
						Get_Pos();
						pwm0 -=3;
						delay_ms(50);
						SetPWM1(pwm0);
					}
					//测距
					Get_Distance();
					for(i=0;i<21;i++)
					{
						if(Num[i] == L)
						{
							temp_pwm = Pwm[i];
							break;
						}
						else if(Num[i]<L && Num[i+1]>L)
						{
							temp_pwm = (Pwm[i]+Pwm[i+1])/2.0;
							break;
						}
						else if(L>Num[20])
								temp_pwm = Pwm[20];
					}
					
					SetPWM2(temp_pwm);
					delay_ms(200);
					//开火
					Power = 1;
					delay_ms(500);
					Shoot = 1;
					delay_ms(1000);
					Power = 0;
					Shoot = 0;
					count = 1;
				}
			}
			if(Mode == 5)
			{
				int i = 0;
				int cnt_ = 0;
				if(count == 0)
				{
					SetPWM2(1600);
					
					for(i=2093;i>1426;i-=15)
					{
						SetPWM1(i);
						Get_Pos();
						if((Pos!=253) && Pos<180)
						{
							if(cnt_ == 0)
							{
								SetPWM2(1365);
								Power = 1;
								delay_ms(500);
								Shoot = 1;
								delay_ms(10);
								Power = 0;
								Shoot = 0;
								SetPWM2(1600);
								cnt_++;
							}
						}
						delay_ms(50);
					}
					for(i=1426;i<2093;i+=15)
					{
						SetPWM1(i);
						delay_ms(50);
					}
					count = 1;
				}
			}
			if(Mode == 6)
			{
				if(Finish_Flag)
				{				
					if(US2_Buf[1] == 0xA0)
					{
						SetPWM2(1900);
						delay_ms(1500);
						SetPWM2(1600);
					}
					Finish_Flag = 0;
				}
			}
		}
		TIM6_Flag = 0;
	}
}

void TIM6_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)!=RESET)
	{
		cnt++;
		if(cnt == 2)
		{
			GetMenuIndex();
			OLED_Show();
			cnt = 0;
		}
		TIM6_Flag = 1;
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
	}
}


