/*
 * RingBufferDef.h
 *
 * Created: 2014/07/30 9:37:02
 *  Author: tatsuro
 */ 


#ifndef RINGBUFFERDEF_H_
#define RINGBUFFERDEF_H_

#if defined(USE_RS485)

typedef enum{
	Empty,
	DataIn,
	FullUp	
}RingStatus;

typedef struct {
	unsigned char buf[BUFFER_SIZE];		// Buffer
	uint16_t head;						// Head Position
	uint16_t size;						// Current Data Size
	RingStatus status;					// Current Buffer Status
}Uart_Ring_Type; 

void RingBufferInitialize(Uart_Ring_Type *buffer);
uint8_t RingPutChar(unsigned char *data, Uart_Ring_Type *buffer);
uint8_t RingSetChar(unsigned char data, Uart_Ring_Type *buffer);
void BufferChecker(Uart_Ring_Type *buffer);

#endif

#endif /* RINGBUFFERDEF_H_ */