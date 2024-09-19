/**************************************************************
Copyright © zuozhongkai Co., Ltd. 1998-2019. All rights reserved.
文件名	: 	 mian.c
作者	   : 左忠凯
版本	   : V1.0
描述	   : I.MX6U开发板裸机实验5 BSP形式的LED驱动
其他	   : 本实验学习目的:
		 1、将各个不同的文件进行分类，学习如何整理工程、就
		 和学习STM32一样创建工程的各个文件夹分类，实现工程文件
		 的分类化和模块化，便于管理。
		 2、深入学习Makefile，学习Makefile的高级技巧，学习编写
		 通用Makefile。
论坛 	   : www.wtmembed.com
日志	   : 初版V1.0 2019/1/4 左忠凯创建
**************************************************************/
#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_gpio.h"
#include "bsp_int.h"
#include "key.h"
#include "bsp_epittimer.h"
#include "stdio.h"
#include "bsp_lcd.h"
#include "bsp_lcdapi.h"

unsigned int backcolor[10] = {
	LCD_BLUE, LCD_GREEN, LCD_RED, LCD_CYAN, LCD_YELLOW,
	LCD_LIGHTBLUE, LCD_DARKBLUE, LCD_WHITE, LCD_BLACK, LCD_ORANGE
};

/*
 * @description	: mian函数
 * @param 		: 无
 * @return 		: 无
 */
int main(void)
{
	unsigned char index = 0;
	unsigned char state = OFF;

	interrupt_init();// 一定最先调用中断管理器的初始化
	imx6u_clkinit();//配置时钟，全部设置到推荐频率
	clk_enable(); /* 使能所有的时钟 			*/
	// 初始化led
	gpio_init_config_s led_config = {
		.gpio_group = GPIO1,
		.pin_num = 3,
		.inputOnfield = 0,
		.configValue = 0X10B0,
		.direction = kGPIO_DigitalOutput,
		.outputLogic = 1,
		.interruptMode = kGPIO_NoIntmode};
	gpio_init(IOMUXC_GPIO1_IO03_GPIO1_IO03, &led_config);
	// 初始化按键
	gpio_init_config_s key_config = {
		.gpio_group = GPIO1,
		.pin_num = 18,
		.inputOnfield = 0,
		.configValue = 0xF080,
		.direction = kGPIO_DigitalInput,
        .outputLogic = 1,
        .interruptMode = kGPIO_IntFallingEdge
	};
	gpio_init(IOMUXC_UART1_CTS_B_GPIO1_IO18, &key_config);
	// 初始化蜂鸣器
	gpio_init_config_s beep_config = {
		.gpio_group = GPIO5,
		.pin_num = 1,
		.inputOnfield = 0,
		.configValue = 0X10B0,
		.direction = kGPIO_DigitalOutput,
		.outputLogic = 1,
		.interruptMode = kGPIO_NoIntmode};
	gpio_init(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, &beep_config);
	// 定时器及其中断配置
	epit1_init(0,66000000/100,epit1_key_irqhandler);
	delay_init();
	// // 初始化按键外部中断
    // GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    // // system_register_irqhandler(GPIO1_Combined_16_31_IRQn, (system_irq_handler_t)keyDelay_irqhandler,NULL);// 使用延迟函数实现按键外部中断识别
	// system_register_irqhandler(GPIO1_Combined_16_31_IRQn, (system_irq_handler_t)keyTimer_irqhandler,NULL);// 使用定时器中断实现按键消抖
    // gpio_enable_int(GPIO1, 18);
	// 初始化LCD
	lcd_init();

	tftlcd_dev.forecolor = LCD_RED;// 设置前景颜色，画笔为红色
	lcd_show_string(10,10,400,32,32,(char *)"ALPHA-IMX6ULELCD TEST");
	lcd_draw_rectangle(10,52,1014,290); // 绘制矩形边框
	lcd_drawline(10,52,1014,290); // 绘制线条
	lcd_drawline(10,290,1014,52);
	lcd_draw_Circle(512,171,119); // 绘制圆形

	while (1)
	{
		index++;
		if(index == 10){
			index = 0;
		}
		lcd_fill(0,300,1023,599,backcolor[index]);// 填充部分屏幕
		lcd_show_string(800,10,240,32,32,(char *)"INDEX=");
		lcd_shownum(896,10,index,2,32);// 叠加显示数字

		state = !state;
		gpio_pin_write(GPIO1, 3, (uint32_t)!state);
		delayms(1000);
	}

	return 0;
}

int raise(int a)
{
	return 0;
}

