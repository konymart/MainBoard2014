/*
 * Input.c
 *
 * Created: 2014/07/26 13:36:38
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "../globalDef.h"
#include "./Input.h"

// SW

#define DIP0	0x01
#define DIP1	0x02
#define DIP2	0x04
#define DIP3	0x08

void SwitchInitialize(void){
	// Limit SW
	cbi(DDRF, PF7);
	sbi(PORTF, PF7);
	cbi(DDRF, PF6);
	sbi(PORTF, PF6);
	
	// Dip SW
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
	
	if(!bit_is_set(PINF, PF3)){
		result |= DIP0;
	}		
	if(!bit_is_set(PINF, PF2)){
		result |= DIP1;
	}		
	if(!bit_is_set(PINF, PF1)){
		result |= DIP2;
	}
	if(!bit_is_set(PINF, PF0)){
		result |= DIP3;
	}		
	
	return result;
}

bool GetSwitchStatus(uint8_t no){
	switch(no){
	case 0:
		if(!bit_is_set(PINF, PF6))	return true;
		else						return false;
		break;
	case 1:
		if(!bit_is_set(PINF, PF7))	return true;
		else						return false;		
		break;
	default:
		return false;
		break;
	}
}


// EX

void ExInitialize(void){
	cbi(DDRD, PD0);
	sbi(PORTD, PD0);
	sbi(EIMSK, INT0);
	sbi(EICRA, ISC01);
	cbi(EICRA, ISC00);
	
	cbi(DDRD, PD1);
	sbi(PORTD, PD1);
	sbi(EIMSK, INT1);
	sbi(EICRA, ISC11);
	cbi(EICRA, ISC10);
}

ISR(INT0_vect){
	
}

ISR(INT1_vect){
	
}