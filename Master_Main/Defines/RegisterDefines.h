/*
 * RegisterDefines.h
 *
 * Created: 2014/06/17 20:22:49
 *  Author: tatsuro
 */ 


#ifndef REGISTERDEFINES_H_
#define REGISTERDEFINES_H_


#include <avr/io.h>
#include "../globalDef.h"

/*
 * IOポートに関わるレジスタの定義
 */
	#if defined(DDRA)
		#define DDRA_REG	DDRA
		#define PORTA_REG	PORTA
		#define PINA_REG	PINA
	#endif
	#if defined(DDRB)
		#define DDRB_REG	DDRB
		#define PORTB_REG	PORTB
		#define PINB_REG	PINB
	#endif
	#if defined(DDRC)
		#define DDRC_REG	DDRC
		#define PORTC_REG	PORTC
		#define PINC_REG	PINC
	#endif
	#if defined(DDRD)
		#define DDRD_REG	DDRD
		#define PORTD_REG	PORTD
		#define PIND_REG	PIND
	#endif
	#if defined(DDRE)
		#define DDRE_REG	DDRE
		#define PORTE_REG	PORTE
		#define PINE_REG	PINE
	#endif
	#if defined(DDRF)
		#define DDRF_REG	DDRF
		#define PORTF_REG	PORTF
		#define PINF_REG	PINF
	#endif
	#if defined(DDRG)
		#define DDRG_REG	DDRG
		#define PORTG_REG	PORTG
		#define PING_REG	PING
	#endif
	#if defined(DDRH)
		#define DDRH_REG	DDRH
		#define PORTH_REG	PORTH
		#define PINH_REG	PINH
	#endif
	#if defined(DDRJ)
		#define DDRJ_REG	DDRJ
		#define PORTJ_REG	PORTJ
		#define PINJ_REG	PINJ
	#endif
	#if defined(DDRK)
		#define DDRK_REG	DDRK
		#define PORTK_REG	PORTK
		#define PINK_REG	PINK
	#endif
	#if defined(DDRL)
		#define DDRL_REG	DDRL
		#define PORTL_REG	PORTL
		#define PINL_REG	PINL
	#endif

/*
 * タイマーに関わるレジスタの定義
 */
