/*
 * RemotoControl.c
 *
 * Created: 2014/06/17 20:36:38
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include "../../globalDef.h"

#if defined(USE_MU)

#include <avr/interrupt.h>
#include <stdbool.h>
#include "./RCClassic.h"
#include "./RCReceiveDef.h"
#if defined(USE_LED)
	#include "../../Output/Led/LedDef.h"
#endif

#if defined(USE_RS485)
	#include "../RS485/RS485Def.h"
#endif

volatile bool CtrlLost;
static volatile uint8_t count;
static volatile uint16_t timerCount;
static volatile bool phase;
static volatile char value;
static volatile char packet[24];
static volatile char check[] = "DR=";
static union controllerData ctrlData;
static union controllerData keepCtrlData;
static uint8_t defaultCtrlData[RC_DATA_LENGTH] = RC_DEFAULT_DATA;

void CtrlDataInitialize(void) {
	uint8_t loop;
	
	CtrlLost = false;
	count = 0;
	phase = false;
	timerCount = 0;
#if defined(USE_SENSOR_HUB)
	SensorTimerCount = 0;
#endif
// 受信データに初期データを代入
	for(loop=0; loop<RC_DATA_LENGTH; loop++) {
		ctrlData.buf[loop] = defaultCtrlData[loop];
	}	
}

union controllerData* GetControllerData(void) {
	uint8_t loop;
	
	cli();
	
	for(loop=0; loop<RC_DATA_LENGTH; loop++) {
		keepCtrlData.buf[loop] = ctrlData.buf[loop];
	}
	
	sei();
	
	return &keepCtrlData;
}

union controllerData* ControllerDataReset(void) {
	uint8_t loop;
	
	cli();
	
	for(loop=0; loop<RC_DATA_LENGTH; loop++) {
		keepCtrlData.buf[loop] = defaultCtrlData[loop];
	}
	
	sei();
	
	return &keepCtrlData;
}

#if (MU_UART_NO == 0)
ISR(USART0_RX_vect) {
	value = *USART.U0.UDREG;
	
	if(phase) {
		packet[count] = value;
		if(count < 2) {
			if(value != check[count]) {
				phase = false;
				CtrlLost = true;
				#if defined(USE_LED)
					LedArray[MU_LED_NO] = LED_OFF;
				#endif
			}
		}
		else if(count == 8) {
			ctrlData.buf[0] = packet[5];
			ctrlData.buf[1] = packet[6];
			ctrlData.buf[2] = packet[7];
			ctrlData.buf[3] = packet[8];
			phase = false;
			#if defined(USE_LED)
				LedArray[MU_LED_NO] = LED_ON;
			#endif
			timerCount = 0;
			CtrlLost = false;
		}
		count++;
	}
	else {
		if(value == '*') {
			count = 0;
			phase = true;
		}
	}
}
#elif (MU_UART_NO == 1)
ISR(USART1_RX_vect) {
	value = *USART.U1.UDREG;
	
	if(phase) {
		packet[count] = value;
		if(count < 2) {
			if(value != check[count]) {
				phase = false;
				CtrlLost = true;
				#if defined(USE_LED)
					LedArray[MU_LED_NO] = LED_OFF;
				#endif
			}
		}
		else if(count == 8) {
			ctrlData.buf[0] = packet[5];
			ctrlData.buf[1] = packet[6];
			ctrlData.buf[2] = packet[7];
			ctrlData.buf[3] = packet[8];
			phase = false;
			#if defined(USE_LED)
				LedArray[MU_LED_NO] = LED_ON;
			#endif
			CtrlLost = false;
			timerCount = 0;
		}
		count++;
	}
	else {
		if(value == '*') {
			count = 0;
			phase = true;
		}
	}
}
#elif (MU_UART_NO == 2)
ISR(USART2_RX_vect) {
	value = *USART.U2.UDREG;
	
	if(phase) {
		packet[count] = value;
		if(count < 2) {
			if(value != check[count]) {
				phase = false;
				#if defined(USE_LED)
					LedArray[MU_LED_NO] = LED_OFF;
				#endif
			}
		}
		else if(count == 8) {
			ctrlData.buf[0] = packet[5];
			ctrlData.buf[1] = packet[6];
			ctrlData.buf[2] = packet[7];
			ctrlData.buf[3] = packet[8];
			phase = false;
			#if defined(USE_LED)
				LedArray[MU_LED_NO] = LED_ON;
			#endif
			timerCount = 0;
		}
		count++;
	}
	else {
		if(value == '*') {
			count = 0;
			phase = true;
		}
	}
}
#elif (MU_UART_NO == 3)
ISR(USART3_RX_vect) {
	value = *USART.U3.UDREG;
	
	if(phase) {
		packet[count] = value;
		if(count < 2) {
			if(value != check[count]) {
				phase = false;
				#if defined(USE_LED)
					LedArray[MU_LED_NO] = LED_OFF;
				#endif
			}
		}
		else if(count == 8) {
			ctrlData.buf[0] = packet[5];
			ctrlData.buf[1] = packet[6];
			ctrlData.buf[2] = packet[7];
			ctrlData.buf[3] = packet[8];
			phase = false;
			#if defined(USE_LED)
				LedArray[MU_LED_NO] = LED_ON;
			#endif
			timerCount = 0;
		}
		count++;
	}
	else {
		if(value == '*') {
			count = 0;
			phase = true;
		}
	}
}
#endif

#if (SAFETY_TIMER_NO == 0)
ISR(TIMER0_OVF_vect) {
	uint8_t loop;
	
	timerCount++;
#if defined(USE_SENSOR_HUB)
	SensorTimerCount++;
#endif
	if(timerCount>=RC_SAFETY_COUNT) {

// 受信データに初期データを代入
		for(loop=0; loop<RC_DATA_LENGTH; loop++) {
			ctrlData.buf[loop] = defaultCtrlData[loop];
		}
		LedArray[MU_LED_NO] = LED_OFF;
		timerCount = 0;
		CtrlLost  = true;
	}	
		
	#if defined(USE_SENSOR_HUB)
	if(!SensorDataReceived){
		if(SensorTimerCount >= 200){
			LedArray[SENSOR_LED_NO] = LED_OFF;
			SensorBoardLost = true;
			SensorTimerCount = 0;
			SensorDataReceived = true;
		}		
	}	
	#endif
}
#elif (SAFETY_TIMER_NO == 1)
ISR(TIMER1_OVF_vect) {
	uint8_t loop;
	
	timerCount++;
#if defined(USE_SENSOR_HUB)
	SensorTimerCount++;
#endif
	if(timerCount>=RC_SAFETY_COUNT) {

// 受信データに初期データを代入
		for(loop=0; loop<RC_DATA_LENGTH; loop++) {
			ctrlData.buf[loop] = defaultCtrlData[loop];
		}
		LedArray[MU_LED_NO] = LED_OFF;
		timerCount = 0;
		CtrlLost  = true;
	}	
	
	#if defined(USE_SENSOR_HUB)
	if(!SensorDataReceived){
		if(SensorTimerCount >= 200){
			LedArray[SENSOR_LED_NO] = LED_OFF;
			SensorBoardLost = true;
			SensorTimerCount = 0;
			SensorDataReceived = true;
		}		
	}	
	#endif	
}
#elif (SAFETY_TIMER_NO == 2)
ISR(TIMER2_OVF_vect) {
	uint8_t loop;
	
	timerCount++;
#if defined(USE_SENSOR_HUB)
	SensorTimerCount++;
#endif
	if(timerCount>=RC_SAFETY_COUNT) {

// 受信データに初期データを代入
		for(loop=0; loop<RC_DATA_LENGTH; loop++) {
			ctrlData.buf[loop] = defaultCtrlData[loop];
		}
		LedArray[MU_LED_NO] = LED_OFF;
		timerCount = 0;
		CtrlLost  = true;
	}	
	
	#if defined(USE_SENSOR_HUB)
	if(!SensorDataReceived){
		if(SensorTimerCount >= 200){
			LedArray[SENSOR_LED_NO] = LED_OFF;
			SensorBoardLost = true;
			SensorTimerCount = 0;
			SensorDataReceived = true;
		}		
	}	
	#endif	
}
#elif (SAFETY_TIMER_NO == 3)
ISR(TIMER3_OVF_vect) {
	uint8_t loop;
	
	timerCount++;
	SensorTimerCount++;
	if(timerCount>=RC_SAFETY_COUNT) {

// 受信データに初期データを代入
		for(loop=0; loop<RC_DATA_LENGTH; loop++) {
			ctrlData.buf[loop] = defaultCtrlData[loop];
		}
		LedArray[MU_LED_NO] = LED_OFF;
		timerCount = 0;
		CtrlLost  = true;
	}	
	
	#if defined(USE_SENSOR_HUB)
	if(!SensorDataReceived){
		if(SensorTimerCount >= 200){
			LedArray[SENSOR_LED_NO] = LED_OFF;
			SensorBoardLost = true;
			SensorTimerCount = 0;
			SensorDataReceived = true;
		}		
	}	
	#endif	
}
#elif (SAFETY_TIMER_NO == 4)
ISR(TIMER4_OVF_vect) {
	uint8_t loop;
	
	timerCount++;
#if defined(USE_SENSOR_HUB)
	SensorTimerCount++;
#endif
	if(timerCount>=RC_SAFETY_COUNT) {

// 受信データに初期データを代入
		for(loop=0; loop<RC_DATA_LENGTH; loop++) {
			ctrlData.buf[loop] = defaultCtrlData[loop];
		}
		LedArray[MU_LED_NO] = LED_OFF;
		timerCount = 0;
		CtrlLost  = true;
	}	
	
	#if defined(USE_SENSOR_HUB)
	if(!SensorDataReceived){
		if(SensorTimerCount >= 200){
			LedArray[SENSOR_LED_NO] = LED_OFF;
			SensorBoardLost = true;
			SensorTimerCount = 0;
			SensorDataReceived = true;
		}		
	}	
	#endif	
}
#elif (SAFETY_TIMER_NO == 5)
ISR(TIMER5_OVF_vect) {
	uint8_t loop;
	
	timerCount++;
#if defined(USE_SENSOR_HUB)
	SensorTimerCount++;
#endif
	if(timerCount>=RC_SAFETY_COUNT) {

// 受信データに初期データを代入
		for(loop=0; loop<RC_DATA_LENGTH; loop++) {
			ctrlData.buf[loop] = defaultCtrlData[loop];
		}
		LedArray[MU_LED_NO] = LED_OFF;
		timerCount = 0;
		CtrlLost  = true;
	}	
	
	#if defined(USE_SENSOR_HUB)
	if(!SensorDataReceived){
		if(SensorTimerCount >= 200){
			LedArray[SENSOR_LED_NO] = LED_OFF;
			SensorBoardLost = true;
			SensorTimerCount = 0;
			SensorDataReceived = true;
		}		
	}	
	#endif	
}
#endif

#endif
