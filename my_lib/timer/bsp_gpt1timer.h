#ifndef _BSP_GPT1TIMER_H
#define _BSP_GPT1TIMER_H
#include "imx6ul.h"

void gpt1_init(uint32_t frac, uint32_t value);
void gpt1_start(void);
void gpt1_stop(void);
void gpt1_restart(uint32_t value);

#endif
