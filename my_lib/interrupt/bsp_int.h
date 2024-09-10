#ifndef _BSP_INT_H
#define _BSP_INT_H_

#include "imx6ul.h"

/* 中断回调函数形式（定义成结构体指针的形式） */
typedef void (*system_irq_handler_t) (unsigned int giccIar, void *param);

/* 一个中断源可以对应一个中断回调结构体 */
typedef struct _sys_irp_handle
{
    system_irq_handler_t irqHandler;   /* 中断处理函数 */
    void *userParam;    /* 中断处理函数的用户参数 */
}sys_irq_handle_t;

/* 函数声明 */
void interrupt_init(void);
void system_irqtable_init(void);
void system_register_irqhandler(IRQn_Type irq, system_irq_handler_t handler, void *userParam);
void system_irqhandler(unsigned int giccIar);
void default_irqhandler(unsigned int giccIar,void *userParam);

#endif  // _BSP_INT_H_
