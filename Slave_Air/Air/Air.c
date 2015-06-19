/*
 * Air.c
 *
 * Created: 2014/06/21 15:10:53
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "../globalDef.h"
#include "./Air.h"
#include "../RS485/RS485.h"
#include "../Safety/Safety.h"
#include "../Led/Led.h"

io Air[8] = { 
	{ (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC0 }, 
	{ (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC1 }, 
	{ (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC2 }, 
	{ (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC3 }, 
	{ (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC4 },
	{ (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC5 }, 
	{ (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC6 }, 
	{ (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC7 }
};

static volatile RS485_Air AirData;
static volatile uint8_t val;
static volatile uint8_t phase;
static volatile uint8_t count;
static volatile bool addrCheck = false;
static volatile char packet[10];
static volatile char check[] = "DR=";
static volatile char StartCode[] = "%$";
static volatile bool StartCodeCheck = false;
static volatile char EndCode[] = "\r\n";
static volatile bool EndCodeCheck = false;
static volatile bool LineStatus = NO_DATA_IN_LINE;

static volatile uint8_t timerCounter = 0;

void AirInitialize(void){
	volatile uint8_t i;
	
	phase = 0;
	val = 0;
	count = 0;
	
	for(i = 0; i < 8; i++){
		sbi(*Air[i].ddr, Air[i].bit);
		sbi(*Air[i].port, Air[i].bit);
		
	}
	AirData.data = 0x00;
	AirData.addr = AddressSetter();	
}

void AirUpdate(void){
	volatile uint8_t i;
	
	cli();
	
	if(PowerCheck()){
		AirDataInitialize();
	}
	
	for(i = 0; i < 8; i++){
		if(AirData.data & (1 << i))		cbi(*Air[i].port, Air[i].bit);
		else							sbi(*Air[i].port, Air[i].bit);	
	}
	
	sei();
}

static uint8_t AddressSetter(){
	return (0x80 | GetDipSwitchStatus());
}

static void AirDataInitialize(){	
	AirData.data = 0x00;
}


ISR(USART1_RX_vect) {
	val = UDR1;
	
	if(phase == 1){
		if(addrCheck){
			if(val == AirData.addr){
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
		else if(count >= 3){
			AirData.data = packet[3];
				
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
		AirDataInitialize();
		LedDrive(0, false);
	}
}