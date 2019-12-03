/**
 * \file
 *
 * \brief Empty user application template
 *
 */

#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#define F_CPU 1000000
#include <util/delay.h>
#include "lcd.h"
#include <stdio.h>
#include "libio.h"
#include "main.h"
#include "libmorse.h"


// Externally referenced, change main.h if changing amount of strings
char messages[TOT_MESSAGES][MESSAGE_LENGTH] = { "Hello", "Goodbye", "SOS", "ECE 312", "Beep" };

/*defining functions */
void init_gpio(void);
void displayLeft(void);
void displayRight(void);
void enterValue(void);
void ValueToMorseCode(void);
void PlayMC(void);

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	 lcd_init(LCD_DISP_ON);
	 
	 
	 
	 //char messages[TOT_MESSAGES][10] = { "Hello", "SOS", "Goodbye" };
	 
	 lcd_clrscr();
	
	 init_gpio();
	 int cursor = 0;
	 
	 set_buzzer(ON);
	 _delay_ms(1000);
	 set_buzzer(OFF);
	  
	while (1){
		// Refresh the menu prompt
		lcd_clrscr();
		lcd_gotoxy(0,0);
		lcd_puts("Message?");
			
			
		if( !(PIN(PORT_LR) & (1<<PIN_LEFT)) ) { // If user presses left button move the cursor
			cursor--;
		}
		else if( !(PIN(PORT_LR) & (1<<PIN_RIGHT)) ) { // If user presses right button move the cursor
			cursor++;
		}
		else if ( !(PIN(PORT_ENTER) & (1<<PIN_ENTER))) { // If user presses the enter button
			init_morse(cursor); // initalize the morse process by passing the message index
		} // the buzzer will play
		
		// Cycle the cursor back if it steps out of bounds
		if (cursor < 0) { cursor = TOT_MESSAGES - 1; }
		if (cursor > TOT_MESSAGES -1) { cursor = 0; }
			
		lcd_gotoxy(0,1);
		lcd_puts(messages[cursor]); // display selected message
		_delay_ms(250);
	}
}

void init_gpio(void) {
	
	ADMUX |= (1<<REFS0)|(1<<REFS1); //sets Avcc as the reference, 1.1 is our Vref
	
	ADCSRA |= (1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); // enable the ADC, 128 prescale
	
	TCCR0A |= ( (1<<WGM01)|(1<<COM0B0));
	TCCR0B |= ( 1<<CS01 );
	
	OCR0A = 0x6F;
	
	DDR(PORT_LR) &= ~( (1<<(PIN_LEFT))| (1<<PIN_RIGHT) ); // the 3 push buttons are inputs
	PORT(PORT_LR) |= ((1<<PIN_LEFT)| (1<<PIN_RIGHT) );

	DDR(PORT_ENTER) &= ~(1<<PIN_ENTER); 
	PORT(PORT_ENTER)|=  (1<<PIN_ENTER);

	DDR(PORT_BUZZER) |= (1<<PIN_BUZZER); //the buzzer is the output
	
	DDR(PORT_LED) |= (1<<PIN_LED); //the led is the output
	PORT(PORT_LED) &= ~(1<<PIN_LED); // Turn the led off
	//DDRD |= (1<<PORTD5);
}




