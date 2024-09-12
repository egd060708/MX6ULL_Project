#include "bsp_gpt1timer.h"

/**
 * @brief 初始化gpt1定时器
 * @param frac 分频值
 * @param value 重装载值
 * @return None
 */
void gpt1_init(uint32_t frac, uint32_t value)
{
    GPT1->CR = 0;
    GPT1->CR = 1 << 15;//进入软复位
    while((GPT1->CR >> 15) & 0x01);//等待复位完成
    /* GPT的CR寄存器设置，通用设置 */
    // bit 22:20 000 输出比较1的输出功能关闭，对应的引脚没反应
    // bit 9 0 restart模式，当CNT等于OCR1的时候产生中断
    // bit 8:6 001 GPT时钟源选择ipg_clk=66Mhz
    GPT1->CR = (1<<6);

    /* GPT的PR寄存器设置，分频设置 */
    GPT1->PR = frac;

    /* GPT的OCR1寄存器，1Mhz设置比较值为最大 */
    GPT1->OCR[0] = value;

}

/**
 * @brief gpt1定时器使能
 * @return None
 */
void gpt1_start(void)
{
    GPT1->CR |= 1<<0;
}

/**
 * @brief gpt1定时器关闭
 * @return None
 */
void gpt1_stop(void)
{
    GPT1->CR &= ~(1 << 0);
}

/**
 * @brief gpt1定时器重启
 * @param value 重装载值
 * @return None
 */
void gpt1_restart(uint32_t value)
{
    GPT1->CR &= ~(1 << 0); // 首先关闭定时器
    GPT1->OCR[0] = value;      // 重置重装载值
    GPT1->CR |= (1 << 0);  // 重新打开计数器
}