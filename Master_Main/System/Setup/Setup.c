/*
 * Setup.c
 *
 * Created: 2014/06/19 19:49:12
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include "./Setup.h"
#include "./SetupDef.h"
#include "../../globalDef.h"
#if (defined(USE_UART) || defined(USE_MU))
	#include "../../Communication/Uart/UartDef.h"
#endif
#if defined(USE_MU)
	#include "../../Communication/Mu/MuDef.h"
#endif
#if defined(USE_ENCODER)
	#include "../../Input/Encoder/EncoderDef.h"
#endif
#if defined(USE_EXINT)
	#include "../../Input/Exint/ExintDef.h"
#endif
#if defined(USE_MOTOR)
	#include "../../Output/Motor/MotorDef.h"
#endif
#if defined(USE_SERVO)
	#include "../../Output/Servo/ServoDef.h"
#endif
#if defined(USE_SAFETY)
	#include "../../System/Safety/SafetyDef.h"
#endif


struct st_io IO;
#if defined(USE_TIMER)
	struct st_timer TIMER;
#endif
#if (defined(USE_UART) || defined(USE_MU))
	struct st_usart USART;
#endif
#if defined(USE_EXINT)
	struct st_exint EXINT;
#endif
#if defined(USE_PCINT)
	struct st_pcint PCINT;
#endif


void SystemSetup(void) {
	IORegSetup();			// Setup.c
	#if defined(USE_TIMER)
		TimerRegSetup();	// Setup.c
		TimerSetup();		// Setup.c
	#endif
	#if (defined(USE_UART) || defined(USE_MU))
		UartRegSetup();		// Setup.c
		UartSetup();		// Uart.c
	#endif
	#if defined(USE_EXINT)
		ExintRegSetup();	// Setup.c
	#endif
	#if defined(USE_PCINT)
		PcintRegSetup();	// Setup.c
	#endif
	
	#if defined(USE_EXINT)
		ExintSetup();
	#endif
	#if defined(USE_PCINT)
		PcintSetup();
	#endif
	#if defined(USE_ENCODER)
		EncoderSetup();		// Encoder.c
	#endif
	#if defined(USE_MU)
		MuSetup();			// Mu.c
	#endif
	
	#if defined(USE_MOTOR)
		MotorSetup();		// Motor.c
	#endif
	#if defined(USE_SERVO)
		ServoSetup();		// Servo.c
	#endif
	
	#if defined(USE_SAFETY)
		SafetySetup();		// Safety.c
	#endif
}

static void IORegSetup(void) {
	#ifdef DDRA
		IO.PA.DDR =		(uint8_t*)&DDRA_REG;
		IO.PA.PORT =	(uint8_t*)&PORTA_REG;
		IO.PA.PIN =		(uint8_t*)&PINA_REG;
	#endif
	#ifdef DDRB
		IO.PB.DDR =		(uint8_t*)&DDRB_REG;
		IO.PB.PORT =	(uint8_t*)&PORTB_REG;
		IO.PB.PIN =		(uint8_t*)&PINB_REG;
	#endif
	#ifdef DDRC
		IO.PC.DDR =		(uint8_t*)&DDRC_REG;
		IO.PC.PORT =	(uint8_t*)&PORTC_REG;
		IO.PC.PIN =		(uint8_t*)&PINC_REG;
	#endif
	#ifdef DDRD
		IO.PD.DDR =		(uint8_t*)&DDRD_REG;
		IO.PD.PORT =	(uint8_t*)&PORTD_REG;
		IO.PD.PIN =		(uint8_t*)&PIND_REG;
	#endif
	#ifdef DDRE
		IO.PE.DDR =		(uint8_t*)&DDRE_REG;
		IO.PE.PORT =	(uint8_t*)&PORTE_REG;
		IO.PE.PIN =		(uint8_t*)&PINE_REG;
	#endif
	#ifdef DDRF
		IO.PF.DDR =		(uint8_t*)&DDRF_REG;
		IO.PF.PORT =	(uint8_t*)&PORTF_REG;
		IO.PF.PIN =		(uint8_t*)&PINF_REG;
	#endif
	#ifdef DDRG
		IO.PG.DDR =		(uint8_t*)&DDRG_REG;
		IO.PG.PORT =	(uint8_t*)&PORTG_REG;
		IO.PG.PIN =		(uint8_t*)&PING_REG;
	#endif
	#ifdef DDRH
		IO.PH.DDR =		(uint8_t*)&DDRH_REG;
		IO.PH.PORT =	(uint8_t*)&PORTH_REG;
		IO.PH.PIN =		(uint8_t*)&PINH_REG;
	#endif
	#ifdef DDRJ
		IO.PJ.DDR =		(uint8_t*)&DDRJ_REG;
		IO.PJ.PORT =	(uint8_t*)&PORTJ_REG;
		IO.PJ.PIN =		(uint8_t*)&PINJ_REG;
	#endif
	#ifdef DDRK
		IO.PK.DDR =		(uint8_t*)&DDRK_REG;
		IO.PK.PORT =	(uint8_t*)&PORTK_REG;
		IO.PK.PIN =		(uint8_t*)&PINK_REG;
	#endif
	#ifdef DDRL
		IO.PL.DDR =		(uint8_t*)&DDRL_REG;
		IO.PL.PORT =	(uint8_t*)&PORTL_REG;
		IO.PL.PIN =		(uint8_t*)&PINL_REG;
	#endif
}

#if defined(USE_TIMER)
static void TimerRegSetup() {
	#if defined(TCNT0)
		TIMER.T0.TCCRA =	(uint8_t*)&TCCR0_REG;
		TIMER.T0.TCCRB =	(uint8_t*)&TCCR0_REG;
		TIMER.T0.TCNT =		(uint8_t*)&TCNT0_REG;
		TIMER.T0.OCRA =		(uint8_t*)&OCR0_REG;
		TIMER.T0.OCRB =		(uint8_t*)&OCR0_REG;
		TIMER.T0.TCIMSK =	(uint8_t*)&TIMSK0_REG;
		TIMER.T0.TCIFR =	(uint8_t*)&TIFR0_REG;
	#endif
	#if defined(TCNT1)
		TIMER.T1.TCCRA =	(uint8_t*)&TCCR1A_REG;
		TIMER.T1.TCCRB =	(uint8_t*)&TCCR1B_REG;
		TIMER.T1.TCCRC =	(uint8_t*)&TCCR1C_REG;
		TIMER.T1.TCNT =		(uint16_t*)&TCNT1_REG;
		TIMER.T1.OCRA =		(uint16_t*)&OCR1A_REG;
		TIMER.T1.OCRB =		(uint16_t*)&OCR1B_REG;
		TIMER.T1.OCRC =		(uint16_t*)&OCR1C_REG;
		TIMER.T1.ICR =		(uint16_t*)&ICR1_REG;
		TIMER.T1.TCIMSK =	(uint8_t*)&TIMSK1_REG;
		TIMER.T1.TCIFR =	(uint8_t*)&TIFR1_REG;
	#endif
	#if defined(TCNT2)
		TIMER.T2.TCCRA =	(uint8_t*)&TCCR2_REG;
		TIMER.T2.TCCRB =	(uint8_t*)&TCCR2_REG;
		TIMER.T2.TCNT =		(uint8_t*)&TCNT2_REG;
		TIMER.T2.OCRA =		(uint8_t*)&OCR2_REG;
		TIMER.T2.OCRB =		(uint8_t*)&OCR2_REG;
		TIMER.T2.TCIMSK =	(uint8_t*)&TIMSK2_REG;
		TIMER.T2.TCIFR =	(uint8_t*)&TIFR2_REG;
	#endif
	#if defined(TCNT3)
		TIMER.T3.TCCRA =	(uint8_t*)&TCCR3A_REG;
		TIMER.T3.TCCRB =	(uint8_t*)&TCCR3B_REG;
		TIMER.T3.TCCRC =	(uint8_t*)&TCCR3C_REG;
		TIMER.T3.TCNT =		(uint16_t*)&TCNT3_REG;
		TIMER.T3.OCRA =		(uint16_t*)&OCR3A_REG;
		TIMER.T3.OCRB =		(uint16_t*)&OCR3B_REG;
		TIMER.T3.OCRC =		(uint16_t*)&OCR3C_REG;
		TIMER.T3.ICR =		(uint16_t*)&ICR3_REG;
		TIMER.T3.TCIMSK =	(uint8_t*)&TIMSK3_REG;
		TIMER.T3.TCIFR =	(uint8_t*)&ETIFR3_REG;
	#endif
	#if defined(TCNT4)
		TIMER.T4.TCCRA =	(uint8_t*)&TCCR4A_REG;
		TIMER.T4.TCCRB =	(uint8_t*)&TCCR4B_REG;
		TIMER.T4.TCCRC =	(uint8_t*)&TCCR4C_REG;
		TIMER.T4.TCNT =		(uint16_t*)&TCNT4_REG;
		TIMER.T4.OCRA =		(uint16_t*)&OCR4A_REG;
		TIMER.T4.OCRB =		(uint16_t*)&OCR4B_REG;
		TIMER.T4.OCRC =		(uint16_t*)&OCR4C_REG;
		TIMER.T4.ICR =		(uint16_t*)&ICR4_REG;
		TIMER.T4.TCIMSK =	(uint8_t*)&TIMSK4_REG;
		TIMER.T4.TCIFR =	(uint8_t*)&TIFR4_REG;
	#endif
	#if defined(TCNT5)
		TIMER.T5.TCCRA =	(uint8_t*)&TCCR5A_REG;
		TIMER.T5.TCCRB =	(uint8_t*)&TCCR5B_REG;
		TIMER.T5.TCCRC =	(uint8_t*)&TCCR5C_REG;
		TIMER.T5.TCNT =		(uint16_t*)&TCNT5_REG;
		TIMER.T5.OCRA =		(uint16_t*)&OCR5A_REG;
		TIMER.T5.OCRB =		(uint16_t*)&OCR5B_REG;
		TIMER.T5.OCRC =		(uint16_t*)&OCR5C_REG;
		TIMER.T5.ICR =		(uint16_t*)&ICR5_REG;
		TIMER.T5.TCIMSK =	(uint8_t*)&TIMSK5_REG;
		TIMER.T5.TCIFR =	(uint8_t*)&TIFR5_REG;
	#endif
}
#endif

#if defined(USE_TIMER)
static void TimerSetup() {
	#if defined(USE_TIMER0)
		if(TIMER0_WGM & 0x01)	sbi(*TIMER.T0.TCCRA, WGM00_BIT);
		else					cbi(*TIMER.T0.TCCRA, WGM00_BIT);
		if(TIMER0_WGM & 0x02)	sbi(*TIMER.T0.TCCRA, WGM01_BIT);
		else					cbi(*TIMER.T0.TCCRA, WGM01_BIT);
		//if(TIMER0_WGM & 0x04)	//sbi(*TIMER.T0.TCCRB, WGM02_BIT);
		//else					//cbi(*TIMER.T0.TCCRB, WGM02_BIT);
		if(TIMER0_CS & 0x01)	sbi(*TIMER.T0.TCCRB, CS00_BIT);
		else					cbi(*TIMER.T0.TCCRB, CS00_BIT);
		if(TIMER0_CS & 0x02)	sbi(*TIMER.T0.TCCRB, CS01_BIT);
		else					cbi(*TIMER.T0.TCCRB, CS01_BIT);
		if(TIMER0_CS & 0x04)	sbi(*TIMER.T0.TCCRB, CS02_BIT);
		else					cbi(*TIMER.T0.TCCRB, CS02_BIT);
	#endif
	#if defined(USE_TIMER1)
		if(TIMER1_WGM & 0x01)	sbi(*TIMER.T1.TCCRA, WGM10_BIT);
		else					cbi(*TIMER.T1.TCCRA, WGM10_BIT);
		if(TIMER1_WGM & 0x02)	sbi(*TIMER.T1.TCCRA, WGM11_BIT);
		else					cbi(*TIMER.T1.TCCRA, WGM11_BIT);
		if(TIMER1_WGM & 0x04)	sbi(*TIMER.T1.TCCRB, WGM12_BIT);
		else					cbi(*TIMER.T1.TCCRB, WGM12_BIT);
		if(TIMER1_WGM & 0x08)	sbi(*TIMER.T1.TCCRB, WGM13_BIT);
		else					cbi(*TIMER.T1.TCCRB, WGM13_BIT);
		if(TIMER1_CS & 0x01)	sbi(*TIMER.T1.TCCRB, CS10_BIT);
		else					cbi(*TIMER.T1.TCCRB, CS10_BIT);
		if(TIMER1_CS & 0x02)	sbi(*TIMER.T1.TCCRB, CS11_BIT);
		else					cbi(*TIMER.T1.TCCRB, CS11_BIT);
		if(TIMER1_CS & 0x04)	sbi(*TIMER.T1.TCCRB, CS12_BIT);
		else					cbi(*TIMER.T1.TCCRB, CS12_BIT);
	#endif
	#if defined(USE_TIMER2)
		if(TIMER2_WGM & 0x01)	sbi(*TIMER.T2.TCCRA, WGM20_BIT);
		else					cbi(*TIMER.T2.TCCRA, WGM20_BIT);
		if(TIMER2_WGM & 0x02)	sbi(*TIMER.T2.TCCRA, WGM21_BIT);
		else					cbi(*TIMER.T2.TCCRA, WGM21_BIT);
		//if(TIMER2_WGM & 0x04)	//sbi(*TIMER.T2.TCCRB, WGM22_BIT);
		//else					//cbi(*TIMER.T2.TCCRB, WGM22_BIT);
		if(TIMER2_CS & 0x01)	sbi(*TIMER.T2.TCCRB, CS20_BIT);
		else					cbi(*TIMER.T2.TCCRB, CS20_BIT);
		if(TIMER2_CS & 0x02)	sbi(*TIMER.T2.TCCRB, CS21_BIT);
		else					cbi(*TIMER.T2.TCCRB, CS21_BIT);
		if(TIMER2_CS & 0x04)	sbi(*TIMER.T2.TCCRB, CS22_BIT);
		else					cbi(*TIMER.T2.TCCRB, CS22_BIT);
	#endif
	#if defined(USE_TIMER3)
		if(TIMER3_WGM & 0x01)	sbi(*TIMER.T3.TCCRA, WGM30_BIT);
		else					cbi(*TIMER.T3.TCCRA, WGM30_BIT);
		if(TIMER3_WGM & 0x02)	sbi(*TIMER.T3.TCCRA, WGM31_BIT);
		else					cbi(*TIMER.T3.TCCRA, WGM31_BIT);
		if(TIMER3_WGM & 0x04)	sbi(*TIMER.T3.TCCRB, WGM32_BIT);
		else					cbi(*TIMER.T3.TCCRB, WGM32_BIT);
		if(TIMER3_WGM & 0x08)	sbi(*TIMER.T3.TCCRB, WGM33_BIT);
		else					cbi(*TIMER.T3.TCCRB, WGM33_BIT);
		if(TIMER3_CS & 0x01)	sbi(*TIMER.T3.TCCRB, CS30_BIT);
		else					cbi(*TIMER.T3.TCCRB, CS30_BIT);
		if(TIMER3_CS & 0x02)	sbi(*TIMER.T3.TCCRB, CS31_BIT);
		else					cbi(*TIMER.T3.TCCRB, CS31_BIT);
		if(TIMER3_CS & 0x04)	sbi(*TIMER.T3.TCCRB, CS32_BIT);
		else					cbi(*TIMER.T3.TCCRB, CS32_BIT);
	#endif
	#if defined(USE_TIMER4)
		if(TIMER4_WGM & 0x01)	sbi(*TIMER.T4.TCCRA, WGM40_BIT);
		else					cbi(*TIMER.T4.TCCRA, WGM40_BIT);
		if(TIMER4_WGM & 0x02)	sbi(*TIMER.T4.TCCRA, WGM41_BIT);
		else					cbi(*TIMER.T4.TCCRA, WGM41_BIT);
		if(TIMER4_WGM & 0x04)	sbi(*TIMER.T4.TCCRB, WGM42_BIT);
		else					cbi(*TIMER.T4.TCCRB, WGM42_BIT);
		if(TIMER4_WGM & 0x08)	sbi(*TIMER.T4.TCCRB, WGM43_BIT);
		else					cbi(*TIMER.T4.TCCRB, WGM43_BIT);
		if(TIMER4_CS & 0x01)	sbi(*TIMER.T4.TCCRB, CS40_BIT);
		else					cbi(*TIMER.T4.TCCRB, CS40_BIT);
		if(TIMER4_CS & 0x02)	sbi(*TIMER.T4.TCCRB, CS41_BIT);
		else					cbi(*TIMER.T4.TCCRB, CS41_BIT);
		if(TIMER4_CS & 0x04)	sbi(*TIMER.T4.TCCRB, CS42_BIT);
		else					cbi(*TIMER.T4.TCCRB, CS42_BIT);
	#endif
	#if defined(USE_TIMER5)
		if(TIMER5_WGM & 0x01)	sbi(*TIMER.T5.TCCRA, WGM50_BIT);
		else					cbi(*TIMER.T5.TCCRA, WGM50_BIT);
		if(TIMER5_WGM & 0x02)	sbi(*TIMER.T5.TCCRA, WGM51_BIT);
		else					cbi(*TIMER.T5.TCCRA, WGM51_BIT);
		if(TIMER5_WGM & 0x04)	sbi(*TIMER.T5.TCCRB, WGM52_BIT);
		else					cbi(*TIMER.T5.TCCRB, WGM52_BIT);
		if(TIMER5_WGM & 0x08)	sbi(*TIMER.T5.TCCRB, WGM53_BIT);
		else					cbi(*TIMER.T5.TCCRB, WGM53_BIT);
		if(TIMER5_CS & 0x01)	sbi(*TIMER.T5.TCCRB, CS50_BIT);
		else					cbi(*TIMER.T5.TCCRB, CS50_BIT);
		if(TIMER5_CS & 0x02)	sbi(*TIMER.T5.TCCRB, CS51_BIT);
		else					cbi(*TIMER.T5.TCCRB, CS51_BIT);
		if(TIMER5_CS & 0x04)	sbi(*TIMER.T5.TCCRB, CS52_BIT);
		else					cbi(*TIMER.T5.TCCRB, CS52_BIT);
	#endif
}
#endif

#if (defined(USE_UART) || defined(USE_MU))
static void UartRegSetup() {
	#if defined(UDR0) || defined(UDR)
		USART.U0.UCASRA =	(uint8_t*)&UCSR0A_REG;
		USART.U0.UCASRB =	(uint8_t*)&UCSR0B_REG;
		USART.U0.UCASRC =	(uint8_t*)&UCSR0C_REG;
		USART.U0.UBRREGH =	(uint8_t*)&UBRR0H_REG;
		USART.U0.UBRREGL =	(uint8_t*)&UBRR0L_REG;
		USART.U0.UDREG =	(uint8_t*)&UDR0_REG;
	#endif
	#if defined(UDR1)
		USART.U1.UCASRA =	(uint8_t*)&UCSR1A_REG;
		USART.U1.UCASRB =	(uint8_t*)&UCSR1B_REG;
		USART.U1.UCASRC =	(uint8_t*)&UCSR1C_REG;
		USART.U1.UBRREGH =	(uint8_t*)&UBRR1H_REG;
		USART.U1.UBRREGL =	(uint8_t*)&UBRR1L_REG;
		USART.U1.UDREG =	(uint8_t*)&UDR1_REG;
	#endif
	#if defined(UDR2)
		USART.U2.UCASRA =	(uint8_t*)&UCSR2A_REG;
		USART.U2.UCASRB =	(uint8_t*)&UCSR2B_REG;
		USART.U2.UCASRC =	(uint8_t*)&UCSR2C_REG;
		USART.U2.UBRREGH =	(uint8_t*)&UBRR2H_REG;
		USART.U2.UBRREGL =	(uint8_t*)&UBRR2L_REG;
		USART.U2.UDREG =	(uint8_t*)&UDR2_REG;
	#endif
	#if defined(UDR3)
		USART.U3.UCASRA =	(uint8_t*)&UCSR3A_REG;
		USART.U3.UCASRB =	(uint8_t*)&UCSR3B_REG;
		USART.U3.UCASRC =	(uint8_t*)&UCSR3C_REG;
		USART.U3.UBRREGH =	(uint8_t*)&UBRR3H_REG;
		USART.U3.UBRREGL =	(uint8_t*)&UBRR3L_REG;
		USART.U3.UDREG =	(uint8_t*)&UDR3_REG;
	#endif
}
#endif

#if defined(USE_EXINT)
static void ExintRegSetup() {
	#if defined(EIMSK)
		EXINT.EXICRA =	(uint8_t*)&EICRA_REG;
		EXINT.EXICRB =	(uint8_t*)&EICRB_REG;
		EXINT.EXIMSK =	(uint8_t*)&EIMSK_REG;
		EXINT.EXIFR =	(uint8_t*)&EIFR_REG;
	#endif
}
#endif

#if defined(USE_PCINT)
static void PcintRegSetup() {
	#if defined(PCICR)
		PCINT.PCICREG =	(uint8_t*)&PCICR_REG;
		PCINT.PCIFREG =	(uint8_t*)&PCIFR_REG;
		PCINT.PCMASK0 =	(uint8_t*)&PCMSK0_REG;
		PCINT.PCMASK1 =	(uint8_t*)&PCMSK1_REG;
		PCINT.PCMASK2 =	(uint8_t*)&PCMSK2_REG;
	#endif
}
#endif
