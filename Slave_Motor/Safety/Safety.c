/*
 * Safety.c
 *
 * Created: 2014/07/26 13:35:52
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include "../globalDef.h"
#include "../Led/Led.h"
#include "./Safety.h"

void SafetyInitialize(void){
	// Power
	cbi(DDRA, PA0);
	sbi(PORTA, PA0);
	
	// Timer
	TCCR3A = 0x00;
	TCCR3B = 0x02;
	ETIMSK = 0x04;
	TCNT3 = 0;
}

bool PowerCheck(void){
	if(!bit_is_set(PINA, PA0)){
		LedDrive(1, true);
		return false;
	}
	else{
		LedDrive(1, false);
		return true;
	}
}
