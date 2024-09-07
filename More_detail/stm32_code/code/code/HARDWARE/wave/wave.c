#include "wave.h"
#include "delay.h"

#define Trig GPIO_Pin_9
#define Echo GPIO_Pin_10

float Distance;

void Wave_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitSture;
	EXTI_InitTypeDef  EXTI_InitSture;

	//如果外部中断的话则一定使能AFIO复用功能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA,ENABLE);
	
	
	//配置IO端口
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_Out_PP;   //推挽输出模式
	GPIO_InitSture.GPIO_Pin=Trig;                //将PA9于Trig相连
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOA,&GPIO_InitSture);
	
	GPIO_InitSture.GPIO_Mode=GPIO_Mode_IPD;      //上拉输入模式
	GPIO_InitSture.GPIO_Pin=Echo;                //将PA10于Echo相连
	GPIO_InitSture.GPIO_Speed=GPIO_Speed_50MHz;  
	GPIO_Init(GPIOA,&GPIO_InitSture);
	
	//中断和10端口映射一起
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource10);
	
	//外部中断配置
	EXTI_InitSture.EXTI_Line=EXTI_Line10;
	EXTI_InitSture.EXTI_LineCmd=ENABLE;
	EXTI_InitSture.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitSture.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitSture);
	
}


//单位cm
//v = 340m/s = 34000cm/s = 34000cm/10^6us = 0.034cm/us = 3.4cm/100us
//s = vt/2 = t*3.4/2 = t* 340/200
void EXTI15_10_IRQHandler(void)
{   		
	if(EXTI_GetITStatus(EXTI_Line10)!=RESET)
	{
		TIM_SetCounter(TIM1,0);
		TIM_Cmd(TIM1,ENABLE);
		
		while(GPIO_ReadInputDataBit(GPIOA,Echo));  //等待低电平	
		TIM_Cmd(TIM1,DISABLE);
		
		Distance=(float)(TIM_GetCounter(TIM1)*340)/200;			
		EXTI_ClearITPendingBit(EXTI_Line10);
	}
}

void Wave_Strat(void)
{
	GPIO_SetBits(GPIOA,Trig);   //将Trig设置为高电平
	delay_us(20);               //持续大于10us触发，触发超声波模块工作
	GPIO_ResetBits(GPIOA,Trig); 	
}

