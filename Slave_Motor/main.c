/*
 * Slave_Motor.c
 *
 * Created: 2014/07/26 13:30:08
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "./globalDef.h"
#include "./Led/Led.h"
#include "./Input/Input.h"
#include "./RS485/RS485.h"
#include "./Motor/Motor.h"
#include "./Safety/Safety.h"

int main(void){
	cli();
	LedInitialize();
	SwitchInitialize();
	ExInitialize();
	MotorInitialize();
	SafetyInitialize();
	RS485Initialize(12);
	
	while(1){
		sei();
		MotorDrive();
	}
}