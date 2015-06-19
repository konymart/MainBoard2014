/*
 * Safety.c
 *
 * Created: 2014/06/21 11:50:57
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include "../globalDef.h"
#include "../Led/Led.h"
#include "./Safety.h"

void SafetyInitialize(void){	
	// Timer
	TCCR3A = 0x00;
	TCCR3B = 0x02;
	ETIMSK = 0x04;
	TCNT3 = 0;
}
