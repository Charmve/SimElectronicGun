#ifndef __PID_H
#define __PID_H

#include "sys.h"
#include "Menu.h"

//增量式和位置式选择
#define M1_Pos
#define M2_Pos
//#define M1_Add
//#define M2_Add

//抗饱和积分
#define SumErrorMax 300

//////////////////PID结构体声明///////////////////
typedef struct
{
	float  Kp;      			//比例常数 P
	float  Ki;        		//积分常数 I
	float  Kd;      			//微分常数 D
	float	 Current;				//当前值
	float  Target;  	  	//设定目标 
	double SumError;			//误差累计 
	float  LastError;   	//上次的误差
	float  PreviousError;	//上上次误差
}PIDTypdDef;

//外部变量
extern PIDTypdDef M1_PID;
extern PIDTypdDef M2_PID;

//函数声明
void PID_ParaInit(void);
int M1_PID_Balance(void);
int M2_PID_Balance(void);
void Set_M1_PID(float Kp,float Ki,float Kd);
void Set_M2_PID(float Kp,float Ki,float Kd);
void Set_M1_Target(float Target);
void Set_M2_Target(float Target);

#endif

