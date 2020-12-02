/*-----------------------------------------------------------------------------------------------------
��д��718����ʵ����
ƽ̨��STM32F103ZET6
���ܣ����PWM���Ƶ��
-------------------------------------------------------------------------------------------------------*/
#include "motor.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

/**
  * @brief	��ʼ���߼���ʱ��TIM1
  *	@param	��
  *	@retval ��
  */
void tim_motor_init()
{
	/*-------=------����Ƚ�ͨ��1��2��3��4��GPIO��ʼ��-------------*/
	GPIO_InitTypeDef GPIO_InitStructure;														//����GPIO��ʼ���ṹ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);						//ʹ����ӳ��IOʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 
																| GPIO_Pin_13 | GPIO_Pin_14;			//����GPIO�ܽ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;									//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;								//�������Ƶ��
	GPIO_Init(GPIOE, &GPIO_InitStructure);													//��ʼ��GPIO
	
	/*----------------------ʱ���ṹ���ʼ��-----------------------*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;									//������ʱ��ʱ���ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	 					//ʹ����ӳ�䶨ʱ��ʱ��

	/* �������ڣ���������Ϊ0.0005s����ʾ��Tout= ((arr+1)*(psc+1))/Tclk */
	TIM_TimeBaseStructure.TIM_Period = 500-1;												//��ʱ������arr�����Զ���װ�ؼĴ�����ֵ
																																	//�ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Prescaler = 71;	 											//��ʱ��Ԥ��Ƶ������psc��ʱ��Դ����Ԥ��Ƶ�����Ƕ�ʱ��ʱ��
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;					//ʱ�ӷ�Ƶ���ӣ��������������������ʱ����Ҫ�õ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;			//����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;								//�����ظ���������ֵΪ0���������ظ�����
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);  								//��ʼ����ʱ��

	/*--------------------����ȽϽṹ���ʼ��---------------------*/
	TIM_OCInitTypeDef TIM_OCInitStructure;	 												//������ʱ������ȽϽṹ��
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  							//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  	//ʹ������Ƚ�
	TIM_OCInitStructure.TIM_Pulse = 0;   														//���ó�ʼռ�ձ�
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  			//�������:TIM����Ƚϼ��Ը�(�ߵ�ƽ��Ч)
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  											//��ʼ������Ƚ�ͨ��1
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);  											//��ʼ������Ƚ�ͨ��2
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);  											//��ʼ������Ƚ�ͨ��3
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  											//��ʼ������Ƚ�ͨ��4
	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  							//ʹ��ͨ��1��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  							//ʹ��ͨ��2��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  							//ʹ��ͨ��3��CCR3�ϵ�Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  							//ʹ��ͨ��4��CCR4�ϵ�Ԥװ�ؼĴ���
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);						//ʹ��AFIO����ʱ��
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);								//������ӳ��
	
	TIM_Cmd(TIM1, ENABLE);   																				//ʹ��TIM
	TIM_ARRPreloadConfig(TIM1, ENABLE); 														//ʹ��TIM1��ARR�ϵ�Ԥװ�ؼĴ���
	TIM_CtrlPWMOutputs(TIM1, ENABLE);   														//�����ʹ�ܣ���ʹ�õ���ͨ�ö�ʱ��������Ҫ�����ʹ��
}

/**
  * @brief	�������
  *	@param	motor_num:��������motor_1/motor_2/motor_3/motor_4��ѡ����Ƶ��1/2/3/4
  *	@param	speed_set:PWM�ߵ�ƽ��ʱ�䡣���������ٶ��趨ֵ�����Ƶ��ת��.��Χ0-500
  *	@retval ��
  */
void motor_run(int motor_num,int speed_set)
{
	switch(motor_num)
	{
		case motor_1:
			TIM_SetCompare1(TIM1,speed_set);
			break;
		case motor_2:
			TIM_SetCompare2(TIM1,speed_set);
			break;
		case motor_3:
			TIM_SetCompare3(TIM1,speed_set);
			break;
		case motor_4:
			TIM_SetCompare4(TIM1,speed_set);
			break;
		default:
			break;
	}
}
