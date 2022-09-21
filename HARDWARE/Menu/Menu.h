#ifndef __MENU_H
#define __MENU_H

#include "sys.h"
#include "key.h"
#include "oled.h"
#include "MyVariable.h"
#include "usart.h"
#include "PID.h"
#include "control.h"
extern u8 confirm;
extern u8 Motor;
extern u8 Mode;
extern u8 count;

void Fresh_Pos(void);
void GetMenuIndex(void);
void OLED_Show(void);

#endif

