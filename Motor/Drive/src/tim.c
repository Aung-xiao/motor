#include "stm32f10x.h"

//void TIM_Init(uint16_t per, uint16_t psc)
//{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;   //定义定时器结构体变量
//	NVIC_InitTypeDef NVIC_InitStruct;   //定义中断优先级结构体变量
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   //使能TIM3的时钟
//	
//	TIM_TimeBaseInitStruct.TIM_Period=per;   //设置自动重装载的周期值
//	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;   //设置预分频值
//	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;   //向上计数模式
//	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;   //设置时钟分割
//	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);   //定时器初始化函数
//	
//	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);   //TIM3中断使能
//	
//	NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;   //TIM3中断通道
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;   //抢占优先级0
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;   //子优先级1
//	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;   //使能TIM3中断通道
//	NVIC_Init(&NVIC_InitStruct);   //中断优先级初始化函数
//	
//	TIM_Cmd(TIM3,ENABLE);   //TIM3使能
//}

void TIM_Init(uint16_t per, uint16_t psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;   //定义GPIO结构体变量
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;   //定义定时器结构体变量
	TIM_OCInitTypeDef TIM_OCInitStruct;   //定义输出比较结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);   //GPIOA时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   //使能TIM3的时钟
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;   //配置GPIO第6引脚
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;   //配置GPIO为复用推挽输出
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;   //配置GPIO速率
	GPIO_Init(GPIOA,&GPIO_InitStruct);   //GPIO初始化函数
	
	TIM_TimeBaseInitStruct.TIM_Period=per;   //设置自动重装载的周期值
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc;   //设置预分频值
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;   //向上计数模式
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;   //设置时钟分割
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);   //定时器初始化函数
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;   //PWM模式1
	TIM_OCInitStruct.TIM_Pulse=0;   //初始化占空比为0
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_Low;   //输出比较极性低
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;   //比较输出使能
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);   //比较输出初始化函数
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);   //输出比较1预装载寄存器使能
	
	TIM_Cmd(TIM3,ENABLE);   //TIM3使能
}