#if defined(USE_TIMER)
	#if defined(TCNT0)
		#define TCCR0_REG	TCCR0
			#define COM01_BIT	COM01
			#define COM00_BIT	COM00
			#define WGM01_BIT	WGM01
			#define WGM00_BIT	WGM00
			#define FOC0_BIT	FOC0
			#define CS02_BIT	CS02
			#define CS01_BIT	CS01
			#define CS00_BIT	CS00
		#define TCNT0_REG	TCNT0
		#define OCR0_REG	OCR0
			#define OCR0_PORT	IO.PB
			#define OCR0_BIT	PB4
		#define TIMSK0_REG	TIMSK
			#define OCIE0_BIT	OCIE0
			#define TOIE0_BIT	TOIE0
		#define TIFR0_REG	TIFR
	#endif
	#ifdef TCNT1
		#define TCCR1A_REG	TCCR1A
			#define COM1A1_BIT	COM1A1
			#define COM1A0_BIT	COM1A0
			#define COM1B1_BIT	COM1B1
			#define COM1B0_BIT	COM1B0
			#define COM1C1_BIT	COM1C1
			#define COM1C0_BIT	COM1C0
			#define WGM11_BIT	WGM11
			#define WGM10_BIT	WGM10
		#define TCCR1B_REG	TCCR1B
			#define ICNC1_BIT	ICNC1
			#define ICES1_BIT	ICES1
			#define WGM13_BIT	WGM13
			#define WGM12_BIT	WGM12
			#define CS12_BIT	CS12
			#define CS11_BIT	CS11
			#define CS10_BIT	CS10
		#define TCCR1C_REG	TCCR1C
		#define TCNT1_REG	TCNT1
		#define OCR1A_REG	OCR1A
			#define OCR1A_PORT	IO.PB
			#define OCR1A_BIT	PB5
		#define OCR1B_REG	OCR1B
			#define OCR1B_PORT	IO.PB
			#define OCR1B_BIT	PB6
		#define OCR1C_REG	OCR1C
			#define OCR1C_PORT	IO.PB
			#define OCR1C_BIT	PB7
		#define ICR1_REG	ICR1
		#define TIMSK1_REG	TIMSK
			#define ICIE1_BIT	TICIE1
			#define OCIE1C_BIT	OCIE1C
			#define OCIE1B_BIT	OCIE1B
			#define OCIE1A_BIT	OCIE1A
			#define TOIE1_BIT	TOIE1
		#define TIFR1_REG	TIFR
	#endif
	#ifdef TCNT2
		#define TCCR2_REG	TCCR2
			#define COM21_BIT	COM21
			#define COM20_BIT	COM20
			#define WGM21_BIT	WGM21
			#define WGM20_BIT	WGM20
			#define FOC2_BIT	FOC2
			#define CS22_BIT	CS22
			#define CS21_BIT	CS21
			#define CS20_BIT	CS20
		#define TCNT2_REG	TCNT2
		#define OCR2_REG	OCR2
			#define OCR2_PORT	IO.PB
			#define OCR2_BIT	PB7
		#define TIMSK2_REG	TIMSK
			#define OCIE2_BIT	OCIE2
			#define TOIE2_BIT	TOIE2
		#define TIFR2_REG	TIFR
	#endif
	#ifdef TCNT3
		#define TCCR3A_REG	TCCR3A
			#define COM3A1_BIT	COM3A1
			#define COM3A0_BIT	COM3A0
			#define COM3B1_BIT	COM3B1
			#define COM3B0_BIT	COM3B0
			#define COM3C1_BIT	COM3C1
			#define COM3C0_BIT	COM3C0
			#define WGM31_BIT	WGM31
			#define WGM30_BIT	WGM30
		#define TCCR3B_REG	TCCR3B
			#define ICNC3_BIT	ICNC3
			#define ICES3_BIT	ICES3
			#define WGM33_BIT	WGM33
			#define WGM32_BIT	WGM32
			#define CS32_BIT	CS32
			#define CS31_BIT	CS31
			#define CS30_BIT	CS30
		#define TCCR3C_REG	TCCR3C
		#define TCNT3_REG	TCNT3
		#define OCR3A_REG	OCR3A
			#define OCR3A_PORT	IO.PE
			#define OCR3A_BIT	PE3
		#define OCR3B_REG	OCR3B
			#define OCR3B_PORT	IO.PE
			#define OCR3B_BIT	PE4
		#define OCR3C_REG	OCR3C
			#define OCR3C_PORT	IO.PE
			#define OCR3C_BIT	PE5
		#define ICR3_REG	ICR3
		#define TIMSK3_REG	TIMSK
			#define ICIE3_BIT	TICIE3
			#define OCIE3C_BIT	OCIE3C
			#define OCIE3B_BIT	OCIE3B
			#define OCIE3A_BIT	OCIE3A
			#define TOIE3_BIT	TOIE3
		#define ETIFR3_REG	ETIFR
	#endif
	#ifdef TCNT4
		#define TCCR4A_REG	TCCR4A
			#define COM4A1_BIT	COM4A1
			#define COM4A0_BIT	COM4A0
			#define COM4B1_BIT	COM4B1
			#define COM4B0_BIT	COM4B0
			#define COM4C1_BIT	COM4C1
			#define COM4C0_BIT	COM4C0
			#define WGM41_BIT	WGM41
			#define WGM40_BIT	WGM40
		#define TCCR4B_REG	TCCR4B
			#define ICNC4_BIT	ICNC4
			#define ICES4_BIT	ICES4
			#define WGM43_BIT	WGM43
			#define WGM42_BIT	WGM42
			#define CS42_BIT	CS42
			#define CS41_BIT	CS41
			#define CS40_BIT	CS40
		#define TCCR4C_REG	TCCR4C
		#define TCNT4_REG	TCNT4
		#define OCR4A_REG	OCR4A
			#define OCR4A_PORT	IO.PH
			#define OCR4A_BIT	PH3
		#define OCR4B_REG	OCR4B
			#define OCR4B_PORT	IO.PH
			#define OCR4B_BIT	PH4
		#define OCR4C_REG	OCR4C
			#define OCR4C_PORT	IO.PH
			#define OCR4C_BIT	PH5
		#define ICR4_REG	ICR4
		#define TIMSK4_REG	TIMSK4
			#define ICIE4_BIT	ICIE4
			#define OCIE4C_BIT	OCIE4C
			#define OCIE4B_BIT	OCIE4B
			#define OCIE4A_BIT	OCIE4A
			#define TOIE4_BIT	TOIE4
		#define TIFR4_REG	TIFR4
	#endif
	#ifdef TCNT5
		#define TCCR5A_REG	TCCR5A
			#define COM5A1_BIT	COM5A1
			#define COM5A0_BIT	COM5A0
			#define COM5B1_BIT	COM5B1
			#define COM5B0_BIT	COM5B0
			#define COM5C1_BIT	COM5C1
			#define COM5C0_BIT	COM5C0
			#define WGM51_BIT	WGM51
			#define WGM50_BIT	WGM50
		#define TCCR5B_REG	TCCR5B
			#define ICNC5_BIT	ICNC5
			#define ICES5_BIT	ICES5
			#define WGM53_BIT	WGM53
			#define WGM52_BIT	WGM52
			#define CS52_BIT	CS52
			#define CS51_BIT	CS51
			#define CS50_BIT	CS50
		#define TCCR5C_REG	TCCR5C
		#define TCNT5_REG	TCNT5
		#define OCR5A_REG	OCR5A
			#define OCR5A_PORT	IO.PL
			#define OCR5A_BIT	PL3
		#define OCR5B_REG	OCR5B
			#define OCR5B_PORT	IO.PL
			#define OCR5B_BIT	PL4
		#define OCR5C_REG	OCR5C
			#define OCR5C_PORT	IO.PL
			#define OCR5C_BIT	PL5
		#define ICR5_REG	ICR5
		#define TIMSK5_REG	TIMSK5
			#define ICIE5_BIT	ICIE5
			#define OCIE5C_BIT	OCIE5C
			#define OCIE5B_BIT	OCIE5B
			#define OCIE5A_BIT	OCIE5A
			#define TOIE5_BIT	TOIE5
		#define TIFR5_REG	TIFR5
	#endif
