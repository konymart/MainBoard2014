/*
 * RS485.c
 *
 * Created: 2014/06/21 10:09:18
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../globalDef.h"
#include "../Uart/Uart.h"
#include "./RS485.h"

void RS485Initialize(uint8_t baud){
	UartInitialize(UART_RE | UART_TE | UART_RXCIE, baud);
	sbi(DDRD, PD4);
	
	RS485_Select(RS485_RE);
}

void RS485_putchar(uint8_t data){
	cli();
	RS485_Select(RS485_SE);
	uart_putchar(data);
	RS485_Select(RS485_RE);
	sei();
}

void RS485_getchar(uint8_t *data){
	cli();
	RS485_Select(RS485_RE);
	uart_getchar(data);
	sei();
}

static void RS485_Select(uint8_t option){
	if(option)		sbi(PORTD, PD4);
	else			cbi(PORTD, PD4);
}
