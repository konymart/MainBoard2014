/*
 * main.c
 *
 * Created: 2014/06/21 10:07:19
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "./globalDef.h"
#include "./RS485/RS485.h"
#include "./Switch/Switch.h"
#include "./Led/Led.h"
#include "./Safety/Safety.h"
#include "./Output/Output.h"

int main(void){
	uint8_t i;
	cli();
	SwitchInitialize();
	LedInitialize();
	OutputInitialize();
	SafetyInitialize();
	RS485Initialize(12);
	sei();
	while(1){
		OutputUpdate();
	}
}
