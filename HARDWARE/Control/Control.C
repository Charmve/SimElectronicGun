#include "control.h"
#include "delay.h"

int L = 0;
int Angle = -30;
int Pos = 0;

void Get_Pos(void)
{
	Pos = (int)(Rec_Buf[0]|(Rec_Buf[1]<<8));
}

void Get_Distance(void)
{
	L = (int)(Rec_Buf[2]|(Rec_Buf[3]<<8))-30;
}

void X_Control(void)
{
	int Pwm;
	Get_Pos();
	Pwm = M1_PID_Balance();
	
	static int temp;
	temp += Pwm;
	if(temp < 1427) temp = 1427;
	if(temp > 2093) temp = 2093;
//	Pwm = RangeM1(M1_PID_Balance());
	SetPWM1(temp);
}



int RangeM1(int pwm)
{
	if(pwm > 1000) pwm = 1000;
	if(pwm <-1000) pwm = -1000;
	return pwm;
}

void Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
}

void Sound(u16 frq)
{
	u32 time;
	if(frq != 1000)
	{
		time = 500000/((u32)frq);
		BEEP = 1;
		delay_us(time);
		BEEP = 0;
		delay_us(time);
	}else
		delay_us(1000);
}
void Sound2(u16 time)
{
    BEEP = 1;
    delay_ms(time);
    BEEP = 0;
    delay_ms(time);
}

void play_music(void)
{
	//              低7  1   2   3   4   5   6   7  高1 高2 高3 高4 高5 不发音
	uc16 tone[] = {247,262,294,330,349,392,440,294,523,587,659,698,784,1000};//音频数据表
	//红尘情歌
	u8 music[]={5,5,6,8,7,6,5,6,13,13,//音调
                5,5,6,8,7,6,5,3,13,13,
                2,2,3,5,3,5,6,3,2,1,
                6,6,5,6,5,3,6,5,13,13,

                5,5,6,8,7,6,5,6,13,13,
                5,5,6,8,7,6,5,3,13,13,
                2,2,3,5,3,5,6,3,2,1,
                6,6,5,6,5,3,6,1,	

                13,8,9,10,10,9,8,10,9,8,6,
                13,6,8,9,9,8,6,9,8,6,5,
                13,2,3,5,5,3,5,5,6,8,7,6,
                6,10,9,9,8,6,5,6,8};	
	u8 time[] = {2,4,2,2,2,2,2,8,4, 4, //时间
                2,4,2,2,2,2,2,8,4, 4, 
                2,4,2,4,2,2,4,2,2,8,
                2,4,2,2,2,2,2,8,4 ,4, 

                2,4,2,2,2,2,2,8,4, 4, 
                2,4,2,2,2,2,2,8,4, 4, 
                2,4,2,4,2,2,4,2,2,8,
                2,4,2,2,2,2,2,8,

                4, 2,2,2, 4, 2,2,2, 2,2,8,
                4, 2,2,2,4,2,2,2,2,2,8,
                4, 2,2,2,4,2,2,5,2,6,2,4,
                2,2 ,2,4,2,4,2,2,12};	
	u32 yanshi;
	u16 i,e;
	yanshi = 10;
	for(i=0;i<sizeof(music)/sizeof(music[0]);i++){
		for(e=0;e<((u16)time[i])*tone[music[i]]/yanshi;e++){
			Sound((u32)tone[music[i]]);
		}	
	}
}

