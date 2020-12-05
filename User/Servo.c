#include "Servo.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

/**
  * @brief	高级定时器初始化
  *	@param	无
  *	@retval 无
  */
void TIM_PWM_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;	//GPIO初始化结构体
	//输出比较通道1、2、3 GPIO初始化
	RCC_APB2PeriphClockCmd(RCC_APBPeriph_TIMx_GPIOx, ENABLE);	//使能外设总线时钟
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_2;	//设置GPIO管脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//设置输出频率
	GPIO_Init(TIM_GPIO, &GPIO_InitStructure);	//初始化GPIO
	
	
	TIM_OCInitTypeDef TIM_OCInitStructure;	 //定时器输出比较结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	//定时器时基结构体
	
	RCC_APB1PeriphClockCmd(RCC_APBPeriph_TIMx, ENABLE);	 //使能定时器时钟
	
	/*--------------------时基结构体初始化-------------------------*/
	// 配置周期，这里配置为0.02s
	TIM_TimeBaseStructure.TIM_Period = 20000-1;	//自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Prescaler= 71;	 //驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		//时钟分频因子 ，输出互补脉冲配置死区时间需要用到
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		//计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	//设置重复计数器的值为0，不设置重复计数
	TIM_TimeBaseInit(TIM_SERVO, &TIM_TimeBaseStructure);  //初始化定时器

	/*--------------------输出比较结构体初始化-------------------*/	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //选择定时器模式:TIM脉冲宽度调制模式1
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //使能输出比较
	TIM_OCInitStructure.TIM_Pulse = 0;  //设置初始占空比
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //输出极性:TIM输出比较极性高(高电平有效)
	
	TIM_OC1Init(TIM_SERVO, &TIM_OCInitStructure);  //初始化输出比较通道1
	TIM_OC1PreloadConfig(TIM_SERVO, TIM_OCPreload_Enable);  //使能通道1的CCR4上的预装载寄存器
	
	TIM_OC2Init(TIM_SERVO, &TIM_OCInitStructure);  //初始化输出比较通道2
	TIM_OC2PreloadConfig(TIM_SERVO, TIM_OCPreload_Enable);  //使能通道2的CCR4上的预装载寄存器
	
	TIM_OC3Init(TIM_SERVO, &TIM_OCInitStructure);  //初始化输出比较通道3
	TIM_OC3PreloadConfig(TIM_SERVO, TIM_OCPreload_Enable);  //使能通道3的CCR4上的预装载寄存器
	
	TIM_Cmd(TIM_SERVO, ENABLE);  //使能TIM
	TIM_CtrlPWMOutputs(TIM_SERVO, ENABLE);  //主输出使能，当使用的是通用定时器，不需要主输出使能
}

/**
  * 舵机控制函数
	* 舵机使用提示：舵机中值的占空比、PWM频率、舵机打角范围对应的占空比
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
