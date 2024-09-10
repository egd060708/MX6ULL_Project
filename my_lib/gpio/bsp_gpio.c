#include "bsp_gpio.h"
#include "bsp_delay.h"

/**
 * @brief GPIO口初始函数
 * @param _muxRegister IO复用寄存器地址
 * @param _muxMode IO复用模式（0~8）
 * @param _inputRegister 外设输入IO选择寄存器地址
 * @param _inputDaisy 外设输入IO选择寄存器的值
 * @param _configRegister IO配置寄存器地址
 * @param _init_config GPIO初始化配置结构体
 */
void gpio_init(uint32_t _muxRegister,
			   uint32_t _muxMode,
			   uint32_t _inputRegister,
			   uint32_t _inputDaisy,
			   uint32_t _configRegister,
			   gpio_init_config_s *_init_config)
{
	/* 1、初始化IO复用，并且关闭软件输入 */
	IOMUXC_SetPinMux(_muxRegister, _muxMode, _inputRegister, _inputDaisy, _configRegister, _init_config->inputOnfield);
	/* 2、、配置GPIO1_IO03的IO属性
	 *bit 16: HYS开关
	 *bit [15:14]: 上下拉
	 *bit [13]: kepper功能
	 *bit [12]: pull/keeper使能
	 *bit [11]: 开路输出
	 *bit [7:6]: IO速度
	 *bit [5:3]: IO驱动能力
	 *bit [0]: 转换率
	 */
	IOMUXC_SetPinConfig(_muxRegister, _muxMode, _inputRegister, _inputDaisy, _configRegister, _init_config->configValue);
	/* 3、配置输入输出 */
	if (_init_config->direction == kGPIO_DigitalInput)
	{
		_init_config->gpio_group->GDIR &= ~(1 << _init_config->pin_num); // 设置为输入模式
	}
	else if (_init_config->direction == kGPIO_DigitalOutput)
	{
		_init_config->gpio_group->GDIR |= (1 << _init_config->pin_num);							   // 设置为输出模式
		gpio_pin_write(_init_config->gpio_group, _init_config->pin_num, _init_config->outputLogic); // 配置输出端口的默认电平
	}
}

/**
 * @brief GPIO 电平配置
 * @param _gpio_group GPIO寄存器组
 * @param _pin GPIO引脚号
 * @param _value 0: 输出低电平, 1: 输出高电平
 */
void gpio_pin_write(GPIO_Type *_gpio_group, uint32_t _pin, uint32_t _value)
{
	if (_value == 1U)
	{
		_gpio_group->DR |= (1U << _pin); /* 输出高电平 */
	}
	else if (_value == 0U)
	{
		_gpio_group->DR &= ~(1U << _pin); /* 输出低电平 */
	}
}

/**
 * @brief 读取GPIO电平
 * @param _gpio_group GPIO寄存器组
 * @param _pin GPIO引脚号
 */
uint32_t gpio_pin_read(GPIO_Type *_gpio_group, uint32_t _pin)
{
	return (((_gpio_group->DR) >> _pin) & 0x1); /* 读取GPIO状态 */
}

/**
 * @brief GPIO中断配置
 * @param _gpio_group GPIO寄存器组
 * @param _pin GPIO引脚号
 * @param _interruptMode 中断模式
 */
void gpio_int_config(GPIO_Type* _gpio_group, uint32_t _pin, gpio_interrupt_mode_e _interruptMode)
{
	volatile uint32_t *icr; // volatile关键字防优化
	uint32_t icrShift;
	icrShift = _pin;
	_gpio_group->EDGE_SEL &= ~(1U << _pin); // ��除中断边��选择
	if(_pin < 16)
	{
		icr = &(_gpio_group->ICR1);
	}
	else
	{
		icr = &(_gpio_group->ICR2);
		icrShift -= 16;
	}
	switch(_interruptMode)
	{
		case(kGPIO_IntLowLevel):
			*icr &= ~(3U << (icrShift * 2));
			break;
		case(kGPIO_IntHighLevel):
			*icr = (*icr & (~(3U << (icrShift * 2)))) | (1U << (icrShift * 2));
			break;
		case(kGPIO_IntRisingEdge):
			*icr = (*icr & (~(3U << (icrShift * 2)))) | (2U << (icrShift * 2));
			break;
		case(kGPIO_IntFallingEdge):
			*icr |= (3U << (icrShift * 2));
			break;
		case(kGPIO_IntRisingOrFallingEdge):
			_gpio_group->EDGE_SEL |= (1U << _pin); // 使能中断边沿选择
			break;
		case(kGPIO_NoIntmode):
			break;
		default:
			break;
	}
}

/**
 * @brief GPIO中断使能函数
 * @param _gpio_group GPIO寄存器组
 * @param _pin GPIO引脚号
 */
void gpio_enable_int(GPIO_Type* _gpio_group, uint32_t _pin)
{
	_gpio_group->IMR |= (1U << _pin); /* 使能中断 */
}

/**
 * @brief GPIO中断失能函数
 * @param _gpio_group GPIO寄存器组
 * @param _pin GPIO引脚号
 */
void gpio_disable_int(GPIO_Type* _gpio_group, uint32_t _pin)
{
	_gpio_group->IMR &= ~(1U << _pin); /* 失能中断 */
}

/**
 * @brief GPIO清除中断标志位
 * @param _gpio_group GPIO寄存器组
 * @param _pin GPIO引脚号
 */
void gpio_clear_int_flags(GPIO_Type* _gpio_group, uint32_t _pin)
{
	_gpio_group->ISR |= (1U << _pin); /* 清除中断标志 */
}
