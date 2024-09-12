/***************************************************************
Copyright © zuozhongkai Co., Ltd. 1998-2019. All rights reserved.
文件名	: 	 bsp_delay.c
作者	   : 左忠凯
版本	   : V1.0
描述	   : 延时文件。
其他	   : 无
论坛 	   : www.wtmembed.com
日志	   : 初版V1.0 2019/1/4 左忠凯创建
***************************************************************/
#include "bsp_delay.h"
#include "bsp_gpt1timer.h"

/**
 * @brief delay初始化函数
 * @return None
 */
void delay_init(void)
{
	gpt1_init(65,0XFFFFFFFF);
	gpt1_start();
}

/*
 * @description	: 短时间延时函数
 * @param - n	: 要延时循环次数(空操作循环次数，模式延时)
 * @return 		: 无
 */
void delay_short(volatile unsigned int n)
{
	while(n--){}
}

/*
 * @description	: 延时函数,在396Mhz的主频下
 * 			  	  延时时间大约为1ms
 * @param - n	: 要延时的ms数
 * @return 		: 无
 */
void delay(volatile unsigned int n)
{
	while(n--)
	{
		delay_short(0x7ff);
	}
}

/**
 * @brief us延时
 * @param usdelay us延时时间
 * @return None
 */
void delayus(uint32_t usdelay)
{
	uint32_t oldcnt,newcnt;
	uint32_t tcntvalue = 0;//总时间

	oldcnt = GPT1->CNT;
	while(1)
	{
		newcnt = GPT1->CNT;
		if(newcnt != oldcnt)
		{
			if(newcnt > oldcnt)//gpt向上计数并且没有溢出
			{
				tcntvalue += newcnt - oldcnt;
			}
			else
			{
				tcntvalue += 0XFFFFFFFF - oldcnt + newcnt;
			}
			oldcnt = newcnt;
			if(tcntvalue >= usdelay)
			{
				break;
			}
		}
	}
}

/**
 * @brief ms延时
 * @param msdelay ms延时时间
 * @return None
 */
void delayms(uint32_t msdelay)
{
	int i;
	for(i = 0; i < msdelay; i++)
	{
		delayus(1000);
	}
}



