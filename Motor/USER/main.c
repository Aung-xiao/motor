#include "led.h"
#include "delay.h"
#include "sys.h"
#include "includes.h"

float Velocity_A=10;
int main(void)
{	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	 	CAN1_Init();																		// CAN1
		M3508_Motor_Init();															// M3508µç»ú	
		while(1)
		{
			PID_incremental_PID_calculation(&M3508_CHASSIS_MOTOR_PID_RPM[0], M3508_CHASSIS_MOTOR_REAL_INFO[0].RPM ,Velocity_A);
			M3508_CHASSIS_MOTOR_REAL_INFO[0].TARGET_CURRENT = M3508_CHASSIS_MOTOR_PID_RPM[0].output;
			chassis_m3508_send_motor_currents_can1();			
		}
}

