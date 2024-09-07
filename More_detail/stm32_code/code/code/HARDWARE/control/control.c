#include "control.h" 
#include <math.h>

float Pitch,Roll,Yaw;						        //�Ƕ�
short aacx,aacy,aacz;		                        //�Ǽ��ٶ�
short gyrox,gyroy,gyroz;	                        //���ٶ�

int Vertical_out,Velocity_out;                      //ֱ����&�ٶȻ����������
int PWM1;                                           //�������
int Encoder_Motor;	                                //����������������������ݣ��ٶȣ�

static int filter_angle =0.0;
float alpha = 0.95;
float Med_Angle=-3.6;	                                //��е��ֵ---�������޸���Ļ�е��ֵ���ɡ�
float Vertical_Kp=-30,Vertical_Kd=0;                  //ֱ����KP��KD


void EXTI9_5_IRQHandler(void)                       //MPU6050�ⲿ�жϷ�������10ms����һ��
{
	if(EXTI_GetITStatus(EXTI_Line5)!=0)                 //һ���ж�
	{
		if(PBin(5)==0)                                  //�����ж�
		{           
			EXTI_ClearITPendingBit(EXTI_Line5);         //����жϱ�־λ
            
			Encoder_Motor=Read_Encoder_TIM4();          //1.�ɼ�����������&MPU6050�Ƕ���Ϣ��
			
			mpu_dmp_get_data(&Pitch,&Roll,&Yaw);			//�Ƕ�
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�����ǽ��ٶ�
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�Ǽ��ٶ�

			int temp1 = Pitch;
			filter_angle= temp1*alpha + filter_angle *(1-alpha);
			Vertical_out=Vertical(Med_Angle,filter_angle,gyroy);//ֱ����

			//�ѿ�����������ص�����ϣ�������յĵĿ��ơ�
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
ֱ����PD������
*********************/
int Vertical(float Med,float Angle,float gyro_y)
{
	int PWM_out1;
	PWM_out1=Vertical_Kp*(Med-Angle)-Vertical_Kd*(gyro_y);
	return PWM_out1;
}