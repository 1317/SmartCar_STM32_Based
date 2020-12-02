#ifndef _SERVO_H_
#define _SERVO_H_

#define	RCC_APBPeriph_TIMx_GPIOx	RCC_APB2Periph_GPIOA
#define	RCC_APBPeriph_TIMx	RCC_APB1Periph_TIM2
#define	TIM_GPIO	GPIOA
#define TIM_SERVO	TIM2

extern void TIM_PWM_Init(void);

extern void Servo_open(void);
extern void Servo_close(void);

#endif
