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
// DIP�X�C�b�`�̏�����
	DipSwitchInitialize();
// UART�̏����� (���x�ݒ�19200bps)
	UartInitialize[MU_UART_NO](UART_RE|UART_TE, 51);
	
// �X�C�b�`����g�p����`�����l���y�уO���[�v������
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

// �O���[�vID��ݒ�
	MuSendCommand("GI", Group[selectNumber], 2);
// �`�����l����ݒ�
	MuSendCommand("CH", Channel[selectNumber], 2);
// �@��ID��ݒ�
	MuSendCommand("EI", EI[selectNumber], 2);
// �ړI��ID��ݒ�
	MuSendCommand("DI", DI[selectNumber], 2);
// �{�[���[�g��4800bps��
	MuSendCommand("BR", "48", 2);

// UART�̏����� (���x�ݒ�4800bps)
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