#ifndef __CAN1_H
#define __CAN1_H
#include "stm32f10x.h"

void CAN1_Init(void);
void CAN2_Init(void);
extern unsigned char can1_tx_success_flag;

#endif
