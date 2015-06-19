/*
 * Buzzer.c
 *
 * Created: 2014/06/19 17:54:38
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include "../../globalDef.h"

#if defined(USE_BUZZER)

#include <stdbool.h>
#include "./Buzzer.h"
#include "./BuzzerDef.h"

bool BuzzerStatus;

void BuzzerInitialize() {
	sbi(*BUZZER_PORT.DDR, BUZZER_BIT);
	cbi(*BUZZER_PORT.PORT, BUZZER_BIT);
	BuzzerStatus = BUZZER_OFF;
}

void BuzzerUpdate(void) {
	Buzzer(BuzzerStatus);
}

static void Buzzer(bool status) {
	if(status)	sbi(*BUZZER_PORT.PORT, BUZZER_BIT);
	else		cbi(*BUZZER_PORT.PORT, BUZZER_BIT);
}

#endif