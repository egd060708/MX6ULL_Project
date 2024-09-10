#include "key.h"
#include "bsp_gpio.h"
#include "bsp_delay.h"


/**
 * @brief 按键获取函数
 * @param _gpio_group GPIO寄存器组
 * @param _pin GPIO引脚号
 * @param _dir 按键方向，也就是什么电平触发，0或1
 */
uint32_t key_get_value(GPIO_Type *_gpio_group, uint32_t _pin, uint32_t _dir)
{
	uint32_t ret = 0;
	static unsigned char release = 1;							  /* 按键松开 */
	if ((release == 1) && (gpio_pin_read(_gpio_group, _pin) == _dir)) /* KEY0 按下 */
	{
		delay(10);	 /* 延时消抖 */
		release = 0; /* 标记按键按下 */
		if (gpio_pin_read(_gpio_group, _pin) == 0)
		{
			ret = 1;
		}
	}
	else if (gpio_pin_read(_gpio_group, _pin) != _dir) /* KEY0 未按下 */
	{
		ret = 0;
		release = 1; /* 标记按键释放 */
	}

	return ret;
}

void key_irphandler(void)
{
    static uint32_t state = 0;
    delay(10);
    if(gpio_pin_read(GPIO1, 18) == 0)
	{
		state = !state;
		gpio_pin_write(GPIO5, 1, (uint32_t)!state);
	}
	gpio_clear_int_flags(GPIO1, 18);// 清除中断标志位
}