/*
 * Switch.c
 *
 * Created: 2014/06/21 10:25:11
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "../globalDef.h"
#include "./Switch.h"

#define DIP0	0x01
#define DIP1	0x02
#define DIP2	0x04
#define DIP3	0x08

void SwitchInitialize(void){
	cbi(DDRF, PF3);
	sbi(PORTF, PF3);
	cbi(DDRF, PF2);
	sbi(PORTF, PF2);
	cbi(DDRF, PF1);
	sbi(PORTF, PF1);
	cbi(DDRF, PF0);
	sbi(PORTF, PF0);
}

uint8_t GetDipSwitchStatus(void){
	uint8_t result = 0x00;
	
	if(!bit_is_set(PINF, PF0)){
		result |= DIP0;
	}		
	if(!bit_is_set(PINF, PF1)){
		result |= DIP1;
	}		
	if(!bit_is_set(PINF, PF2)){
		result |= DIP2;
	}
	if(!bit_is_set(PINF, PF3)){
		result |= DIP3;
	}		
	
	return result;
}