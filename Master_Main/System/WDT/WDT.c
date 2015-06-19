/*
 * WDT.c
 *
 * Created: 2014/08/04 15:36:04
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include "../../globalDef.h"

#ifdef WDT_RESET

void WDTInitialize(void){
	wdt_reset();
	wdt_enable(WDT_RESET_TIME);
}

#endif
