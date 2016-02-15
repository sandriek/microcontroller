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
		_delay_ms(1)
	}
int main(void)
{

	DDRD= 0b11111111;
	PORTD = 0b00000001;
    while (1) 
    {
	if(PORTD != 0b10000000){
	wait(50);
	 PORTD << 1;}
	else{
	PORTD >>>1;
	}
	 
	
	}
    return 0;
}


