#include "key.h"
#include "delay.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//����������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

//������ʼ������
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOA,GPIOEʱ��
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; //KEY0��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE4
	
	 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP��Ӧ����PA0
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA0
 
} 

//unsigned char KEY_Scan(void)
//{	 
//	unsigned char key_code;

//   if(KEY0_Scan()==1)key_code=2;
//	else if(KEY2_Scan()==1)key_code=3;
//	else key_code=0;
//	return key_code;
//}






//unsigned char KEY0_Scan(void)
//{	 
//	static char key_up0=0;//�������ɿ���־	

// 	if(KEY0==0)
//	{
//		/*��ʱȥ���� */
//	delay_ms(10);	
//	
//		if(KEY0==0)
//		{
//			key_up0=1;
//    }
//		
//	 }
//	 if(KEY0==1&&key_up0==1)
//	 {
//		key_up0=0;
//    return 1;
//    }
//		return 0;
//}



//unsigned char KEY2_Scan(void)
//{	 
//	static char key_up2=0;//�������ɿ���־	

// 	if(KEY2==1)
//	{
//		/*��ʱȥ���� */
//	delay_ms(10);	
//	
//		if(KEY2==1)
//		{
//			key_up2=1;
//    }	
//	 }
//	 if(KEY2==0&&key_up2==1)
//	 {
//		key_up2=0;
//    return 1;
//    }
//		return 0;
//}

//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��WKUP���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY0==0||WK_UP==1))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)return 1;
		else if(WK_UP==1)return 4;
	}else if(KEY0==1&&WK_UP==0)key_up=1; 	    
 	return 0;// �ް�������
}




















