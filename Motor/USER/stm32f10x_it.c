#include "stm32f10x.h"
#include "delay.h"
#include "stdio.h"

void EXTI15_10_IRQHandler(void)   //按键中断服务函数
{
	if(EXTI_GetITStatus(EXTI_Line12)!=RESET)   //判断是否触发进入中断
	{
		Delay_ms(10);   //按键消抖
		printf("The USER_KEY has been pressed!\r\n");   //打印输出信息
	}
	EXTI_ClearITPendingBit(EXTI_Line12);   //清除EXTI_Line12上的中断标志位
}


void TIM3_IRQHandler(void)   //TIM3中断服务函数
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)   //判断是否触发TIM3更新中断
	{
		GPIOC->ODR ^= GPIO_Pin_13;   //PC13（用户灯）电平翻转
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);   //清除TIM3更新中断标志位
	}
}

