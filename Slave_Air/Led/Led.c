/*
 * Led.c
 *
 * Created: 2014/06/21 10:10:01
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include "../globalDef.h"
#include "./Led.h"

io led[4] = {
	{(uint8_t*)&DDRA, (uint8_t*)&PORTA, PA7},
	{(uint8_t*)&DDRA, (uint8_t*)&PORTA, PA6},
	{(uint8_t*)&DDRA, (uint8_t*)&PORTA, PA5},
	{(uint8_t*)&DDRA, (uint8_t*)&PORTA, PA4}
};

void LedInitialize(void){
	volatile uint8_t i;
	
	for(i = 0; i < 4; i++){
		sbi(*led[i].ddr, led[i].bit);
		sbi(*led[i].port, led[i].bit);
	}
}

void LedDrive(uint8_t no, bool select){
	if(select)		cbi(*led[no].port, led[no].bit);
	else			sbi(*led[no].port, led[no].bit);
}
