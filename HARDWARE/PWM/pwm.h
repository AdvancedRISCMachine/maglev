#ifndef _PWM_H
#define _PWM_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
#define TIM8_CH1_Port GPIOC
#define TIM8_CH1_Pin GPIO_Pin_6
#define TIM8_CH1_Pinsource GPIO_PinSource6
#define TIM8_CH1_AF GPIO_AF_TIM8
#define TIM8_CH1_CLK RCC_AHB1Periph_GPIOC

#define TIM8_CH1N_Port GPIOA
#define TIM8_CH1N_Pin GPIO_Pin_7
#define TIM8_CH1N_Pinsource GPIO_PinSource7
#define TIM8_CH1N_AF GPIO_AF_TIM8
#define TIM8_CH1N_CLK RCC_AHB1Periph_GPIOA

#define TIM8_CH2_Port GPIOC
#define TIM8_CH2_Pin GPIO_Pin_7
#define TIM8_CH2_Pinsource GPIO_PinSource7
#define TIM8_CH2_AF GPIO_AF_TIM8
#define TIM8_CH2_CLK RCC_AHB1Periph_GPIOC

#define TIM8_CH2N_Port GPIOB
#define TIM8_CH2N_Pin GPIO_Pin_14
#define TIM8_CH2N_Pinsource GPIO_PinSource14
#define TIM8_CH2N_AF GPIO_AF_TIM8
#define TIM8_CH2N_CLK RCC_AHB1Periph_GPIOB
void	TIM8_Init(u32 arr,u32 psc);
void	TIM8_GPIO_Init(void);
void	TIM8_PWM_OUT_Init(u32 arr,u32 psc);

#endif
