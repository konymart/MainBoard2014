/*
 * RS485.h
 *
 * Created: 2014/07/26 13:35:29
 *  Author: tatsuro
 */ 


#ifndef RS485_H_
#define RS485_H_

// Include
#include <avr/io.h>

// Define
#define RS485_RE	(0x00)
#define RS485_SE	(0x01)

// Global
void RS485Initialize(uint8_t baud);
void RS485_putchar(uint8_t data);
void RS485_getchar(uint8_t *data);

// Static
static void RS485_Select(uint8_t option);

#endif /* RS485_H_ */