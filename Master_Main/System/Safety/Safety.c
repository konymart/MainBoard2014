/*
 * Safety.c
 *
 * Created: 2014/06/19 19:47:14
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include "../../globalDef.h"

#if defined(USE_SAFETY)

#include <stdbool.h>
#include "./Safety.h"
#include "./SafetyDef.h"
#include "../../Output/Buzzer/BuzzerDef.h"
#include "../../Output/Led/LedDef.h"
#include "../../Communication/RemoteControl/RCReceiveDef.h"

void (*SafetyInitialize[6])(void);

#if defined(USE_POWER_CHECK)
volatile bool powerLost;
#endif
#if defined(USE_BUZZER)
bool buzzerStatus;
bool buzzerStopFlag;
bool buzzerPatternStatus;
uint16_t buzzerCount;
#endif

void SafetySetup() {
	#if defined(USE_TIMER0)
		SafetyInitialize[0] = SafetyInitialize0;
	#endif
	#if defined(USE_TIMER1)
		SafetyInitialize[1] = SafetyInitialize1;
	#endif
	#if defined(USE_TIMER2)
		SafetyInitialize[2] = SafetyInitialize2;
	#endif
	#if defined(USE_TIMER3)
		SafetyInitialize[3] = SafetyInitialize3;
	#endif
	#if defined(USE_TIMER4)
		SafetyInitialize[4] = SafetyInitialize4;
	#endif
	#if defined(USE_TIMER5)
		SafetyInitialize[5] = SafetyInitialize5;
	#endif
}

#if defined(USE_POWER_CHECK)
void SafetyChecker(void) {
	if( !bit_is_set(*SAFETY_READ_PORT.PIN, SAFETY_READ_BIT)) {
		powerLost = false;
		#if defined(USE_LED)
			LedArray[SAFETY_LED_NO] = LED_ON;
		#endif
	}
	else {
		powerLost = true;
		#if defined(USE_LED)
			LedArray[SAFETY_LED_NO] = LED_OFF;
		#endif
	}
	
	#if defined(USE_BUZZER)
		if(powerLost && CtrlLost) {
			buzzerStopFlag = true;
			if(buzzerCount == 0) {
				buzzerCount = 15;
				buzzerStatus = !buzzerStatus;
			}
			BuzzerStatus = buzzerStatus;
			buzzerCount--;
		}
		else if(!powerLost && CtrlLost) {
			buzzerStopFlag = true;
			if(buzzerCount == 0) {
				buzzerCount = 3;
				buzzerStatus = !buzzerStatus;
			}
			BuzzerStatus = buzzerStatus;
			buzzerCount--;
		}
		else if(powerLost && !CtrlLost) {
			buzzerStopFlag = true;
			if(buzzerCount == 0) {
				if(buzzerPatternStatus){
					buzzerCount = 15;
				}else{
					buzzerCount = 5;
				}
				buzzerStatus = !buzzerStatus;
				if(!buzzerStatus){
					buzzerPatternStatus = !buzzerPatternStatus;
				}
			}
			BuzzerStatus = buzzerStatus;
			buzzerCount--;
		}
		else {
			if(buzzerStopFlag) {
				BuzzerStatus = BUZZER_OFF;
				buzzerStopFlag = false;
				buzzerCount = 0;
			}
		}
	#endif
}
#endif

#if defined(USE_TIMER0)
static void SafetyInitialize0(void) {
	sbi(*TIMER.T0.TCIMSK, TOIE0_BIT);
	
	#if defined(USE_POWER_CHECK)
		cbi(*SAFETY_READ_PORT.DDR, SAFETY_READ_BIT);
		sbi(*SAFETY_READ_PORT.PORT, SAFETY_READ_BIT);
	#endif
	
	#if defined(USE_POWER_CHECK)
		powerLost = false;
	#endif
	#if defined(USE_BUZZER)
		buzzerStatus = false;
		buzzerCount = 0;
		buzzerPatternStatus = false;
	#endif
}
#endif

#if defined(USE_TIMER1)
static void SafetyInitialize1(void) {
	sbi(*TIMER.T1.TCIMSK, TOIE1_BIT);
	
	#if defined(USE_POWER_CHECK)
		cbi(*SAFETY_READ_PORT.DDR, SAFETY_READ_BIT);
		sbi(*SAFETY_READ_PORT.PORT, SAFETY_READ_BIT);
	#endif
	
	#if defined(USE_POWER_CHECK)
		powerLost = false;
	#endif
	#if defined(USE_BUZZER)
		buzzerStatus = false;
		buzzerCount = 0;
		buzzerPatternStatus = false;
	#endif
}
#endif

#if defined(USE_TIMER2)
static void SafetyInitialize2(void) {
	sbi(*TIMER.T2.TCIMSK, TOIE2_BIT);
	
	#if defined(USE_POWER_CHECK)
		cbi(*SAFETY_READ_PORT.DDR, SAFETY_READ_BIT);
		sbi(*SAFETY_READ_PORT.PORT, SAFETY_READ_BIT);
	#endif
	
	#if defined(USE_POWER_CHECK)
		powerLost = false;
	#endif
	#if defined(USE_BUZZER)
		buzzerStatus = false;
		buzzerCount = 0;
		buzzerPatternStatus = false;
	#endif
}
#endif

#if defined(USE_TIMER3)
static void SafetyInitialize3(void) {
	sbi(*TIMER.T3.TCIMSK, TOIE3_BIT);
	
	#if defined(USE_POWER_CHECK)
		cbi(*SAFETY_READ_PORT.DDR, SAFETY_READ_BIT);
		sbi(*SAFETY_READ_PORT.PORT, SAFETY_READ_BIT);
	#endif
	
	#if defined(USE_POWER_CHECK)
		powerLost = false;
	#endif
	#if defined(USE_BUZZER)
		buzzerStatus = false;
		buzzerCount = 0;
		buzzerPatternStatus = false;
	#endif
}
#endif

#if defined(USE_TIMER4)
static void SafetyInitialize4(void) {
	sbi(*TIMER.T4.TCIMSK, TOIE4_BIT);
	
	#if defined(USE_POWER_CHECK)
		cbi(*SAFETY_READ_PORT.DDR, SAFETY_READ_BIT);
		sbi(*SAFETY_READ_PORT.PORT, SAFETY_READ_BIT);
	#endif
	
	#if defined(USE_POWER_CHECK)
		powerLost = false;
	#endif
	#if defined(USE_BUZZER)
		buzzerStatus = false;
		buzzerCount = 0;
		buzzerPatternStatus = false;
	#endif
}
#endif

#if defined(USE_TIMER5)
static void SafetyInitialize5(void) {
	sbi(*TIMER.T5.TCIMSK, TOIE5_BIT);
	
	#if defined(USE_POWER_CHECK)
		cbi(*SAFETY_READ_PORT.DDR, SAFETY_READ_BIT);
		sbi(*SAFETY_READ_PORT.PORT, SAFETY_READ_BIT);
	#endif
	
	#if defined(USE_POWER_CHECK)
		powerLost = false;
	#endif
	#if defined(USE_BUZZER)
		buzzerStatus = false;
		buzzerCount = 0;
		buzzerPatternStatus = false;
	#endif
}
#endif

#endif
