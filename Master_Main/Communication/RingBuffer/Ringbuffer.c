/*
 * Ringbuffer.c
 *
 * Created: 2014/07/30 9:36:27
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../globalDef.h"
#include "../Uart/UartDef.h"
#include "./RingBufferDef.h"

#if defined(USE_RS485)

// Initialize for RingBuffer
void RingBufferInitialize(Uart_Ring_Type *buffer){
	uint16_t i;
	
	buffer->head = 0;
	buffer->size = 0;
	buffer->status = Empty;
	
	for(i = 0; i < BUFFER_SIZE; i++){
		buffer->buf[i] = 0x00;
	}
}

// Output the Data from RingbBuffer 
// If RingBuffer UnderFlow, Return 0, else Return 1 
uint8_t RingPutChar(unsigned char *data, Uart_Ring_Type *buffer){
	cli();
	if(buffer->size == 0){
		buffer->status = Empty;
		stop_uart1tx_interrupt();
		return 0;
	}
	
	*data = buffer->buf[buffer->head];
	buffer->buf[buffer->head] = 'A';
	buffer->size -= 1;
	buffer->head += 1;
	buffer->head %= BUFFER_SIZE;
	
	if (buffer->size == 0){
		buffer->status = Empty;
	}
	
	sei();
	return 1;
}

// Input the Data for RingBuffer
// If RingBuffer OverFlow, Return 0, else Return 1
uint8_t RingSetChar(unsigned char data, Uart_Ring_Type *buffer){
	cli();
	if(buffer->size >= BUFFER_SIZE){
		buffer->status = FullUp;
		return 0;
	}
	
	buffer->status = DataIn;
	buffer->buf[(buffer->head + buffer->size) % BUFFER_SIZE] = data;
	buffer->size += 1;
	
	if (buffer->size >= BUFFER_SIZE){
		buffer->status = FullUp;
	}
	BufferChecker(buffer);
	
	sei();
	
	return 1;
}

// Check for RingBuffer and UDRE_Empty_Interrupt Control
void BufferChecker(Uart_Ring_Type *buffer){
	if(buffer->status != Empty)	start_uart1tx_interrupt();
	else						stop_uart1tx_interrupt();
}	

#endif