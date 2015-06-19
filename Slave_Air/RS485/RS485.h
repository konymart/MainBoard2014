/*
 * RS485.h
 *
 * Created: 2014/06/21 10:09:29
 *  Author: tatsuro
 */ 


#ifndef RS485_H_
#define RS485_H_

#include <avr/io.h>

#define RS485_RE	(0x00)
#define RS485_SE	(0x01)

static void RS485_Select(uint8_t option);
void RS485Initialize(uint8_t baud);
void RS485_putchar(uint8_t data);
void RS485_getchar(uint8_t *data);

#endif /* RS485_H_ */