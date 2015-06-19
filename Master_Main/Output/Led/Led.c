/*
 * Led.c
 *
 * Created: 2014/06/19 17:55:07
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include "../../globalDef.h"

#if defined(USE_LED)

#include <stdbool.h>
#include "./Led.h"
#include "./LedDef.h"

volatile bool LedArray[USING_LED];
void (*Led4bitPack[5])(uint8_t value);
void (*LedFunctions[USING_LED])(bool status);

void LedInitialize(void) {
	uint8_t loop;
	
	#if defined(USE_LED00)
		sbi(*LED_00_PORT.DDR, LED_00_BIT);
		LedFunctions[0] = LED0;
	#endif
	#if defined(USE_LED01)
		sbi(*LED_01_PORT.DDR, LED_01_BIT);
		LedFunctions[1] = LED1;
	#endif
	#if defined(USE_LED02)
		sbi(*LED_02_PORT.DDR, LED_02_BIT);
		LedFunctions[2] = LED2;
	#endif
	#if defined(USE_LED03)
		sbi(*LED_03_PORT.DDR, LED_03_BIT);
		LedFunctions[3] = LED3;
	#endif
	#if defined(USE_LED04)
		sbi(*LED_04_PORT.DDR, LED_04_BIT);
		LedFunctions[4] = LED4;
	#endif
	#if defined(USE_LED05)
		sbi(*LED_05_PORT.DDR, LED_05_BIT);
		LedFunctions[5] = LED5;
	#endif
	#if defined(USE_LED06)
		sbi(*LED_06_PORT.DDR, LED_06_BIT);
		LedFunctions[6] = LED6;
	#endif
	#if defined(USE_LED07)
		sbi(*LED_07_PORT.DDR, LED_07_BIT);
		LedFunctions[7] = LED7;
	#endif
	#if defined(USE_LED08)
		sbi(*LED_08_PORT.DDR, LED_08_BIT);
		LedFunctions[8] = LED8;
	#endif
	#if defined(USE_LED09)
		sbi(*LED_09_PORT.DDR, LED_09_BIT);
		LedFunctions[9] = LED9;
	#endif
	#if defined(USE_LED10)
		sbi(*LED_10_PORT.DDR, LED_10_BIT);
		LedFunctions[10] = LED10;
	#endif
	#if defined(USE_LED11)
		sbi(*LED_11_PORT.DDR, LED_11_BIT);
		LedFunctions[11] = LED11;
	#endif
	#if defined(USE_LED12)
		sbi(*LED_12_PORT.DDR, LED_12_BIT);
		LedFunctions[12] = LED12;
	#endif
	#if defined(USE_LED13)
		sbi(*LED_13_PORT.DDR, LED_13_BIT);
		LedFunctions[13] = LED13;
	#endif
	#if defined(USE_LED14)
		sbi(*LED_14_PORT.DDR, LED_14_BIT);
		LedFunctions[14] = LED14;
	#endif
	#if defined(USE_LED15)
		sbi(*LED_15_PORT.DDR, LED_15_BIT);
		LedFunctions[15] = LED15;
	#endif
	#if defined(USE_LED16)
		sbi(*LED_16_PORT.DDR, LED_16_BIT);
		LedFunctions[16] = LED16;
	#endif
	#if defined(USE_LED17)
		sbi(*LED_17_PORT.DDR, LED_17_BIT);
		LedFunctions[17] = LED17;
	#endif
	#if defined(USE_LED18)
		sbi(*LED_18_PORT.DDR, LED_18_BIT);
		LedFunctions[18] = LED18;
	#endif
	#if defined(USE_LED19)
		sbi(*LED_19_PORT.DDR, LED_19_BIT);
		LedFunctions[19] = LED19;
	#endif
	#if defined(USE_LED20)
		sbi(*LED_20_PORT.DDR, LED_20_BIT);
		LedFunctions[20] = LED20;
	#endif
	#if defined(USE_LED01) && defined(USE_LED02) && defined(USE_LED03) && defined(USE_LED04)
		Led4bitPack[0] = Led4bitPack0;
	#endif
	#if defined(USE_LED05) && defined(USE_LED06) && defined(USE_LED07) && defined(USE_LED08)
		Led4bitPack[1] = Led4bitPack1;
	#endif
	#if defined(USE_LED09) && defined(USE_LED10) && defined(USE_LED11) && defined(USE_LED12)
		Led4bitPack[2] = Led4bitPack2;
	#endif
	#if defined(USE_LED13) && defined(USE_LED14) && defined(USE_LED15) && defined(USE_LED16)
		Led4bitPack[3] = Led4bitPack3;
	#endif
	#if defined(USE_LED17) && defined(USE_LED18) && defined(USE_LED19) && defined(USE_LED20)
		Led4bitPack[4] = Led4bitPack4;
	#endif
	
	for(loop=0; loop<USING_LED; loop++) {
		LedArray[loop] = LED_OFF;
	}
}

void LedUpdate(void) {
	uint8_t loop;
	
	for(loop=0; loop<USING_LED; loop++) {
		LedFunctions[loop](LedArray[loop]);
	}
}

#if defined(USE_LED00)
static void LED0(bool status) {
	if(status)	cbi(*LED_00_PORT.PORT, LED_00_BIT);
	else		sbi(*LED_00_PORT.PORT, LED_00_BIT);
}
#endif

#if defined(USE_LED01)
static void LED1(bool status) {
	if(status)	cbi(*LED_01_PORT.PORT, LED_01_BIT);
	else		sbi(*LED_01_PORT.PORT, LED_01_BIT);
}
#endif

#if defined(USE_LED02)
static void LED2(bool status) {
	if(status)	cbi(*LED_02_PORT.PORT, LED_02_BIT);
	else		sbi(*LED_02_PORT.PORT, LED_02_BIT);
}
#endif

#if defined(USE_LED03)
static void LED3(bool status) {
	if(status)	cbi(*LED_03_PORT.PORT, LED_03_BIT);
	else		sbi(*LED_03_PORT.PORT, LED_03_BIT);
}
#endif

#if defined(USE_LED04)
static void LED4(bool status) {
	if(status)	cbi(*LED_04_PORT.PORT, LED_04_BIT);
	else		sbi(*LED_04_PORT.PORT, LED_04_BIT);
}
#endif

#if defined(USE_LED05)
static void LED5(bool status) {
	if(status)	cbi(*LED_05_PORT.PORT, LED_05_BIT);
	else		sbi(*LED_05_PORT.PORT, LED_05_BIT);
}
#endif

#if defined(USE_LED06)
static void LED6(bool status) {
	if(status)	cbi(*LED_06_PORT.PORT, LED_06_BIT);
	else		sbi(*LED_06_PORT.PORT, LED_06_BIT);
}
#endif

#if defined(USE_LED07)
static void LED7(bool status) {
	if(status)	cbi(*LED_07_PORT.PORT, LED_07_BIT);
	else		sbi(*LED_07_PORT.PORT, LED_07_BIT);
}
#endif

#if defined(USE_LED08)
static void LED8(bool status) {
	if(status)	cbi(*LED_08_PORT.PORT, LED_08_BIT);
	else		sbi(*LED_08_PORT.PORT, LED_08_BIT);
}
#endif

#if defined(USE_LED09)
static void LED9(bool status) {
	if(status)	cbi(*LED_09_PORT.PORT, LED_09_BIT);
	else		sbi(*LED_09_PORT.PORT, LED_09_BIT);
}
#endif

#if defined(USE_LED10)
static void LED10(bool status) {
	if(status)	cbi(*LED_10_PORT.PORT, LED_10_BIT);
	else		sbi(*LED_10_PORT.PORT, LED_10_BIT);
}
#endif

#if defined(USE_LED11)
static void LED11(bool status) {
	if(status)	cbi(*LED_11_PORT.PORT, LED_11_BIT);
	else		sbi(*LED_11_PORT.PORT, LED_11_BIT);
}
#endif

#if defined(USE_LED12)
static void LED12(bool status) {
	if(status)	cbi(*LED_12_PORT.PORT, LED_12_BIT);
	else		sbi(*LED_12_PORT.PORT, LED_12_BIT);
}
#endif

#if defined(USE_LED13)
static void LED13(bool status) {
	if(status)	cbi(*LED_13_PORT.PORT, LED_13_BIT);
	else		sbi(*LED_13_PORT.PORT, LED_13_BIT);
}
#endif

#if defined(USE_LED14)
static void LED14(bool status) {
	if(status)	cbi(*LED_14_PORT.PORT, LED_14_BIT);
	else		sbi(*LED_14_PORT.PORT, LED_14_BIT);
}
#endif

#if defined(USE_LED15)
static void LED15(bool status) {
	if(status)	cbi(*LED_15_PORT.PORT, LED_15_BIT);
	else		sbi(*LED_15_PORT.PORT, LED_15_BIT);
}
#endif

#if defined(USE_LED16)
static void LED16(bool status) {
	if(status)	cbi(*LED_16_PORT.PORT, LED_16_BIT);
	else		sbi(*LED_16_PORT.PORT, LED_16_BIT);
}
#endif

#if defined(USE_LED17)
static void LED17(bool status) {
	if(status)	cbi(*LED_17_PORT.PORT, LED_17_BIT);
	else		sbi(*LED_17_PORT.PORT, LED_17_BIT);
}
#endif

#if defined(USE_LED18)
static void LED18(bool status) {
	if(status)	cbi(*LED_18_PORT.PORT, LED_18_BIT);
	else		sbi(*LED_18_PORT.PORT, LED_18_BIT);
}
#endif

#if defined(USE_LED19)
static void LED19(bool status) {
	if(status)	cbi(*LED_19_PORT.PORT, LED_19_BIT);
	else		sbi(*LED_19_PORT.PORT, LED_19_BIT);
}
#endif

#if defined(USE_LED20)
static void LED20(bool status) {
	if(status)	cbi(*LED_20_PORT.PORT, LED_20_BIT);
	else		sbi(*LED_20_PORT.PORT, LED_20_BIT);
}
#endif

#if defined(USE_LED01) && defined(USE_LED02) && defined(USE_LED03) && defined(USE_LED04)
static void Led4bitPack0(uint8_t value) {
	if(value & 0x01)	LedArray[1] = LED_OFF;
	else				LedArray[1] = LED_ON;
	if(value & 0x02)	LedArray[2] = LED_OFF;
	else				LedArray[2] = LED_ON;
	if(value & 0x04)	LedArray[3] = LED_OFF;
	else				LedArray[3] = LED_ON;
	if(value & 0x08)	LedArray[4] = LED_OFF;
	else				LedArray[4] = LED_ON;
}
#endif

#if defined(USE_LED05) && defined(USE_LED06) && defined(USE_LED07) && defined(USE_LED08)
static void Led4bitPack1(uint8_t value) {
	if(value & 0x01)	LedArray[5] = LED_OFF;
	else				LedArray[5] = LED_ON;
	if(value & 0x02)	LedArray[6] = LED_OFF;
	else				LedArray[6] = LED_ON;
	if(value & 0x04)	LedArray[7] = LED_OFF;
	else				LedArray[7] = LED_ON;
	if(value & 0x08)	LedArray[8] = LED_OFF;
	else				LedArray[8] = LED_ON;
}
#endif

#if defined(USE_LED09) && defined(USE_LED10) && defined(USE_LED11) && defined(USE_LED12)
static void Led4bitPack2(uint8_t value) {
	if(value & 0x01)	LedArray[9] = LED_OFF;
	else				LedArray[9] = LED_ON;
	if(value & 0x02)	LedArray[10] = LED_OFF;
	else				LedArray[10] = LED_ON;
	if(value & 0x04)	LedArray[11] = LED_OFF;
	else				LedArray[11] = LED_ON;
	if(value & 0x08)	LedArray[12] = LED_OFF;
	else				LedArray[12] = LED_ON;
}
#endif

#if defined(USE_LED13) && defined(USE_LED14) && defined(USE_LED15) && defined(USE_LED16)
static void Led4bitPack3(uint8_t value) {
	if(value & 0x01)	LedArray[13] = LED_OFF;
	else				LedArray[13] = LED_ON;
	if(value & 0x02)	LedArray[14] = LED_OFF;
	else				LedArray[14] = LED_ON;
	if(value & 0x04)	LedArray[15] = LED_OFF;
	else				LedArray[15] = LED_ON;
	if(value & 0x08)	LedArray[16] = LED_OFF;
	else				LedArray[16] = LED_ON;
}
#endif

#if defined(USE_LED17) && defined(USE_LED18) && defined(USE_LED19) && defined(USE_LED20)
static void Led4bitPack4(uint8_t value) {
	if(value & 0x01)	LedArray[17] = LED_OFF;
	else				LedArray[17] = LED_ON;
	if(value & 0x02)	LedArray[18] = LED_OFF;
	else				LedArray[18] = LED_ON;
	if(value & 0x04)	LedArray[19] = LED_OFF;
	else				LedArray[19] = LED_ON;
	if(value & 0x08)	LedArray[20] = LED_OFF;
	else				LedArray[20] = LED_ON;
}
#endif

#endif
