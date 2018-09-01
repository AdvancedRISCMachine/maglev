#include "pid.h"
#include "adc.h"
#include "arm_math.h"
////////////
extern float ADC_ValueLocal[2]; 
float U1,U2,duty1,duty2;
float U1_want=2.36,U2_want=1.76;//min POWER U1_want=2.15,U2_want=1.55
float pid_error1,pid_error2;
arm_pid_instance_f32 PID;
////////////////////////////////////
float Kp=110,Ki=0,Kd=0;
float pid_sum=0;
float error_last=0;
int EN_P=1,EN_I=1,EN_D=1;

float pid_1(float pid_error)//Î»ÖÃĞÍ£¬error=ideal-real;
{
	float output,pid_dev;
	pid_sum+=pid_error;
//	if(Ki*pid_sum>50) pid_sum=50/Ki;
//		else if(Ki*pid_sum<-50) pid_sum=-50/Ki;
	pid_dev=pid_error-error_last;
	output=Kp*EN_P*pid_error+Ki*EN_I*pid_sum+Kd*EN_D*pid_dev;
	if(output>100) output=100;
	else if(output<-100) output=-100;
	return output;
}

//TIM6 for PID
void TIM6_Init(u32 arr,u32 psc)//tim6
{	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);

  TIM_TimeBaseStructure.TIM_Period = arr-1;   
  TIM_TimeBaseStructure.TIM_Prescaler =psc-1;
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM6,ENABLE);
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
//	
//	  PID.Kp = 0;        /* Proporcional */
//    PID.Ki = 0;        /* Integral */
//    PID.Kd = 0.5;        /* Derivative */
//     
//	arm_pid_init_f32(&PID, 1);
   
}

void TIM6_DAC_IRQHandler(void)
{
	//ADC_VAL_AVG();//
	ADC_VAL();
	U1=ADC_ValueLocal[0];
	U2=ADC_ValueLocal[1]; 
	
	pid_error1 =U1_want - U1;
	pid_error2 =U2_want - U2;
	
	//duty1 = arm_pid_f32(&PID, pid_error1);
	duty1 = 0.01*pid_1(pid_error1);
	duty1 = (duty1+1)/2;
//	if (duty1 > 1) 
//	{duty1 = 1;} 
//	else if (duty1 < 0) 
//	{duty1 = 0;}
	
	//duty2 = arm_pid_f32(&PID, pid_error2);
	duty2 = 0.01*pid_1(pid_error2);
	duty2 = (duty2+1)/2;
//	if (duty2 > 1) 
//	{duty2 = 1;} 
//	else if (duty2 < 0)
//	{duty2 = 0;}

	TIM_SetCompare1(TIM8,duty1*500);	
	TIM_SetCompare2(TIM8,duty2*500);
	
  TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
}

///////////
 void NVIC_Configuration(void)
{
		NVIC_InitTypeDef NVIC_InitStructure;
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);		
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn; 	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);	
	
}
