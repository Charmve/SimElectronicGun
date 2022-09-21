#include "PID.h"

//PID变量声明
PIDTypdDef M1_PID;
PIDTypdDef M2_PID;

//PID参数初始化
void PID_ParaInit(void)
{
	M1_PID.Kp							= 0;		//比例常数 P
 	M1_PID.Ki							= 0;		//积分常数 I
 	M1_PID.Kd							= 0;		//微分常数 D
	M1_PID.Current				= 0;		//当前位置
 	M1_PID.Target					= 0;  	//设定目标 
	M1_PID.SumError				= 0;   	//误差累计
	M1_PID.LastError			= 0;		//上次的误差
	M1_PID.PreviousError	= 0;		//上上次误差
	
	M2_PID.Kp							= 0;		//比例常数 P
	M2_PID.Ki							= 0;		//积分常数 I
 	M2_PID.Kd							= 0;		//微分常数 D
	M2_PID.Current				= 0;		//当前位置
	M2_PID.Target					= 0;   	//设定目标 
	M2_PID.SumError				= 0;   	//误差累计
	M2_PID.LastError			= 0;		//上次的误差
	M2_PID.PreviousError	= 0;		//上上次误差
}

///////////////////////位置式PID///////////////////////////
//pwm=Kp*e(k)+Ki*∑e(k)+Kd[e(k)-e(k-1)]
#ifdef M1_Pos
//M1位置式PID计算	
int M1_PID_Balance(void)
{
	static float iError,dError;
	iError = M1_PID.Target - M1_PID.Current;				//偏差
	if(Motor == 1)
		M1_PID.SumError += iError;										//积分
	else
		M1_PID.SumError = 0;													//如果电机停止运动则清空误差和
	if(M1_PID.SumError > SumErrorMax)								//积分限幅
		M1_PID.SumError = SumErrorMax;
	else if(M1_PID.SumError < -SumErrorMax)
		M1_PID.SumError = -SumErrorMax;
	dError = iError - M1_PID.LastError;							//当前微分
	M1_PID.LastError = iError;
	
	return(int)(  M1_PID.Kp * iError								//比例项
          		+ M1_PID.Ki * M1_PID.SumError 			//积分项
          		+ M1_PID.Kd * dError);           		//微分项
}
#endif

#ifdef M2_Pos
//M2位置式PID计算	
int M2_PID_Balance(void)
{
	static float iError,dError;
	iError = M2_PID.Target - M2_PID.Current;				//偏差
	if(Motor == 1)
		M2_PID.SumError += iError;										//积分
	else
		M2_PID.SumError = 0;													//如果电机停止运动则清空误差和
	if(M2_PID.SumError > SumErrorMax)								//积分限幅
		M2_PID.SumError = SumErrorMax;
	else if(M2_PID.SumError < -SumErrorMax)
		M2_PID.SumError = -SumErrorMax;	
	dError = iError - M2_PID.LastError;							//当前微分
	M2_PID.LastError = iError;
	
	return(int)(  M2_PID.Kp * iError								//比例项
          		+ M2_PID.Ki * M2_PID.SumError 			//积分项
          		+ M2_PID.Kd * dError);           		//微分项
}
#endif


///////////////////////增量式PID/////////////////////////
//pwm+=Kp[e(k)-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]

#ifdef M1_Add
int M1_PID_Balance(void)
{
	static float pError,iError,dError;
	iError = M1_PID.Target - M1_PID.Current;										//偏差
	pError = iError - M1_PID.LastError;
	dError = iError - 2*M1_PID.LastError + M1_PID.PreviousError;
	M1_PID.PreviousError = M1_PID.LastError;										//保存误差
	M1_PID.LastError = iError;
	return(int)(  M1_PID.Kp * pError														//比例项
          		+ M1_PID.Ki * iError 														//积分项
          		+ M1_PID.Kd * dError);           								//微分项
}
#endif

#ifdef M2_Add
int M2_PID_Balance(void)
{
	static float pError,iError,dError;
	iError = M2_PID.Target - M2_PID.Current;										//偏差
	pError = iError - M2_PID.LastError;
	dError = iError - 2*M2_PID.LastError + M2_PID.PreviousError;
	M2_PID.PreviousError = M2_PID.LastError;										//保存误差
	M2_PID.LastError = iError;
	return(int)(  M2_PID.Kp * pError														//比例项
          		+ M2_PID.Ki * iError 														//积分项
          		+ M2_PID.Kd * dError);           								//微分项
}
#endif

void Set_M1_PID(float Kp,float Ki,float Kd)
{
	M1_PID.Kp = Kp;
	M1_PID.Ki = Ki;
	M1_PID.Kd = Kd;
}

void Set_M1_Target(float Target)
{
	M1_PID.Target = Target;
}

void Set_M2_Target(float Target)
{
	M2_PID.Target = Target;
}

void Set_M2_PID(float Kp,float Ki,float Kd)
{
	M2_PID.Kp = Kp;
	M2_PID.Ki = Ki;
	M2_PID.Kd = Kd;
}


