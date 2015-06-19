/*
 * Switch.c
 *
 * Created: 2014/06/19 18:25:58
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include "../../globalDef.h"

#if (defined(USE_SWITCH) || defined(USE_DIP_SWITCH) || defined(USE_MU))

#include "./SwitchDef.h"
#if defined(USE_SWITCH)
#include <stdbool.h>
#endif

#if defined(USE_SWITCH)
bool SwitchArray[USING_SWITCH];
#endif

#if defined(USE_SWITCH)
void SwitchInitialize() {
	uint8_t loop;

	#if (USING_SWITCH > 0)
		cbi(*SWITCH_0_PORT.DDR, SWITCH_0_BIT);
		sbi(*SWITCH_0_PORT.PORT, SWITCH_0_BIT);
	#endif
	#if (USING_SWITCH > 1)
		cbi(*SWITCH_1_PORT.DDR, SWITCH_1_BIT);
		sbi(*SWITCH_1_PORT.PORT, SWITCH_1_BIT);
	#endif
	#if (USING_SWITCH > 2)
		cbi(*SWITCH_2_PORT.DDR, SWITCH_2_BIT);
		sbi(*SWITCH_2_PORT.PORT, SWITCH_2_BIT);
	#endif
	#if (USING_SWITCH > 3)
		cbi(*SWITCH_3_PORT.DDR, SWITCH_3_BIT);
		sbi(*SWITCH_3_PORT.PORT, SWITCH_3_BIT);
	#endif
	#if (USING_SWITCH > 4)
		cbi(*SWITCH_4_PORT.DDR, SWITCH_4_BIT);
		sbi(*SWITCH_4_PORT.PORT, SWITCH_4_BIT);
	#endif
	#if (USING_SWITCH > 5)
		cbi(*SWITCH_5_PORT.DDR, SWITCH_5_BIT);
		sbi(*SWITCH_5_PORT.PORT, SWITCH_5_BIT);
	#endif
	#if (USING_SWITCH > 6)
		cbi(*SWITCH_6_PORT.DDR, SWITCH_6_BIT);
		sbi(*SWITCH_6_PORT.PORT, SWITCH_6_BIT);
	#endif
	#if (USING_SWITCH > 7)
		cbi(*SWITCH_7_PORT.DDR, SWITCH_7_BIT);
		sbi(*SWITCH_7_PORT.PORT, SWITCH_7_BIT);
	#endif
	#if (USING_SWITCH > 8)
		cbi(*SWITCH_8_PORT.DDR, SWITCH_8_BIT);
		sbi(*SWITCH_8_PORT.PORT, SWITCH_8_BIT);
	#endif
	
	for(loop=0; loop<USING_SWITCH; loop++) {
		SwitchArray[loop] = SWITCH_OFF;
	}
}
#endif

#if (defined(USE_DIP_SWITCH) || defined(USE_MU))
void DipSwitchInitialize() {
	cbi(*DIP_0_PORT.DDR, DIP_0_BIT);
	sbi(*DIP_0_PORT.PORT, DIP_0_BIT);
	cbi(*DIP_1_PORT.DDR, DIP_1_BIT);
	sbi(*DIP_1_PORT.PORT, DIP_1_BIT);
	cbi(*DIP_2_PORT.DDR, DIP_2_BIT);
	sbi(*DIP_2_PORT.PORT, DIP_2_BIT);
	cbi(*DIP_3_PORT.DDR, DIP_3_BIT);
	sbi(*DIP_3_PORT.PORT, DIP_3_BIT);
}
#endif

#if defined(USE_SWITCH)
void GetSwitchStatus(void) {
	#if (USING_SWITCH > 0)
		if( !(*SWITCH_0_PORT.PIN & (1<<SWITCH_0_BIT)))	SwitchArray[0] = SWITCH_ON;
		else											SwitchArray[0] = SWITCH_OFF;
	#endif
	#if (USING_SWITCH > 1)
		if( !(*SWITCH_1_PORT.PIN & (1<<SWITCH_1_BIT)))	SwitchArray[1] = SWITCH_ON;
		else											SwitchArray[1] = SWITCH_OFF;
	#endif
	#if (USING_SWITCH > 2)
		if( !(*SWITCH_2_PORT.PIN & (1<<SWITCH_2_BIT)))	SwitchArray[2] = SWITCH_ON;
		else											SwitchArray[2] = SWITCH_OFF;
	#endif
	#if (USING_SWITCH > 3)
		if( !(*SWITCH_3_PORT.PIN & (1<<SWITCH_3_BIT)))	SwitchArray[3] = SWITCH_ON;
		else											SwitchArray[3] = SWITCH_OFF;
	#endif
	#if (USING_SWITCH > 4)
		if( !(*SWITCH_4_PORT.PIN & (1<<SWITCH_4_BIT)))	SwitchArray[4] = SWITCH_ON;
		else											SwitchArray[4] = SWITCH_OFF;
	#endif
	#if (USING_SWITCH > 5)
		if( !(*SWITCH_5_PORT.PIN & (1<<SWITCH_5_BIT)))	SwitchArray[5] = SWITCH_ON;
		else											SwitchArray[5] = SWITCH_OFF;
	#endif
	#if (USING_SWITCH > 6)
		if( !(*SWITCH_6_PORT.PIN & (1<<SWITCH_6_BIT)))	SwitchArray[6] = SWITCH_ON;
		else											SwitchArray[6] = SWITCH_OFF;
	#endif
	#if (USING_SWITCH > 7)
		if( !(*SWITCH_7_PORT.PIN & (1<<SWITCH_7_BIT)))	SwitchArray[7] = SWITCH_ON;
		else											SwitchArray[7] = SWITCH_OFF;
	#endif
	#if (USING_SWITCH > 8)
		if( !(*SWITCH_8_PORT.PIN & (1<<SWITCH_8_BIT)))	SwitchArray[8] = SWITCH_ON;
		else											SwitchArray[8] = SWITCH_OFF;
	#endif
}
#endif

#if defined(USE_SWITCH)
void SwitchStatusReset(void) {
	uint8_t loop;
	
	for(loop=0; loop<USING_SWITCH; loop++) {
		SwitchArray[loop] = SWITCH_OFF;
	}
}
#endif

#if (defined(USE_DIP_SWITCH) || defined(USE_MU))
uint8_t GetDipSwitchStatus(void) {
	uint8_t buffer;
	
	buffer = 0x00;
	
	if( !bit_is_set(*DIP_0_PORT.PIN, DIP_0_BIT) ) {
		buffer |= DIP_0;
	}
	if( !bit_is_set(*DIP_1_PORT.PIN, DIP_1_BIT) ) {
		buffer |= DIP_1;
	}
	if( !bit_is_set(*DIP_2_PORT.PIN, DIP_2_BIT) ) {
		buffer |= DIP_2;
	}
	if( !bit_is_set(*DIP_3_PORT.PIN, DIP_3_BIT) ) {
		buffer |= DIP_3;
	}
	
	return buffer;
}
#endif

#endif
