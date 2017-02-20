/*
 * UART.c
 *
 * Created: 21/02/2017 0:55:08
 * Author : Anggara Wijaya
 */ 
#define F_CPU 8000000UL

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "uart.h"

#define UART_BAUD_RATE      9600      


int main(void)
{
    unsigned int c;
    char buffer[7];
    int  num=134;
	
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); 
    sei();
    uart_puts("String stored in SRAM\n");
    uart_puts_P("String stored in FLASH\n");   
    itoa( num, buffer, 10);        
    uart_puts(buffer);
    uart_putc('\r');
    
    for(;;)
    {
        c = uart_getc();
        if ( c & UART_NO_DATA )
        {
        }
        else
        {
            if ( c & UART_FRAME_ERROR )
            {
                uart_puts_P("UART Frame Error: ");
            }
            if ( c & UART_OVERRUN_ERROR )
            {
                uart_puts_P("UART Overrun Error: ");
            }
            if ( c & UART_BUFFER_OVERFLOW )
            {
                uart_puts_P("Buffer overflow error: ");
            }
            uart_putc( (unsigned char)c );
        }
    }
    
}