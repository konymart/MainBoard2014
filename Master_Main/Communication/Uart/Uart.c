/*
 * Uart.c
 *
 * Created: 2014/06/17 20:28:00
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include "../../globalDef.h"

#if (defined(USE_UART) || defined(USE_MU))

#include "./Uart.h"
#include "./UartDef.h"

void (*UartInitialize[4])(uint8_t option, uint16_t baudrate);
void (*UartSend[4])(uint8_t sendData);
void (*UartReceive[4])(uint8_t* receiveData);

void UartSetup(void) {
	#if (defined(UDR0) || defined(UDR))
		UartInitialize[0] = UartInitialize0;
		UartSend[0] = UartSend0;
		UartReceive[0] = UartReceive0;
	#endif
	#if defined(UDR1)
		UartInitialize[1] = UartInitialize1;
		UartSend[1] = UartSend1;
		UartReceive[1] = UartReceive1;
	#endif
	#if defined(UDR2)
		UartInitialize[2] = UartInitialize2;
		UartSend[2] = UartSend2;
		UartReceive[2] = UartReceive2;
	#endif
	#if defined(UDR3)
		UartInitialize[3] = UartInitialize3;
		UartSend[3] = UartSend3;
		UartReceive[3] = UartReceive3;
	#endif
}

#if (defined(UDR0) || defined(UDR))
static void UartInitialize0(uint8_t option, uint16_t baudrate) {
	#ifndef SIMULATION_MODE
		uint16_t loop;
	#endif
	
	sbi(*USART.U0.UCASRA, U2X0_BIT);
	
	*USART.U0.UCASRB = 0x00;
	*USART.U0.UCASRC = (1<<UCSZ01_BIT) | (1<<UCSZ00_BIT);

	#ifndef SIMULATION_MODE
		for(loop=0; loop<5000; loop++);
	#endif
	
	*USART.U0.UCASRA &= 0xE3;
	*USART.U0.UCASRB = option;
	
	*USART.U0.UBRREGH = (uint8_t)(baudrate>>8);
	*USART.U0.UBRREGL = (uint8_t)(baudrate);
}
#endif

#if defined(UDR1)
static void UartInitialize1(uint8_t option, uint16_t baudrate) {
	#ifndef SIMULATION_MODE
		uint16_t loop;
	#endif
	
	sbi(*USART.U1.UCASRA, U2X1_BIT);
	
	*USART.U1.UCASRB = 0x00;
	*USART.U1.UCASRC = (1<<UCSZ11_BIT) | (1<<UCSZ10_BIT);

	#ifndef SIMULATION_MODE
		for(loop=0; loop<5000; loop++);
	#endif
	
	cbi(*USART.U1.UCASRA, FE1_BIT);
	cbi(*USART.U1.UCASRA, DOR1_BIT);
	cbi(*USART.U1.UCASRA, UPE1_BIT);
	*USART.U1.UCASRB = option;
	
	*USART.U1.UBRREGH = (uint8_t)(baudrate>>8);
	*USART.U1.UBRREGL = (uint8_t)(baudrate);
}
#endif

#if defined(UDR2)
static void UartInitialize2(uint8_t option, uint16_t baudrate) {
	#ifndef SIMULATION_MODE
		uint16_t loop;
	#endif
	
	sbi(*USART.U2.UCASRA, U2X2_BIT);
	
	*USART.U2.UCASRB = 0x00;
	*USART.U2.UCASRC = (1<<UCSZ21_BIT) | (1<<UCSZ20_BIT);

	#ifndef SIMULATION_MODE
		for(loop=0; loop<5000; loop++);
	#endif
	
	cbi(*USART.U2.UCASRA, FE2_BIT);
	cbi(*USART.U2.UCASRA, DOR2_BIT);
	cbi(*USART.U2.UCASRA, UPE2_BIT);
	*USART.U2.UCASRB = option;
	
	*USART.U2.UBRREGH = (uint8_t)(baudrate>>8);
	*USART.U2.UBRREGL = (uint8_t)(baudrate);
}
#endif

#if defined(UDR3)
static void UartInitialize3(uint8_t option, uint16_t baudrate) {
	#ifndef SIMULATION_MODE
		uint16_t loop;
	#endif
	
	sbi(*USART.U3.UCASRA, U2X3_BIT);
	
	*USART.U3.UCASRB = 0x00;
	*USART.U3.UCASRC = (1<<UCSZ31_BIT) | (1<<UCSZ30_BIT);

	#ifndef SIMULATION_MODE
		for(loop=0; loop<5000; loop++);
	#endif
	
	*USART.U3.UCASRA &= 0xE3;
	*USART.U3.UCASRB = option;
	
	*USART.U3.UBRREGH = (uint8_t)(baudrate>>8);
	*USART.U3.UBRREGL = (uint8_t)(baudrate);
}
#endif

#if (defined(UDR0) || defined(UDR))
static void UartSend0(uint8_t sendData) {
	#ifndef SIMULATION_MODE
		uint16_t loop;
	#endif

	while( !bit_is_set(*USART.U0.UCASRA, UDRE0_BIT) );
	*USART.U0.UDREG = sendData;
	cbi(*USART.U0.UCASRA, UDRE0_BIT);

	#ifndef SIMULATION_MODE
		for(loop=0; loop<1000; loop++);
	#endif
}
#endif

#if defined(UDR1)
static void UartSend1(uint8_t sendData) {
	#ifndef SIMULATION_MODE
		uint16_t loop;
	#endif

	#ifndef SIMULATION_MODE
		while( !bit_is_set(*USART.U1.UCASRA, UDRE1_BIT) );
	#endif
	*USART.U1.UDREG = sendData;
	cbi(*USART.U1.UCASRA, UDRE1_BIT);

	#ifndef SIMULATION_MODE
		for(loop=0; loop<1000; loop++);
	#endif
}
#endif

#if defined(UDR2)
static void UartSend2(uint8_t sendData) {
	#ifndef SIMULATION_MODE
		uint16_t loop;
	#endif

	#ifndef SIMULATION_MODE
		while( !bit_is_set(*USART.U2.UCASRA, UDRE2_BIT) );
	#endif
	*USART.U2.UDREG = sendData;
	cbi(*USART.U2.UCASRA, UDRE2_BIT);

	#ifndef SIMULATION_MODE
		for(loop=0; loop<1000; loop++);
	#endif
}
#endif

#if defined(UDR3)
static void UartSend3(uint8_t sendData) {
	#ifndef SIMULATION_MODE
		uint16_t loop;
	#endif

	#ifndef SIMULATION_MODE
		while( !bit_is_set(*USART.U3.UCASRA, UDRE3_BIT) );
	#endif
	*USART.U3.UDREG = sendData;
	cbi(*USART.U3.UCASRA, UDRE3_BIT);

	#ifndef SIMULATION_MODE
		for(loop=0; loop<1000; loop++);
	#endif
}
#endif

#if (defined(UDR0) || defined(UDR))
static void UartReceive0(uint8_t* receiveData) {
	#ifndef SIMULATION_MODE
		uint16_t loop;
	#endif
	
	#ifndef SIMULATION_MODE
		while( !bit_is_set(*USART.U0.UCASRA, RXC0_BIT));
	#endif
	cbi(*USART.U0.UCASRA, RXC0_BIT);
	*receiveData = *USART.U0.UDREG;	
	
	#ifndef SIMULATION_MODE
		for(loop=0; loop<1000; loop++);
	#endif
}
#endif

#if defined(UDR1)
static void UartReceive1(uint8_t* receiveData) {
	#ifndef SIMULATION_MODE
		uint16_t loop;
	#endif
	
	#ifndef SIMULATION_MODE
		while( !bit_is_set(*USART.U1.UCASRA, RXC1_BIT));
	#endif
	cbi(*USART.U1.UCASRA, RXC1_BIT);
	*receiveData = *USART.U1.UDREG;

	#ifndef SIMULATION_MODE
		for(loop=0; loop<1000; loop++);
	#endif
}
#endif

#if defined(UDR2)
static void UartReceive2(uint8_t* receiveData) {
	#ifndef SIMULATION_MODE
		uint16_t loop;
	#endif
	
	#ifndef SIMULATION_MODE
		while( !bit_is_set(*USART.U2.UCASRA, RXC2_BIT));
	#endif
	cbi(*USART.U2.UCASRA, RXC2_BIT);
	*receiveData = *USART.U2.UDREG;	
	
	#ifndef SIMULATION_MODE
		for(loop=0; loop<1000; loop++);
	#endif
}
#endif

#if defined(UDR3)
static void UartReceive3(uint8_t* receiveData) {
	#ifndef SIMULATION_MODE
		uint16_t loop;
	#endif
	
	#ifndef SIMULATION_MODE
		while( !bit_is_set(*USART.U3.UCASRA, RXC3_BIT));
	#endif
	cbi(*USART.U3.UCASRA, RXC3_BIT);
	*receiveData = *USART.U3.UDREG;	
	
	#ifndef SIMULATION_MODE
		for(loop=0; loop<1000; loop++);
	#endif
}
#endif

#endif