#endif

/*
 * USARTに関わるレジスタの定義
 */
#if (defined(USE_UART) || defined(USE_MU))
	#if defined(UDR0) || defined(UDR)
		#define UCSR0A_REG	UCSR0A
			#define RXC0_BIT	RXC0
			#define TXC0_BIT	TXC0
			#define UDRE0_BIT	UDRE0
			#define FE0_BIT		FE0
			#define DOR0_BIT	DOR0
			#define UPE_BIT		UPE0
			#define U2X0_BIT	U2X0
			#define MPCM0_BIT	MPCM0
		#define UCSR0B_REG	UCSR0B
			#define RXCIE0_BIT	RXCIE0
			#define TXCIE0_BIT	TXCIE0
			#define UDRIE0_BIT	UDRIE0
			#define RXEN0_BIT	RXEN0
			#define TXEN0_BIT	TXEN0
			#define UCSZ02_BIT	UCSZ02
			#define RXB80_BIT	RXB80
			#define TXB80_BIT	TXB80
		#define UCSR0C_REG	UCSR0C
			#define UMSEL0_BIT	UMSEL0
			#define UPM01_BIT	UPM01
			#define USBS0_BIT	USBS0
			#define UCSZ01_BIT	UCSZ01
			#define UCSZ00_BIT	UCSZ00
			#define UCPOL0_BIT	UCPOL0
		#define UBRR0H_REG	UBRR0H
		#define UBRR0L_REG	UBRR0L
		#define UDR0_REG	UDR0
	#endif
	#if defined(UDR1)
		#define UCSR1A_REG	UCSR1A
			#define RXC1_BIT	RXC1
			#define TXC1_BIT	TXC1
			#define UDRE1_BIT	UDRE1
			#define FE1_BIT		FE1
			#define DOR1_BIT	DOR1
			#define UPE1_BIT	UPE1
			#define U2X1_BIT	U2X1
			#define MPCM1_BIT	MPCM1
		#define UCSR1B_REG	UCSR1B
			#define RXCIE1_BIT	RXCIE1
			#define TXCIE1_BIT	TXCIE1
			#define UDRIE1_BIT	UDRIE1
			#define RXEN1_BIT	RXEN1
			#define TXEN1_BIT	TXEN1
			#define UCSZ12_BIT	UCSZ12
			#define RXB81_BIT	RXB81
			#define TXB81_BIT	TXB81
		#define UCSR1C_REG	UCSR1C
			#define UMSEL1_BIT	UMSEL1
			#define UPM11_BIT	UPM11
			#define USBS1_BIT	USBS1
			#define UCSZ11_BIT	UCSZ11
			#define UCSZ10_BIT	UCSZ10
			#define UCPOL1_BIT	UCPOL1
		#define UBRR1H_REG	UBRR1H
		#define UBRR1L_REG	UBRR1L
		#define UDR1_REG	UDR1
	#endif
	#if defined(UDR2)
		#define UCSR2A_REG	UCSR2A
			#define RXC2_BIT	RXC2
			#define TXC2_BIT	TXC2
			#define UDRE2_BIT	UDRE2
			#define FE2_BIT		FE2
			#define DOR2_BIT	DOR2
			#define UPE2_BIT	UPE2
			#define U2X2_BIT	U2X2
			#define MPCM2_BIT	MPCM2
		#define UCSR2B_REG	UCSR2B
			#define RXCIE2_BIT	RXCIE2
			#define TXCIE2_BIT	TXCIE2
			#define UDRIE2_BIT	UDRIE2
			#define RXEN2_BIT	RXEN2
			#define TXEN2_BIT	TXEN2
			#define UCSZ22_BIT	UCSZ22
			#define RXB82_BIT	RXB82
			#define TXB82_BIT	TXB82
		#define UCSR2C_REG	UCSR2C
			#define UMSEL21_BIT	UMSEL21
			#define UMSEL20_BIT	UMSEL20
			#define UPM21_BIT	UPM21
			#define USBS2_BIT	USBS2
			#define UCSZ21_BIT	UCSZ21
			#define UCSZ20_BIT	UCSZ20
			#define UCPOL2_BIT	UCPOL2
		#define UBRR2H_REG	UBRR2H
		#define UBRR2L_REG	UBRR2L
		#define UDR2_REG	UDR2
	#endif
	#if defined(UDR3)
		#define UCSR3A_REG	UCSR3A
			#define RXC3_BIT	RXC3
			#define TXC3_BIT	TXC3
			#define UDRE3_BIT	UDRE3
			#define FE3_BIT		FE3
			#define DOR3_BIT	DOR3
			#define UPE3_BIT	UPE3
			#define U2X3_BIT	U2X3
			#define MPCM3_BIT	MPCM3
		#define UCSR3B_REG	UCSR3B
			#define RXCIE3_BIT	RXCIE3
			#define TXCIE3_BIT	TXCIE3
			#define UDRIE3_BIT	UDRIE3
			#define RXEN3_BIT	RXEN3
			#define TXEN3_BIT	TXEN3
			#define UCSZ32_BIT	UCSZ32
			#define RXB83_BIT	RXB83
			#define TXB83_BIT	TXB83
		#define UCSR3C_REG	UCSR3C
			#define UMSEL31_BIT	UMSEL31
			#define UMSEL30_BIT	UMSEL30
			#define UPM31_BIT	UPM31
			#define USBS3_BIT	USBS3
			#define UCSZ31_BIT	UCSZ31
			#define UCSZ30_BIT	UCSZ30
			#define UCPOL3_BIT	UCPOL3
		#define UBRR3H_REG	UBRR3H
		#define UBRR3L_REG	UBRR3L
		#define UDR3_REG	UDR3
	#endif
