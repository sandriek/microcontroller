/*
 * Week3.3.c
 *
 * Created: 3/8/2016 11:13:00 AM
 * Author : Tom Remeeus
 */ 

#define Bit(x)(1<<x)

#include <avr/io.h>
#include <avr/interrupt.h>

int msCount = 0;
int LEDswitch = 0;

void ToggleD7(void)
{
	PORTD ^= Bit(7);
}

void init(void)
{
	DDRD |= Bit(7);

	OCR2 = 125;
	TIMSK |= Bit(7);
	sei();
	TCCR2 = 0b00001011;
}

ISR(TIMER2_COMP_vect)
{
	msCount ++;

	if(LEDswitch && msCount == 25)
	{
		LEDswitch = 0;
		msCount = 0;
		ToggleD7();
	}
	else if(!LEDswitch && msCount == 15)
	{
		LEDswitch = 1;
		msCount = 0;
		ToggleD7();
	}
}

int main(void)
{
	init();
	
	while (1)
	{
	}
}
