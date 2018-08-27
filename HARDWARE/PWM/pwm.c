#include "pwm.h"
#include "led.h"
#include "usart.h"

/////////////////
void TIM8_Init(u32 arr,u32 psc)
{
	TIM8_GPIO_Init();
	TIM8_PWM_OUT_Init(arr,psc);
}

void TIM8_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd (TIM8_CH1_CLK|TIM8_CH1N_CLK|TIM8_CH2_CLK|TIM8_CH2N_CLK, ENABLE); 
	
	GPIO_PinAFConfig(TIM8_CH1_Port,TIM8_CH1_Pinsource,TIM8_CH1_AF);
	GPIO_PinAFConfig(TIM8_CH1N_Port,TIM8_CH1N_Pinsource,TIM8_CH1N_AF);
	GPIO_PinAFConfig(TIM8_CH2_Port,TIM8_CH2_Pinsource,TIM8_CH2_AF);
	GPIO_PinAFConfig(TIM8_CH2N_Port,TIM8_CH2N_Pinsource,TIM8_CH2N_AF);
	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin = TIM8_CH1_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 	
	GPIO_Init(TIM8_CH1_Port, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = TIM8_CH1N_Pin;	
	GPIO_Init(TIM8_CH1N_Port, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = TIM8_CH2_Pin;
	GPIO_Init(TIM8_CH2_Port, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = TIM8_CH2N_Pin;
	GPIO_Init(TIM8_CH2N_Port, &GPIO_InitStructure);
}
void TIM8_PWM_OUT_Init(u32 arr,u32 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); 

  /* 累计 TIM_Period个后产生一个更新或者中断*/		
  //当定时器从0计数到1023，即为1024次，为一个定时周期
	//当定时器从0计数到8400-1，即为8400次，为一个定时周期ARR
  TIM_TimeBaseStructure.TIM_Period = arr;// 高级控制定时器时钟源TIM8CLK =168MHz
	
  TIM_TimeBaseStructure.TIM_Prescaler =psc;	// 设定定时器频率为=TIMxCLK/(TIM_Prescaler+1)=100000Hz
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
	
  /*PWM模式配置*/
	//配置为PWM模式1
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse=arr*0.5; //CCR
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
  //使能通道1
  TIM_OC1Init(TIM8, &TIM_OCInitStructure);	
  //使能通道2
  TIM_OC2Init(TIM8, &TIM_OCInitStructure);	 
	/* 使能通道1重载 */
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
		
	/* 自动输出使能，断路、死区时间和锁定配置 */
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
  TIM_BDTRInitStructure.TIM_DeadTime =15;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
  TIM_BDTRConfig(TIM8, &TIM_BDTRInitStructure);
	
	// 使能定时器
	TIM_ITConfig(TIM8,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM8, ENABLE);	
	
	/* 主动输出使能 */
  TIM_CtrlPWMOutputs(TIM8, ENABLE);
	
}
