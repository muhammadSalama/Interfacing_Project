/*
 * UART_DVR.h
 *
 * Created: 4/3/2015 10:01:29 PM
 *  Author: mohamed
 */ 


#ifndef UART_DVR_H_
#define UART_DVR_H_

#include "common_macros.h"
#include "std_types.h"

#include "micro_config.h"
#define ENABLED 1
#define DISABLED 0
#define SYNC 1
#define ASYNC 0
#define ENABLED_ODD 11
#define ENABLED_EVEN 10
#define One_stop_bit 1
#define two_stop_bit 2
#define NORMAL_SPEED 0
#define DOUBLE_SPEED 1
#define five_bit_mode 5
#define six_bit_mode 6
#define seven_bit_mode 7
#define eight_bit_mode 8
#define nine_bit_mode 9
#define Rising_edge_TX 0
#define Falling_edge_TX 1
#define UART_Mode SYNC
#define RX_Enable 0
#define TX_Enable 1
#define TX_RX_Enable 2

 typedef struct {
	 uint8 Mode ;
	 uint8 Stop_bit;
	 uint8 Prty_mode;
	 uint8 Clk_Plrty;
	 uint8 Char_Size;
	 uint8 Speed_mode;
	 uint16 Rate;
	 uint8 TX_RX;
	 
	 
	}UART_Config;
	
	#define Mode_Error -110
	uint8 UART_Init(UART_Config *g_UART_Config);

	void UART_sendByte(const char data);

	char UART_recieveByte(void);

	void UART_sendString(const char *Str);

	void UART_receiveString(char *Str); // Receive until #
#endif /* UART_DVR_H_ */
