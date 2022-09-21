#ifndef __ButtonArray_H
#define __ButtonArray_H

#include "sys.h"

#define Row1 PCout(0)
#define Row2 PCout(2)
#define Row3 PCout(4)
#define Row4 PCout(6)

#define Col1 PCout(1)
#define Col2 PCout(3)
#define Col3 PCout(5)
#define Col4 PCout(7)

#define Row_In()  {GPIOC->CRL&=0XF0F0F0F0;GPIOC->CRL|=0x08080808;}
#define Row_Out() {GPIOC->CRL&=0XF0F0F0F0;GPIOC->CRL|=0x03030303;}

#define Col_In()	{GPIOC->CRL&=0X0F0F0F0F;GPIOC->CRL|=0x80808080;}
#define Col_Out() {GPIOC->CRL&=0X0F0F0F0F;GPIOC->CRL|=0x30303030;}

void ButtonArray_Init(void);
u8 ButtonArray_KeyPress(void);

#endif

