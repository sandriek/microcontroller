/*
 * b2.c
 *
 * Created: 15-2-2016 16:20:09
 * Author : sander
 */ 

#include <avr/io.h>
#include <util/delay.h>
void wait(int ms)
{
	for(int i=0; i<ms;i++){
		_delay_ms(1);
	}
	}
int main(void)
{

	DDRD= 0b11111111;
    while (1) 
    {
	
	if (PINC0 & 1){
	PORTD = 0b01000000;
	wait(500);
	PORTD = 0b00000000;
	}
	else{
	PORTD = 0b00000000;
    }
	}
    return 0;
}


