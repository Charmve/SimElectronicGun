#include "Menu.h"

#define A Pos
#define B Pos
#define C L
#define D Angle
#define A_Step 1
#define B_Step 1
#define C_Step 1
#define D_Step 1

//行、页标志位的声明
//page
u8 page_num = 0;
u8 page_num_last = 1;
//line
u8 line_num = 0;
u8 line_num_last = 0;
//一行分为两列，判断在哪列
u8 col_num = 0;
u8 col_num_last = 0;
//用来记录改变第几行的值
u8 order = 0xff;
//判断是加还是减
u8 op=0;
//功能模式标志位
u8 Mode = 0;
//电机状态标志位
u8 Motor = 1;
u8 Motor_last = 1;
//修改标志位
u8 change = 0;
//
u8 confirm = 0;
u8 count = 0;

//第一页的界面
static void UI_0(void)
{
	OLED_ShowCHinese(20,0,0);
	OLED_ShowCHinese(36,0,1);
	OLED_ShowCHinese(52,0,2);
	OLED_ShowCHinese(68,0,3);
	OLED_ShowCHinese(84,0,4);
	
	OLED_ShowString(0,2,"1.PID",16);
	OLED_ShowCHinese(42,2,5);
	OLED_ShowCHinese(58,2,6);
	OLED_ShowString(0,4,"2.",16);
	OLED_ShowCHinese(15,4,7);
	OLED_ShowCHinese(31,4,8);
	OLED_ShowCHinese(47,4,9);
	OLED_ShowCHinese(63,4,10);
	OLED_ShowString(0,6,"3.",16);
	OLED_ShowCHinese(15,6,11);
	OLED_ShowCHinese(31,6,12);
	OLED_ShowCHinese(47,6,13);
	OLED_ShowCHinese(63,6,14);
}

static void UI_1(void)
{
	OLED_ShowString(25,0,"PID Adjust",16);
	OLED_ShowString(25,2,"Kp:",8);
	OLED_ShowString(25,3,"Ki:",8);
	OLED_ShowString(25,4,"Kd:",8);
	OLED_ShowString(25,5,"Kp:",8);
	OLED_ShowString(25,6,"Ki:",8);
	OLED_ShowString(25,7,"Kd:",8);
	OLED_Showfloat(50,2,M1_PID.Kp,4,2,8);
	OLED_Showfloat(50,3,M1_PID.Ki,4,2,8);
	OLED_Showfloat(50,4,M1_PID.Kd,4,2,8);
	OLED_Showfloat(50,5,M2_PID.Kp,4,2,8);
	OLED_Showfloat(50,6,M2_PID.Ki,4,2,8);
	OLED_Showfloat(50,7,M2_PID.Kd,4,2,8);
}

static void UI_2(void)
{
	OLED_ShowChar(23,0,'|',16);
	OLED_ShowChar(23,2,'|',16);
	OLED_ShowChar(23,4,'|',16);
	OLED_ShowChar(23,6,'|',16);
	OLED_ShowString(0,0,"Fun",8);
	OLED_ShowString(0,2,"1",8);
	OLED_ShowString(0,3,"2",8);
	OLED_ShowString(0,4,"3",8);
	OLED_ShowString(0,5,"4",8);
	OLED_ShowString(0,6,"5",8);
	OLED_ShowString(0,7,"6",8);
	OLED_ShowString(50,0,"Para",16);
	OLED_ShowString(38,2,"P:",16);
	OLED_ShowString(38,4,"L:",16);
	OLED_ShowString(38,6,"A:",16);
	OLED_ShowNum(68,2,B,3,16);
	OLED_ShowNum(68,4,C,3,16);
	OLED_ShowNum(68,6,D,3,16);
}

static void UI_3(void)
{
	OLED_ShowString(0,0,"D:",16);
	OLED_ShowString(0,2,"T:",16);
}

