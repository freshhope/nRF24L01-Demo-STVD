/**
  ******************************************************************************
  * @author  泽耀科技 ASHINING
  * @version V3.0
  * @date    2016-10-08
  * @brief   主函数C文件
  ******************************************************************************
  * @attention
  *
  * 官网	:	http://www.ashining.com
  * 淘宝	:	https://shop105912646.taobao.com
  * 阿里巴巴:	https://cdzeyao.1688.com
  ******************************************************************************
  */
  


#include "main.h"

#define TX_NODE 2
#define MAX_WAVEINDEX 255
// 最大值:255  最小值:0
const unsigned char  SINWAVE[] = {
 127, 130, 133, 136, 139, 143, 146, 149, 152, 155, 158, 161, 164, 167, 170, 173,
 176, 179, 182, 184, 187, 190, 193, 195, 198, 200, 203, 205, 208, 210, 213, 215,
 217, 219, 221, 224, 226, 228, 229, 231, 233, 235, 236, 238, 239, 241, 242, 244,
 245, 246, 247, 248, 249, 250, 251, 251, 252, 253, 253, 254, 254, 254, 254, 254,
 255, 254, 254, 254, 254, 254, 253, 253, 252, 251, 251, 250, 249, 248, 247, 246,
 245, 244, 242, 241, 239, 238, 236, 235, 233, 231, 229, 228, 226, 224, 221, 219,
 217, 215, 213, 210, 208, 205, 203, 200, 198, 195, 193, 190, 187, 184, 182, 179,
 176, 173, 170, 167, 164, 161, 158, 155, 152, 149, 146, 143, 139, 136, 133, 130,
 127, 124, 121, 118, 115, 111, 108, 105, 102,  99,  96,  93,  90,  87,  84,  81,
  78,  75,  72,  70,  67,  64,  61,  59,  56,  54,  51,  49,  46,  44,  41,  39,
  37,  35,  33,  30,  28,  26,  25,  23,  21,  19,  18,  16,  15,  13,  12,  10,
   9,   8,   7,   6,   5,   4,   3,   3,   2,   1,   1,   0,   0,   0,   0,   0,
   0,   0,   0,   0,   0,   0,   1,   1,   2,   3,   3,   4,   5,   6,   7,   8,
   9,  10,  12,  13,  15,  16,  18,  19,  21,  23,  25,  26,  28,  30,  33,  35,
  37,  39,  41,  44,  46,  49,  51,  54,  56,  59,  61,  64,  67,  70,  72,  75,
  78,  81,  84,  87,  90,  93,  96,  99, 102, 105, 108, 111, 115, 118, 121, 124,
};
unsigned char iWave;
//                     ID    Data
unsigned char tx[2] = {TX_NODE, 0x00};

const char *g_Ashining = "ashining";
uint8_t g_TxMode = 0, g_UartRxFlag = 0;
uint8_t g_UartRxBuffer[ 100 ] = { 0 };
uint8_t g_RF24L01RxBuffer[ 32 ] = { 1,2,3,4,5,6,7,8,9 }; 



/**
  * @brief :主函数 
  * @param :无
  * @note  :无
  * @retval:无
  */
void main( void )
{
	uint8_t i = 0;

	//串口初始化
	drv_uart_init( 9600 );
	
	//LED初始化
	drv_led_init( );
	
	//SPI初始化
	drv_spi_init( );

	//RF24L01初始化
	NRF24L01_Gpio_Init( );
	NRF24L01_check( );
	RF24L01_Init( );
	
	led_red_off( );
	led_green_off( );
	for( i = 0; i < 6; i++ )
	{
		led_red_flashing( );
		led_green_flashing( );
		drv_delay_ms( 500 );
	}
	
#ifdef	__RF24L01_TX_TEST__		
//=========================================================================================//	
//*****************************************************************************************//
//************************************* 发送 **********************************************//
//*****************************************************************************************//
//=========================================================================================//	
	
	//按键初始化
	drv_button_init( );
	
	RF24L01_Set_Mode( MODE_TX );		//发送模式
	
	while( 1 )	
	{
		//模式切换
		if( BUTOTN_PRESS_DOWN == drv_button_check( ))
		{
			g_TxMode = 1 - g_TxMode;		//模式会在 TX_MODE_1( 0 ),TX_MODE_2( 1 )之间切换
			
			//状态显示清零
			led_green_off( );
			led_red_off( );
			
			if( TX_MODE_1 == g_TxMode )
			{
				for( i = 0; i < 6; i++ )		
				{
					led_red_flashing( );	//固定发送模式，红灯闪烁3次
					drv_delay_ms( 500 );		
				}
			}
			else
			{
				for( i = 0; i < 6; i++ )
				{
					led_green_flashing( );	//串口发送模式，绿灯闪烁3次
					drv_delay_ms( 500 );
				}
			}
		}
		
		//发送
		if( TX_MODE_1 == g_TxMode )
		{
#if TX_NODE == 1
            tx[1] = SINWAVE[iWave++];
#endif
#if TX_NODE == 2
            tx[1] = iWave++;
#endif
			NRF24L01_TxPacket( (uint8_t *)(&tx[0]), 2 );		//模式1发送固定字符,1S一包
			drv_delay_ms( 100 );		
			led_red_flashing( );			
		}
		else
		{	
			//查询串口数据
			i = drv_uart_rx_bytes( g_UartRxBuffer );
			
			if( 0 != i )
			{
				NRF24L01_TxPacket( g_UartRxBuffer, i );
				led_red_flashing( );
			}
		}
	}
	
#else		
//=========================================================================================//	
//*****************************************************************************************//
//************************************* 接收 **********************************************//
//*****************************************************************************************//
//=========================================================================================//	
	
	RF24L01_Set_Mode( MODE_RX );		//接收模式	
	
	while( 1 )
	{
		NRF24L01_RxPacket( g_RF24L01RxBuffer );		//接收字节
		i = NRF24L01_Read_Reg( R_RX_PL_WID );		//接收字节个数
		if( 2 == i )
		{
            i = 3;
            g_RF24L01RxBuffer[2] = g_RF24L01RxBuffer[0] + g_RF24L01RxBuffer[1];
			led_green_flashing( );
			drv_uart_tx_bytes( g_RF24L01RxBuffer,i );	//输出接收到的字节
			
		}
	}
		

#endif
}