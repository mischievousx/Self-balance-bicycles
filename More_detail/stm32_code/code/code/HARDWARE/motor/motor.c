#include "motor.h"
static int turn=790;
int PWM_MAX=6500,PWM_MIN=-6500;	                   //PWM限幅变量

//初始化动量轮电机驱动（启动、正反转）引脚
void MOTOR_1_Init(void)                              
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //使能GPIOB的时钟

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;         //推挽输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;     //PB8 PB9
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}

//初始化运动电机驱动（正反转）引脚
void MOTOR_2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //使能GPIOB的时钟

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;         //推挽输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;     //PA5 PA6
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}



/*限幅函数*/
void Limit(int *pwm)
{
	if(*pwm>PWM_MAX)*pwm=PWM_MAX;
	if(*pwm<PWM_MIN)*pwm=PWM_MIN;
}

/*赋值函数*/
/*入口参数：PID运算完成后的最终PWM值*/
void Load(int pwm)
{
	//1.研究正负号，对应正反转
	if(pwm>0)   EN=1,DIR=1;//正转
	else        EN=1,DIR=0;//反转
	//2.研究PWM值
	TIM_SetCompare2(TIM3,abs(pwm));
}

void Stop(float *Med_Jiaodu,float *Jiaodu)
{   
    if(*Jiaodu>5)Led1=1,Led2=0;
    if(*Jiaodu<(-10))Led1=0,Led2=1;
	if(abs(*Jiaodu-*Med_Jiaodu)>12)
    {
        EN=0;
        Beep=1;
    }
    else Beep=0;
}

/*运动电机控制函数*/
void Forward(void)
{
    Ain1=0,Ain2=1;//前进
    TIM_SetCompare3(TIM3,1000);//速度
}


void Backward(void)
{
    Ain1=1,Ain2=0;
    TIM_SetCompare3(TIM3,3500);
}

void Stopped(void)
{
    Ain1=0,Ain2=0;
}


void Right(void)
{
    turn+=25;
    if(turn>1000)turn=1000;
    TIM_SetCompare1(TIM2, turn);
}

void Left(void)
{
    turn-=25;
    if(turn<580)turn=580;
    TIM_SetCompare1(TIM2, turn);
}

void Goright(void)
{
    turn+=25;
    if(turn>1000)turn=1000;
    TIM_SetCompare1(TIM2, turn);
    Forward();
}

void Goleft(void)
{
    turn-=25;
	if(turn<580)turn=580;
    TIM_SetCompare1(TIM2, turn);
    Forward();
}


