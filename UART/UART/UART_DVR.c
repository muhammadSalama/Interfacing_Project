/*
 * UART_DVR.c
 *
 * Created: 4/3/2015 10:01:01 PM
 *  Author: mohamed
 */ 
#include "UART_DVR.h"



uint8 UART_Init(UART_Config *g_UART_Config)
{
	uint8 prty_error=0,stop_Error=0,speed_error=0 , bit_mode_error=0, polarity_error=0;
	uint16 UBRR=0;
	
    if(g_UART_Config->Mode==SYNC)
	{
	  CLEAR_BIT(UCSRC,URSEL);
	  
	  UBRR = (F_CPU/(2*g_UART_Config->Rate))-1;
	  UBRRL=UBRR;
	  UBRRH=(UBRR>>8);
	    
	  SET_BIT(UCSRC,URSEL);
	  
	  SET_BIT(UCSRC,UMSEL);
	  
	  if(g_UART_Config->Clk_Plrty==Rising_edge_TX)
	  {
        CLEAR_BIT(UCSRC,UCPOL);
	  }
	  else if (g_UART_Config->Clk_Plrty==Falling_edge_TX)
	  {
		   SET_BIT(UCSRC,UCPOL);
	  
	  }
	  else
	  polarity_error=-1;
	  
	  
	  
	}
	else if(g_UART_Config->Mode==ASYNC) 
	{ 
	 
	  if(g_UART_Config->Speed_mode==NORMAL_SPEED) 
	 
	 { 
		 
		  
	  CLEAR_BIT(UCSRA,U2X);
	 
	  CLEAR_BIT(UCSRC,URSEL);
	  UBRR = (F_CPU/((uint32)16*g_UART_Config->Rate))-1;
	  UBRRL=UBRR;
	  UBRRH=(UBRR>>8);
	  //UCSRA = (1<<U2X);
     			 
	}
	 else if(g_UART_Config->Speed_mode==DOUBLE_SPEED)
	 {
		 
	 
	  SET_BIT(UCSRA,U2X);
	  CLEAR_BIT(UCSRC,URSEL);
       UBRR = (F_CPU/((uint32) 8*g_UART_Config->Rate))-1;
	 //UBRR=1;
	 // UBRR=12;
	   UBRRL=UBRR;
	   UBRRH=(UBRR>>8);
	 //UCSRA = (1<<U2X);
	 
	
	 }
	 
	  else
	 {speed_error=-1;}
	 
	 
	 
	 
	 
	 
	 
	  SET_BIT(UCSRC,URSEL);	
	  
	  CLEAR_BIT(UCSRC,UMSEL);
	  
	  CLEAR_BIT(UCSRC,UCPOL);
	
	}
	else
	polarity_error= Mode_Error;
	
	switch(g_UART_Config->Prty_mode)
	//case DISA : CLEAR_BIT(UCSRC,UPM1);
	            //    CLEAR_BIT(UCSRC,UPM0);
					//break;
{					
	case ENABLED_ODD: SET_BIT(UCSRC,UPM1);
	                  SET_BIT(UCSRC,UPM0);
	                  break;
	case DISABLED: CLEAR_BIT(UCSRC,UPM1);
	               CLEAR_BIT(UCSRC,UPM0);
	               break;
				   
	case ENABLED_EVEN : SET_BIT(UCSRC,UPM1);
	                    CLEAR_BIT(UCSRC,UPM0);
	                    break;
    
	default : prty_error=-1;
										
	
}
 if(g_UART_Config->Stop_bit==One_stop_bit)
 {
	 CLEAR_BIT(UCSRC,USBS);
 }
 else if(g_UART_Config->Stop_bit==two_stop_bit)
 {
	 SET_BIT(UCSRC,USBS);
 }
 else
 stop_Error=-1;
 
 switch(g_UART_Config->Char_Size)
 //case DISA : CLEAR_BIT(UCSRC,UPM1);
 //    CLEAR_BIT(UCSRC,UPM0);
 //break;
 {
	 case five_bit_mode: CLEAR_BIT(UCSRC,UCSZ0);
	                     CLEAR_BIT(UCSRC,UCSZ1);
						 CLEAR_BIT(UCSRB,UCSZ2);
	                     break;
     case six_bit_mode: SET_BIT(UCSRC,UCSZ0);
                         CLEAR_BIT(UCSRC,UCSZ1);
                         CLEAR_BIT(UCSRB,UCSZ2);
                         break;
						 						 
     case seven_bit_mode: CLEAR_BIT(UCSRC,UCSZ0);
	                   SET_BIT(UCSRC,UCSZ1);
	                   CLEAR_BIT(UCSRB,UCSZ2);
					   	break;
     case eight_bit_mode: SET_BIT(UCSRC,UCSZ0);
                          SET_BIT(UCSRC,UCSZ1);
                          CLEAR_BIT(UCSRB,UCSZ2);
					      break;
	case nine_bit_mode : SET_BIT(UCSRC,UCSZ0);
	                     SET_BIT(UCSRC,UCSZ1);
	                     SET_BIT(UCSRB,UCSZ2);	
						 break;	
	default: bit_mode_error=-1;					 		  
											   
	}
	// CLEAR_BIT(UCSRC,URSEL);
	 //return speed_error;
	 
	 switch(g_UART_Config->TX_RX)
	 {
		 case TX_Enable: SET_BIT(UCSRB,TXEN);
		                 CLEAR_BIT(UCSRB,RXEN);
						 break;
						 
		 case RX_Enable: SET_BIT(UCSRB,RXEN);
		                 CLEAR_BIT(UCSRB,TXEN);
		                 break;				 
		 case TX_RX_Enable: SET_BIT(UCSRB,TXEN);
		                    SET_BIT(UCSRB,RXEN);
							
		                   break;
	 }
     
return speed_error;
}

void UART_sendByte(const char data)
{
	while(!(UCSRA & (1<<UDRE))){} //UDRE flag is set when the buffer is empty and ready for transmitting a new byte so wait until this flag is set to one.
	UDR = data;
}

char UART_recieveByte(void)
{
	while(!(UCSRA & (1<<RXC))){} //RXC flag is set when the UART receive data so until this flag is set to one
	return UDR;
}

void UART_sendString(const char *Str)
{
	unsigned char i = 0;
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
}

void UART_receiveString(char *Str)
{
	unsigned char i = 0;
	Str[i] = UART_recieveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}
	Str[i] = '\0';
}

   

