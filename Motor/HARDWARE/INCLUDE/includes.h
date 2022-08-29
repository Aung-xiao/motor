#ifndef _INCLUDES_H
#define _INCLUDES_H

/*****************************************************************
               �����������������ͷ�ļ�
*****************************************************************/

//FreeRTOSϵͳ��Ҫ��ͷ�ļ�
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


//C++��Ҫ��ͷ�ļ�
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include "math.h"

/* ������Ӳ��bspͷ�ļ� */
#include "can.h"
#include "m3508.h"
#include "pid.h"



/*****************************************************************
               ���������������еĺ궨��
****************************************************************/
#define PI 								 3.14159265358979f
#define COS45              0.70710678f
#define SIN45              0.70710678f
#define ABS(x)      ((x)>0? (x):(-(x)))
#define MIN(x,y)    ((x)<(y)? (x):(y) )


// debug��������
#define USE_DATASCOPE			0
#define USE_DEBUG					0
#define USE_PATH					1


// M3508������
#define M3508_CHASSIS_MOTOR_ID_1      0x201
#define M3508_CHASSIS_MOTOR_ID_2      0x202
#define M3508_CHASSIS_MOTOR_ID_3      0x203
#define M3508_CHASSIS_MOTOR_ID_4      0x204
#define M3508_CHASSIS_MOTOR_ID_5	    0x205
#define M3508_CHASSIS_MOTOR_ID_7			0x207


#define CAN2_M2006_MOTOR_ID_1      		0x201
#define CAN2_M2006_MOTOR_ID_2      		0x202


// AK80������
#define AK80_MOTOR_ID       0x00

// ��צ���
#define CLAW_OPEN		0x00
#define CLAW_CLOSE	0x01

// Chassis Config
#define WHEEL_R            0.076f	                  //���Ӱ뾶(��λ��m) 
#define Robot_R            0.456f                  	//���ֵ����ľ���(��λ��m)
#define M3508_RM_To_MS     (PI*WHEEL_R)/570.0f      //ת�����ٶȵ�ת�� (��λ��m/s) 
#define M3508_MS_To_RM     570.0f/(PI*WHEEL_R)      //�ٶ���ת�ٵ�ת�� (��λ��m/s)  
#define MS_TO_RPM          21*60/(PI*WHEEL_R*2)     //����ֱ��152mm��������ٱ�1:21������һȦpi*152mm
#define RM_transition_MS (PI * WHEEL_R) / 570.0f //ת�����ٶȵ�ת��
#define MS_transition_RM 570.0f / (PI * WHEEL_R) //�ٶ���ת�ٵ�ת��
																										// ���㹫ʽ��1/��pi*����ֱ����*���ٱ�*60

#endif
