/*
 * week5.2.c
 *
 * Created: 22-3-2016 11:25:00
 * Author : sander
 */ 

#include <avr/io.h>
#include "uart0.h"#include "lcd.h"


   char character;


   void wait( int ms )
   {
	   for (int tms=0; tms<ms; tms++)
	   {
		   _delay_ms( 1 );						// library function (max 30 ms at 8MHz)
	   }
   }


   // send/receive uart - dB-meter
   int main( void )
   {
	  char buffer[16];						// declare string buffer
	  DDRB = 0xFF;							// set PORTB for output
	  DDRC = 0xFF;
	  init();								// initialize LCD-display
	  usart0_init();							// initialize USART0
	  usart0_start();

	  while (1)
	  {
		  wait(50);							// every 50 ms (busy waiting)
		  PORTB ^= BIT(7);					// toggle bit 7 for testing
			
		  uart0_receiveString( buffer );		// receive string from uart
			char tempBuffer[16];
			for (int i = 0; i <= 8; i++)
			{
				tempBuffer[i] = buffer[(i+1)];
			}

		  clear();
		  display_text(tempBuffer, 8);
	  }
   }


