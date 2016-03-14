#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)			(1 << (x))

unsigned int sCount=0, minutes=0, hours=0;

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

// Initialize timer 1: fast PWM at pin PORTB.6 (hundredth ms)
void timer1Init( void )
{
	OCR1A = 0;					// RED, default, off
	OCR1B = 0;					// GREEN, default, off
	OCR1C = 0;					// BLUE, default, off
	TCCR1A = 0b10101001;		// compare output OC1A,OC1B,OC1C
	TCCR1B = 0b00001011;		// fast PWM 8 bit, prescaler=64, RUN
}

// Set pulse width for RED on pin PB5, 0=off, 255=max
void setRed( unsigned char red )
{
	OCR1A = red;
}
 void setGreen( unsigned char green)
 {
	 OCR1B = green;
 }
 void setBlue( unsigned char blue){
	 OCR1C = blue;
 }
int main( void )
{
	DDRB = 0xFF;					
	timer1Init();
	wait(100);

	while (1)
	{
		int delta = 1;
		setRed (255);
		for (int red = 0; red<=255; red+=delta)
		{
			setRed( red );				
			delta += 2;					
			wait(100);					
		}
		for (int red = 255; red>=0; red-=delta)
		{
			setRed( red );				
			delta -= 2;					
			wait(100);					
		}
		setRed( 255 );
		delta = 1;
		wait(100);

		for (int green = 255; green>=0; green-=delta)
		{
			setGreen( green );
			
			delta += 2;					
			wait(100);					
		}
		for (int green = 0; green<=255; green+=delta)
		{
			setGreen( green );
			delta -= 2;					
			wait(100);					
		}
		setGreen( 255 );
		delta = 1;
		wait(100);
		for (int blue = 255; blue>=0; blue-=delta)
		{
			setBlue( blue );

			delta += 2;					
			wait(100);					
		}
		for (int blue = 0; blue<=255; blue+=delta)
		{
			setBlue( blue );
			
			delta -= 2;				
			wait(100);					
		}
				setBlue( 255 );
				delta = 1;
				wait(100);

		for (int yellow = 255; yellow>=0; yellow-=delta)
		{
			setGreen( yellow );
			setRed( yellow);
			delta += 2;					
			wait(100);					
		}
		for (int yellow = 0; yellow<=255; yellow+=delta)
		{
			setGreen( yellow );
			setRed( yellow);
			delta += 2;					
			wait(100);				
		}
		setGreen( 255 );
		setRed( 255);
		delta = 1;
		wait(100);


		for (int white = 255; white>=0; white-=delta)
		{
			setGreen( white );
			setRed( white);
			setBlue(white);
			delta += 2;					
			wait(100);					
		}
		for (int white = 0; white<=255; white+=delta)
		{
			setGreen( white );
			setRed( white);
			setBlue(white);
			delta += 2;					
			wait(100);				
		}
		setGreen( 255 );
		setRed( 255);
		delta = 1;
		wait(100);
	} 
}
