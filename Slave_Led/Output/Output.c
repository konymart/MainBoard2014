/*
 * Output.c
 *
 * Created: 2014/06/21 10:09:40
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "../globalDef.h"
#include "./Output.h"
#include "../RS485/RS485.h"
#include "../Safety/Safety.h"
#include "../Led/Led.h"

io Output[16] = { 
	{ (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC0 }, 
	{ (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC1 }, 
	{ (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC2 }, 
	{ (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC3 }, 
	{ (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC4 },
	{ (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC5 }, 
	{ (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC6 }, 
	{ (uint8_t*)&DDRC,(uint8_t*)&PORTC, PC7 }, 
	{ (uint8_t*)&DDRF,(uint8_t*)&PORTF, PF0 },
	{ (uint8_t*)&DDRF,(uint8_t*)&PORTF, PF1 }, 
	{ (uint8_t*)&DDRF,(uint8_t*)&PORTF, PF2 }, 
	{ (uint8_t*)&DDRF,(uint8_t*)&PORTF, PF3 },
	{ (uint8_t*)&DDRF,(uint8_t*)&PORTF, PF4 },
	{ (uint8_t*)&DDRF,(uint8_t*)&PORTF, PF5 }, 
	{ (uint8_t*)&DDRF,(uint8_t*)&PORTF, PF6 }, 
	{ (uint8_t*)&DDRF,(uint8_t*)&PORTF, PF7 }
};

static volatile RS485_Output OutputData;
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

void OutputInitialize(void){
	volatile uint8_t i;
	
	phase = 0;
	val = 0;
	count = 0;
	
	for(i = 0; i < 16; i++){
		sbi(*Output[i].ddr, Output[i].bit);
		sbi(*Output[i].port, Output[i].bit);
		
		OutputData.data[i] = 0x00;
	}
	OutputData.addr = AddressSetter();	
}

void OutputUpdate(void){
	volatile uint8_t i;
	
	cli();
	
	for(i = 0; i < 16; i++){
		if(OutputData.data[i >> 2] & (1 << (i%4)))		cbi(*Output[i].port, Output[i].bit);
		else											sbi(*Output[i].port, Output[i].bit);	
	}
	
	sei();
}

static uint8_t AddressSetter(){
	return (0x40 | GetDipSwitchStatus());
}

static void OutputDataInitialize(){
	volatile uint8_t i;
	
	for(i = 0; i < 16; i++){
		OutputData.data[i] = 0x00;
	}
}


ISR(USART1_RX_vect) {
	val = UDR1;
	
	if(phase == 1){
		if(addrCheck){
			if(val == OutputData.addr){
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
			OutputData.data[0] = packet[3];
			OutputData.data[1] = packet[4];
			OutputData.data[2] = packet[5];
			OutputData.data[3] = packet[6];
				
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
		OutputDataInitialize();
		LedDrive(0, false);
	}
}
