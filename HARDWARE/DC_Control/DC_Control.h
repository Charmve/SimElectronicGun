#ifndef __DC_CONTROL_H
#define __DC_CONTROL_H

#include "sys.h"

#define Power PCout(0)
#define Shoot PCout(1)

void DC_GPIO_Init(void);

#endif

