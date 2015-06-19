/*
 * Motor.c
 *
 * Created: 2014/06/19 17:55:36
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include "../../globalDef.h"

#if defined(USE_MOTOR)

#include <stdbool.h>
#include "./Motor.h"
#include "./MotorDef.h"

struct Motor MotorArray[USING_MOTOR];
void (*PwmTimerInitialize[6])(uint8_t port);
void (*MotorFunctions[USING_MOTOR])(uint8_t status, uint8_t pwm);

void MotorSetup(void) {
	#if defined(USE_TIMER0)
		PwmTimerInitialize[0] = PwmTimerInitialize0;
	#endif
	#if defined(USE_TIMER1)
		PwmTimerInitialize[1] = PwmTimerInitialize1;
	#endif
	#if defined(USE_TIMER2)
		PwmTimerInitialize[2] = PwmTimerInitialize2;
	#endif
	#if defined(USE_TIMER3)
		PwmTimerInitialize[3] = PwmTimerInitialize3;
	#endif
	#if defined(USE_TIMER4)
		PwmTimerInitialize[4] = PwmTimerInitialize4;
	#endif
	#if defined(USE_TIMER5)
		PwmTimerInitialize[5] = PwmTimerInitialize5;
	#endif
}

void MotorInitialize(void) {
	uint8_t loop;
	
	#if defined(USE_MOTOR00)
		sbi(*MOTOR_00_D1_PORT.DDR, MOTOR_00_D1_BIT);
		sbi(*MOTOR_00_D2_PORT.DDR, MOTOR_00_D2_BIT);
		PwmTimerInitialize[MOTOR00_TIMER_NO](MOTOR00_PWM_PORT);
		MotorFunctions[0] = SetActionMotor0;
	#endif
	#if defined(USE_MOTOR01)
		sbi(*MOTOR_01_D1_PORT.DDR, MOTOR_01_D1_BIT);
		sbi(*MOTOR_01_D2_PORT.DDR, MOTOR_01_D2_BIT);
		PwmTimerInitialize[MOTOR01_TIMER_NO](MOTOR01_PWM_PORT);
		MotorFunctions[1] = SetActionMotor1;
	#endif
	#if defined(USE_MOTOR02)
		sbi(*MOTOR_02_D1_PORT.DDR, MOTOR_02_D1_BIT);
		sbi(*MOTOR_02_D2_PORT.DDR, MOTOR_02_D2_BIT);
		PwmTimerInitialize[MOTOR02_TIMER_NO](MOTOR02_PWM_PORT);
		MotorFunctions[2] = SetActionMotor2;
	#endif
	#if defined(USE_MOTOR03)
		sbi(*MOTOR_03_D1_PORT.DDR, MOTOR_03_D1_BIT);
		sbi(*MOTOR_03_D2_PORT.DDR, MOTOR_03_D2_BIT);
		PwmTimerInitialize[MOTOR03_TIMER_NO](MOTOR03_PWM_PORT);
		MotorFunctions[3] = SetActionMotor3;
	#endif
	#if defined(USE_MOTOR04)
		sbi(*MOTOR_04_D1_PORT.DDR, MOTOR_04_D1_BIT);
		sbi(*MOTOR_04_D2_PORT.DDR, MOTOR_04_D2_BIT);
		PwmTimerInitialize[MOTOR04_TIMER_NO](MOTOR04_PWM_PORT);
		MotorFunctions[4] = SetActionMotor4;
	#endif
	#if defined(USE_MOTOR05)
		sbi(*MOTOR_05_D1_PORT.DDR, MOTOR_05_D1_BIT);
		sbi(*MOTOR_05_D2_PORT.DDR, MOTOR_05_D2_BIT);
		PwmTimerInitialize[MOTOR05_TIMER_NO](MOTOR05_PWM_PORT);
		MotorFunctions[5] = SetActionMotor5;
	#endif
	#if defined(USE_MOTOR06)
		sbi(*MOTOR_06_D1_PORT.DDR, MOTOR_06_D1_BIT);
		sbi(*MOTOR_06_D2_PORT.DDR, MOTOR_06_D2_BIT);
		PwmTimerInitialize[MOTOR06_TIMER_NO](MOTOR06_PWM_PORT);
		MotorFunctions[6] = SetActionMotor6;
	#endif
	#if defined(USE_MOTOR07)
		sbi(*MOTOR_07_D1_PORT.DDR, MOTOR_07_D1_BIT);
		sbi(*MOTOR_07_D2_PORT.DDR, MOTOR_07_D2_BIT);
		PwmTimerInitialize[MOTOR07_TIMER_NO](MOTOR07_PWM_PORT);
		MotorFunctions[7] = SetActionMotor7;
	#endif
	#if defined(USE_MOTOR08)
		sbi(*MOTOR_08_D1_PORT.DDR, MOTOR_08_D1_BIT);
		sbi(*MOTOR_08_D2_PORT.DDR, MOTOR_08_D2_BIT);
		PwmTimerInitialize[MOTOR08_TIMER_NO](MOTOR08_PWM_PORT);
		MotorFunctions[8] = SetActionMotor8;
	#endif
	#if defined(USE_MOTOR09)
		sbi(*MOTOR_09_D1_PORT.DDR, MOTOR_09_D1_BIT);
		sbi(*MOTOR_09_D2_PORT.DDR, MOTOR_09_D2_BIT);
		PwmTimerInitialize[MOTOR09_TIMER_NO](MOTOR09_PWM_PORT);
		MotorFunctions[9] = SetActionMotor9;
	#endif
	#if defined(USE_MOTOR10)
		sbi(*MOTOR_10_D1_PORT.DDR, MOTOR_10_D1_BIT);
		sbi(*MOTOR_10_D2_PORT.DDR, MOTOR_10_D2_BIT);
		MotorFunctions[10] = SetActionMotor10;
	#endif
	#if defined(USE_MOTOR11)
		sbi(*MOTOR_11_D1_PORT.DDR, MOTOR_11_D1_BIT);
		sbi(*MOTOR_11_D2_PORT.DDR, MOTOR_11_D2_BIT);
		MotorFunctions[11] = SetActionMotor11;
	#endif
	#if defined(USE_MOTOR12)
		sbi(*MOTOR_12_D1_PORT.DDR, MOTOR_12_D1_BIT);
		sbi(*MOTOR_12_D2_PORT.DDR, MOTOR_12_D2_BIT);
		MotorFunctions[12] = SetActionMotor12;
	#endif
	#if defined(USE_MOTOR13)
		sbi(*MOTOR_13_D1_PORT.DDR, MOTOR_13_D1_BIT);
		sbi(*MOTOR_13_D2_PORT.DDR, MOTOR_13_D2_BIT);
		MotorFunctions[13] = SetActionMotor13;
	#endif
	#if defined(USE_MOTOR14)
		sbi(*MOTOR_14_D1_PORT.DDR, MOTOR_14_D1_BIT);
		sbi(*MOTOR_14_D2_PORT.DDR, MOTOR_14_D2_BIT);
		MotorFunctions[14] = SetActionMotor14;
	#endif

	for(loop=0; loop<USING_MOTOR; loop++) {
		MotorArray[loop].status = FREE;
		MotorArray[loop].pwm = 0;
	}
}

void MotorUpdate(void) {
	uint8_t loop;
	
	for(loop=0; loop<USING_MOTOR; loop++) {
		MotorFunctions[loop](MotorArray[loop].status, MotorArray[loop].pwm);
	}
}

#if defined(USE_TIMER0)
static void PwmTimerInitialize0(uint8_t port) {
	if(port == 'A') {
		sbi(*OCR0_PORT.DDR, OCR0_BIT);
		sbi(*TIMER.T0.TCCRA, COM01_BIT);
		cbi(*TIMER.T0.TCCRA, COM00_BIT);
	}
}
#endif

#if defined(USE_TIMER1)
static void PwmTimerInitialize1(uint8_t port) {
	if(port == 'A') {
		sbi(*OCR1A_PORT.DDR, OCR1A_BIT);
		sbi(*TIMER.T1.TCCRA, COM1A1_BIT);
		cbi(*TIMER.T1.TCCRA, COM1A0_BIT);
	}
	else if(port == 'B') {
		sbi(*OCR1B_PORT.DDR, OCR1B_BIT);
		sbi(*TIMER.T1.TCCRA, COM1B1_BIT);
		cbi(*TIMER.T1.TCCRA, COM1B0_BIT);
	}
	else if(port == 'C') {
		sbi(*OCR1C_PORT.DDR, OCR1C_BIT);
		sbi(*TIMER.T1.TCCRA, COM1C1_BIT);
		cbi(*TIMER.T1.TCCRA, COM1C0_BIT);
	}
}
#endif

#if defined(USE_TIMER2)
static void PwmTimerInitialize2(uint8_t port) {
	if(port == 'A') {
		sbi(*OCR2_PORT.DDR, OCR2_BIT);
		sbi(*TIMER.T2.TCCRA, COM21_BIT);
		cbi(*TIMER.T2.TCCRA, COM20_BIT);
	}
}
#endif

#if defined(USE_TIMER3)
static void PwmTimerInitialize3(uint8_t port) {
	if(port == 'A') {
		sbi(*OCR3A_PORT.DDR, OCR3A_BIT);
		sbi(*TIMER.T3.TCCRA, COM3A1_BIT);
		cbi(*TIMER.T3.TCCRA, COM3A0_BIT);
	}
	else if(port == 'B') {
		sbi(*OCR3B_PORT.DDR, OCR3B_BIT);
		sbi(*TIMER.T3.TCCRA, COM3B1_BIT);
		cbi(*TIMER.T3.TCCRA, COM3B0_BIT);
	}
	else if(port == 'C') {
		sbi(*OCR3C_PORT.DDR, OCR3C_BIT);
		sbi(*TIMER.T3.TCCRA, COM3C1_BIT);
		cbi(*TIMER.T3.TCCRA, COM3C0_BIT);
	}
}
#endif

#if defined(USE_TIMER4)
static void PwmTimerInitialize4(uint8_t port) {
	if(port == 'A') {
		sbi(*OCR4A_PORT.DDR, OCR4A_BIT);
		sbi(*TIMER.T4.TCCRA, COM4A1_BIT);
		cbi(*TIMER.T4.TCCRA, COM4A0_BIT);
	}
	else if(port == 'B') {
		sbi(*OCR4B_PORT.DDR, OCR4B_BIT);
		sbi(*TIMER.T4.TCCRA, COM4B1_BIT);
		cbi(*TIMER.T4.TCCRA, COM4B0_BIT);
	}
	else if(port == 'C') {
		sbi(*OCR4C_PORT.DDR, OCR4C_BIT);
		sbi(*TIMER.T4.TCCRA, COM4C1_BIT);
		cbi(*TIMER.T4.TCCRA, COM4C0_BIT);
	}
}
#endif

#if defined(USE_TIMER5)
static void PwmTimerInitialize5(uint8_t port) {
	if(port == 'A') {
		sbi(*OCR5A_PORT.DDR, OCR5A_BIT);
		sbi(*TIMER.T5.TCCRA, COM5A1_BIT);
		cbi(*TIMER.T5.TCCRA, COM5A0_BIT);
	}
	else if(port == 'B') {
		sbi(*OCR5B_PORT.DDR, OCR5B_BIT);
		sbi(*TIMER.T5.TCCRA, COM5B1_BIT);
		cbi(*TIMER.T5.TCCRA, COM5B0_BIT);
	}
	else if(port == 'C') {
		sbi(*OCR5C_PORT.DDR, OCR5C_BIT);
		sbi(*TIMER.T5.TCCRA, COM5C1_BIT);
		cbi(*TIMER.T5.TCCRA, COM5C0_BIT);
	}
}
#endif

uint8_t PwmSetter(uint8_t duty) {
	uint16_t result;
	result = duty * 141;
	result >>= 8;
	result += (duty << 1);
	return (uint8_t)result;
}

static void MotorStatusChecker(uint8_t* status, uint8_t* pwm) {
	bool tmp;
	
// 与えられたpwmが100より大きければ100にする．
	if(*pwm > 100) *pwm = 100;
	
// 与えられたpwmが-100より小さければ-100にする．
	else if(*pwm < -100) *pwm = -100;
	
// 与えられたpwmがマイナスの値であれば
// モーターの挙動を反転させ，PWM数値を自然数にする．
	if(*pwm < 0) {
		*pwm = (~(*pwm)+0x01);
		if(bit_is_set(*status, 0))	tmp = true;
		else						tmp = false;
		if(bit_is_set(*status, 1))	sbi(*status, 0);
		else						cbi(*status, 0);
		if(tmp)						sbi(*status, 1);
		else						cbi(*status, 1);
	}
}


#if defined(USE_MOTOR00)
static void SetActionMotor0(uint8_t status, uint8_t pwm) {
	MotorStatusChecker(&status, &pwm);
	if(status & 0x01)	sbi(*MOTOR_00_D1_PORT.PORT, MOTOR_00_D1_BIT);
	else				cbi(*MOTOR_00_D1_PORT.PORT, MOTOR_00_D1_BIT);
	if(status & 0x02)	sbi(*MOTOR_00_D2_PORT.PORT, MOTOR_00_D2_BIT);
	else				cbi(*MOTOR_00_D2_PORT.PORT, MOTOR_00_D2_BIT);
	*MOTOR_00_PWM_OCR = PwmSetter(pwm);
}
#endif

#if defined(USE_MOTOR01)
static void SetActionMotor1(uint8_t status, uint8_t pwm) {
	MotorStatusChecker(&status, &pwm);
	if(status & 0x01)	sbi(*MOTOR_01_D1_PORT.PORT, MOTOR_01_D1_BIT);
	else				cbi(*MOTOR_01_D1_PORT.PORT, MOTOR_01_D1_BIT);
	if(status & 0x02)	sbi(*MOTOR_01_D2_PORT.PORT, MOTOR_01_D2_BIT);
	else				cbi(*MOTOR_01_D2_PORT.PORT, MOTOR_01_D2_BIT);
	*MOTOR_01_PWM_OCR = PwmSetter(pwm);
}
#endif

#if defined(USE_MOTOR02)
static void SetActionMotor2(uint8_t status, uint8_t pwm) {
	MotorStatusChecker(&status, &pwm);
	if(status & 0x01)	sbi(*MOTOR_02_D1_PORT.PORT, MOTOR_02_D1_BIT);
	else				cbi(*MOTOR_02_D1_PORT.PORT, MOTOR_02_D1_BIT);
	if(status & 0x02)	sbi(*MOTOR_02_D2_PORT.PORT, MOTOR_02_D2_BIT);
	else				cbi(*MOTOR_02_D2_PORT.PORT, MOTOR_02_D2_BIT);
	*MOTOR_02_PWM_OCR = PwmSetter(pwm);
}
#endif

#if defined(USE_MOTOR03)
static void SetActionMotor3(uint8_t status, uint8_t pwm) {
	MotorStatusChecker(&status, &pwm);
	if(status & 0x01)	sbi(*MOTOR_03_D1_PORT.PORT, MOTOR_03_D1_BIT);
	else				cbi(*MOTOR_03_D1_PORT.PORT, MOTOR_03_D1_BIT);
	if(status & 0x02)	sbi(*MOTOR_03_D2_PORT.PORT, MOTOR_03_D2_BIT);
	else				cbi(*MOTOR_03_D2_PORT.PORT, MOTOR_03_D2_BIT);
	*MOTOR_03_PWM_OCR = PwmSetter(pwm);
}
#endif

#if defined(USE_MOTOR04)
static void SetActionMotor4(uint8_t status, uint8_t pwm) {
	MotorStatusChecker(&status, &pwm);
	if(status & 0x01)	sbi(*MOTOR_04_D1_PORT.PORT, MOTOR_04_D1_BIT);
	else				cbi(*MOTOR_04_D1_PORT.PORT, MOTOR_04_D1_BIT);
	if(status & 0x02)	sbi(*MOTOR_04_D2_PORT.PORT, MOTOR_04_D2_BIT);
	else				cbi(*MOTOR_04_D2_PORT.PORT, MOTOR_04_D2_BIT);
	*MOTOR_04_PWM_OCR = PwmSetter(pwm);
}
#endif

#if defined(USE_MOTOR05)
static void SetActionMotor5(uint8_t status, uint8_t pwm) {
	MotorStatusChecker(&status, &pwm);
	if(status & 0x01)	sbi(*MOTOR_05_D1_PORT.PORT, MOTOR_05_D1_BIT);
	else				cbi(*MOTOR_05_D1_PORT.PORT, MOTOR_05_D1_BIT);
	if(status & 0x02)	sbi(*MOTOR_05_D2_PORT.PORT, MOTOR_05_D2_BIT);
	else				cbi(*MOTOR_05_D2_PORT.PORT, MOTOR_05_D2_BIT);
	*MOTOR_05_PWM_OCR = PwmSetter(pwm);
}
#endif

#if defined(USE_MOTOR06)
static void SetActionMotor6(uint8_t status, uint8_t pwm) {
	MotorStatusChecker(&status, &pwm);
	if(status & 0x01)	sbi(*MOTOR_06_D1_PORT.PORT, MOTOR_06_D1_BIT);
	else				cbi(*MOTOR_06_D1_PORT.PORT, MOTOR_06_D1_BIT);
	if(status & 0x02)	sbi(*MOTOR_06_D2_PORT.PORT, MOTOR_06_D2_BIT);
	else				cbi(*MOTOR_06_D2_PORT.PORT, MOTOR_06_D2_BIT);
	*MOTOR_06_PWM_OCR = PwmSetter(pwm);
}
#endif

#if defined(USE_MOTOR07)
static void SetActionMotor7(uint8_t status, uint8_t pwm) {
	MotorStatusChecker(&status, &pwm);
	if(status & 0x01)	sbi(*MOTOR_07_D1_PORT.PORT, MOTOR_07_D1_BIT);
	else				cbi(*MOTOR_07_D1_PORT.PORT, MOTOR_07_D1_BIT);
	if(status & 0x02)	sbi(*MOTOR_07_D2_PORT.PORT, MOTOR_07_D2_BIT);
	else				cbi(*MOTOR_07_D2_PORT.PORT, MOTOR_07_D2_BIT);
	*MOTOR_07_PWM_OCR = PwmSetter(pwm);
}
#endif

#if defined(USE_MOTOR08)
static void SetActionMotor8(uint8_t status, uint8_t pwm) {
	MotorStatusChecker(&status, &pwm);
	if(status & 0x01)	sbi(*MOTOR_08_D1_PORT.PORT, MOTOR_08_D1_BIT);
	else				cbi(*MOTOR_08_D1_PORT.PORT, MOTOR_08_D1_BIT);
	if(status & 0x02)	sbi(*MOTOR_08_D2_PORT.PORT, MOTOR_08_D2_BIT);
	else				cbi(*MOTOR_08_D2_PORT.PORT, MOTOR_08_D2_BIT);
	*MOTOR_08_PWM_OCR = PwmSetter(pwm);
}
#endif

#if defined(USE_MOTOR09)
static void SetActionMotor9(uint8_t status, uint8_t pwm) {
	MotorStatusChecker(&status, &pwm);
	if(status & 0x01)	sbi(*MOTOR_09_D1_PORT.PORT, MOTOR_09_D1_BIT);
	else				cbi(*MOTOR_09_D1_PORT.PORT, MOTOR_09_D1_BIT);
	if(status & 0x02)	sbi(*MOTOR_09_D2_PORT.PORT, MOTOR_09_D2_BIT);
	else				cbi(*MOTOR_09_D2_PORT.PORT, MOTOR_09_D2_BIT);
	*MOTOR_09_PWM_OCR = PwmSetter(pwm);
}
#endif

#if defined(USE_MOTOR10)
static void SetActionMotor10(uint8_t status, uint8_t pwm) {
	if(status & 0x01)	sbi(*MOTOR_10_D1_PORT.PORT, MOTOR_10_D1_BIT);
	else				cbi(*MOTOR_10_D1_PORT.PORT, MOTOR_10_D1_BIT);
	if(status & 0x02)	sbi(*MOTOR_10_D2_PORT.PORT, MOTOR_10_D2_BIT);
	else				cbi(*MOTOR_10_D2_PORT.PORT, MOTOR_10_D2_BIT);
}
#endif

#if defined(USE_MOTOR11)
static void SetActionMotor11(uint8_t status, uint8_t pwm) {
	if(status & 0x01)	sbi(*MOTOR_11_D1_PORT.PORT, MOTOR_11_D1_BIT);
	else				cbi(*MOTOR_11_D1_PORT.PORT, MOTOR_11_D1_BIT);
	if(status & 0x02)	sbi(*MOTOR_11_D2_PORT.PORT, MOTOR_11_D2_BIT);
	else				cbi(*MOTOR_11_D2_PORT.PORT, MOTOR_11_D2_BIT);
}
#endif

#if defined(USE_MOTOR12)
static void SetActionMotor12(uint8_t status, uint8_t pwm) {
	if(status & 0x01)	sbi(*MOTOR_12_D1_PORT.PORT, MOTOR_12_D1_BIT);
	else				cbi(*MOTOR_12_D1_PORT.PORT, MOTOR_12_D1_BIT);
	if(status & 0x02)	sbi(*MOTOR_12_D2_PORT.PORT, MOTOR_12_D2_BIT);
	else				cbi(*MOTOR_12_D2_PORT.PORT, MOTOR_12_D2_BIT);
}
#endif

#if defined(USE_MOTOR13)
static void SetActionMotor13(uint8_t status, uint8_t pwm) {
	if(status & 0x01)	sbi(*MOTOR_13_D1_PORT.PORT, MOTOR_13_D1_BIT);
	else				cbi(*MOTOR_13_D1_PORT.PORT, MOTOR_13_D1_BIT);
	if(status & 0x02)	sbi(*MOTOR_13_D2_PORT.PORT, MOTOR_13_D2_BIT);
	else				cbi(*MOTOR_13_D2_PORT.PORT, MOTOR_13_D2_BIT);
}
#endif

#if defined(USE_MOTOR14)
static void SetActionMotor14(uint8_t status, uint8_t pwm) {
	if(status & 0x01)	sbi(*MOTOR_14_D1_PORT.PORT, MOTOR_14_D1_BIT);
	else				cbi(*MOTOR_14_D1_PORT.PORT, MOTOR_14_D1_BIT);
	if(status & 0x02)	sbi(*MOTOR_14_D2_PORT.PORT, MOTOR_14_D2_BIT);
	else				cbi(*MOTOR_14_D2_PORT.PORT, MOTOR_14_D2_BIT);
}
#endif

#endif
