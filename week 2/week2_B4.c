/*
 * B6.c
 *
 * Created: 15-2-2016 19:01:48
 * Author : sander
 */ 
 typedef struct {
	 unsigned char data;
	 unsigned int delay ;
 } PATTERN_STRUCT;

#include <avr/io.h>
#include <util/delay.h>
PATTERN_STRUCT lookup[] = {
	  {0b00001000, 2500}
	, {0b00010100, 2500}
	, {0b01000000, 2500}
	, {0b00100010, 2500}
	, {0b00000001, 2500}
	, {0b00000001, 2500}
	, {0b00100010, 2500}
	, {0b01000000, 2500}
	, {0b00010100, 2500}
	, {0b00001000, 2500}  
	, {0b00001000, 2500}
	, {0b00010000, 2500}
	, {0b01000000, 2500}
	, {0b00000010, 2500}
	, {0b00000001, 2500}
	, {0b00100000, 2500}
	, {0b01000000, 2500}
	, {0b00000100, 2500}
};
void wait(int ms)
{
	for(int i=0; i<ms;i++){
		_delay_ms(1);
	}
}

int main(void)
{
	DDRF= 0b11111111;
	int index = 0;
    while (1) 
    {
		int index = 0;
		while( index <= 17 ) {
			PORTF = lookup[index].data;
			wait(lookup[index].delay);
			index++;
		}
	 }
	 
	 
	}


