#include "includes.h"

/*********************
 velocity �����˵��ٶ� 
 speed    �����rpm 
 RPM      ���ת��rpm
 *********************/

M3508_REAL_INFO M3508_CHASSIS_MOTOR_REAL_INFO[6] = {0}; 
M3508_REAL_INFO M2006_CHASSIS_MOTOR_REAL_INFO[4] = {0}; 

PID M3508_CHASSIS_MOTOR_PID_RPM[8];	// 6��M3508���
PID M2006_CHASSIS_MOTOR_PID_RPM[4];	// 4��M2006���
PID M2006_CHASSIS_MOTOR_PID_POSITION[4];	// 4��M2006���
PID M3508_CHASSIS_MOTOR_PID_POSITION[4];	// 4��M2006���
// M3508��ʼ��
void M3508_Motor_Init(void)
{
	// ���ֵ��̵���ٶȻ�PID��ʼ��
	PID_parameter_init(&M3508_CHASSIS_MOTOR_PID_RPM[0], 10.0, 1.0, 0.0, 16384, 16384, -1);
	PID_parameter_init(&M3508_CHASSIS_MOTOR_PID_RPM[1], 10.0, 1.0, 0.0, 16384, 16384, -1);
	PID_parameter_init(&M3508_CHASSIS_MOTOR_PID_RPM[2], 10.0, 1.0, 0.0, 16384, 16384, -1);	
	// ̧����������ٶȻ�PID��ʼ��
	PID_parameter_init(&M3508_CHASSIS_MOTOR_PID_RPM[3], 10.0, 1.0, 0.0, 16384, 16384, -1);	
	// צ�ӷ�ת����ٶȻ�PID��ʼ��
	PID_parameter_init(&M3508_CHASSIS_MOTOR_PID_RPM[4] , 10.0, 1.0, 0.0, 16384, 16384, -1);
	PID_parameter_init(&M3508_CHASSIS_MOTOR_PID_RPM[5] , 10.0, 1.0, 0.0, 16384, 16384, -1);	
	
	// M2006����ٶȻ�PID��ʼ��
	PID_parameter_init(&M2006_CHASSIS_MOTOR_PID_RPM[0], 10.0, 1.0, 0.0, 2000, 2000, -1);	
	PID_parameter_init(&M2006_CHASSIS_MOTOR_PID_RPM[1], 10.0, 1.0, 0.0, 2000, 2000, -1);	
	PID_parameter_init(&M2006_CHASSIS_MOTOR_PID_RPM[2], 10.0, 1.0, 0.0, 2000, 2000, -1);	
	PID_parameter_init(&M2006_CHASSIS_MOTOR_PID_RPM[3], 10.0, 1.0, 0.0, 2000, 2000, -1);	

	PID_parameter_init(&M3508_CHASSIS_MOTOR_PID_RPM[6], 10.0, 1.0, 0.0, 10000, 10000, -1);	
	PID_parameter_init(&M3508_CHASSIS_MOTOR_PID_RPM[7], 10.0, 1.0, 0.0, 10000, 10000, -1);		

	
		// M2006���λ�û�PID��ʼ��
	PID_parameter_init(&M2006_CHASSIS_MOTOR_PID_POSITION[0], 50.0, 0.0, 0.0, 16384, 16384, -1);	
	PID_parameter_init(&M2006_CHASSIS_MOTOR_PID_POSITION[1], 50.0, 0.0, 0.0, 16384, 16384, -1);	
	PID_parameter_init(&M2006_CHASSIS_MOTOR_PID_POSITION[2], 2.3, 0.0, 0.0, 16384, 16384, -1);	
	PID_parameter_init(&M2006_CHASSIS_MOTOR_PID_POSITION[3], 2.3, 0.0, 0.0, 16384, 16384, -1);	
	
	PID_parameter_init(&M3508_CHASSIS_MOTOR_PID_POSITION[0], 50.0, 0.0, 0.0, 16384, 16384, -1);	
	PID_parameter_init(&M3508_CHASSIS_MOTOR_PID_POSITION[1], 50.0, 0.0, 0.0, 16384, 16384, -1);	
}

 

