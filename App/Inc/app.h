#ifndef APP_H
#define APP_H

#include <stdint.h>
#include "stm32h7xx_hal.h"


// 外部函数声明
void App_Init(void);
void App_Run(void);
void App_Jump(uint32_t entry);

#endif // APP_H