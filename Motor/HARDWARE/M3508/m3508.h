#ifndef __M3508_H
#define __M3508_H
#include "stm32f10x.h"



// M3508返回的电机真实信息
typedef struct M3508_REAL_INFO
{
	uint16_t ANGLE;   		        //采样角度						
	int16_t  RPM;								
	int16_t  CURRENT;
	int16_t  TARGET_CURRENT;
	
	// 角度积分时用到下面变量
	float		 REAL_ANGLE;         //处理过的真实角度（必须用float）
	u8			 FIRST_ANGLE_INTEGRAL_FLAG;
	uint16_t LAST_ANGLE;
}M3508_REAL_INFO;


extern struct M3508_REAL_INFO M3508_CHASSIS_MOTOR_REAL_INFO[6];   // 1-3分别对应顺时针方向的底盘电机，4为抬升机构，5为翻转机构
extern struct M3508_REAL_INFO M2006_CHASSIS_MOTOR_REAL_INFO[4];		//4个M2006电机

extern struct PID M3508_CHASSIS_MOTOR_PID_RPM[8];    			 // 驱动M3508电机
extern struct PID M2006_CHASSIS_MOTOR_PID_RPM[4];    			 // 驱动M2006电机（速度环）
extern struct PID M2006_CHASSIS_MOTOR_PID_POSITION[4];     // 驱动M2006电机(位置环)
extern struct PID M3508_CHASSIS_MOTOR_PID_POSITION[4];     // 驱动M2006电机(位置环)

void M3508_Motor_Init(void);
void m3508_update_m3508_info_can1(CanRxMsg *msg);
void chassis_m3508_send_motor_currents_can1(void);
void M3508AngleIntegral(M3508_REAL_INFO *M3508_MOTOR);



#endif




