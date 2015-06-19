/*
 * main.c
 *
 * Created: 2014/06/06 12:22:05
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include "./System/Setup/SetupDef.h"
#include "./System/Initialize/InitializeDef.h"
#include "./System/Process/ProcessDef.h"

int main(void){
	SystemSetup();
	SystemInitialize();
	SystemProcess();	
	while(1);	
}	
