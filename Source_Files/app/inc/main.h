/**
  ******************************************************************************
  * @author  泽耀科技 ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   主配置H文件
  ******************************************************************************
  * @attention
  *
  * 官网	:	http://www.ashining.com
  * 淘宝	:	https://shop105912646.taobao.com
  * 阿里巴巴:	https://cdzeyao.1688.com
  ******************************************************************************
  */



#ifndef __MAIN_H__
#define __MAIN_H__


#include "drv_button.h"
#include "drv_delay.h"
#include "drv_led.h"
#include "drv_spi.h"
#include "drv_uart.h"
#include "drv_RF24L01.h"


#define 	__RF24L01_TX_TEST__							//**@@ ������Է��͹�������Ҫ����ú꣬������Խ�������Ҫ���θú� **@@//
//#define 	__USE_SOFT_SPI_INTERFACE__					//**@@ ���ʹ�����SPI����Ҫ����ú꣬��֮���ʹ��Ӳ��SPI����Ҫ���θú� **@@//


/** ����ģʽ���� */
enum
{
	TX_MODE_1 = 0,		//发送模式1，发送固定的字符串
	TX_MODE_2			//发送模式2，发送串口接收到的数据
};


#endif
