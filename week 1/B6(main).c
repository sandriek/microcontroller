/*
 * B6.c
 *
 * Created: 15-2-2016 19:01:48
 * Author : sander
 */ 

#include <avr/io.h>


int main(void)
{
	DDRD= 0b11111111;
	int state = 0;
	int sleeptime = 1000;
    while (1) 
    {
		if (PINC0 & 1){
		if (state == 0){
		state = 1;
		}
		else{
		state = 0;
		}
		switch (state)
		{
			case 0:
			int sleeptime = 1000;
			break;

			case 1:
			int sleeptime =  4000;
			break;
		}
		}
		PORTD = 0b1000000;
		wait(sleeptime);
		PORTD = 0b0000000;
		
    }
}


