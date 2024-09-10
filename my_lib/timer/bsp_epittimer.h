#ifndef _BSP_EPITTIMER_H
#define _BSP_EPITTIMER_H

#include "imx6ul.h"

void epit1_init(uint32_t frac, uint32_t value);
void epit1_irqhandler(void);

#endif