// ���õ��ͨ��CAN���������ݸ���m3508��״̬��Ϣ
// ����Ƶ�ʣ�1kHz
void m3508_update_m3508_info_can1(CanRxMsg *msg)
{

	switch(msg -> StdId)  // ����׼ID
	{
    case M3508_CHASSIS_MOTOR_ID_1://A����
		{ 
			M3508_CHASSIS_MOTOR_REAL_INFO[0].ANGLE   = (msg -> Data[0] << 8) | msg -> Data[1];  // ת�ӻ�е�Ƕ�
			M3508_CHASSIS_MOTOR_REAL_INFO[0].RPM     = (msg -> Data[2] << 8) | msg -> Data[3];  // ʵ��ת��ת��
			M3508_CHASSIS_MOTOR_REAL_INFO[0].CURRENT = (msg -> Data[4] << 8) | msg -> Data[5];  // ʵ��ת�ص���
			M3508AngleIntegral(&M3508_CHASSIS_MOTOR_REAL_INFO[0]);
		}; break;
		
		case M3508_CHASSIS_MOTOR_ID_2://B����
		{ 
			M3508_CHASSIS_MOTOR_REAL_INFO[1].ANGLE   = (msg -> Data[0] << 8) | msg -> Data[1];  // ת�ӻ�е�Ƕ�
			M3508_CHASSIS_MOTOR_REAL_INFO[1].RPM     = (msg -> Data[2] << 8) | msg -> Data[3];  // ʵ��ת��ת��
			M3508_CHASSIS_MOTOR_REAL_INFO[1].CURRENT = (msg -> Data[4] << 8) | msg -> Data[5];  // ʵ��ת�ص���
			M3508AngleIntegral(&M3508_CHASSIS_MOTOR_REAL_INFO[1]);
		}; break;
		
		case M3508_CHASSIS_MOTOR_ID_3://C����
		{ 
			M3508_CHASSIS_MOTOR_REAL_INFO[2].ANGLE   = (msg -> Data[0] << 8) | msg -> Data[1];  // ת�ӻ�е�Ƕ�
			M3508_CHASSIS_MOTOR_REAL_INFO[2].RPM     = (msg -> Data[2] << 8) | msg -> Data[3];  // ʵ��ת��ת��
			M3508_CHASSIS_MOTOR_REAL_INFO[2].CURRENT = (msg -> Data[4] << 8) | msg -> Data[5];  // ʵ��ת�ص���
			M3508AngleIntegral(&M3508_CHASSIS_MOTOR_REAL_INFO[2]);
		}; break;	
		
		case M3508_CHASSIS_MOTOR_ID_4://̧������
		{ 
			M3508_CHASSIS_MOTOR_REAL_INFO[3].ANGLE   = (msg -> Data[0] << 8) | msg -> Data[1];  // ת�ӻ�е�Ƕ�
			M3508_CHASSIS_MOTOR_REAL_INFO[3].RPM     = (msg -> Data[2] << 8) | msg -> Data[3];  // ʵ��ת��ת��
			M3508_CHASSIS_MOTOR_REAL_INFO[3].CURRENT = (msg -> Data[4] << 8) | msg -> Data[5];  // ʵ��ת�ص���
		  M3508AngleIntegral_special_up(&M3508_CHASSIS_MOTOR_REAL_INFO[3]);
//		M3508AngleIntegral(&M3508_CHASSIS_MOTOR_REAL_INFO[3]);
		}; break;
		
		case M3508_CHASSIS_MOTOR_ID_5://D����
		{ 
			M3508_CHASSIS_MOTOR_REAL_INFO[4].ANGLE   = (msg -> Data[0] << 8) | msg -> Data[1];  // ת�ӻ�е�Ƕ�
			M3508_CHASSIS_MOTOR_REAL_INFO[4].RPM     = (msg -> Data[2] << 8) | msg -> Data[3];  // ʵ��ת��ת��
			M3508_CHASSIS_MOTOR_REAL_INFO[4].CURRENT = (msg -> Data[4] << 8) | msg -> Data[5];  // ʵ��ת�ص���
			M3508AngleIntegral(&M3508_CHASSIS_MOTOR_REAL_INFO[4]);					
		}; break;

					
		case M3508_CHASSIS_MOTOR_ID_7://3508��ȡ����
		{ 
			M3508_CHASSIS_MOTOR_REAL_INFO[5].ANGLE   = (msg -> Data[0] << 8) | msg -> Data[1];  // ת�ӻ�е�Ƕ�
			M3508_CHASSIS_MOTOR_REAL_INFO[5].RPM     = (msg -> Data[2] << 8) | msg -> Data[3];  // ʵ��ת��ת��
			M3508_CHASSIS_MOTOR_REAL_INFO[5].CURRENT = (msg -> Data[4] << 8) | msg -> Data[5];  // ʵ��ת�ص���		
//			M3508AngleIntegral(&M3508_CHASSIS_MOTOR_REAL_INFO[5]);	
			M3508AngleIntegral_special_CLAW(&M3508_CHASSIS_MOTOR_REAL_INFO[5]);			
		}; break;

		
		case M2006_CHASSIS_MOTOR_ID_0://2006������ұߣ�
		{ 
			M2006_CHASSIS_MOTOR_REAL_INFO[0].ANGLE= (msg -> Data[0] << 8) | msg -> Data[1];  // ת�ӻ�е�Ƕ�
			M2006_CHASSIS_MOTOR_REAL_INFO[0].RPM     = (msg -> Data[2] << 8) | msg -> Data[3];  // ʵ��ת��ת��
			M2006_CHASSIS_MOTOR_REAL_INFO[0].CURRENT = (msg -> Data[4] << 8) | msg -> Data[5];  // ʵ��ת�ص���
			M2006AngleIntegral_special_left_turn(&M2006_CHASSIS_MOTOR_REAL_INFO[0]);			//??????????????Ϊɶ�����õ�����ͨ��ʼ������������
		}; break;

		case M2006_CHASSIS_MOTOR_ID_1://2006�������ߣ�
		{ 
			M2006_CHASSIS_MOTOR_REAL_INFO[1].ANGLE= (msg -> Data[0] << 8) | msg -> Data[1];  // ת�ӻ�е�Ƕ�
			M2006_CHASSIS_MOTOR_REAL_INFO[1].RPM     = (msg -> Data[2] << 8) | msg -> Data[3];  // ʵ��ת��ת��
			M2006_CHASSIS_MOTOR_REAL_INFO[1].CURRENT = (msg -> Data[4] << 8) | msg -> Data[5];  // ʵ��ת�ص���
			M2006AngleIntegral_special_right_turn(&M2006_CHASSIS_MOTOR_REAL_INFO[1]);			
		}; break;
		
		default: break;
	}
}



