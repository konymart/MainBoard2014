/*
 * Uart.c
 *
 * Created: 2014/06/21 10:08:57
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include "../globalDef.h"

void UartInitialize(uint8_t option, uint8_t baudrate){
	uint16_t loop;
	sbi(UCSR1A, U2X1);
	
	UCSR1B = 0x00;
	UCSR1C = (1<<UCSZ11) | (1<<UCSZ10);
	
	for(loop=0; loop<5000; loop++);
	
	UCSR1A &= 0xE3;
	UCSR1B = option;
	
	UBRR1H = (uint8_t)(baudrate>>8);
	UBRR1L = (uint8_t)(baudrate);
}

void uart_putchar(uint8_t data){
	volatile uint16_t i;
	while(!bit_is_set(UCSR1A, UDRE1));
	UDR1 = data;
	
	cbi(UCSR1A, UDRE1);
	
	for(i = 0; i < 5000; i++);
}

void uart_getchar(uint8_t *data){
	while(!bit_is_set(UCSR1A, RXC1));
	*data = UDRE1;
	cbi(UCSR1A, RXC1);
}