//刷新指针
static void Fresh_Pointer(void)
{
	if(page_num == 0)
	{
		OLED_ShowChar(110,line_num_last,' ',16);
		OLED_ShowChar(110,line_num,'<',16);
	}
	else if(page_num == 1)
	{
		OLED_ShowChar(110,line_num_last,' ',8);
		OLED_ShowChar(110,line_num,'<',8);
	}
	else if(page_num == 2)
	{
		if(col_num == col_num_last)
		{
			if(col_num == 0)
			{
				OLED_ShowChar(12,line_num_last,' ',8);
				OLED_ShowChar(12,line_num,'<',8);
			}
			else
			{
				OLED_ShowChar(110,line_num_last,' ',16);
				OLED_ShowChar(110,line_num,'<',16);
			}
		}
		else
		{
			if(col_num)
			{
				line_num = 2;
				OLED_ShowChar(12,line_num_last,' ',8);
				OLED_ShowChar(110,line_num,'<',16);
				line_num_last = line_num;
			}
			else
			{
				OLED_ShowChar(110,line_num_last,' ',16);
				OLED_ShowChar(12,line_num,'<',8);
			}
		}
	}
	else
	{
		OLED_ShowChar(110,line_num_last,' ',16);
		OLED_ShowChar(110,line_num,'<',16);
	}
}

//刷新PID参数
void Fresh_PID(void)
{
	switch(order)
	{
		case 0:
			if(op == 0)
				M1_PID.Kp-=0.2;
			else
				M1_PID.Kp+=0.2;
			OLED_ShowString(50,2,"      ",8);
			OLED_Showfloat(50,2,M1_PID.Kp,4,2,8);
			break;
		case 1:
			if(op == 0)
				M1_PID.Ki-=0.2;
			else
				M1_PID.Ki+=0.2;
			OLED_ShowString(50,3,"      ",8);
			OLED_Showfloat(50,3,M1_PID.Ki,4,2,8);
			break;
		case 2:
			if(op == 0)
				M1_PID.Kd-=0.2;
			else
				M1_PID.Kd+=0.2;
			OLED_ShowString(50,4,"      ",8);
			OLED_Showfloat(50,4,M1_PID.Kd,4,2,8);
			break;
		case 3:
			if(op == 0)
				M2_PID.Kp-=0.2;
			else
				M2_PID.Kp+=0.2;
			OLED_ShowString(50,5,"      ",8);
			OLED_Showfloat(50,5,M2_PID.Kp,4,2,8);
			break;
		case 4:
			if(op == 0)
				M2_PID.Ki-=0.2;
			else
				M2_PID.Ki+=0.2;
			OLED_ShowString(50,6,"      ",8);
			OLED_Showfloat(50,6,M2_PID.Ki,4,2,8);
			break;
		case 5:
			if(op == 0)
				M2_PID.Kd-=0.2;
			else
				M2_PID.Kd+=0.2;
			OLED_ShowString(50,7,"      ",8);
			OLED_Showfloat(50,7,M2_PID.Kd,4,2,8);
			break;
	}
}


void Fresh_Motor(void)
{
}

void Fresh_DT(void)
{
}

void Fresh_Pos(void)
{
	OLED_ShowString(68,2,"   ",16);
	OLED_ShowNum(68,2,B,3,16);
}

void Fresh_Para(void)
{
	switch(order)
	{
		case 0:
			if(op==0)
				A-=A_Step;
			else
				A+=A_Step;
			OLED_ShowString(48,0,"     ",16);
			OLED_ShowNum(68,0,A,3,16);
			break;
		case 1:
			if(op==0)
				B-=B_Step;
			else
				B+=B_Step;
			OLED_ShowString(68,2,"   ",16);
			OLED_ShowNum(68,2,B,3,16);
			break;
		case 2:
			if(op==0)
				C-=C_Step;
			else
				C+=C_Step;
			OLED_ShowString(68,4,"     ",16);
			OLED_ShowNum(68,4,C,3,16);
			break;
		case 3:
			if(op==0)
				D-=D_Step;
			else
				D+=D_Step;
			OLED_ShowString(68,6,"     ",16);
			if(D<0)
			{
				OLED_ShowNum(68,6,-D,3,16);
				OLED_ShowChar(68,6,'-',16);
			}
			else
			{
				OLED_ShowNum(68,6,D,3,16);
			}
			break;
	}
}