void chassis_m3508_send_motor_currents_can1(void)
{
	CanTxMsg tx_message_1;

	// ���ÿ��ƶ�
	tx_message_1.IDE = CAN_Id_Standard;
	tx_message_1.RTR = CAN_RTR_Data;
	tx_message_1.DLC = 0x08;
	
	// �����ٲöκ����ݶ�	
	tx_message_1.StdId = 0x200;  // ����IDΪ 1 2 3 4 �ĵ��
	tx_message_1.Data[0] = (uint8_t)(M3508_CHASSIS_MOTOR_REAL_INFO[0].TARGET_CURRENT >> 8);
	tx_message_1.Data[1] = (uint8_t) M3508_CHASSIS_MOTOR_REAL_INFO[0].TARGET_CURRENT;
	tx_message_1.Data[2] = (uint8_t)(M3508_CHASSIS_MOTOR_REAL_INFO[1].TARGET_CURRENT >> 8);
	tx_message_1.Data[3] = (uint8_t) M3508_CHASSIS_MOTOR_REAL_INFO[1].TARGET_CURRENT;
	tx_message_1.Data[4] = (uint8_t)(M3508_CHASSIS_MOTOR_REAL_INFO[2].TARGET_CURRENT >> 8);
	tx_message_1.Data[5] = (uint8_t) M3508_CHASSIS_MOTOR_REAL_INFO[2].TARGET_CURRENT;
	tx_message_1.Data[6] = (uint8_t)(M3508_CHASSIS_MOTOR_REAL_INFO[3].TARGET_CURRENT >> 8);
	tx_message_1.Data[7] = (uint8_t) M3508_CHASSIS_MOTOR_REAL_INFO[3].TARGET_CURRENT;

	CAN_Transmit(CAN1, &tx_message_1);
}



