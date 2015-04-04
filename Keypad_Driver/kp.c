/*
 * kp.c
 *
 * Created: 3/29/2015 10:58:58 PM
 *  Author: mohamed
 */ 


#include "keypad.h"

int main(void)
{
	uint8 key=0;
	DDRC  = 0xFF; /* 7-segment pins as output pins */
	PORTC = 0; /* 7-segment displays Zero at the beginning */

	while(1)
	{
		key = KeyPad_getPressedKey(); /* get the pressed button from keypad */
		if((key >= 0) && (key <= 9))
		{
			PORTC = key;
		}
	}
}