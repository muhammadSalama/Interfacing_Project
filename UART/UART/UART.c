/*
 * UART.c
 *
 * Created: 4/3/2015 9:59:26 PM
 *  Author: mohamed
 */ 


//#include <avr/io.h>
#include "UART_DVR.h"
int main(void)
{
   char Str[20];
   char data;
  UART_Config UART_Conf;
  UART_Conf.Mode=ASYNC;
  UART_Conf.Speed_mode=NORMAL_SPEED;
  UART_Conf.Char_Size=eight_bit_mode;
  UART_Conf.Stop_bit=One_stop_bit;
  UART_Conf.Rate=2400;
  UART_Conf.Prty_mode=DISABLED;
  UART_Conf.TX_RX=TX_RX_Enable;
  UART_Init(& UART_Conf);
  //UBRRH = 0;
 //UBRRL = 12;
  //UCSRB = (1<<RXEN) | (1<<TXEN);
   while(1)
   {
	   //data = UART_recieveByte(); //Receive Byte from Terminal1
	   //UART_sendByte(data); //Resend the received byte to Terminal2
	   UART_receiveString(Str); //Receive String from Terminal
	   UART_sendString(Str); //Resend the string to Terminal2
   }
   }