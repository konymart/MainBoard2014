/*
 * Air.c
 *
 * Created: 2014/06/19 17:54:07
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include "../../globalDef.h"

#if defined(USE_AIR)

#include <stdbool.h>
#include "./Air.h"
#include "./AirDef.h"

bool AirArray[USING_AIR];
void (*AirFunctions[USING_AIR])(bool status);

void AirInitialize(void) {
	uint8_t loop;
	
	#if defined(USE_AIR00)
		sbi(*AIR_0_PORT.DDR, AIR_0_BIT);
		AirFunctions[0] = SetActionAir0;
	#endif
	#if defined(USE_AIR01)
		sbi(*AIR_1_PORT.DDR, AIR_1_BIT);
		AirFunctions[1] = SetActionAir1;
	#endif
	#if defined(USE_AIR02)
		sbi(*AIR_2_PORT.DDR, AIR_2_BIT);
		AirFunctions[2] = SetActionAir2;
	#endif
	#if defined(USE_AIR03)
		sbi(*AIR_3_PORT.DDR, AIR_3_BIT);
		AirFunctions[3] = SetActionAir3;
	#endif
	#if defined(USE_AIR04)
		sbi(*AIR_4_PORT.DDR, AIR_4_BIT);
		AirFunctions[4] = SetActionAir4;
	#endif
	#if defined(USE_AIR05)
		sbi(*AIR_5_PORT.DDR, AIR_5_BIT);
		AirFunctions[5] = SetActionAir5;
	#endif
	#if defined(USE_AIR06)
		sbi(*AIR_6_PORT.DDR, AIR_6_BIT);
		AirFunctions[6] = SetActionAir6;
	#endif
	#if defined(USE_AIR07)
		sbi(*AIR_7_PORT.DDR, AIR_7_BIT);
		AirFunctions[7] = SetActionAir7;
	#endif
	#if defined(USE_AIR08)
		sbi(*AIR_8_PORT.DDR, AIR_8_BIT);
		AirFunctions[8] = SetActionAir8;
	#endif
	#if defined(USE_AIR09)
		sbi(*AIR_9_PORT.DDR, AIR_9_BIT);
		AirFunctions[9] = SetActionAir9;
	#endif

// エア出力状態配列の初期化
	for(loop=0; loop<USING_AIR; loop++) {
		AirArray[loop] = AIR_OFF;
	}
	
	return ;
}

void AirUpdate(void) {
// 変数を宣言
	uint8_t loop;
// 各ポートの状態を更新
	for(loop=0; loop<USING_AIR; loop++) {
		AirFunctions[loop](AirArray[loop]);
	}
}

#if defined(USE_AIR00)
static void SetActionAir0(bool status) {
	if(status)	cbi(*AIR_0_PORT.PORT, AIR_0_BIT);
	else		sbi(*AIR_0_PORT.PORT, AIR_0_BIT);
}
#endif

#if defined(USE_AIR01)
static void SetActionAir1(bool status) {
	if(status)	cbi(*AIR_1_PORT.PORT, AIR_1_BIT);
	else		sbi(*AIR_1_PORT.PORT, AIR_1_BIT);
}
#endif

#if defined(USE_AIR02)
static void SetActionAir2(bool status) {
	if(status)	cbi(*AIR_2_PORT.PORT, AIR_2_BIT);
	else		sbi(*AIR_2_PORT.PORT, AIR_2_BIT);
}
#endif

#if defined(USE_AIR03)
static void SetActionAir3(bool status) {
	if(status)	cbi(*AIR_3_PORT.PORT, AIR_3_BIT);
	else		sbi(*AIR_3_PORT.PORT, AIR_3_BIT);
}
#endif

#if defined(USE_AIR04)
static void SetActionAir4(bool status) {
	if(status)	cbi(*AIR_4_PORT.PORT, AIR_4_BIT);
	else		sbi(*AIR_4_PORT.PORT, AIR_4_BIT);
}
#endif

#if defined(USE_AIR05)
static void SetActionAir5(bool status) {
	if(status)	cbi(*AIR_5_PORT.PORT, AIR_5_BIT);
	else		sbi(*AIR_5_PORT.PORT, AIR_5_BIT);
}
#endif

#if defined(USE_AIR06)
static void SetActionAir6(bool status) {
	if(status)	cbi(*AIR_6_PORT.PORT, AIR_6_BIT);
	else		sbi(*AIR_6_PORT.PORT, AIR_6_BIT);
}
#endif

#if defined(USE_AIR07)
static void SetActionAir7(bool status) {
	if(status)	cbi(*AIR_7_PORT.PORT, AIR_7_BIT);
	else		sbi(*AIR_7_PORT.PORT, AIR_7_BIT);
}
#endif

#if defined(USE_AIR08)
static void SetActionAir8(bool status) {
	if(status)	cbi(*AIR_8_PORT.PORT, AIR_8_BIT);
	else		sbi(*AIR_8_PORT.PORT, AIR_8_BIT);
}
#endif

#if defined(USE_AIR09)
static void SetActionAir9(bool status) {
	if(status)	cbi(*AIR_9_PORT.PORT, AIR_9_BIT);
	else		sbi(*AIR_9_PORT.PORT, AIR_9_BIT);
}
#endif

#endif
