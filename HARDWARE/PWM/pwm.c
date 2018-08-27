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

  /* �ۼ� TIM_Period�������һ�����»����ж�*/		
  //����ʱ����0������1023����Ϊ1024�Σ�Ϊһ����ʱ����
	//����ʱ����0������8400-1����Ϊ8400�Σ�Ϊһ����ʱ����ARR
  TIM_TimeBaseStructure.TIM_Period = arr;// �߼����ƶ�ʱ��ʱ��ԴTIM8CLK =168MHz
	
  TIM_TimeBaseStructure.TIM_Prescaler =psc;	// �趨��ʱ��Ƶ��Ϊ=TIMxCLK/(TIM_Prescaler+1)=100000Hz
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
	
  /*PWMģʽ����*/
	//����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse=arr*0.5; //CCR
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
  //ʹ��ͨ��1
  TIM_OC1Init(TIM8, &TIM_OCInitStructure);	
  //ʹ��ͨ��2
  TIM_OC2Init(TIM8, &TIM_OCInitStructure);	 
	/* ʹ��ͨ��1���� */
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
		
	/* �Զ����ʹ�ܣ���·������ʱ����������� */
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
  TIM_BDTRInitStructure.TIM_DeadTime =15;
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
  TIM_BDTRConfig(TIM8, &TIM_BDTRInitStructure);
	
	// ʹ�ܶ�ʱ��
	TIM_ITConfig(TIM8,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM8, ENABLE);	
	
	/* �������ʹ�� */
  TIM_CtrlPWMOutputs(TIM8, ENABLE);
	
}
