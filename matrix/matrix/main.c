#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "Spi.h"
int check = 0;
int running = 0;
int runningstate = 0;
int place = 0;
int helpnumber = 0;
int beep = 0;
typedef struct {
	unsigned char data;
} PATTERN_STRUCT;
PATTERN_STRUCT liftup[] = {
	//0
	  {0b10011100}
	, {0b10110110}
	, {0b10100010}
	, {0b10100010}
	, {0b10100010}
	, {0b10110110}
	, {0b10011100}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//pijl
	, {0b10001000}
	, {0b10011100}
	, {0b10111110}
	, {0b11111111}
	, {0b10011100}
	, {0b10011100}
	, {0b10011100}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//1
	, {0b10001000}
	, {0b10001100}
	, {0b10001010}
	, {0b10001000}
	, {0b10001000}
	, {0b10001000}
	, {0b10111110}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//pijl
	, {0b10001000}
	, {0b10011100}
	, {0b10111110}
	, {0b11111111}
	, {0b10011100}
	, {0b10011100}
	, {0b10011100}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//2
	, {0b10011100}
	, {0b10100010}
	, {0b10100000}
	, {0b10010000}
	, {0b10001000}
	, {0b10000100}
	, {0b10111110}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//pijl
	, {0b10001000}
	, {0b10011100}
	, {0b10111110}
	, {0b11111111}
	, {0b10011100}
	, {0b10011100}
	, {0b10011100}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//3
	, {0b10011100}
	, {0b10100010}
	, {0b10100000}
	, {0b10011000}
	, {0b10100000}
	, {0b10100010}
	, {0b10011100}


};
PATTERN_STRUCT liftdown[] = {
	//0
	  {0b10011100}
	, {0b10110110}
	, {0b10100010}
	, {0b10100010}
	, {0b10100010}
	, {0b10110110}
	, {0b10011100}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//pijl
	, {0b10011100}
	, {0b10011100}
	, {0b10011100}
	, {0b11111111}
	, {0b10111110}
	, {0b10011100}
	, {0b10001000}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//1
	, {0b10001000}
	, {0b10001100}
	, {0b10001010}
	, {0b10001000}
	, {0b10001000}
	, {0b10001000}
	, {0b10111110}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//pijl
	, {0b10011100}
	, {0b10011100}
	, {0b10011100}
	, {0b11111111}
	, {0b10111110}
	, {0b10011100}
	, {0b10001000}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//2
	, {0b10011100}
	, {0b10100010}
	, {0b10100000}
	, {0b10010000}
	, {0b10001000}
	, {0b10000100}
	, {0b10111110}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//pijl
	, {0b10011100}
	, {0b10011100}
	, {0b10011100}
	, {0b11111111}
	, {0b10111110}
	, {0b10011100}
	, {0b10001000}
	//tussenstukje
	, {0b10000000}
	, {0b10000000}
	//3
	, {0b10011100}
	, {0b10100010}
	, {0b10100000}
	, {0b10011000}
	, {0b10100000}
	, {0b10100010}
	, {0b10011100}


};
PATTERN_STRUCT smileys[] = {
	//smileyblij
	  {30}, {33}, {210}, {192}, {210}, {204}, {33}, {30}
	//smiley neutraal
	, {30} , {33}  , {210}  , {192}  , {222}  , {192}  , {33} , {30}

	//smiley niet blij
	, {30} 	, {33}	, {210}	, {192}	, {204}	, {210}	, {33}	, {30}


};
PATTERN_STRUCT scrollingRow1[] = {
	 /*N*/{1},{0},{0},{0},{1}, /* */{0},{0}, /*E*/ {1},{1},{1},{1},{1}, /* */{0},{0},/*R*/{1},{1},{1},{1},{0}, /* */{0},{0}, /*D*/{1},{1},{1},{0},{0}, /* */{0},{0}, /*S*/{0},{1},{1},{1},{0}, /* */{0},{0},{0},{0}, /*A*/{0},{1},{1},{1},{0}, /* */{0},{0}, /*R*/{1},{1},{1},{1},{0}, /* */{0},{0}, /*E*/{1},{1},{1},{1},{1}, /* */{0},{0},{0},{0}, /*T*/{1},{1},{1},{1},{1},
	 /* */{0},{0}, /*H*/{1},{0},{0},{0},{0}, /* */{0},{0}, /*E*/{1},{1},{1},{1},{1},/* */{0},{0},{0},{0}, /*N*/{1},{0},{0},{0},{1}, /* */{0},{0}, /*E*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*W*/{1},{0},{0},{0},{1}, /* */{0},{0},{0},{0}, /*C*/{0},{0},{1},{1},{1}, /* */{0},{0}, /*O*/{0},{1},{1},{1},{0}, /* */{0},{0}, /*O*/{0},{1},{1},{1},{0}, /* */{0},{0},/*L*/{1},{0},{0},{0},{0},
};
PATTERN_STRUCT scrollingRow2[] = {
	/*N*/{1},{0},{0},{0},{1}, /* */{0},{0}, /*E*/ {1},{1},{1},{1},{1}, /* */{0},{0},/*R*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*D*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*S*/{1},{1},{1},{1},{1}, /* */{0},{0},{0},{0}, /*A*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*R*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*E*/{1},{1},{1},{1},{1}, /* */{0},{0},{0},{0}, /*T*/{1},{1},{1},{1},{1},
	/* */{0},{0}, /*H*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*E*/{1},{1},{1},{1},{1},/* */{0},{0},{0},{0}, /*N*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*E*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*W*/{1},{1},{1},{1},{1}, /* */{0},{0},{0},{0}, /*C*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*O*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*O*/{1},{1},{1},{1},{1}, /* */{0},{0},/*L*/{1},{1},{1},{1},{1},
};
PATTERN_STRUCT scrollingRow3[] = {
	/*N*/{1},{0},{0},{0},{1}, /* */{0},{0}, /*E*/ {1},{1},{1},{1},{1}, /* */{0},{0},/*R*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*D*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*S*/{1},{1},{1},{1},{1}, /* */{0},{0},{0},{0}, /*A*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*R*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*E*/{1},{1},{1},{1},{1}, /* */{0},{0},{0},{0}, /*T*/{1},{1},{1},{1},{1},
	/* */{0},{0}, /*H*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*E*/{1},{1},{1},{1},{1},/* */{0},{0},{0},{0}, /*N*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*E*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*W*/{1},{1},{1},{1},{1}, /* */{0},{0},{0},{0}, /*C*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*O*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*O*/{1},{1},{1},{1},{1}, /* */{0},{0},/*L*/{1},{1},{1},{1},{1},
};
PATTERN_STRUCT scrollingRow4[] = {
	/*N*/{1},{0},{0},{0},{1}, /* */{0},{0}, /*E*/ {1},{1},{1},{1},{1}, /* */{0},{0},/*R*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*D*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*S*/{1},{1},{1},{1},{1}, /* */{0},{0},{0},{0}, /*A*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*R*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*E*/{1},{1},{1},{1},{1}, /* */{0},{0},{0},{0}, /*T*/{1},{1},{1},{1},{1},
	/* */{0},{0}, /*H*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*E*/{1},{1},{1},{1},{1},/* */{0},{0},{0},{0}, /*N*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*E*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*W*/{1},{1},{1},{1},{1}, /* */{0},{0},{0},{0}, /*C*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*O*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*O*/{1},{1},{1},{1},{1}, /* */{0},{0},/*L*/{1},{1},{1},{1},{1},
};
PATTERN_STRUCT scrollingRow5[] = {
	/*N*/{1},{0},{0},{0},{1}, /* */{0},{0}, /*E*/ {1},{1},{1},{1},{1}, /* */{0},{0},/*R*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*D*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*S*/{1},{1},{1},{1},{1}, /* */{0},{0},{0},{0}, /*A*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*R*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*E*/{1},{1},{1},{1},{1}, /* */{0},{0},{0},{0}, /*T*/{1},{1},{1},{1},{1},
	/* */{0},{0}, /*H*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*E*/{1},{1},{1},{1},{1},/* */{0},{0},{0},{0}, /*N*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*E*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*W*/{1},{1},{1},{1},{1}, /* */{0},{0},{0},{0}, /*C*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*O*/{1},{1},{1},{1},{1}, /* */{0},{0}, /*O*/{1},{1},{1},{1},{1}, /* */{0},{0},/*L*/{1},{1},{1},{1},{1},
};
void smileyblij(void){
int x = 0;
for (int adres = 0; adres <= 14; adres += 2)
{
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(adres);	// Address
	twi_tx(smileys[x].data);	// data
	twi_stop();
	x++;
}

}
void smileyneut(void){
	int x = 8;
	for (int adres = 0; adres <= 14; adres += 2)
	{
		twi_start();
		twi_tx(0xE0);	// Display I2C addres + R/W bit
		twi_tx(adres);	// Address
		twi_tx(smileys[x].data);	// data
		twi_stop();
		x++;
	}

}
void smileyniet(void){
	int x = 16;
	for (int adres = 0; adres <= 14; adres += 2)
	{
		twi_start();
		twi_tx(0xE0);	// Display I2C addres + R/W bit
		twi_tx(adres);	// Address
		twi_tx(smileys[x].data);	// data
		twi_stop();
		x++;
	}

}
void gobeep(void){
	while(beep == 1){
	buttoncheck();
	PORTA = 0xff;
	wait(50);
	PORTA = 0x00;
	wait(48);
	}

}
void numbercheck(void){
switch (check)
{
	case 1111:
	running = 1;
	runningstate = 1;
	check = 0;
	LiftStart();
	break;
	default:
	check = 0;
	break;
	case 2222:
	running = 1;
	runningstate = 2;
	check = 0;
	smileyblij();
	break;
}

}
void buttoncheck(){
if (PINF == 0b00000001)
{
	switch (runningstate)
	{
		case 1:
			running = 0;
			runningstate= 0;
			clearmatrix();
		break;
		case 2:
			running = 0;
			runningstate = 0;
			beep = 0;
			clearmatrix();
		break;
		case 3:
		running = 0;
		runningstate = 0;
		clearmatrix();
		break;

	}
}
else{
	if (PINF == 0b00000010)
	{
	 switch (runningstate)
	 {
		 case 0:

		 if(check < 1000 && check > 100)
		 {
			 check+= 1000;
			  numbercheck();
			  wait(1000);
		 }
		 if(check < 100 && check > 10)
		 {
			 check+= 100;
		 }
		 if(check < 10 && check > 0)
		 {
			 check+= 10;
		 }
		 if (check == 0)
		 {
			 check += 1;
		 }
		 display_nummer(check);
		 break;
		 case 1:
		 if (place == 0){
			 running = 0;
			 runningstate= 0;
			 clearmatrix();
		 }
		 if (place > 0)
		 {
		 wait(500);
		 clear();
		 Liftdown(0);
		 }
		 break;
		 case 2:
	     beep = 0;
		 smileyneut();
		 break;
	}
	}
	else{

			if (PINF == 0b00000100){
			 switch (runningstate)
			 {
				 case 0:
				if(check < 1000 && check > 100)
				{
					check+= 2000;
					numbercheck();
					wait(1000);
				}
				if(check < 100 && check > 10)
				{
					check+= 200;
				}
				if(check < 10 && check > 0)
				{
					check+= 20;
				}
				if (check == 0)
				{
					
					check += 2;
				}
				display_nummer(check);
				 break;
				 case 1:
				 if (place > 17)
				 {
				 wait(500);
				 Liftdown(17);
				 }
				 if (place < 17){
				 wait(500);
				 Liftup(17);
				 }
				 break;
				 case 2:
				 beep = 0;
				 smileyblij();

				 break;
			}}
			else{
				if (PINF == 0b00001000){
				 switch (runningstate)
				 {
					 case 0:
					 
						 
					 
					 if(check < 1000 && check > 100)
					 {
						 check+= 3000;
						 numbercheck();
						 wait(1000);
					 }
					 if(check < 100 && check > 10)
					 {
						 check+= 300;
					 }
					 if(check < 10 && check > 0)
					 {
						 check+= 30;
					 }
					 if (check == 0)
					 {
						
						 check += 3;
					 }
					  display_nummer(check);
					 break;
					 case 1:
					 if (place > 35)
					 {
					 wait(500);
						 Liftdown(35);
					 }
					 if (place < 35){
						 wait(500);
						 Liftup(35);
					 }
					 break;
					 case 2:
					 smileyniet();
					 beep = 1;
					 gobeep();
					 break;
				}}
				else{
					if (PINF == 0b00010000){
					switch (runningstate)
					{

						case 0:
						
							
							
							if(check < 1000 && check > 100)
							{
								check+= 4000;
								numbercheck();
								wait(1000);
							}
							if(check < 100 && check > 10)
							{
								check+= 400;
							}
							if(check < 10 && check > 0)
							{
								check+= 40;
							}
							if (check == 0)
							{
								display_nummer(check);
								check += 4;
							}
							
						 display_nummer(check);
						break;
						case 1:
						if (place > 53)
						{
							wait(500);
							Liftdown(53);
						}
						if (place < 53){
							wait(500);
							Liftup(53);
						}
						break;
						case 2:
						break;
					}
					}
				}
			}
	}
}
}
void LiftStart(void){
int x = 0;
for (int adres = 0; adres <= 14; adres += 2)
{
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(adres);	// Address
	twi_tx(liftup[x].data);	// data
	twi_stop();
	x++;
}
}
void clearmatrix(void){
for (int adres = 0; adres <= 14; adres += 2)
{
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(adres);	// Address
	twi_tx(0);	// data
	twi_stop();
}
}
void Liftup(int desti){
	for (place; place <= desti; place++)
	{
	int x = place;
		for (int adres = 0; adres <= 14; adres += 2)
		{
			twi_start();
			twi_tx(0xE0);	// Display I2C addres + R/W bit
			twi_tx(adres);	// Address
			twi_tx(liftup[x].data);	// data
			twi_stop();
			x++;
		}
		wait(1250);
	}
	}

