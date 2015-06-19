/*
 * main.c
 *
 * Created: 2014/06/21 15:08:29
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "./globalDef.h"
#include "./RS485/RS485.h"
#include "./Switch/Switch.h"
#include "./Led/Led.h"
#include "./Air/Air.h"

int main(void){
	cli();
	SwitchInitialize();
	LedInitialize();
	SafetyInitialize();
	AirInitialize();
	RS485Initialize(12);
	sei();
	while(1){
		AirUpdate();
	}
}