void chassis_m3508_m2006_send_motor_currents_can1(void)
{
	CanTxMsg tx_message_2;
	
	// ���ÿ��ƶ�
	tx_message_2.IDE = CAN_Id_Standard;
	tx_message_2.RTR = CAN_RTR_Data;
	tx_message_2.DLC = 0x08;
	
	// �����ٲöκ����ݶ�
	tx_message_2.StdId = 0x1FF;  // ����IDΪ 5 6 7 8 �ĵ��(������3508����2006)
	tx_message_2.Data[0] = (uint8_t)(M3508_CHASSIS_MOTOR_REAL_INFO[4].TARGET_CURRENT >> 8);
	tx_message_2.Data[1] = (uint8_t) M3508_CHASSIS_MOTOR_REAL_INFO[4].TARGET_CURRENT;	      //ID 5 
  tx_message_2.Data[2] = (uint8_t)( M2006_CHASSIS_MOTOR_REAL_INFO[0].TARGET_CURRENT >> 8 ) ;
  tx_message_2.Data[3] = (uint8_t) M2006_CHASSIS_MOTOR_REAL_INFO[0].TARGET_CURRENT; //ID 6
	tx_message_2.Data[4] = (uint8_t)(M3508_CHASSIS_MOTOR_REAL_INFO[5].TARGET_CURRENT >> 8);
	tx_message_2.Data[5] = (uint8_t) M3508_CHASSIS_MOTOR_REAL_INFO[5].TARGET_CURRENT;	      //ID 7 
  tx_message_2.Data[6] = (uint8_t)( M2006_CHASSIS_MOTOR_REAL_INFO[1].TARGET_CURRENT >> 8 ) ;
  tx_message_2.Data[7] = (uint8_t) M2006_CHASSIS_MOTOR_REAL_INFO[1].TARGET_CURRENT; //ID 8
	
	CAN_Transmit(CAN1, &tx_message_2);
}



