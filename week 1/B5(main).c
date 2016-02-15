/*
 * b5.c
 *
 * Created: 15-2-2016 18:38:33
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
	DDRD = 0b11111111;
	int ledAni1[6] = {0b00000000, 0b1000001, 0b11000011, 0b01100110, 0b00111100, 0b00011000};
	int ledAni2[12]= {0b00000000, 0b1000001, 0b11000011, 0b01100110, 0b00111100, 0b00011000, 0b00000000, 0b00011000, 0b00111100,0b01100110,0b11000011, 0b1000001};
    /* Replace with your application code */
    while (1) 
    {
		for(int i = 0; i<11; i++)
		{
		wait(1000);
		PORTD = ledAni2[i];
		int j = 10;
		}

    }
}

