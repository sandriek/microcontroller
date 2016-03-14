/*
 * week3.c
 *
 * Created: 23-2-2016 10:45:39
 * Author : sander
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include <avr/interrupt.h>

int main(void)
{
    
	DDRC = 0xFF;
	DDRD  = 0b00000000 ;
	TCCR2 = 0b00000111;
	TIMSK |= 0b00000010;
	char buf[3];
	int cijfer;
	int ind;
	
	sei();

	while (1)
	{
	if (cijfer != TCNT2){
	cijfer = TCNT2;
	if(cijfer < 10){
	ind = 0;
	}
	else{
	if(cijfer >= 10 && cijfer < 100){
	ind = 1;
	}
	else{
	ind = 2;
	}
	}
	itoa(cijfer, buf, 10);
	char* s = buf;
	clear();
	init();
	//setcursor(5);
	display_text(s, ind);
	_delay_ms(100);
	}
	else{

	}
	}
	return 1;
}

