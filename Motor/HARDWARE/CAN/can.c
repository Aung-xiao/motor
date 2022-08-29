#include "includes.h"
// CAN1初始化 用于M3508
// PA11 -> CANRX
// PA12 -> CANTX
void CAN1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	CAN_InitTypeDef CAN_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能 PORTA 时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//使能 CAN1 时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化 IO
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化 IO
	//CAN 单元设置
	CAN_InitStructure.CAN_TTCM=DISABLE; //非时间触发通信模式
	CAN_InitStructure.CAN_ABOM=DISABLE; //软件自动离线管理
	CAN_InitStructure.CAN_AWUM=DISABLE; //睡眠模式通过软件唤醒
	CAN_InitStructure.CAN_NART=ENABLE; //禁止报文自动传送
	CAN_InitStructure.CAN_RFLM=DISABLE; //报文不锁定,新的覆盖旧的
	CAN_InitStructure.CAN_TXFP=DISABLE; //优先级由报文标识符决定
	CAN_InitStructure.CAN_Mode= 1; //模式设置：0,普通模式;1,回环模式;
	//设置波特率
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq; //重新同步跳跃宽度(Tsjw)
	CAN_InitStructure.CAN_BS1=CAN_BS2_4tq; //时间段 1 占用时间单位
	CAN_InitStructure.CAN_BS2=CAN_BS1_7tq; // 时间段 2 占用时间单位
	CAN_InitStructure.CAN_Prescaler=3; //分频系数(Fdiv)为 brp+1
	CAN_Init(CAN1, &CAN_InitStructure); // 初始化 CAN1 
	CAN_FilterInitStructure.CAN_FilterNumber=0; //过滤器 0
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //32 位
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000; //32 位 ID
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000; //32 位 MASK
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;// FIFO0
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //激活过滤器 0
	CAN_FilterInit(&CAN_FilterInitStructure); //滤波器初始化

	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE); //FIFO0 消息挂号中断允许.
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 主优先级为 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // 次优先级为 0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 主优先级为 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // 次优先级为 1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


// CAN1的发送中断函数
void USB_HP_CAN1_TX_IRQHandler(void)
{
    if(CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET) 
		{
	   CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
     
    }
}

/*WAITING_TEST*/
// CAN1的FIFO0接受中断函数
void USB_LP_CAN1_RX0_IRQHandler(void)
{
  CanRxMsg CAN1_RX0_message;  // 临时存放接受数据的结构体
	
  if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET) 
  {
		CAN_Receive(CAN1, CAN_FIFO0, &CAN1_RX0_message);  // 读取数据
		m3508_update_m3508_info_can1(&CAN1_RX0_message);  // M3508电机数据处理
		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
  }
}


