#include "stm32f10x.h"
#include "key.h"
#include "delay.h"
#include "stdio.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;   //定义GPIO结构体变量
	EXTI_InitTypeDef EXTI_InitStruct;	//定义外部中断结构体变量
	NVIC_InitTypeDef NVIC_InitStruct;	//定义中断优先级结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);   //使能GPIOB的时钟并开启复用时钟
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;   //配置GPIO第12引脚
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;   //配置GPIO为上拉输入
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;   //配置GPIO速率
	GPIO_Init(GPIOB,&GPIO_InitStruct);   //GPIO初始化函数
	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12);   //PB12中断线映射
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;   //外部中断模式
	EXTI_InitStruct.EXTI_Line=EXTI_Line12;   //中断线12
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;   //下降沿触发
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;   //中断线使能
	EXTI_Init(&EXTI_InitStruct);   //外部中断初始化函数
	
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;   //配置外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;   //设置抢占优先级为0
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;   //设置子优先级为1
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;   //使能外部中断通道
	NVIC_Init(&NVIC_InitStruct);   //中断优先级初始化函数
}

void KEY_Scan(void)
{
	if(USER_KEY == 0)   //判断按键是否按下
	{
		Delay_ms(10);   //延时消抖
		if(USER_KEY == 0)   //再次判断按键是否按下
		{
			printf("The USER_KEY has been pressed!\r\n");  //向电脑端串口助手输出按下信息
		}
	}
}
