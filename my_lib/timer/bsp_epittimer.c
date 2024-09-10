#include "bsp_epittimer.h"
#include "bsp_int.h"
#include "bsp_gpio.h"

void epit1_init(uint32_t frac, uint32_t value)
{
    // 限制最大分频值
    if(frac > 0XFFF)
        frac = 0xFFF;
    EPIT1->CR = 0;// 先清零
    /* 
      * CR寄存器: 
       * bit25:24 01 时钟源选择Peripheral clock=66MHz 
       * bit15:4  frac 分频值 
       * bit3: 1  当计数器到0的话从LR重新加载数值 
       * bit2: 1  比较中断使能 
       * bit1:    1  初始计数值来源于LR寄存器值 
       * bit0:    0  先关闭EPIT1 
    */ 
   EPIT1->CR = (1 << 24 | frac << 4 | 1 << 3 | 1 << 2 | 1 << 1);
   EPIT1->LR = value; // 重装载值
   EPIT1->CMPR = 0; // 比较寄存器值

   /* 使能GIC中对应的中断 */
   GIC_EnableIRQ(EPIT1_IRQn);
   system_register_irqhandler(EPIT1_IRQn,(system_irq_handler_t)epit1_irqhandler,NULL);
   EPIT1->CR |= 1 << 0; // 使能EPIT1
}

void epit1_irqhandler(void)
{
    static uint8_t state = 0;
    state = !state;
    // 如果比较中断发生了
    if(EPIT1->SR & (1 << 0)) 
    {
        // 反转led状态
        gpio_pin_write(GPIO1, 3, (uint32_t)!state);
    }
    EPIT1->SR |= 1<<0; // 清除中断标志位
}