// ���õ��ͨ��CAN���������ݸ���m3508��״̬��Ϣ
// ����Ƶ�ʣ�1kHz
void m3508_update_m3508_info_can2(CanRxMsg *msg)
{

	switch(msg -> StdId)  // ����׼ID
	{
		case CAN2_M2006_MOTOR_ID_1://2006���һ
		{ 
			M2006_CHASSIS_MOTOR_REAL_INFO[2].ANGLE= (msg -> Data[0] << 8) | msg -> Data[1];  // ת�ӻ�е�Ƕ�
			M2006_CHASSIS_MOTOR_REAL_INFO[2].RPM     = (msg -> Data[2] << 8) | msg -> Data[3];  // ʵ��ת��ת��
			M2006_CHASSIS_MOTOR_REAL_INFO[2].CURRENT = (msg -> Data[4] << 8) | msg -> Data[5];  // ʵ��ת�ص���
			M2006AngleIntegral_special_left_push(&M2006_CHASSIS_MOTOR_REAL_INFO[2]);			
		}; break;

		case CAN2_M2006_MOTOR_ID_2://2006�����
		{ 
			M2006_CHASSIS_MOTOR_REAL_INFO[3].ANGLE= (msg -> Data[0] << 8) | msg -> Data[1];  // ת�ӻ�е�Ƕ�
			M2006_CHASSIS_MOTOR_REAL_INFO[3].RPM     = (msg -> Data[2] << 8) | msg -> Data[3];  // ʵ��ת��ת��
			M2006_CHASSIS_MOTOR_REAL_INFO[3].CURRENT = (msg -> Data[4] << 8) | msg -> Data[5];  // ʵ��ת�ص���
			M2006AngleIntegral_special_right_push(&M2006_CHASSIS_MOTOR_REAL_INFO[3]);			
		}; break;
		default: break;
	}
}


void chassis_m3508_send_motor_currents_can2(void)
{
	CanTxMsg tx_message_3;

	// ���ÿ��ƶ�
	tx_message_3.IDE = CAN_Id_Standard;
	tx_message_3.RTR = CAN_RTR_Data;
	tx_message_3.DLC = 0x08;
	
	// �����ٲöκ����ݶ�	
	tx_message_3.StdId = 0x200;  // ����IDΪ 1 2 3 4 �ĵ��
	tx_message_3.Data[0] = (uint8_t)(M2006_CHASSIS_MOTOR_REAL_INFO[2].TARGET_CURRENT >> 8);
	tx_message_3.Data[1] = (uint8_t) M2006_CHASSIS_MOTOR_REAL_INFO[2].TARGET_CURRENT;
	tx_message_3.Data[2] = (uint8_t)(M2006_CHASSIS_MOTOR_REAL_INFO[3].TARGET_CURRENT >> 8);
	tx_message_3.Data[3] = (uint8_t) M2006_CHASSIS_MOTOR_REAL_INFO[3].TARGET_CURRENT;

	CAN_Transmit(CAN2, &tx_message_3);
}


// M3508����ǶȻ���
void M3508AngleIntegral(M3508_REAL_INFO *M3508_MOTOR)
{
	float delta_pos = 0;
	
	// ��¼��һ�ν���ʱ������
	if(!M3508_MOTOR->FIRST_ANGLE_INTEGRAL_FLAG)
	{
		M3508_MOTOR->LAST_ANGLE = M3508_MOTOR->ANGLE;
		M3508_MOTOR->FIRST_ANGLE_INTEGRAL_FLAG = 1;
		return;
	}
	
	// ����仯�ĽǶ�
	if(M3508_MOTOR->RPM >= 0)
	{
		if(M3508_MOTOR->ANGLE < M3508_MOTOR->LAST_ANGLE)
		{
			if(abs(8191 + M3508_MOTOR->ANGLE - M3508_MOTOR->LAST_ANGLE) < 1250)  // ��������CAN����ʱ�������ת���ǶȽ����˲�
			{
				delta_pos = ((float)(8191 + M3508_MOTOR->ANGLE - M3508_MOTOR->LAST_ANGLE) / 8191.0f) * 360.0f;
				delta_pos = delta_pos / 3591.0f * 187.0f;	//���ٱ�
			}
		}
		else
		{
			delta_pos = ((float)(M3508_MOTOR->ANGLE - M3508_MOTOR->LAST_ANGLE) / 8191.0f) * 360.0f;
			delta_pos = delta_pos / 3591.0f * 187.0f;	//���ٱ�
		}
		
		// �˲�
		if(delta_pos > 0) 
			M3508_MOTOR->REAL_ANGLE += delta_pos;  // ����	
	}
	else
	{
		if(M3508_MOTOR->ANGLE > M3508_MOTOR->LAST_ANGLE)
		{
			if(abs(8191 - M3508_MOTOR->ANGLE + M3508_MOTOR->LAST_ANGLE) < 1250)  // ��������CAN����ʱ�������ת���ǶȽ����˲�			
			{
				delta_pos = ((float)(8191 - M3508_MOTOR->ANGLE + M3508_MOTOR->LAST_ANGLE) / 8191.0f) * 360.0f;
				delta_pos = delta_pos / 3591.0f * 187.0f;	//���ٱ�
			}
		}	
		else
		{
			delta_pos = ((float)(M3508_MOTOR->ANGLE - M3508_MOTOR->LAST_ANGLE) / 8191.0f) * 360.0f;
			delta_pos = delta_pos / 3591.0f * 187.0f;	//���ٱ�
		}
		
		// �˲�
		if(delta_pos < 0) 
			M3508_MOTOR->REAL_ANGLE += delta_pos;  // ����
	}

	// �洢�Ƕ�ֵ
	M3508_MOTOR->LAST_ANGLE = M3508_MOTOR->ANGLE;
}

