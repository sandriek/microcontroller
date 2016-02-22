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
	  {0b00111111}//0
	, {0b00000110}//1
	, {0b01011011}//2
	, {0b01001111}//3
	, {0b01100110}//4
	, {0b01101101}//5
	, {0b01111101}//6
	, {0b00000111}//7
	, {0b01111111}//8
	, {0b01101111}//9
	, {0b01110111}//a
	, {0b01111100}//b
	, {0b01011000}//c
	, {0b01011110}//d
	, {0b01111001}//E
	, {0b01110001}//f,  
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
		 if (PINC == 0b00000001 && PIND == 0b00000001){
			 index = 0;
			 display(index);
			 wait(2000);
		 }
		 else{
	 if (PINC == 0b00000001 ){
	  index++;
	  display(index);
	  wait(2000);
	 }
	 if (PIND == 0b00000001){
	 index--;
	 display(index);
	 wait(2000);
	 }
	 }
	 }
	 
	 
	}
		
		
    

void display(int digit){
if (digit >= 0 && digit <= 15)
{
PORTF = lookup[digit].data;
wait(2000);
}
else{
PORTF = lookup[14].data;
wait(2000);
}
return 1;
}


