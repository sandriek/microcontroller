/*
 * week 4.c
 *
 * Created: 1-3-2016 10:54:20
 * Author : sander
 */ 
 #define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)			(1 << (x))

unsigned int sCount=0, minutes=0, hours=0;

void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			
	}
}

void timer1Init( void )
{
	OCR1A = 1;					// RED, default, off
	OCR1B = 1;					// GREEN, default, off
	OCR1C = 0;					// BLUE, default, off
	TCCR1A = 0b10101001;		// compare output OC1A,OC1B,OC1C
	TCCR1B = 0b00001011;		// fast PWM 8 bit, prescaler=64, RUN
}


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
	wait(3000);
	int delta = 1;
	int delta1 = 1;
	int delta2 = 1;
		for (int red = 255; red>=0; red-=delta)
		{
			setRed( red );
			delta += 2;					
			wait(100);					
		}
		
	while (1)
	{
		
	
				for (int blue = 255; blue>=0; blue-=delta1)
				{
					setBlue( blue );

					delta1 += 2;					
					wait(100);					
				}
		for (int red = 0; red<=255; red+=delta)
		{
			setRed( red );	
			
			delta -= 2;					
			wait(100);					
		}
		
		for (int green = 255; green>=0; green-=delta2)
		{
			setGreen( green );
			
			delta2 += 2;					
			wait(100);					
		}
		
				for (int blue = 0; blue<=255; blue+=delta1)
				{
					setBlue( blue );
					
					delta1 -= 2;					
					wait(100);					
				}
				
						for (int red = 255; red>=0; red-=delta)
						{
							setRed( red );

							delta += 2;					
							wait(100);					
						}
						
				for (int green = 0; green<=255; green+=delta2)
				{
					setGreen( green );
					
					delta2 -= 2;					
					wait(100);					
				}

		
	}
}