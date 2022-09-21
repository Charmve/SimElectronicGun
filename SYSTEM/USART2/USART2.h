#ifndef __USART2_H
#define __USART2_H


#include "sys.h"

extern u8 Finish_Flag;
extern u8 US2_Buf[2];


void USART2_Init(u32 bound);

#endif