void GetMenuIndex(void)
{
	u8 cKeyPressNum = KEY_Scan(0);
	switch(cKeyPressNum)
	{
		case UP_PRES:
			if(page_num == 0 && line_num>=2 && line_num<=6)
			{
				if(line_num == 2)	line_num = 6;
				else line_num-=2;
				break;
			}
			if(page_num == 1 && line_num>=2 && line_num<=7)
			{
				if(line_num == 2)	line_num=7;
				else line_num--;
				break;
			}
			if(page_num == 2)
			{
				if(line_num<=7 && col_num == 0)
				{
					if(line_num == 2)	line_num=7;
					else line_num--;
					break;
				}
				if(line_num<=6 && col_num == 1)
				{
					if(line_num == 2)	line_num=6;
					else line_num-=2;
					break;
				}
			}
			break;
		case DOWN_PRES:
			if(page_num == 0 && line_num>=2 && line_num<=6)
			{
				if(line_num == 6)	line_num = 2;
				else line_num+=2;
				break;
			}
			if(page_num == 1 && line_num>=2 && line_num<=7)
			{
				if(line_num == 7)	line_num=2;
				else line_num++;
				break;
			}
			if(page_num == 2)
			{
				if(line_num<=7 && col_num == 0)
				{
					if(line_num == 7)	line_num=2;
					else line_num++;
					break;
				}
				if(line_num<=6 && col_num == 1)
				{
					if(line_num == 6)	line_num=2;
					else line_num+=2;
					break;
				}
			}
			break;
		case LEFT_PRES:
			if(page_num == 2 && change == 0)
			{
				col_num = 0;
				break;
			}
			if(page_num == 1)
			{
				order = line_num-2;
				op = 0;
				break;
			}
			if(page_num == 2 && change == 1)
			{
				order = line_num/2;
				op = 0;
				printf("%d",order);
				break;
			}
			if(page_num == 3)
			{
				order = line_num;
				op = 0;
				break;
			}
			break;
		case RIGHT_PRES:
			if(page_num == 2 && change == 0)
			{
				col_num = 1;
				break;
			}
			if(page_num == 1)
			{
				order = line_num-2;
				op = 1;
				break;
			}
			if(page_num == 2 && change == 1)
			{
				order = line_num/2;
				printf("%d",order);
				op = 1;
				break;
			}
			break;
		case MID_PRES:
			if(page_num == 0)
			{
				if(line_num == 2) page_num = 1;
				if(line_num == 4) page_num = 2;
				if(line_num == 6) page_num = 3;
			}
			if(page_num == 2 && col_num == 1)
			{
				if(change == 0)
				{
					change = 1;
				}
				else
				{
					change = 0;
					confirm = 1;
				}
			}
			if(page_num == 2 && col_num == 0)
			{
				Mode = line_num-1;
				count = 0;
			}
			break;
		case START_PRES:
			if(page_num!=0)
				page_num = 0;
			else
			{
				Mode = 0;
				Motor = 0;
			}
			break;
		default:
			break;
	}
}

void OLED_Show(void)
{
	if(page_num == 0)
	{
		if(page_num!=page_num_last)
		{
			OLED_Clear();
			UI_0();
			line_num = 2;
			line_num_last = 0;
		}
		if(line_num!=line_num_last)
		{
			Fresh_Pointer();
			line_num_last = line_num;
		}
		if(Motor !=Motor_last)
		{
			Fresh_Motor();
			Motor_last = Motor; 
		}
	}
	//////////////////////////////////////////////////
	else if(page_num == 1)
	{
		if(page_num!=page_num_last)
		{
			OLED_Clear();
			UI_1();
			line_num = 2;
			line_num_last = 0;
		}
		if(line_num!=line_num_last)
		{
			Fresh_Pointer();
			line_num_last = line_num;
		}
		if(order != 0xff)
		{
			Fresh_PID();
			order = 0xff;
		}
	}
	///////////////////////////////////////////////////
	else if(page_num == 2)
	{
		if(page_num!=page_num_last)
		{
			OLED_Clear();
			UI_2();
			line_num = 2;
			line_num_last = 3;
			col_num = 0;
			col_num_last = 0;
		}
		if(line_num!=line_num_last)
		{
			Fresh_Pointer();
			line_num_last = line_num;
		}
		if(col_num!=col_num_last)
		{
			Fresh_Pointer();
			col_num_last = col_num;
		}
		if(order!=0xff)
		{
			Fresh_Para();
			order = 0xff;
		}
		Fresh_Pos();
	}
	///////////////////////////////////////////////////
	else
	{
		if(page_num!=page_num_last)
		{
			OLED_Clear();
			line_num = 0;
			line_num_last = 2;
			UI_3();
		}
//		if(line_num!=line_num_last)
//		{
//			Fresh_Pointer();
//			line_num_last = line_num;
//		}
	}
	if(page_num_last!=page_num) page_num_last = page_num;
}


