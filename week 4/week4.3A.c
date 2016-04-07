
/*
 * Project name:
     Demo4_1 : Free running AD conversion on channel 1, PORTF.1
 * Author: Avans-TI, JW
 * Revision History: 
     20101229: - initial release;
 * Description:
     This program gives an interrupt on each ms
 * Test configuration:
     MCU:             ATmega128
     Dev.Board:       BIGAVR6
     Oscillator:      External Clock 08.0000 MHz
     Ext. Modules:    -
     SW:              AVR-GCC
 * NOTES:
     - Turn ON the PORT LEDs at SW12.1 - SW12.8
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)	(1 << (x))

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}


// Initialize ADC: 10-bits (left justified), free running
void adcInit( void )
{
	ADMUX = 0b01100001;			// AREF=VCC, result left adjusted, channel1 at pin PF1
	ADCSRA = 0b11100110;		// ADC-enable, no interrupt, start, free running, division by 64
}


// Main program: ADC at PF1
int main( void )
{
	DDRF = 0x00;				// set PORTF for input (ADC)
	DDRA = 0xFF;				// set PORTA for output 
	DDRB = 0xFF;				// set PORTB for output
	adcInit();					// initialize ADC
	int temp = 0;
	while (1)
	{
		PORTB = ADCL;			// Show MSB/LSB (bit 10:0) of ADC
		temp = ADCH;
		switch (temp)
		{
			case 0:
			PORTA = 0b00000000;
			break;
			case 25:
			PORTA = 0b10000000;
			break;
			case 41:
			PORTA = 0b11000000;
			break;
			case 64:
			PORTA = 0b11100000;
			break;
			case 83:
			PORTA = 0b11110000;
			break;
			case 99:
			PORTA = 0b11111000;
			break;
			case 112:
			PORTA = 0b11111100;
			break;
			case 155:
			PORTA = 0b11111110;
			break;
			case 243:
			PORTA = 0b11111111;
			break;
		}
		//PORTA = ADCH;
		wait(100);				// every 100 ms (busy waiting)
	}
}

