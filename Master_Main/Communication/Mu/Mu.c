/*
 * Mu.c
 *
 * Created: 2014/06/17 20:34:59
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include "../../globalDef.h"

#if defined(USE_MU)

#include "./Mu.h"
#include "./MuDef.h"
#include "../../Input/Switch/SwitchDef.h"
#include "../Uart/UartDef.h"

static uint8_t selectNumber;

static char Group[][4]		= {"01", "02", "03", "04"};
static char Channel[][4]	= {"08", "14", "1F", "2E"};
static char DI[][4]			= {"10", "20", "40", "80"};
static char EI[][4]			= {"01", "02", "04", "08"};

static void (*MuTxChar[4])(uint8_t);
static void (*MuRxChar[4])(uint8_t*);

void MuSetup(void) {
	uint8_t loop;
	
	for(loop=0; loop<4; loop++) {
		MuTxChar[loop] = UartSend[loop];
		MuRxChar[loop] = UartReceive[loop];
	}
}

void MuInitialize(void) {
// DIPスイッチの初期化
	DipSwitchInitialize();
// UARTの初期化 (速度設定19200bps)
	UartInitialize[MU_UART_NO](UART_RE|UART_TE, 51);
	
// スイッチから使用するチャンネル及びグループを決定
	if( GetDipSwitchStatus() & DIP_0 ) {
		selectNumber = 0;
	}
	else if( GetDipSwitchStatus() & DIP_1 ) {
		selectNumber = 1;
	}
	else if( GetDipSwitchStatus() & DIP_2 ) {
		selectNumber = 2;
	}
	else if( GetDipSwitchStatus() & DIP_3 ) {
		selectNumber = 3;
	}
	else {
		selectNumber = 0;
	}

// グループIDを設定
	MuSendCommand("GI", Group[selectNumber], 2);
// チャンネルを設定
	MuSendCommand("CH", Channel[selectNumber], 2);
// 機器IDを設定
	MuSendCommand("EI", EI[selectNumber], 2);
// 目的局IDを設定
	MuSendCommand("DI", DI[selectNumber], 2);
// ボーレートを4800bpsに
	MuSendCommand("BR", "48", 2);

// UARTの初期化 (速度設定4800bps)
	UartInitialize[MU_UART_NO](UART_RE|UART_TE|UART_RXCIE, 207);
}

static void MuSendCommand(char* cmd, char* value, uint8_t valueLen) {
	MuTxChar[MU_UART_NO]('@');
	MuTxChar[MU_UART_NO](cmd[0]);
	MuTxChar[MU_UART_NO](cmd[1]);
	
	while( valueLen-- ) {
		MuTxChar[MU_UART_NO](*value);
		value++;
	}
	
	MuTxChar[MU_UART_NO]('\r');
	MuTxChar[MU_UART_NO]('\n');
}

#endif