// M2006����ǶȻ���
void M2006AngleIntegral(M3508_REAL_INFO *M3508_MOTOR)
{
	float delta_pos = 0;
	
	// ��¼��һ�ν���ʱ������
	if(!M3508_MOTOR->FIRST_ANGLE_INTEGRAL_FLAG)
	{
		M3508_MOTOR->LAST_ANGLE = M3508_MOTOR->ANGLE;
		M3508_MOTOR->FIRST_ANGLE_INTEGRAL_FLAG = 1;
		return;
	}
	
	// ����仯�ĽǶ�
	if(M3508_MOTOR->RPM >= 0)
	{
		if(M3508_MOTOR->ANGLE < M3508_MOTOR->LAST_ANGLE)
		{
			if(abs(8191 + M3508_MOTOR->ANGLE - M3508_MOTOR->LAST_ANGLE) < 1250)  // ��������CAN����ʱ�������ת���ǶȽ����˲�
			{
				delta_pos = ((float)(8191 + M3508_MOTOR->ANGLE - M3508_MOTOR->LAST_ANGLE) / 8191.0f) * 360.0f;
				delta_pos = delta_pos / 3591.0f * 187.0f;	//���ٱ�
			}
		}
		else
		{
			delta_pos = ((float)(M3508_MOTOR->ANGLE - M3508_MOTOR->LAST_ANGLE) / 8191.0f) * 360.0f;
			delta_pos = delta_pos / 3591.0f * 187.0f;	//���ٱ�
		}
		
		// �˲�
		if(delta_pos > 0) 
			M3508_MOTOR->REAL_ANGLE += delta_pos*180.0f/334.0f;  // ����	
	}
	else
	{
		if(M3508_MOTOR->ANGLE > M3508_MOTOR->LAST_ANGLE)
		{
			if(abs(8191 - M3508_MOTOR->ANGLE + M3508_MOTOR->LAST_ANGLE) < 1250)  // ��������CAN����ʱ�������ת���ǶȽ����˲�			
			{
				delta_pos = ((float)(8191 - M3508_MOTOR->ANGLE + M3508_MOTOR->LAST_ANGLE) / 8191.0f) * 360.0f;
				delta_pos = delta_pos / 3591.0f * 187.0f;	//���ٱ�
			}
		}	
		else
		{
			delta_pos = ((float)(M3508_MOTOR->ANGLE - M3508_MOTOR->LAST_ANGLE) / 8191.0f) * 360.0f;
			delta_pos = delta_pos / 3591.0f * 187.0f;	//���ٱ�
		}
		
		// �˲�
		if(delta_pos < 0) 
			M3508_MOTOR->REAL_ANGLE += delta_pos*180.0f/334.0f;  // ����
	}

	// �洢�Ƕ�ֵ
	M3508_MOTOR->LAST_ANGLE = M3508_MOTOR->ANGLE;
}
















