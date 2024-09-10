#include "bsp_int.h"

/* 中断嵌套计数器 */
static unsigned int irqNesting;

/* 中断服务函数表(直接从官方sdk库函数中取出中断向量数量) */
static sys_irq_handle_t irqTable[NUMBER_OF_INT_VECTORS];

/**
 * @brief 中断初始化函数
 * @param None
 * @return None
 */
void interrupt_init(void)
{
    GIC_Init();  // 初始化GIC(中断控制器)
    system_irqtable_init();  // 初始化中断向量表
    __set_VBAR((uint32_t)0x87800000);  // 中断向量表偏移
}

/**
 * @brief 初始化中断服务函数表
 * @param None
 * @return None
 */
void system_irqtable_init(void)
{
    unsigned int i = 0;
    irqNesting = 0;

    /* 首先要把所有中断服务函数设置为默认值（第二个参数相当于把一个死循环函数的指针设置成默认中断服务函数） */
    for(i = 0;i < NUMBER_OF_INT_VECTORS; i++)
    {
        system_register_irqhandler((IRQn_Type)i,default_irqhandler,NULL);
    }
}

/**
 * @brief 给指定的中断号注册中断服务函数
 * @param irq 中断号
 * @param handler 中断服务函数
 * @param userParam 用户参数
 * @return None
 */
void system_register_irqhandler(IRQn_Type irq, system_irq_handler_t handler, void *userParam)
{
    irqTable[irq].irqHandler = handler;
    irqTable[irq].userParam = userParam;
}

/**
 * @brief C语言中断服务函数，所有irq汇编中断都会调用这个函数，通过中断号查找对应回调函数处理
 * @param giccIar 中断号
 * @return None
 */
void system_irqhandler(unsigned int giccIar)
{
    uint32_t intNum = giccIar & 0x3FFUL;  // 获取中断号

    /* 检查中断号是否在系统适用范围内 */
    if((intNum == 1020) || (intNum >= NUMBER_OF_INT_VECTORS))
    {
        return;  // 非法中断
    }

    irqNesting++;  // 嵌套计数器加一

    /* 根据中断号在中断函数向量表中调用对应的中断服务函数 */
    irqTable[intNum].irqHandler(intNum, irqTable[intNum].userParam);

    irqNesting--;  // 中断回调函数执行完成，嵌套计数器减一
}

/**
 * @brief 默认中断服务函数
 * @param giccIar 中断号
 * @param userParam 用户参数
 * @return None
 */
void default_irqhandler(unsigned int giccIar, void *userParam)
{
    while(1)
    {
        // 死循环
    }
}