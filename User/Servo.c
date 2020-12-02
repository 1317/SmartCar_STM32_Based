#include "Servo.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

/**
  * @brief	�߼���ʱ����ʼ��
  *	@param	��
  *	@retval ��
  */
void TIM_PWM_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;	//GPIO��ʼ���ṹ��
	//����Ƚ�ͨ��1��2��3 GPIO��ʼ��
	RCC_APB2PeriphClockCmd(RCC_APBPeriph_TIMx_GPIOx, ENABLE);	//ʹ����������ʱ��
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_2;	//����GPIO�ܽ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�������Ƶ��
	GPIO_Init(TIM_GPIO, &GPIO_InitStructure);	//��ʼ��GPIO
	
	
	TIM_OCInitTypeDef TIM_OCInitStructure;	 //��ʱ������ȽϽṹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	//��ʱ��ʱ���ṹ��
	
	RCC_APB1PeriphClockCmd(RCC_APBPeriph_TIMx, ENABLE);	 //ʹ�ܶ�ʱ��ʱ��
	
	/*--------------------ʱ���ṹ���ʼ��-------------------------*/
	// �������ڣ���������Ϊ0.02s
	TIM_TimeBaseStructure.TIM_Period = 20000-1;	//�Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Prescaler= 71;	 //����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		//ʱ�ӷ�Ƶ���� ���������������������ʱ����Ҫ�õ�
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		//����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	//�����ظ���������ֵΪ0���������ظ�����
	TIM_TimeBaseInit(TIM_SERVO, &TIM_TimeBaseStructure);  //��ʼ����ʱ��

	/*--------------------����ȽϽṹ���ʼ��-------------------*/	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //ʹ������Ƚ�
	TIM_OCInitStructure.TIM_Pulse = 0;  //���ó�ʼռ�ձ�
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //�������:TIM����Ƚϼ��Ը�(�ߵ�ƽ��Ч)
	
	TIM_OC1Init(TIM_SERVO, &TIM_OCInitStructure);  //��ʼ������Ƚ�ͨ��1
	TIM_OC1PreloadConfig(TIM_SERVO, TIM_OCPreload_Enable);  //ʹ��ͨ��1��CCR4�ϵ�Ԥװ�ؼĴ���
	
	TIM_OC2Init(TIM_SERVO, &TIM_OCInitStructure);  //��ʼ������Ƚ�ͨ��2
	TIM_OC2PreloadConfig(TIM_SERVO, TIM_OCPreload_Enable);  //ʹ��ͨ��2��CCR4�ϵ�Ԥװ�ؼĴ���
	
	TIM_OC3Init(TIM_SERVO, &TIM_OCInitStructure);  //��ʼ������Ƚ�ͨ��3
	TIM_OC3PreloadConfig(TIM_SERVO, TIM_OCPreload_Enable);  //ʹ��ͨ��3��CCR4�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM_SERVO, ENABLE);  //ʹ��TIM
	TIM_CtrlPWMOutputs(TIM_SERVO, ENABLE);  //�����ʹ�ܣ���ʹ�õ���ͨ�ö�ʱ��������Ҫ�����ʹ��
}

/**
  * ������ƺ���
	* ���ʹ����ʾ�������ֵ��ռ�ձȡ�PWMƵ�ʡ������Ƿ�Χ��Ӧ��ռ�ձ�
  */
void Servo_open(void)
{
//TIM_SetCompare1(TIM_SERVO,1775);
	TIM_SetCompare2(TIM_SERVO,1775);
//	TIM_SetCompare3(TIM_SERVO,2000);
}
void Servo_close(void)
{
//	TIM_SetCompare1(TIM_SERVO,1900);
	TIM_SetCompare2(TIM_SERVO,1900);
//	TIM_SetCompare3(TIM_SERVO,1000);
}
