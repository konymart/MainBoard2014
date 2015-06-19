/*
 * Led.h
 *
 * Created: 2014/07/26 13:36:12
 *  Author: tatsuro
 */ 


#ifndef LED_H_
#define LED_H_

#include <avr/io.h>
#include <stdbool.h>

#define LED0	0
#define LED1	1
#define LED2	2
#define LED3	3

void LedInitialize(void);
void LedDrive(uint8_t no, bool select);

#endif /* LED_H_ */