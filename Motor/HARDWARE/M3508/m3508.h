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

typedef struct ARM_VELOCITY_PLANNING //����������ٶȹ滮
{
	float Pstart;        //��ʼλ��
	float Pend;          //����λ��
	float Vstart;        //��ʼ���ٶ�           // ��λ��RPM ����ֵ
	float Vmax;          //�����ٶ�
	float Vend;          //ĩβ���ٶ�
	float Rac;           //����·�̵ı���
	float Rde;           //����·�̵ı���
}ARM_VELOCITY_PLANNING;
extern struct M3508_REAL_INFO M3508_CHASSIS_MOTOR_REAL_INFO[6];   // 1-3�ֱ��Ӧ˳ʱ�뷽��ĵ��̵����4Ϊ̧��������5Ϊ��ת����
extern struct M3508_REAL_INFO M2006_CHASSIS_MOTOR_REAL_INFO[4];		//4��M2006���

extern struct PID M3508_CHASSIS_MOTOR_PID_RPM[8];    			 // ����M3508���
extern struct PID M2006_CHASSIS_MOTOR_PID_RPM[4];    			 // ����M2006������ٶȻ���
extern struct PID M2006_CHASSIS_MOTOR_PID_POSITION[4];     // ����M2006���(λ�û�)
extern struct PID M3508_CHASSIS_MOTOR_PID_POSITION[4];     // ����M2006���(λ�û�)

void M3508_Motor_Init(void);
void m3508_update_m3508_info_can1(CanRxMsg *msg);
void m3508_update_m3508_info_can2(CanRxMsg *msg);
void chassis_m3508_send_motor_currents_can1(void);
void chassis_m3508_m2006_send_motor_currents_can1(void);
void chassis_m3508_send_motor_currents_can2(void);
void chassis_m3508_m2006_send_motor_currents_can2(void);
void M3508AngleIntegral(M3508_REAL_INFO *M3508_MOTOR);
void M2006AngleIntegral(M3508_REAL_INFO *M3508_MOTOR);
void M3508AngleIntegral_special_up(M3508_REAL_INFO *M3508_MOTOR);
void M3508AngleIntegral_special_turn(M3508_REAL_INFO *M3508_MOTOR);
void M3508AngleIntegral_special_claw(M3508_REAL_INFO *M3508_MOTOR);
void M3508AngleIntegral_special_CLAW(M3508_REAL_INFO *M3508_MOTOR);
void M2006AngleIntegral_special_left_turn(M3508_REAL_INFO *M3508_MOTOR);
void M2006AngleIntegral_special_right_turn(M3508_REAL_INFO *M3508_MOTOR);
void M2006AngleIntegral_special_left_push(M3508_REAL_INFO *M3508_MOTOR);
void M2006AngleIntegral_special_right_push(M3508_REAL_INFO *M3508_MOTOR);
/***********���¾�Ϊ���ε����������Ҫ��ֲ�Ķ���********************/
void ad_plan_arm_motor_RPM(	ARM_VELOCITY_PLANNING motion, float pos ,int16_t *TURN_MOTOR_TARGET_RPM);
void ad_plan_robot_motor_RPM_W(float start_pos,float end_pos,float real_pos,float real_speed,int Target_speed,char label)	;
void ad_plan_robot_motor_RPM(float start_pos,float end_pos,float real_pos,int real_speed,int Target_speed,char label)	;


extern struct ARM_VELOCITY_PLANNING *CLAW_NOW_MOTION;	// ָ��צ�ӿ��ϻ����ĵ�ǰ������ָ�� 
extern struct ARM_VELOCITY_PLANNING *UP_NOW_MOTION;	// ָ��̧�������ĵ�ǰ������ָ�� 
extern struct ARM_VELOCITY_PLANNING *TURN_NOW_MOTION;	// ָ��ת�����ĵ�ǰ������ָ�� 

extern struct ARM_VELOCITY_PLANNING CLAW_MOTION,			 CLAW_MOTION_CLOSE,		CLAW_MOTION_INIT,			CLAW_MOTION_OPEN;

extern struct ARM_VELOCITY_PLANNING UP_MOTION,       UP_MOTION1,        UP_MOTION2,       UP_MOTION3,       UP_MOTION4,        UP_MOTION5,
																		UP_MOTION_INIT,	 UP_ASSIST;	


extern struct ARM_VELOCITY_PLANNING STOP_ACTION;

extern float vx_t;
extern float vy_t;
extern float vw_t;

extern float vx_last;
extern float vy_last;
extern int vw_last;
	
extern float start_pos_x;
extern float end_pos_x;
extern float real_vx;
extern float vx;				
extern float vx_in_t;
extern float real_angle_x;

extern float start_pos_y;
extern float end_pos_y;
extern float real_vy;
extern float vy;				
extern float vy_in_t;
extern float real_angle_y;

extern float start_pos_w;
extern float end_pos_w;
extern float real_vw;
extern int vw;				
extern float vw_in_t;
extern float real_angle_w;

#endif




