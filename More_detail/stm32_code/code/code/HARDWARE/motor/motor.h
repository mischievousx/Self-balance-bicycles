#ifndef __MOTOR_H 
#define __MOTOR_H 
#include "sys.h" 

#define DIR    PBout(9)       //动量轮正反切换
#define EN     PBout(8)       //动量轮电机使能引脚

#define Ain1  PAout(5)
#define Ain2  PAout(6)

//#define Bin1  PBout(13)/*【4】*/
//#define Bin2  PBout(12)
//#define PWM1   TIM3->CCR2     //动量轮电机pwm

void MOTOR_1_Init(void); 
void MOTOR_2_Init(void);
void Limit(int *pwm);
void Load(int pwm); 
void Stop(float *Med_Jiaodu,float *Jiaodu);
void Forward(void);
void Backward(void);
void Forward(void);
void Stopped(void);
void Right(void);
void Left(void);
void Goright(void);
void Goleft(void);
#endif 