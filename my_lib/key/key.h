#ifndef _KEY_H
#define _KEY_H

#include "imx6ul.h"

uint32_t key_get_value(GPIO_Type* _gpio_group, uint32_t _pin, uint32_t _dir);

void keyDelay_irqhandler(void);
void keyTimer_irqhandler(void);

#endif