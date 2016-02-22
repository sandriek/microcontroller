/*
 * 
 *
 * Created: 15-2-2016 19:01:48
 * Author : sander
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>


void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		
	}
}

ISR( INT0_vect )
{
	for(int i = 0 ; i <=6; i++){
    PORTD = PORTD<<1;	
	wait(1000);
	}
}


ISR( INT7_vect )

{
for(int i = 0; i<=6; i++){
    PORTD = PORTD>>1;
	wait(1000);
	}
}
int main( void )

{
	DDRD = 0b11111111;	
	PORTD = 0b00000001;		
	EICRA |= 0x0B;			
	EIMSK |= 0b10000001;			

	sei();				

	while (1)
	{							
	}

	return 1;
}