#endif
	
/*
 * 外部割り込みに関わるレジスタの定義
 */
#if defined(USE_EXINT)
	#if defined(EIMSK)
		#define EICRA_REG	EICRA
			#define ISC31_BIT	ISC31
			#define ISC30_BIT	ISC30
			#define ISC21_BIT	ISC21
			#define ISC20_BIT	ISC20
			#define ISC11_BIT	ISC11
			#define ISC10_BIT	ISC10
			#define ISC01_BIT	ISC01
			#define ISC00_BIT	ISC00
		#define EICRB_REG	EICRB
			#define ISC71_BIT	ISC71
			#define ISC70_BIT	ISC70
			#define ISC61_BIT	ISC61
			#define ISC60_BIT	ISC60
			#define ISC51_BIT	ISC51
			#define ISC50_BIT	ISC50
			#define ISC41_BIT	ISC41
			#define ISC40_BIT	ISC40
		#define EIMSK_REG	EIMSK
			#define INT7_BIT	INT7
			#define INT6_BIT	INT6
			#define INT5_BIT	INT5
			#define INT4_BIT	INT4
			#define INT3_BIT	INT3
			#define INT2_BIT	INT2
			#define INT1_BIT	INT1
			#define INT0_BIT	INT0
		#define EIFR_REG	EIFR
	#endif
