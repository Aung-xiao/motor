#ifndef __M3508_H
#define __M3508_H
#include "stm32f10x.h"



// M3508���صĵ����ʵ��Ϣ
typedef struct M3508_REAL_INFO
{
	uint16_t ANGLE;   		        //�����Ƕ�						
	int16_t  RPM;								
	int16_t  CURRENT;
	int16_t  TARGET_CURRENT;
	
	// �ǶȻ���ʱ�õ��������
	float		 REAL_ANGLE;         //���������ʵ�Ƕȣ�������float��
	u8			 FIRST_ANGLE_INTEGRAL_FLAG;
	uint16_t LAST_ANGLE;
}M3508_REAL_INFO;


extern struct M3508_REAL_INFO M3508_CHASSIS_MOTOR_REAL_INFO[6];   // 1-3�ֱ��Ӧ˳ʱ�뷽��ĵ��̵����4Ϊ̧��������5Ϊ��ת����
extern struct M3508_REAL_INFO M2006_CHASSIS_MOTOR_REAL_INFO[4];		//4��M2006���

extern struct PID M3508_CHASSIS_MOTOR_PID_RPM[8];    			 // ����M3508���
extern struct PID M2006_CHASSIS_MOTOR_PID_RPM[4];    			 // ����M2006������ٶȻ���
extern struct PID M2006_CHASSIS_MOTOR_PID_POSITION[4];     // ����M2006���(λ�û�)
extern struct PID M3508_CHASSIS_MOTOR_PID_POSITION[4];     // ����M2006���(λ�û�)

void M3508_Motor_Init(void);
void m3508_update_m3508_info_can1(CanRxMsg *msg);
void chassis_m3508_send_motor_currents_can1(void);
void M3508AngleIntegral(M3508_REAL_INFO *M3508_MOTOR);



#endif




