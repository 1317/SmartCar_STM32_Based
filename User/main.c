
// ADC 6通道采集实验

/**
 * @note	引脚移植修改见 bsp_adc.h 和 bsp_usart.h
 *				配置移植修改见 bsp_adc.h
 */

#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "Servo.h"
#include "motor.h"
// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// 局部变量，用于保存转换计算后的电压值 	 
float V[NOFCHANEL];        

// 软件延时
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{		
	// 配置串口
	USART_Config();
	//TIM初始化
	TIM_PWM_Init();	
	// ADC 初始化
	ADCx_Init();
	tim_motor_init();
	
	int n=0;
	int s;
	int c=1;
	double k;
	
	     motor_run(motor_1,90);//左轮正转
		  //motor_run(motor_2,100);//左轮反转
		  motor_run(motor_3,90);//右轮正转
		  //motor_run(motor_4,100);//右轮反转
	TIM_SetCompare2(TIM_SERVO,1790);
	Delay(0x4affff);
	TIM_SetCompare2(TIM_SERVO,1640);
	Delay(0x35ffff);
	
	printf("\r\n ----这是一个ADC多通道采集实验----\r\n");
	
	while (1)
	{	
    
			V[0] =(float) ADC_ConvertedValue[0]/4096*3.3;
			V[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
			V[2] =(float) ADC_ConvertedValue[2]/4096*3.3;
			V[3] =(float) ADC_ConvertedValue[3]/4096*3.3;
			V[4] =(float) ADC_ConvertedValue[4]/4096*3.3;
			//V[5] =(float) ADC_ConvertedValue[5]/4096*3.3;
		
			printf("\r\n CH0 value 右横= %f V \r\n",V[0]);
			printf("\r\n CH1 value 右直= %f V \r\n",V[1]);
			printf("\r\n CH2 value 左横= %f V \r\n",V[2]);
			printf("\r\n CH3 value 左直= %f V \r\n",V[3]);
			printf("\r\n CH4 value 中横= %f V \r\n",V[4]);
			//printf("\r\n CH5 value = %f V \r\n",V[5]);
		  
		
		  k=(V[1]-V[3])/(V[1]+V[3]);
		  printf("k=%f\r\n",k); //
		  
				  if(V[4]>2&&c%2==1)
				  {
					  
				    TIM_SetCompare2(TIM_SERVO,1783);
						V[4] =(float) ADC_ConvertedValue[4]/4096*3.3;
					  if(V[4]>=3.1)
						n=1;
					  if(V[4]<3&&n==1)
					  {
							TIM_SetCompare2(TIM_SERVO,1888);
							Delay(0x3fffee);	
							n=0;
						}	
						
					}
					
								
						
					
//						TIM_SetCompare2(TIM_SERVO,1870);
//						printf("\r\n CH4 value 中横= %f V \r\n",V[4]);
//						Delay(0xffffee);
//					}
						
			
//			if(V[4]>2&&n%2==0)
//			{
//				  while(V[4]>2)
//				  {
//					 V[4] =(float) ADC_ConvertedValue[4]/4096*3.3;
//				   TIM_SetCompare2(TIM_SERVO,1783);
//					}
//			}
		  s=cs(k);
		  printf ("s=%d\r\n",s);
		  printf("\r\n\r\n");
	    TIM_SetCompare2(TIM_SERVO,s2);//1950 1790 1630
		  motor_run(motor_1,90);//左轮正转
		  //motor_run(motor_2,100);//左轮反转
		  motor_run(motor_3,90);//右轮正转
		  //motor_run(motor_4,100);//右轮反转
			Delay(0x000fff);		 
		}	
}
/*********************************************END OF FILE**********************/

