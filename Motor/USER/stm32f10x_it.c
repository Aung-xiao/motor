#include "stm32f10x.h"
#include "delay.h"
#include "stdio.h"

void EXTI15_10_IRQHandler(void)   //�����жϷ�����
{
	if(EXTI_GetITStatus(EXTI_Line12)!=RESET)   //�ж��Ƿ񴥷������ж�
	{
		Delay_ms(10);   //��������
		printf("The USER_KEY has been pressed!\r\n");   //��ӡ�����Ϣ
	}
	EXTI_ClearITPendingBit(EXTI_Line12);   //���EXTI_Line12�ϵ��жϱ�־λ
}


void TIM3_IRQHandler(void)   //TIM3�жϷ�����
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)   //�ж��Ƿ񴥷�TIM3�����ж�
	{
		GPIOC->ODR ^= GPIO_Pin_13;   //PC13���û��ƣ���ƽ��ת
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);   //���TIM3�����жϱ�־λ
	}
}

