#ifndef   _KEY_H
#define   _KEY_H

#define   USER_KEY     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)   //读PB12管脚宏定义


void KEY_Init(void);   //按键初始化
void KEY_Scan(void);   //按键扫描

#endif

