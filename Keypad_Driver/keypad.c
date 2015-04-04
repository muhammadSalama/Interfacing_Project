/*
 * keypad.c
 *
 * Created: 3/29/2015 11:08:06 PM
 *  Author: mohamed
 */ 
#include "keypad.h"

static DIO_Config g_KP_Col[N_col],g_KP_Row[N_row];  /* use 2-line KP + 4-bit Data Mode + 5*7 dot display Mode */


/****************************************************************************************************/


/***************************************************KP_Configuration****************************************************
* Purpose : To Set KP port the PORT Which the pin belongs to. 'A 'B' 'C' or 'D'
*													   2. the number of the pin in the PORT.
*													   3. the direction of pin as OUTPUT
*													   4. the value of the pin is LOGIC_LOW.
* Input : void
* Output : void
* Notes : #if to decide  to be 8-bit or 4-bit mode
*******************************************************************************************************/


uint8 KeyPad_getPressedKey(void){
	uint8 col,row,count;
	while(1)
	{
		for(col=0;col<N_col;col++) /* loop for columns */
		{
			for(count=0;count<N_col;count++)
			{
			g_KP_Col[count].port      = KP_PORT; // which port KP enable pin
			g_KP_Col[count].pin_num   = 4 + count; //KP enable PIN Number
			g_KP_Col[count].direction = INPUT;
			g_KP_Col[count].val     = LOGIC_HIGH;
			DIO_Set_Direction(& g_KP_Col[count]);
			DIO_Write_Pin(& g_KP_Col[count]);
			
			
			}
			
			for(count=0;count<N_row;count++)
			{
				g_KP_Row[count].port      = KP_PORT; // which port KP enable pin
				g_KP_Row[count].pin_num   = count; //KP enable PIN Number
				g_KP_Row[count].direction = INPUT;
				g_KP_Row[count].val     = LOGIC_HIGH;
				
			    DIO_Set_Direction(& g_KP_Row[count]);
					DIO_Write_Pin(& g_KP_Row[count]);
			}
			
			
			
			g_KP_Col[col].port      = KP_PORT; // which port KP enable pin
			g_KP_Col[col].pin_num   = 4 + col; //KP enable PIN Number
			g_KP_Col[col].direction = OUTPUT; //KP enable PIN OUTPORT
			g_KP_Col[col].val     = LOGIC_LOW;
			DIO_Set_Direction(& g_KP_Col[col]);
			DIO_Write_Pin(& g_KP_Col[col]);
			
			
			
			/* 
			 * each time only one of the column pins will be output and 
			 * the rest will be input pins include the row pins 
			 */ 
		//	KEYPAD_PORT_DIR = (0b00010000<<col); 
			
			/* 
			 * clear the output pin column in this trace and enable the internal 
			 * pull up resistors for the rows pins
			 */ 
			//KEYPAD_PORT_OUT = (~(0b00010000<<col)); 
		
			for(row=0;row<N_row;row++) /* loop for rows */
			{
				
				
				
				
				
				if(!(DIO_Read_Pin(& g_KP_Row[row]))) /* if the switch is press in this row */ 
				{
					while(!(DIO_Read_Pin(& g_KP_Row[row])));
					#if (N_col == 3)  
						return KeyPad_4x3_adjustKeyNumber((row*N_col)+col+1); 
					#elif (N_col == 4)
						return KeyPad_4x4_adjustKeyNumber((row*N_col)+col+1);
					#endif				
				}
			}
		}
	}	
}
#if (N_col == 3)

uint8 KeyPad_4x3_adjustKeyNumber(uint8 button_number)
{
	switch(button_number)
	{
		case 10: return '*'; // ASCII Code of =
		break;
		case 11: return 0;
		break;
		case 12: return '#'; // ASCII Code of +
		break;
		default: return button_number;
	}
}


#elif (N_col == 4)

uint8 KeyPad_4x4_adjustKeyNumber(uint8 button_number)
{
	switch(button_number)
	{
		case 1: return 7;
		break;
		case 2: return 8;
		break;
		case 3: return 9;
		break;
		case 4: return '%'; // ASCII Code of %
		break;
		case 5: return 4;
		break;
		case 6: return 5;
		break;
		case 7: return 6;
		break;
		case 8: return '*'; /* ASCII Code of '*' */
		break;
		case 9: return 1;
		break;
		case 10: return 2;
		break;
		case 11: return 3;
		break;
		case 12: return '-'; /* ASCII Code of '-' */
		break;
		case 13: return 13;  /* ASCII of Enter */
		break;
		case 14: return 0;
		break;
		case 15: return '='; /* ASCII Code of '=' */
		break;
		case 16: return '+'; /* ASCII Code of '+' */
		break;
		default: return button_number;
	}
}

#endif