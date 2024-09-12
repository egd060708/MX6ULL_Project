#ifndef _BSP_EPITTIMER_H
#define _BSP_EPITTIMER_H

#include "imx6ul.h"

void epit1_init(uint32_t frac, uint32_t value, void (*irqhandler));
void epit1_start(void);
void epit1_stop(void);
void epit1_restart(uint32_t value);

void epit1_led_irqhandler(void);
void epit1_key_irqhandler(void);


#endif