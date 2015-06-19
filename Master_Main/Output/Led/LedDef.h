/*
 * LedDef.h
 *
 * Created: 2014/06/19 17:55:23
 *  Author: tatsuro
 */ 


#ifndef LEDDEF_H_
#define LEDDEF_H_

#include <avr/io.h>
#include <stdbool.h>
#include "../../globalDef.h"

#define LED_ON	(0x01)
#define LED_OFF	(0x00)

extern volatile bool LedArray[USING_LED];
extern void (*Led4bitPack[5])(uint8_t value);

extern void LedInitialize(void);
extern void LedUpdate(void);

#endif /* LEDDEF_H_ */