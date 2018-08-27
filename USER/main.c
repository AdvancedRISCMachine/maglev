#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "adc.h"
#include "pid.h"

extern float ADC_ValueLocal[2],duty1,duty2,U1_want,U2_want; 
int main(void)
{  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	NVIC_Configuration();
	delay_init(168);  //初始化延时函数
	uart_init(115200);//初始化串口波特率为115200
	Rheostat_Init();	//ADC初始化
	TIM6_Init(100-1,84-1);//PID 10K Hz//(1000-1,84-1)
	TIM8_Init(500-1,168-1);//2kHz (500-1,168-1)//168M/168=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/500=2Khz.     
	
  TIM_SetCompare1(TIM8,1*500);	
	TIM_SetCompare2(TIM8,1*500);	//修改比较值，修改占空比
	
	while(1) 
	{
 		delay_ms(100);	 
//		ADC_ValueLocal[0] =(float)((uint16_t)ADC_ConvertedValue[0]*3.3/4096); 
//    ADC_ValueLocal[1] =(float)((uint16_t)ADC_ConvertedValue[1]*3.3/4096);    
//    
//    printf("\r\n The current AD value = 0x%08X \r\n", ADC_ConvertedValue[0]); 
//    printf("\r\n The current AD value = 0x%08X \r\n", ADC_ConvertedValue[1]);     
//    
		//ADC_VAL();
	//	printf("\r\nduty1:	%f\r\nU1:	%f\r\nU1WANT:	%f",duty1,ADC_ValueLocal[0],U1_want); 
  printf("\r\n%f				%f",ADC_ValueLocal[0],duty1); 
    //printf("\r\n The current ADC1 value = %f V ",ADC_ConvertedValueLocal[0]); 
    //printf("\r\n The current ADC2 value = %f V ",ADC_ConvertedValueLocal[1]);    
 
	}
}
