
// ADC 6ͨ���ɼ�ʵ��

/**
 * @note	������ֲ�޸ļ� bsp_adc.h �� bsp_usart.h
 *				������ֲ�޸ļ� bsp_adc.h
 */

#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "Servo.h"
#include "motor.h"
// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float V[NOFCHANEL];        

// �����ʱ
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{		
	// ���ô���
	USART_Config();
	//TIM��ʼ��
	TIM_PWM_Init();	
	// ADC ��ʼ��
	ADCx_Init();
	tim_motor_init();
	
	int n=0;
	int s;
	int c=1;
	double k;
	
	     motor_run(motor_1,90);//������ת
		  //motor_run(motor_2,100);//���ַ�ת
		  motor_run(motor_3,90);//������ת
		  //motor_run(motor_4,100);//���ַ�ת
	TIM_SetCompare2(TIM_SERVO,1790);
	Delay(0x4affff);
	TIM_SetCompare2(TIM_SERVO,1640);
	Delay(0x35ffff);
	
	printf("\r\n ----����һ��ADC��ͨ���ɼ�ʵ��----\r\n");
	
	while (1)
	{	
    
			V[0] =(float) ADC_ConvertedValue[0]/4096*3.3;
			V[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
			V[2] =(float) ADC_ConvertedValue[2]/4096*3.3;
			V[3] =(float) ADC_ConvertedValue[3]/4096*3.3;
			V[4] =(float) ADC_ConvertedValue[4]/4096*3.3;
			//V[5] =(float) ADC_ConvertedValue[5]/4096*3.3;
		
			printf("\r\n CH0 value �Һ�= %f V \r\n",V[0]);
			printf("\r\n CH1 value ��ֱ= %f V \r\n",V[1]);
			printf("\r\n CH2 value ���= %f V \r\n",V[2]);
			printf("\r\n CH3 value ��ֱ= %f V \r\n",V[3]);
			printf("\r\n CH4 value �к�= %f V \r\n",V[4]);
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
//						printf("\r\n CH4 value �к�= %f V \r\n",V[4]);
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
		  motor_run(motor_1,90);//������ת
		  //motor_run(motor_2,100);//���ַ�ת
		  motor_run(motor_3,90);//������ת
		  //motor_run(motor_4,100);//���ַ�ת
			Delay(0x000fff);		 
		}	
}
/*********************************************END OF FILE**********************/