void Liftdown(int desti){
	for (place; place >= desti; place--)
	{
		int x=place;
		for (int adres = 0; adres <= 14; adres += 2)
		{
			twi_start();
			twi_tx(0xE0);	// Display I2C addres + R/W bit
			twi_tx(adres);	// Address
			twi_tx(liftdown[x].data);	// data
			twi_stop();
			x++;
		}
		wait(1250);
	}
}



void initall(){
	init();
	spi_masterInit(); // Initialize spi module
	displayDriverInit(); // Initialize display chip
	twi_init();		// Init TWI interface

	// Init HT16K22.
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(0x21);	// Internal osc on
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xA0);	// HT16K33 pins all output
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xE3);	// Display Dimming 4/16 duty cycle
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0x81);	// Display OFF - Blink On
	twi_stop();
}

int main( void )
{
	DDRD = 0b11111111;
	DDRC = 0xFF;
	DDRB=0x01; // Set PB0 pin as output for display select
	initall();
	

	while (1)
	{
	buttoncheck();

	}

	return 1;
}





void wait( int ms )
{
	for (int sms=0; sms<ms; sms++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void twi_init(void)
{
	TWSR = 0;
	TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
}

void twi_start(void)
{
	TWCR = (0x80 | 0x20 | 0x04);
	while( 0x00 == (TWCR & 0x80) );
}

void twi_stop(void)
{
	TWCR = (0x80 | 0x10 | 0x04);
}

void twi_tx(unsigned char data)
{
	TWDR = data;
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
}

