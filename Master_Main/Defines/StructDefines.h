/*
 * StructDefines.h
 *
 * Created: 2014/06/17 20:20:40
 *  Author: tatsuro
 */ 


#ifndef STRUCTDEFINES_H_
#define STRUCTDEFINES_H_


#define NULL	(0x00)

/*
 * IOポートに関するレジスタのアドレスを格納するための構造体を定義
 */
typedef struct {
	uint8_t* DDR;
	uint8_t* PORT;
	uint8_t* PIN;
} st_port;

struct st_io {
	#ifdef DDRA
		st_port PA;
	#endif
	#ifdef DDRB
		st_port PB;
	#endif
	#ifdef DDRC
		st_port PC;
	#endif
	#ifdef DDRD
		st_port PD;
	#endif
	#ifdef DDRE
		st_port PE;
	#endif
	#ifdef DDRF
		st_port PF;
	#endif
	#ifdef DDRG
		st_port PG;
	#endif
	#ifdef DDRH
		st_port PH;
	#endif
	#ifdef DDRJ
		st_port PJ;
	#endif
	#ifdef DDRK
		st_port PK;
	#endif
	#ifdef DDRL
		st_port PL;
	#endif
};

extern struct st_io IO;

/*
 * タイマに関するレジスタのアドレスを格納するための構造体を定義
 */

#if defined(USE_TIMER)
	struct st_timer8 {
		uint8_t* TCCRA;
		uint8_t* TCCRB;
		uint8_t* TCNT;
		uint8_t* OCRA;
		uint8_t* OCRB;
		uint8_t* TCIMSK;
		uint8_t* TCIFR;
	};

	struct st_timer16 {
		uint8_t* TCCRA;
		uint8_t* TCCRB;
		uint8_t* TCCRC;
		uint16_t* TCNT;
		uint16_t* OCRA;
		uint16_t* OCRB;
		uint16_t* OCRC;
		uint16_t* ICR;
		uint8_t* TCIMSK;
		uint8_t* TCIFR;
	};

	struct st_timer {
		#ifdef TCNT0
			struct st_timer8	T0;
		#endif
		#ifdef TCNT1
			struct st_timer16	T1;
		#endif
		#ifdef TCNT2
			struct st_timer8	T2;
		#endif
		#ifdef TCNT3
			struct st_timer16	T3;
		#endif
		#ifdef TCNT4
			struct st_timer16	T4;
		#endif
		#ifdef TCNT5
			struct st_timer16	T5;
		#endif
	};

	extern struct st_timer TIMER;
#endif

/*
 * UARTに関するレジスタのアドレスを格納するための構造体を定義
 */

#if (defined(USE_UART) || defined(USE_MU))
	struct st_uart {
		uint8_t* UCASRA;
		uint8_t* UCASRB;
		uint8_t* UCASRC;
		uint8_t* UDREG;
		uint8_t* UBRREGH;
		uint8_t* UBRREGL;
	};

	struct st_usart {
		#if defined(UDR0) || defined(UDR)
			struct st_uart U0;
		#endif
		#if defined(UDR1)
			struct st_uart U1;
		#endif
		#if defined(UDR2)
			struct st_uart U2;
		#endif
		#if defined(UDR3)
			struct st_uart U3;
		#endif
	};

	extern struct st_usart USART;
#endif

/*
 * ピン割り込みに関するレジスタのアドレスを格納するための構造体を定義
 */

#if defined(USE_EXINT)
	struct st_exint {
		uint8_t* EXICRA;
		uint8_t* EXICRB;
		uint8_t* EXIMSK;
		uint8_t* EXIFR;
	};
	
	extern struct st_exint EXINT;
#endif

/*
 * ピン変化割り込みに関するレジスタのアドレスを格納するための構造体を定義
 */

#if defined(USE_PCINT)
	struct st_pcint {
		uint8_t* PCICREG;
		uint8_t* PCIFREG;
		uint8_t* PCMASK0;
		uint8_t* PCMASK1;
		uint8_t* PCMASK2;
	};
	
	extern struct st_pcint PCINT;
#endif



#endif /* STRUCTDEFINES_H_ */