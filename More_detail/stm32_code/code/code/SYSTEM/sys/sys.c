#include "sys.h"

/*
  ============================================================================================================================
    NVIC_PriorityGroup   | NVIC_IRQChannelPreemptionPriority | NVIC_IRQChannelSubPriority  | Description
  ============================================================================================================================
   NVIC_PriorityGroup_0  |                0                  |            0-15             |   0 bits for pre-emption priority
                         |                                   |                             |   4 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------
   NVIC_PriorityGroup_1  |                0-1                |            0-7              |   1 bits for pre-emption priority
                         |                                   |                             |   3 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_2  |                0-3                |            0-3              |   2 bits for pre-emption priority
                         |                                   |                             |   2 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_3  |                0-7                |            0-1              |   3 bits for pre-emption priority
                         |                                   |                             |   1 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_4  |                0-15               |            0                |   4 bits for pre-emption priority
                         |                                   |                             |   0 bits for subpriority                       
  ============================================================================================================================
*/
void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruct_extiB5;
    NVIC_InitTypeDef NVIC_InitStruct_extiA10;
	NVIC_InitTypeDef NVIC_InitStruct_usart3;
    NVIC_InitTypeDef NVIC_InitStruct_tim2;
    NVIC_InitTypeDef NVIC_InitStruct_tim1;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//4级抢占,4级响应。
	
	//外部中断PB5,即陀螺仪中断
	NVIC_InitStruct_extiB5.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitStruct_extiB5.NVIC_IRQChannelCmd=ENABLE;            //中断使能
	NVIC_InitStruct_extiB5.NVIC_IRQChannelPreemptionPriority=0;  //抢占优先级为0级，值越小优先级越高，0级优先级最高
	NVIC_InitStruct_extiB5.NVIC_IRQChannelSubPriority=0;         //响应优先级为0级，值越小优先级越高，0级优先级最高
	NVIC_Init(&NVIC_InitStruct_extiB5);
	
    //USART3 
    NVIC_InitStruct_usart3.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStruct_usart3.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级1
	NVIC_InitStruct_usart3.NVIC_IRQChannelSubPriority = 0;		//子优先级0
	NVIC_InitStruct_usart3.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStruct_usart3);	                        
    
    //定时器2中断
//    NVIC_InitStruct_tim2.NVIC_IRQChannel=TIM2_IRQn;            
//	NVIC_InitStruct_tim2.NVIC_IRQChannelCmd=ENABLE;            
//	NVIC_InitStruct_tim2.NVIC_IRQChannelPreemptionPriority=1;  
//	NVIC_InitStruct_tim2.NVIC_IRQChannelSubPriority=1;        
//	NVIC_Init(&NVIC_InitStruct_tim2); 
    
    //外部中断PA10
//	NVIC_InitStruct_extiA10.NVIC_IRQChannel=EXTI15_10_IRQn;
//	NVIC_InitStruct_extiA10.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_InitStruct_extiA10.NVIC_IRQChannelPreemptionPriority=2;
//	NVIC_InitStruct_extiA10.NVIC_IRQChannelSubPriority=1;
//	NVIC_Init(&NVIC_InitStruct_extiA10);
    
}