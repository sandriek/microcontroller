#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "Spi.h"

#define F_CPU 8000000;

static int check = 0;
static int running = 0;
static int runningstate = 0;
static int place = 0;
static int helpnumber = 0;
static int beep = 0;

typedef struct 
{
	unsigned char data;
} 
PATTERN_STRUCT;

PATTERN_STRUCT pacman[] = 
{
	//mond open
	{62}, {127}, {189}, {159}, {143}, {191}, {127}, {62},
	//mond 2/3 open
	{30}, {63}, {253}, {159}, {143}, {255}, {63}, {30},
	//mond 1/3 open
	{30}, {63}, {253}, {255}, {159}, {255}, {63}, {30},
	//mond dicht
	{30}, {63}, {253}, {255}, {255}, {255}, {63}, {30}
};

void PacmanAnimatie()
{
	for (int i = 0; i < 5; i ++)
	{
		switch (i)
		{
			case 0: 
				{
					int x = 0;
					for (int adres = 0; adres <= 14; adres += 2)
					{
						twi_start();
						twi_tx(0xE0);	// Display I2C addres + R/W bit
						twi_tx(adres);	// Address
						twi_tx(pacman[x].data);	// data
						twi_stop();
						x++;
					}
				}
			break;

			case 1:
			{
				int x = 8;
				for (int adres = 0; adres <= 14; adres += 2)
				{
					twi_start();
					twi_tx(0xE0);	// Display I2C addres + R/W bit
					twi_tx(adres);	// Address
					twi_tx(pacman[x].data);	// data
					twi_stop();
					x++;
				}
			}
			break;

			case 2:
			{
				int x = 16;
				for (int adres = 0; adres <= 14; adres += 2)
				{
					twi_start();
					twi_tx(0xE0);	// Display I2C addres + R/W bit
					twi_tx(adres);	// Address
					twi_tx(pacman[x].data);	// data
					twi_stop();
					x++;
				}
			}
			break;

			case 3:
			{
				int x = 24;
				for (int adres = 0; adres <= 14; adres += 2)
				{
					twi_start();
					twi_tx(0xE0);	// Display I2C addres + R/W bit
					twi_tx(adres);	// Address
					twi_tx(pacman[x].data);	// data
					twi_stop();
					x++;
				}
			}
			break;

			case 4:
			{
				int x = 16;
				for (int adres = 0; adres <= 14; adres += 2)
				{
					twi_start();
					twi_tx(0xE0);	// Display I2C addres + R/W bit
					twi_tx(adres);	// Address
					twi_tx(pacman[x].data);	// data
					twi_stop();
					x++;
				}
			}
			break;

			case 5:
			{
				int x = 8;
				for (int adres = 0; adres <= 14; adres += 2)
				{
					twi_start();
					twi_tx(0xE0);	// Display I2C addres + R/W bit
					twi_tx(adres);	// Address
					twi_tx(pacman[x].data);	// data
					twi_stop();
					x++;
				}
			}
			break;
		} 

		wait(500);
	}
}

void initall()
{
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

void main( void )
{
	DDRD = 0b11111111;
	DDRC = 0xFF;
	DDRB=0x01; // Set PB0 pin as output for display select
	initall();
	
	while (1)
	{
		PacmanAnimatie();
	}
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