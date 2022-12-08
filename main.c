 /******************************************************************************
 *
 * File Name: main.c
 *
 * Description:source file to test the the ultrasonic sensor using ATmega16
 *
 *
 * Author: Shimaa Gamal
 *
 *******************************************************************************/
#include"lcd.h"
#include"ultrasonic.h"
#include "icu.h"
#include <avr/io.h>

uint16 g_distance=0;

int main(void){

	SREG |= (1<<7);        /* to Enable global interrupts I-bit*/
	LCD_init();            /* initialize the LCD */
	Ultrasonic_init();     /* intialize the sensor and the ICU */
 	LCD_displayString("Distance=");
	LCD_displayStringRowColumn(0,13,"cm");

	while(1){
		LCD_moveCursor(0,10);
		g_distance=Ultrasonic_readDistance();
		/* there's a problem that the LCD always display the number with error 2 to 4cm
		that i couldn't fix*/
		if(g_distance >= 100)
				{
					LCD_intgerToString(g_distance);
				}
				else
				{
					LCD_intgerToString(g_distance);
					/* In case the digital value is two or one digits print space in the next digit place */
					LCD_displayCharacter(' ');
				}

	}

}

