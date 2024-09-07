#include "sys.h"
                                          
int main(void)
{  
  NVIC_Config();                         //配置中断优先级
  delay_init();               
  Beep_Init();                           //初始化蜂鸣器
  uart3_init(9600);                      //初始化串口3（蓝牙）
  OLED_Init();			               			 //初始化OLED
  OLED_Clear();                          //OLED清屏
  adc_Init();                            //初始化ADC
  MOTOR_2_Init();                        //初始化运动电机驱动（正反转）引脚
  PWM_Init_TIM3(7199,0);                 //定时器3初始化PWN_10KHz，用于驱动运动电机
  PWM_Init_TIM2(9999, 143);              //定时器2初始化PWN_50Hz，用于驱动舵机
  TIM_SetCompare1(TIM2, 790);            //舵机复位
  Encoder_Init_TIM4(65535,0);
  OLED_ShowString(25,4,"MPU6050...",16);
  MPU_Init();                            //MPU6050初始化
  while(mpu_dmp_init())
  {
    OLED_ShowString(25,4,"MPU6050 Error",16);
  }
    OLED_ShowString(25,4,"MPU6050 OK!",16); 
  Beep=1;
  delay_ms(400);
  Beep=0;
  MPU6050_EXTI_Init();                   //MPU6050外部中断初始化
  OLED_Clear();
	//Forward();													//电机向前移动
  OLED_ShowString(0,0,"Pitch:         C",16);
  OLED_ShowString(0,3,"Speed:         R",16);
  OLED_ShowString(0,6,"Power:         V",16);
  
  while(1)
  {	        
      //ADC值范围为从0-2^12=4095（111111111111）一般情况下对应电压为0-3.3V
      AdcValue=11.09*(3.3*Get_adc_Average(ADC_Channel_4,10)/0x0fff); 
      
      OLED_Showdecimal(55,0,Pitch,9,16);                 //显示姿态角度Roll
      OLED_Showdecimal(55,3,Encoder_Motor*0.25,9,16);   //运动电机转速
      OLED_Showdecimal(50,6,AdcValue,9,16);             //显示当前电压值
  }
}
