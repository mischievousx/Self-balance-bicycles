#include "control.h" 
#include <math.h>

float Pitch,Roll,Yaw;						        //角度
short aacx,aacy,aacz;		                        //角加速度
short gyrox,gyroy,gyroz;	                        //角速度

int Vertical_out,Velocity_out;                      //直立环&速度环的输出变量
int PWM1;                                           //最终输出
int Encoder_Motor;	                                //动量轮驱动电机编码器数据（速度）

static int filter_angle =0.0;
float alpha = 0.95;
float Med_Angle=-3.6;	                                //机械中值---在这里修改你的机械中值即可。
float Vertical_Kp=-30,Vertical_Kd=0;                  //直立环KP、KD


void EXTI9_5_IRQHandler(void)                       //MPU6050外部中断服务函数，10ms触发一次
{
	if(EXTI_GetITStatus(EXTI_Line5)!=0)                 //一级判定
	{
		if(PBin(5)==0)                                  //二级判定
		{           
			EXTI_ClearITPendingBit(EXTI_Line5);         //清除中断标志位
            
			Encoder_Motor=Read_Encoder_TIM4();          //1.采集编码器数据&MPU6050角度信息。
			
			mpu_dmp_get_data(&Pitch,&Roll,&Yaw);			//角度
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//陀螺仪角速度
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//角加速度

			int temp1 = Pitch;
			filter_angle= temp1*alpha + filter_angle *(1-alpha);
			Vertical_out=Vertical(Med_Angle,filter_angle,gyroy);//直立环

			//把控制输出量加载到电机上，完成最终的的控制。
			PWM1 = 790 + Vertical_out;
			if(PWM1 > 1000)
			{
				PWM1 = 1000;
			};
			if(PWM1 < 580)
			{
				PWM1 = 580;
			}
			TIM_SetCompare1(TIM2, PWM1);
		}
	}
}

/*********************
直立环PD控制器
*********************/
int Vertical(float Med,float Angle,float gyro_y)
{
	int PWM_out1;
	PWM_out1=Vertical_Kp*(Med-Angle)-Vertical_Kd*(gyro_y);
	return PWM_out1;
}