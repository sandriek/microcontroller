/*
 * uart0.c
 *
 * Created: 15-3-2016 12:31:10
 *  Author: sander
 */ 
 #include <avr/io.h>
 #include <util/delay.h>
 #include <avr/interrupt.h>
 #define BIT(x) (1 << (x))
 #define UART0_BAUD 2400 // Baud rate USART0
 #define MYUBRR F_CPU/16/UART0_BAUD - 1 // My USART Baud Rate Register
 #define LF 0x0a
 #define CR	0x0d
 #define F_CPU 8000000
 void usart0_init( void )
 {
 int	ubrr = MYUBRR;
 UBRR0H = ubrr>>8;						// baudrate register, hoge byte
 UBRR0L = ubrr;							// baudrate register, lage byte
 UCSR0C = 0b00000110;					// asynchroon, 8 data - 1 stop - no parity
 UCSR0B = 0b00000000;					// receiver & transmitter enable
 }
 void usart0_start( void )
 {
 UCSR0B |= BIT(RXEN)|BIT(TXEN);
 }
 char uart0_receiveChar()
 {
 	while (!(UCSR0A & BIT(RXC0))) ;			// if RX0 is set: unread data present in buffer
 	return UDR0;
 }
 int uart0_receiveString( char* string)
 {
	 int stop = 0; // boolean for stop value
	 char ch;
	 while (!stop) // while contunie
	 {
		 ch = uart0_receiveChar(); // read ch
		 if ( ch == LF ) // stop at LF
		 stop = 1;
		 else
		 *string++ = ch; // else fill buffer
	 }
	 *string = '\0'; // string terminator
	 return 0;
 }
 int uart0_sendChar( char ch ) 
 {
 while (!(UCSR0A & BIT(UDRE0))) ;
 UDR0 = ch;
 return 0;
 }
