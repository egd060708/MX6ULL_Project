#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H
#include "imx6ul.h"
/***************************************************************
Copyright © zuozhongkai Co., Ltd. 1998-2019. All rights reserved.
文件名	: 	 bsp_led.h
作者	   : 左忠凯
版本	   : V1.0
描述	   : LED驱动头文件。
其他	   : 无
论坛 	   : www.wtmembed.com
日志	   : 初版V1.0 2019/1/4 左忠凯创建
***************************************************************/

/**
 * @brief gpio输出电平结构体
 * @param kGPIO_DigitalInput 输入
 * @param kGPIO_DigitalOutput 输出
 */
typedef enum _gpio_pin_dir_e{
    kGPIO_DigitalInput = 0U,//输入
    kGPIO_DigitalOutput = 1U //输出
}gpio_pin_dir_e;

/**
 * @brief gpio中断类型配置
 * @param kGPIO_NoIntmode 无中断
 * @param kGPIO_IntLowLevel 低电平触发中断
 * @param kGPIO_IntHighLevel 高电平触发中断
 * @param kGPIO_IntRisingEdge 上升沿触发中断
 * @param kGPIO_IntFallingEdge 下降沿触发中断
 * @param kGPIO_IntRisingOrFallingEdge 上升沿或者下降沿触发中断
 */
typedef enum _gpio_interrupt_mode_e
{
    kGPIO_NoIntmode = 0U, //无中断
    kGPIO_IntLowLevel = 1U, //低电平触发中断
    kGPIO_IntHighLevel = 2U, //高电平触发中断
    kGPIO_IntRisingEdge = 3U, // 上升沿触发中断
    kGPIO_IntFallingEdge = 4U, // 下降沿触发中断
    kGPIO_IntRisingOrFallingEdge = 5U // 上升沿或者下降沿触发中断
}gpio_interrupt_mode_e;

/**
 * @param gpio_group 哪一组GPIO，对应GPIOX
 * @param pin_num GPIO端口
 * @param inputOnfield 是否使能软件输入
 * @param configValue 
 * 配置GPIO属性
 * bit 16: HYS开关
 * bit [15:14]: 上下拉
 * bit [13]: kepper功能
 * bit [12]: pull/keeper使能
 * bit [11]: 开路输出
 * bit [7:6]: IO速度
 * bit [5:3]: IO驱动能力
 * bit [0]: 转换率                 
 * @param direction GPIO 方向: 输入还是输出
 * @param outputLogic 如果是输出的话，默认输出电平
 * @param interruptMode gpio中断方式
 */
typedef struct _gpio_init_config_s{
    GPIO_Type *gpio_group;
    uint32_t pin_num;
    uint32_t inputOnfield;
    uint32_t configValue;
    gpio_pin_dir_e direction; /* GPIO 方向:输入还是输出 */
    uint8_t outputLogic; /* 如果是输出的话，默认输出电平 */
    gpio_interrupt_mode_e interruptMode;    /* gpio中断方式 */
}gpio_init_config_s;

void gpio_init(uint32_t _muxRegister,
               uint32_t _muxMode,
               uint32_t _inputRegister,
               uint32_t _inputDaisy,
               uint32_t _configRegister,
			   gpio_init_config_s* _init_config);

void gpio_pin_write(GPIO_Type* _gpio_group, uint32_t _pin, uint32_t _value);

uint32_t gpio_pin_read(GPIO_Type* _gpio_group, uint32_t _pin);

void gpio_int_config(GPIO_Type* _gpio_group, uint32_t _pin, gpio_interrupt_mode_e _interruptMode);

void gpio_enable_int(GPIO_Type* _gpio_group, uint32_t _pin);

void gpio_disable_int(GPIO_Type* _gpio_group, uint32_t _pin);

void gpio_clear_int_flags(GPIO_Type* _gpio_group, uint32_t _pin);

#endif

