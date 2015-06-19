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
	cbi(DDRB, PB4);
	sbi(PORTB, PB4);
	cbi(DDRB, PB5);
	sbi(PORTB, PB5);
	cbi(DDRB, PB6);
	sbi(PORTB, PB6);
	cbi(DDRB, PB7);
	sbi(PORTB, PB7);
}

uint8_t GetDipSwitchStatus(void){
	uint8_t result = 0x00;
	
	if(!bit_is_set(PINB, PB4)){
		result |= DIP0;
	}		
	if(!bit_is_set(PINB, PB5)){
		result |= DIP1;
	}		
	if(!bit_is_set(PINB, PB6)){
		result |= DIP2;
	}
	if(!bit_is_set(PINB, PB7)){
		result |= DIP3;
	}		
	
	return result;
}