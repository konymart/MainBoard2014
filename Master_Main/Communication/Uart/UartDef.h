/*
 * UartDef.h
 *
 * Created: 2014/06/17 20:28:35
 *  Author: tatsuro
 */ 


#ifndef UARTDEF_H_
#define UARTDEF_H_

#include "../../globalDef.h"

#define UART_RE		(0x10)
#define UART_TE		(0x08)
#define UART_TXCIE	(0x40)
#define UART_UDRIE	(0x20)
#define UART_RXCIE	(0x80)

#define start_uart1tx_interrupt()	sbi(UCSR1B,UDRIE1)
#define stop_uart1tx_interrupt()	cbi(UCSR1B,UDRIE1)

extern void UartSetup(void);
extern void (*UartInitialize[4])(uint8_t option, uint16_t baudrate);
extern void (*UartSend[4])(uint8_t sendData);
extern void (*UartReceive[4])(uint8_t* receiveData);


#endif /* UARTDEF_H_ */