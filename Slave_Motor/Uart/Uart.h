/*
 * Uart.h
 *
 * Created: 2014/07/26 13:34:12
 *  Author: tatsuro
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

#define UART_RE		(0x10)
#define UART_TE		(0x08)
#define UART_TXCIE	(0x40)
#define UART_UDRIE	(0x20)
#define UART_RXCIE	(0x80)

void UartInitialize(uint8_t option, uint8_t baudrate);
void uart_putchar(uint8_t data);
void uart_getchar(uint8_t *data);

#endif /* UART_H_ */