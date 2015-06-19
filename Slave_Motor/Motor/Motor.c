/*
 * Motor.c
 *
 * Created: 2014/07/26 13:37:09
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "./Motor.h"
#include "../RS485/RS485.h"
#include "../Led/Led.h"
#include "../Input/Input.h"
#include "../Safety/Safety.h"
#include "../globalDef.h"

Motor motor[4] = {
	{ { (uint8_t*)&DDRB,(uint8_t*)&PORTB, PB2 }, { (uint8_t*)&DDRB,(uint8_t*)&PORTB, PB3 }, { (uint8_t*)&DDRB, PB4, (uint8_t*)&OCR0 } },
	{ { (uint8_t*)&DDRG,(uint8_t*)&PORTG, PG3 }, { (uint8_t*)&DDRG,(uint8_t*)&PORTG, PG4 }, { (uint8_t*)&DDRB, PB5, (uint8_t*)&OCR1A } },
	{ { (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC0 }, { (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC1 }, { (uint8_t*)&DDRB, PB6, (uint8_t*)&OCR1B } },
	{ { (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC2 }, { (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC3 }, { (uint8_t*)&DDRB, PB7, (uint8_t*)&OCR1C } },
};

static volatile RS485_Motor MotorData;
static volatile uint8_t val;
static volatile uint8_t phase;
static volatile uint8_t count;
static volatile bool addrCheck = false;
static volatile char packet[24];
static volatile char check[] = "DR=";
static volatile bool StartCodeCheck = false;
static volatile bool EndCodeCheck = false;
static volatile bool LineStatus = NO_DATA_IN_LINE;
static volatile uint8_t timerCounter = 0;


static void RS485_DataInitialize(void){
	uint8_t i;
	for(i = 0; i < 4; i++){
		MotorData.data[i] = 0x00;
	}
}

static void m(uint8_t no, uint8_t select, uint8_t pwm){
	if(select & 0x01)	sbi(*motor[no].d1.port, motor[no].d1.bit);
	else				cbi(*motor[no].d1.port, motor[no].d1.bit);
	if(select & 0x02)	sbi(*motor[no].d2.port, motor[no].d2.bit);
	else				cbi(*motor[no].d2.port, motor[no].d2.bit);
	*motor[no].pwm.ocr = pwm;
}

static uint8_t AddressSetter(void){
	return (GetDipSwitchStatus() | 0x20);
}

void MotorInitialize(void){
	volatile uint8_t i;
	phase = 0;
	val = 0;
	count = 0;
	
	for(i = 0; i < 4; i++){
		sbi(*motor[i].d1.ddr, motor[i].d1.bit);
		sbi(*motor[i].d2.ddr, motor[i].d2.bit);
		
		sbi(*motor[i].pwm.ddr, motor[i].pwm.bit);
		
		MotorData.data[i] = 0x00;
	}
	
	MotorData.addr = AddressSetter();
	
	// Timer
	TCCR0 = 0x6C;
	
	TCCR1A = 0xA9;
	TCCR1B = 0x0B;
}

void MotorDrive(){
	volatile uint8_t i;
	
	cli();
	
	if(GetSwitchStatus(0) || GetSwitchStatus(1)){
		MotorData.data[0] |= 0xFF;
	}
	
	if(PowerCheck()){
		RS485_DataInitialize();
	}
	
	for(i = 0; i < 4; i++){
		m(i, MotorData.data[i], MotorData.data[i]);
	}
	
	sei();
}

ISR(USART1_RX_vect) {
	val = UDR1;
	
	if(phase == 1){
		if(addrCheck){
			if(val == MotorData.addr){
				phase = 2;
				count = 0;
			}
			else{
				phase = 0;
			}
			addrCheck = false;
		}
		else if(val == '@' && !addrCheck){
			addrCheck = true;
		}
	}		
	else if(phase == 2){
		packet[count] = val;
		if(count < 2){
			if(val != check[count]){
				phase = 0;
				LedDrive(0, false);
			}		
		}
		else if(count >= 6){
			MotorData.data[0] = packet[3];
			MotorData.data[1] = packet[4];
			MotorData.data[2] = packet[5];
			MotorData.data[3] = packet[6];
				
			phase = 0;
			timerCounter = 0;
			LedDrive(0, true);
		}
		count++;
	}
	
	if(StartCodeCheck){
		if(val == '$'){
			StartCodeCheck = false;
			phase = 1;
			count = 0;
			LineStatus = DATA_IN_LINE;
		}
	}
	else{
		if(val == '%'){
			StartCodeCheck = true;
		}
	}
	
	if(EndCodeCheck){
		if(val == '\n'){
			EndCodeCheck = false;
			LineStatus = NO_DATA_IN_LINE;
		}
	}
	else {
		if(val == '\r'){
			EndCodeCheck = true;
		}
	}
}

ISR(TIMER3_OVF_vect){
	timerCounter++;
	
	if(timerCounter > 10){
		timerCounter = 0;
		RS485_DataInitialize();
		LedDrive(0, false);
	}
}