#endif

/*
 * ピン変化割り込みに関わるレジスタの定義
 */
#if defined(USE_PCINT)
	#if defined(PCIFR)
		#define PCICR_REG	PCICR
			#define PCIE2_BIT	PCIE2
			#define PCIE1_BIT	PCIE1
			#define PCIE0_BIT	PCIE0	
		#define PCIFR_REG	PCIFR
			#define PCIF2_BIT	PCIF2
			#define PCIF1_BIT	PCIF1
			#define PCIF0_BIT	PCIF0	
		#define PCMSK0_REG	PCMSK2
			#define PCINT23_BIT	PCINT23
			#define PCINT22_BIT	PCINT22
			#define PCINT21_BIT	PCINT21
			#define PCINT20_BIT	PCINT20
			#define PCINT19_BIT	PCINT19
			#define PCINT18_BIT	PCINT18
			#define PCINT17_BIT	PCINT17
			#define PCINT16_BIT	PCINT16
		#define PCMSK1_REG	PCMSK1
			#define PCINT15_BIT	PCINT15
			#define PCINT14_BIT	PCINT14
			#define PCINT13_BIT	PCINT13
			#define PCINT12_BIT	PCINT12
			#define PCINT11_BIT	PCINT11
			#define PCINT10_BIT	PCINT10
			#define PCINT9_BIT	PCINT9
			#define PCINT8_BIT	PCINT8
		#define PCMSK2_REG	PCMSK0
			#define PCINT7_BIT	PCINT7
			#define PCINT6_BIT	PCINT6
			#define PCINT5_BIT	PCINT5
			#define PCINT4_BIT	PCINT4
			#define PCINT3_BIT	PCINT3
			#define PCINT2_BIT	PCINT2
			#define PCINT1_BIT	PCINT1
			#define PCINT0_BIT	PCINT0
	#endif
#endif


#endif /* REGISTERDEFINES_H_ */