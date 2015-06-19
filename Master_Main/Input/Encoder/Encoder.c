/*
 * Encoder.c
 *
 * Created: 2014/06/19 18:15:17
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include "../../globalDef.h"

#if defined(USE_ENCODER)

#include <avr/interrupt.h>
#include "./Encoder.h"
#include "./EncoderDef.h"
#if defined(USE_EXINT)
#include "../Exint/ExintDef.h"
#endif

volatile uint16_t EncoderArray[USING_ENCODER];

#if defined(USE_TIMER)
	void (*EncoderTimerInitialize[6])(void);
#endif

void EncoderSetup(void) {
	#if (defined(ICIE1_BIT) && defined(USE_TIMER))
		EncoderTimerInitialize[1] = EncoderTimerInitialize0;
	#endif
	#if (defined(ICIE3_BIT) && defined(USE_TIMER))
		EncoderTimerInitialize[3] = EncoderTimerInitialize1;
	#endif
	#if (defined(ICIE4_BIT) && defined(USE_TIMER))
		EncoderTimerInitialize[4] = EncoderTimerInitialize2;
	#endif
	#if (defined(ICIE5_BIT) && defined(USE_TIMER))
		EncoderTimerInitialize[5] = EncoderTimerInitialize3;
	#endif
}

void EncoderInitialize(void) {
	uint8_t loop;
	
	#if defined(USE_ENCODER0)
		cbi(*ENCODER_0_PORT.DDR, ENCODER_0_BIT);
		#if (ENCODER0_MODE == 'T')
			EncoderTimerInitialize[ENCODER0_FUNC_NO]();
		#elif (ENCODER0_MODE == 'E')
			sbi(*ENCODER_0_PORT.PORT, ENCODER_0_BIT);
			ExintInitialize[ENCODER0_FUNC_NO]();
		#endif
	#endif
	
	#if defined(USE_ENCODER1)
		cbi(*ENCODER_1_PORT.DDR, ENCODER_1_BIT);
		#if (ENCODER1_MODE == 'T')
			EncoderTimerInitialize[ENCODER1_FUNC_NO]();
		#elif (ENCODER1_MODE == 'E')
			sbi(*ENCODER_1_PORT.PORT, ENCODER_1_BIT);
			ExintInitialize[ENCODER1_FUNC_NO]();
		#endif
	#endif

	#if defined(USE_ENCODER2)
		cbi(*ENCODER_2_PORT.DDR, ENCODER_2_BIT);
		#if (ENCODER2_MODE == 'T')
			sbi(*ENCODER_2_PORT.PORT, ENCODER_2_BIT);
			EncoderTimerInitialize[ENCODER2_FUNC_NO]();
		#elif (ENCODER2_MODE == 'E')
			ExintInitialize[ENCODER2_FUNC_NO]();
		#endif
	#endif

	#if defined(USE_ENCODER3)
		cbi(*ENCODER_3_PORT.DDR, ENCODER_3_BIT);
		#if (ENCODER3_MODE == 'T')
			EncoderTimerInitialize[ENCODER3_FUNC_NO]();
		#elif (ENCODER3_MODE == 'E')
			sbi(*ENCODER_3_PORT.PORT, ENCODER_3_BIT);
			ExintInitialize[ENCODER3_FUNC_NO]();
		#endif
	#endif

	#if defined(USE_ENCODER4)
		cbi(*ENCODER_4_PORT.DDR, ENCODER_4_BIT);
		#if (ENCODER4_MODE == 'T')
			EncoderTimerInitialize[ENCODER4_FUNC_NO]();
		#elif (ENCODER4_MODE == 'E')
			sbi(*ENCODER_4_PORT.PORT, ENCODER_4_BIT);
			ExintInitialize[ENCODER4_FUNC_NO]();
		#endif
	#endif

	#if defined(USE_ENCODER5)
		cbi(*ENCODER_5_PORT.DDR, ENCODER_5_BIT);
		#if (ENCODER5_MODE == 'T')
			EncoderTimerInitialize[ENCODER5_FUNC_NO]();
		#elif (ENCODER5_MODE == 'E')
			sbi(*ENCODER_5_PORT.PORT, ENCODER_5_BIT);
			ExintInitialize[ENCODER5_FUNC_NO]();
		#endif
	#endif

	#if defined(USE_ENCODER6)
		cbi(*ENCODER_6_PORT.DDR, ENCODER_6_BIT);
		#if (ENCODER6_MODE == 'T')
			EncoderTimerInitialize[ENCODER6_FUNC_NO]();
		#elif (ENCODER6_MODE == 'E')
			sbi(*ENCODER_6_PORT.PORT, ENCODER_6_BIT);
			ExintInitialize[ENCODER6_FUNC_NO]();
		#endif
	#endif

	#if defined(USE_ENCODER7)
		cbi(*ENCODER_7_PORT.DDR, ENCODER_7_BIT);
		#if (ENCODER7_MODE == 'T')
			EncoderTimerInitialize[ENCODER7_FUNC_NO]();
		#elif (ENCODER7_MODE == 'E')
			sbi(*ENCODER_7_PORT.PORT, ENCODER_7_BIT);
			ExintInitialize[ENCODER7_FUNC_NO]();
		#endif
	#endif

	#if defined(USE_ENCODER8)
		cbi(*ENCODER_8_PORT.DDR, ENCODER_8_BIT);
		#if (ENCODER8_MODE == 'T')
			EncoderTimerInitialize[ENCODER8_FUNC_NO]();
		#elif (ENCODER8_MODE == 'E')
			sbi(*ENCODER_8_PORT.PORT, ENCODER_8_BIT);
			ExintInitialize[ENCODER8_FUNC_NO]();
		#endif
	#endif

	#if defined(USE_ENCODER9)
		cbi(*ENCODER_9_PORT.DDR, ENCODER_9_BIT);
		#if (ENCODER9_MODE == 'T')
			EncoderTimerInitialize[ENCODER9_FUNC_NO]();
		#elif (ENCODER9_MODE == 'E')
			sbi(*ENCODER_9_PORT.PORT, ENCODER_9_BIT);
			ExintInitialize[ENCODER9_FUNC_NO]();
		#endif
	#endif

	#if defined(USE_ENCODER10)
		cbi(*ENCODER_10_PORT.DDR, ENCODER_10_BIT);
		#if (ENCODER10_MODE == 'T')
			EncoderTimerInitialize[ENCODER10_FUNC_NO]();
		#elif (ENCODER10_MODE == 'E')
			sbi(*ENCODER_10_PORT.PORT, ENCODER_10_BIT);
			ExintInitialize[ENCODER10_FUNC_NO]();
		#endif
	#endif

	#if defined(USE_ENCODER11)
		cbi(*ENCODER_11_PORT.DDR, ENCODER_11_BIT);
		#if (ENCODER11_MODE == 'T')
			EncoderTimerInitialize[ENCODER11_FUNC_NO]();
		#elif (ENCODER11_MODE == 'E')
			sbi(*ENCODER_11_PORT.PORT, ENCODER_11_BIT);
			ExintInitialize[ENCODER11_FUNC_NO]();
		#endif
	#endif

	#if defined(USE_ENCODER12)
		cbi(*ENCODER_12_PORT.DDR, ENCODER_12_BIT);
		#if (ENCODER12_MODE == 'T')
			EncoderTimerInitialize[ENCODER12_FUNC_NO]();
		#elif (ENCODER12_MODE == 'E')
			sbi(*ENCODER_12_PORT.PORT, ENCODER_12_BIT);
			ExintInitialize[ENCODER12_FUNC_NO]();
		#endif
	#endif
	
	for(loop=0; loop<USING_ENCODER; loop++) {
		EncoderArray[loop] = 0;
	}
}

#if defined(USE_TIMER1)
static void EncoderTimerInitialize0(void) {
	*TIMER.T1.TCCRB |= (1<<ICNC1_BIT) | (1<<ICES1_BIT);
	*TIMER.T1.TCIMSK |= (1<<ICIE1_BIT);
}
#endif

#if defined(USE_TIMER3)
static void EncoderTimerInitialize1(void) {
	*TIMER.T3.TCCRB |= (1<<ICNC3_BIT) | (1<<ICES3_BIT);
	*TIMER.T3.TCIMSK |= (1<<ICIE3_BIT);
}
#endif

#if defined(USE_TIMER4)
static void EncoderTimerInitialize2(void) {
	*TIMER.T4.TCCRB |= (1<<ICNC4_BIT) | (1<<ICES4_BIT);
	*TIMER.T4.TCIMSK |= (1<<ICIE4_BIT);
}
#endif

#if defined(USE_TIMER5)
static void EncoderTimerInitialize3(void) {
	*TIMER.T5.TCCRB |= (1<<ICNC5_BIT) | (1<<ICES5_BIT);
	*TIMER.T5.TCIMSK |= (1<<ICIE5_BIT);
}
#endif


#if defined(USE_ENCODER0)
void ClearEncoder0(void) {
	EncoderArray[0] = 0;
}
#endif

#if defined(USE_ENCODER1)
void ClearEncoder1(void) {
	EncoderArray[1] = 0;
}
#endif

#if defined(USE_ENCODER2)
void ClearEncoder2(void) {
	EncoderArray[2] = 0;
}
#endif

#if defined(USE_ENCODER3)
void ClearEncoder3(void) {
	EncoderArray[3] = 0;
}
#endif

#if defined(USE_ENCODER4)
void ClearEncoder4(void) {
	EncoderArray[4] = 0;
}
#endif

#if defined(USE_ENCODER5)
void ClearEncoder5(void) {
	EncoderArray[5] = 0;
}
#endif

#if defined(USE_ENCODER6)
void ClearEncoder6(void) {
	EncoderArray[6] = 0;
}
#endif

#if defined(USE_ENCODER7)
void ClearEncoder7(void) {
	EncoderArray[7] = 0;
}
#endif

#if defined(USE_ENCODER8)
void ClearEncoder8(void) {
	EncoderArray[8] = 0;
}
#endif

#if defined(USE_ENCODER9)
void ClearEncoder9(void) {
	EncoderArray[9] = 0;
}
#endif

#if defined(USE_ENCODER10)
void ClearEncoder10(void) {
	EncoderArray[10] = 0;
}
#endif

#if defined(USE_ENCODER11)
void ClearEncoder11(void) {
	EncoderArray[11] = 0;
}
#endif

#if defined(USE_ENCODER12)
void ClearEncoder12(void) {
	EncoderArray[12] = 0;
}
#endif

#if defined(USE_ENCODER0)
	#if (ENCODER0_MODE == 'T')
		#if (ENCODER0_FUNC_NO == 1)
			ISR(TIMER1_CAPT_vect) {
				EncoderArray[0]++;
			}
		#elif (ENCODER0_FUNC_NO == 3)
			ISR(TIMER3_CAPT_vect) {
				EncoderArray[0]++;
			}
		#elif (ENCODER0_FUNC_NO == 4)
			ISR(TIMER4_CAPT_vect) {
				EncoderArray[0]++;
			}
		#elif (ENCODER0_FUNC_NO == 5)
			ISR(TIMER5_CAPT_vect) {
				EncoderArray[0]++;
			}
		#endif
	#elif (ENCODER0_MODE == 'E')
		#if (ENCODER0_FUNC_NO == 0)
			ISR(INT0_vect) {
				EncoderArray[0]++;
			}
		#elif (ENCODER0_FUNC_NO == 1)
			ISR(INT1_vect) {
				EncoderArray[0]++;
			}
		#elif (ENCODER0_FUNC_NO == 2)
			ISR(INT2_vect) {
				EncoderArray[0]++;
			}
		#elif (ENCODER0_FUNC_NO == 3)
			ISR(INT3_vect) {
				EncoderArray[0]++;
			}
		#elif (ENCODER0_FUNC_NO == 4)
			ISR(INT4_vect) {
				EncoderArray[0]++;
			}
		#elif (ENCODER0_FUNC_NO == 5)
			ISR(INT5_vect) {
				EncoderArray[0]++;
			}
		#elif (ENCODER0_FUNC_NO == 6)
			ISR(INT6_vect) {
				EncoderArray[0]++;
			}
		#elif (ENCODER0_FUNC_NO == 7)
			ISR(INT7_vect) {
				EncoderArray[0]++;
			}
		#endif
	#endif
#endif

#if defined(USE_ENCODER1)
	#if (ENCODER1_MODE == 'T')
		#if (ENCODER1_FUNC_NO == 1)
			ISR(TIMER1_CAPT_vect) {
				EncoderArray[1]++;
			}
		#elif (ENCODER1_FUNC_NO == 3)
			ISR(TIMER3_CAPT_vect) {
				EncoderArray[1]++;
			}
		#elif (ENCODER1_FUNC_NO == 4)
			ISR(TIMER4_CAPT_vect) {
				EncoderArray[1]++;
			}
		#elif (ENCODER1_FUNC_NO == 5)
			ISR(TIMER5_CAPT_vect) {
				EncoderArray[1]++;
			}
		#endif
	#elif (ENCODER1_MODE == 'E')
		#if (ENCODER1_FUNC_NO == 0)
			ISR(INT0_vect) {
				EncoderArray[1]++;
			}
		#elif (ENCODER1_FUNC_NO == 1)
			ISR(INT1_vect) {
				EncoderArray[1]++;
			}
		#elif (ENCODER1_FUNC_NO == 2)
			ISR(INT2_vect) {
				EncoderArray[1]++;
			}
		#elif (ENCODER1_FUNC_NO == 3)
			ISR(INT3_vect) {
				EncoderArray[1]++;
			}
		#elif (ENCODER1_FUNC_NO == 4)
			ISR(INT4_vect) {
				EncoderArray[1]++;
			}
		#elif (ENCODER1_FUNC_NO == 5)
			ISR(INT5_vect) {
				EncoderArray[1]++;
			}
		#elif (ENCODER1_FUNC_NO == 6)
			ISR(INT6_vect) {
				EncoderArray[1]++;
			}
		#elif (ENCODER1_FUNC_NO == 7)
			ISR(INT7_vect) {
				EncoderArray[1]++;
			}
		#endif
	#endif
#endif

#if defined(USE_ENCODER2)
	#if (ENCODER2_MODE == 'T')
		#if (ENCODER2_FUNC_NO == 1)
			ISR(TIMER1_CAPT_vect) {
				EncoderArray[2]++;
			}
		#elif (ENCODER2_FUNC_NO == 3)
			ISR(TIMER3_CAPT_vect) {
				EncoderArray[2]++;
			}
		#elif (ENCODER2_FUNC_NO == 4)
			ISR(TIMER4_CAPT_vect) {
				EncoderArray[2]++;
			}
		#elif (ENCODER2_FUNC_NO == 5)
			ISR(TIMER5_CAPT_vect) {
				EncoderArray[2]++;
			}
		#endif
	#elif (ENCODER2_MODE == 'E')
		#if (ENCODER2_FUNC_NO == 0)
			ISR(INT0_vect) {
				EncoderArray[2]++;
			}
		#elif (ENCODER2_FUNC_NO == 1)
			ISR(INT1_vect) {
				EncoderArray[2]++;
			}
		#elif (ENCODER2_FUNC_NO == 2)
			ISR(INT2_vect) {
				EncoderArray[2]++;
			}
		#elif (ENCODER2_FUNC_NO == 3)
			ISR(INT3_vect) {
				EncoderArray[2]++;
			}
		#elif (ENCODER2_FUNC_NO == 4)
			ISR(INT4_vect) {
				EncoderArray[2]++;
			}
		#elif (ENCODER2_FUNC_NO == 5)
			ISR(INT5_vect) {
				EncoderArray[2]++;
			}
		#elif (ENCODER2_FUNC_NO == 6)
			ISR(INT6_vect) {
				EncoderArray[2]++;
			}
		#elif (ENCODER2_FUNC_NO == 7)
			ISR(INT7_vect) {
				EncoderArray[2]++;
			}
		#endif
	#endif
#endif

#if defined(USE_ENCODER3)
	#if (ENCODER3_MODE == 'T')
		#if (ENCODER3_FUNC_NO == 1)
			ISR(TIMER1_CAPT_vect) {
				EncoderArray[3]++;
			}
		#elif (ENCODER3_FUNC_NO == 3)
			ISR(TIMER3_CAPT_vect) {
				EncoderArray[3]++;
			}
		#elif (ENCODER3_FUNC_NO == 4)
			ISR(TIMER4_CAPT_vect) {
				EncoderArray[3]++;
			}
		#elif (ENCODER3_FUNC_NO == 5)
			ISR(TIMER5_CAPT_vect) {
				EncoderArray[3]++;
			}
		#endif
	#elif (ENCODER3_MODE == 'E')
		#if (ENCODER3_FUNC_NO == 0)
			ISR(INT0_vect) {
				EncoderArray[3]++;
			}
		#elif (ENCODER3_FUNC_NO == 1)
			ISR(INT1_vect) {
				EncoderArray[3]++;
			}
		#elif (ENCODER3_FUNC_NO == 2)
			ISR(INT2_vect) {
				EncoderArray[3]++;
			}
		#elif (ENCODER3_FUNC_NO == 3)
			ISR(INT3_vect) {
				EncoderArray[3]++;
			}
		#elif (ENCODER3_FUNC_NO == 4)
			ISR(INT4_vect) {
				EncoderArray[3]++;
			}
		#elif (ENCODER3_FUNC_NO == 5)
			ISR(INT5_vect) {
				EncoderArray[3]++;
			}
		#elif (ENCODER3_FUNC_NO == 6)
			ISR(INT6_vect) {
				EncoderArray[3]++;
			}
		#elif (ENCODER3_FUNC_NO == 7)
			ISR(INT7_vect) {
				EncoderArray[3]++;
			}
		#endif
	#endif
#endif

#if defined(USE_ENCODER4)
	#if (ENCODER4_MODE == 'T')
		#if (ENCODER4_FUNC_NO == 1)
			ISR(TIMER1_CAPT_vect) {
				EncoderArray[4]++;
			}
		#elif (ENCODER4_FUNC_NO == 3)
			ISR(TIMER3_CAPT_vect) {
				EncoderArray[4]++;
			}
		#elif (ENCODER4_FUNC_NO == 4)
			ISR(TIMER4_CAPT_vect) {
				EncoderArray[4]++;
			}
		#elif (ENCODER4_FUNC_NO == 5)
			ISR(TIMER5_CAPT_vect) {
				EncoderArray[4]++;
			}
		#endif
	#elif (ENCODER4_MODE == 'E')
		#if (ENCODER4_FUNC_NO == 0)
			ISR(INT0_vect) {
				EncoderArray[4]++;
			}
		#elif (ENCODER4_FUNC_NO == 1)
			ISR(INT1_vect) {
				EncoderArray[4]++;
			}
		#elif (ENCODER4_FUNC_NO == 2)
			ISR(INT2_vect) {
				EncoderArray[4]++;
			}
		#elif (ENCODER4_FUNC_NO == 3)
			ISR(INT3_vect) {
				EncoderArray[4]++;
			}
		#elif (ENCODER4_FUNC_NO == 4)
			ISR(INT4_vect) {
				EncoderArray[4]++;
			}
		#elif (ENCODER4_FUNC_NO == 5)
			ISR(INT5_vect) {
				EncoderArray[4]++;
			}
		#elif (ENCODER4_FUNC_NO == 6)
			ISR(INT6_vect) {
				EncoderArray[4]++;
			}
		#elif (ENCODER4_FUNC_NO == 7)
			ISR(INT7_vect) {
				EncoderArray[4]++;
			}
		#endif
	#endif
#endif

#if defined(USE_ENCODER5)
	#if (ENCODER5_MODE == 'T')
		#if (ENCODER5_FUNC_NO == 1)
			ISR(TIMER1_CAPT_vect) {
				EncoderArray[5]++;
			}
		#elif (ENCODER5_FUNC_NO == 3)
			ISR(TIMER3_CAPT_vect) {
				EncoderArray[5]++;
			}
		#elif (ENCODER5_FUNC_NO == 4)
			ISR(TIMER4_CAPT_vect) {
				EncoderArray[5]++;
			}
		#elif (ENCODER5_FUNC_NO == 5)
			ISR(TIMER5_CAPT_vect) {
				EncoderArray[5]++;
			}
		#endif
	#elif (ENCODER5_MODE == 'E')
		#if (ENCODER5_FUNC_NO == 0)
			ISR(INT0_vect) {
				EncoderArray[5]++;
			}
		#elif (ENCODER5_FUNC_NO == 1)
			ISR(INT1_vect) {
				EncoderArray[5]++;
			}
		#elif (ENCODER5_FUNC_NO == 2)
			ISR(INT2_vect) {
				EncoderArray[5]++;
			}
		#elif (ENCODER5_FUNC_NO == 3)
			ISR(INT3_vect) {
				EncoderArray[5]++;
			}
		#elif (ENCODER5_FUNC_NO == 4)
			ISR(INT4_vect) {
				EncoderArray[5]++;
			}
		#elif (ENCODER5_FUNC_NO == 5)
			ISR(INT5_vect) {
				EncoderArray[5]++;
			}
		#elif (ENCODER5_FUNC_NO == 6)
			ISR(INT6_vect) {
				EncoderArray[5]++;
			}
		#elif (ENCODER5_FUNC_NO == 7)
			ISR(INT7_vect) {
				EncoderArray[5]++;
			}
		#endif
	#endif
#endif

#if defined(USE_ENCODER6)
	#if (ENCODER6_MODE == 'T')
		#if (ENCODER6_FUNC_NO == 1)
			ISR(TIMER1_CAPT_vect) {
				EncoderArray[6]++;
			}
		#elif (ENCODER6_FUNC_NO == 3)
			ISR(TIMER3_CAPT_vect) {
				EncoderArray[6]++;
			}
		#elif (ENCODER6_FUNC_NO == 4)
			ISR(TIMER4_CAPT_vect) {
				EncoderArray[6]++;
			}
		#elif (ENCODER6_FUNC_NO == 5)
			ISR(TIMER5_CAPT_vect) {
				EncoderArray[6]++;
			}
		#endif
	#elif (ENCODER6_MODE == 'E')
		#if (ENCODER6_FUNC_NO == 0)
			ISR(INT0_vect) {
				EncoderArray[6]++;
			}
		#elif (ENCODER6_FUNC_NO == 1)
			ISR(INT1_vect) {
				EncoderArray[6]++;
			}
		#elif (ENCODER6_FUNC_NO == 2)
			ISR(INT2_vect) {
				EncoderArray[6]++;
			}
		#elif (ENCODER6_FUNC_NO == 3)
			ISR(INT3_vect) {
				EncoderArray[6]++;
			}
		#elif (ENCODER6_FUNC_NO == 4)
			ISR(INT4_vect) {
				EncoderArray[6]++;
			}
		#elif (ENCODER6_FUNC_NO == 5)
			ISR(INT5_vect) {
				EncoderArray[6]++;
			}
		#elif (ENCODER6_FUNC_NO == 6)
			ISR(INT6_vect) {
				EncoderArray[6]++;
			}
		#elif (ENCODER6_FUNC_NO == 7)
			ISR(INT7_vect) {
				EncoderArray[6]++;
			}
		#endif
	#endif
#endif

#if defined(USE_ENCODER7)
	#if (ENCODER7_MODE == 'T')
		#if (ENCODER7_FUNC_NO == 1)
			ISR(TIMER1_CAPT_vect) {
				EncoderArray[7]++;
			}
		#elif (ENCODER7_FUNC_NO == 3)
			ISR(TIMER3_CAPT_vect) {
				EncoderArray[7]++;
			}
		#elif (ENCODER7_FUNC_NO == 4)
			ISR(TIMER4_CAPT_vect) {
				EncoderArray[7]++;
			}
		#elif (ENCODER7_FUNC_NO == 5)
			ISR(TIMER5_CAPT_vect) {
				EncoderArray[7]++;
			}
		#endif
	#elif (ENCODER7_MODE == 'E')
		#if (ENCODER7_FUNC_NO == 0)
			ISR(INT0_vect) {
				EncoderArray[7]++;
			}
		#elif (ENCODER7_FUNC_NO == 1)
			ISR(INT1_vect) {
				EncoderArray[7]++;
			}
		#elif (ENCODER7_FUNC_NO == 2)
			ISR(INT2_vect) {
				EncoderArray[7]++;
			}
		#elif (ENCODER7_FUNC_NO == 3)
			ISR(INT3_vect) {
				EncoderArray[7]++;
			}
		#elif (ENCODER7_FUNC_NO == 4)
			ISR(INT4_vect) {
				EncoderArray[7]++;
			}
		#elif (ENCODER7_FUNC_NO == 5)
			ISR(INT5_vect) {
				EncoderArray[7]++;
			}
		#elif (ENCODER7_FUNC_NO == 6)
			ISR(INT6_vect) {
				EncoderArray[7]++;
			}
		#elif (ENCODER7_FUNC_NO == 7)
			ISR(INT7_vect) {
				EncoderArray[7]++;
			}
		#endif
	#endif
#endif

#if defined(USE_ENCODER8)
	#if (ENCODER8_MODE == 'T')
		#if (ENCODER8_FUNC_NO == 1)
			ISR(TIMER1_CAPT_vect) {
				EncoderArray[8]++;
			}
		#elif (ENCODER8_FUNC_NO == 3)
			ISR(TIMER3_CAPT_vect) {
				EncoderArray[8]++;
			}
		#elif (ENCODER8_FUNC_NO == 4)
			ISR(TIMER4_CAPT_vect) {
				EncoderArray[8]++;
			}
		#elif (ENCODER8_FUNC_NO == 5)
			ISR(TIMER5_CAPT_vect) {
				EncoderArray[8]++;
			}
		#endif
	#elif (ENCODER8_MODE == 'E')
		#if (ENCODER8_FUNC_NO == 0)
			ISR(INT0_vect) {
				EncoderArray[8]++;
			}
		#elif (ENCODER8_FUNC_NO == 1)
			ISR(INT1_vect) {
				EncoderArray[8]++;
			}
		#elif (ENCODER8_FUNC_NO == 2)
			ISR(INT2_vect) {
				EncoderArray[8]++;
			}
		#elif (ENCODER8_FUNC_NO == 3)
			ISR(INT3_vect) {
				EncoderArray[8]++;
			}
		#elif (ENCODER8_FUNC_NO == 4)
			ISR(INT4_vect) {
				EncoderArray[8]++;
			}
		#elif (ENCODER8_FUNC_NO == 5)
			ISR(INT5_vect) {
				EncoderArray[8]++;
			}
		#elif (ENCODER8_FUNC_NO == 6)
			ISR(INT6_vect) {
				EncoderArray[8]++;
			}
		#elif (ENCODER8_FUNC_NO == 7)
			ISR(INT7_vect) {
				EncoderArray[8]++;
			}
		#endif
	#endif
#endif

#if defined(USE_ENCODER9)
	#if (ENCODER9_MODE == 'T')
		#if (ENCODER9_FUNC_NO == 1)
			ISR(TIMER1_CAPT_vect) {
				EncoderArray[9]++;
			}
		#elif (ENCODER9_FUNC_NO == 3)
			ISR(TIMER3_CAPT_vect) {
				EncoderArray[9]++;
			}
		#elif (ENCODER9_FUNC_NO == 4)
			ISR(TIMER4_CAPT_vect) {
				EncoderArray[9]++;
			}
		#elif (ENCODER9_FUNC_NO == 5)
			ISR(TIMER5_CAPT_vect) {
				EncoderArray[9]++;
			}
		#endif
	#elif (ENCODER9_MODE == 'E')
		#if (ENCODER9_FUNC_NO == 0)
			ISR(INT0_vect) {
				EncoderArray[9]++;
			}
		#elif (ENCODER9_FUNC_NO == 1)
			ISR(INT1_vect) {
				EncoderArray[9]++;
			}
		#elif (ENCODER9_FUNC_NO == 2)
			ISR(INT2_vect) {
				EncoderArray[9]++;
			}
		#elif (ENCODER9_FUNC_NO == 3)
			ISR(INT3_vect) {
				EncoderArray[9]++;
			}
		#elif (ENCODER9_FUNC_NO == 4)
			ISR(INT4_vect) {
				EncoderArray[9]++;
			}
		#elif (ENCODER9_FUNC_NO == 5)
			ISR(INT5_vect) {
				EncoderArray[9]++;
			}
		#elif (ENCODER9_FUNC_NO == 6)
			ISR(INT6_vect) {
				EncoderArray[9]++;
			}
		#elif (ENCODER9_FUNC_NO == 7)
			ISR(INT7_vect) {
				EncoderArray[9]++;
			}
		#endif
	#endif
#endif

#if defined(USE_ENCODER10)
	#if (ENCODER10_MODE == 'T')
		#if (ENCODER10_FUNC_NO == 1)
			ISR(TIMER1_CAPT_vect) {
				EncoderArray[10]++;
			}
		#elif (ENCODER10_FUNC_NO == 3)
			ISR(TIMER3_CAPT_vect) {
				EncoderArray[10]++;
			}
		#elif (ENCODER10_FUNC_NO == 4)
			ISR(TIMER4_CAPT_vect) {
				EncoderArray[10]++;
			}
		#elif (ENCODER10_FUNC_NO == 5)
			ISR(TIMER5_CAPT_vect) {
				EncoderArray[10]++;
			}
		#endif
	#elif (ENCODER10_MODE == 'E')
		#if (ENCODER10_FUNC_NO == 0)
			ISR(INT0_vect) {
				EncoderArray[10]++;
			}
		#elif (ENCODER10_FUNC_NO == 1)
			ISR(INT1_vect) {
				EncoderArray[10]++;
			}
		#elif (ENCODER10_FUNC_NO == 2)
			ISR(INT2_vect) {
				EncoderArray[10]++;
			}
		#elif (ENCODER10_FUNC_NO == 3)
			ISR(INT3_vect) {
				EncoderArray[10]++;
			}
		#elif (ENCODER10_FUNC_NO == 4)
			ISR(INT4_vect) {
				EncoderArray[10]++;
			}
		#elif (ENCODER10_FUNC_NO == 5)
			ISR(INT5_vect) {
				EncoderArray[10]++;
			}
		#elif (ENCODER10_FUNC_NO == 6)
			ISR(INT6_vect) {
				EncoderArray[10]++;
			}
		#elif (ENCODER10_FUNC_NO == 7)
			ISR(INT7_vect) {
				EncoderArray[10]++;
			}
		#endif
	#endif
#endif

#if defined(USE_ENCODER11)
	#if (ENCODER11_MODE == 'T')
		#if (ENCODER11_FUNC_NO == 1)
			ISR(TIMER1_CAPT_vect) {
				EncoderArray[11]++;
			}
		#elif (ENCODER11_FUNC_NO == 3)
			ISR(TIMER3_CAPT_vect) {
				EncoderArray[11]++;
			}
		#elif (ENCODER11_FUNC_NO == 4)
			ISR(TIMER4_CAPT_vect) {
				EncoderArray[11]++;
			}
		#elif (ENCODER11_FUNC_NO == 5)
			ISR(TIMER5_CAPT_vect) {
				EncoderArray[11]++;
			}
		#endif
	#elif (ENCODER11_MODE == 'E')
		#if (ENCODER11_FUNC_NO == 0)
			ISR(INT0_vect) {
				EncoderArray[11]++;
			}
		#elif (ENCODER11_FUNC_NO == 1)
			ISR(INT1_vect) {
				EncoderArray[11]++;
			}
		#elif (ENCODER11_FUNC_NO == 2)
			ISR(INT2_vect) {
				EncoderArray[11]++;
			}
		#elif (ENCODER11_FUNC_NO == 3)
			ISR(INT3_vect) {
				EncoderArray[11]++;
			}
		#elif (ENCODER11_FUNC_NO == 4)
			ISR(INT4_vect) {
				EncoderArray[11]++;
			}
		#elif (ENCODER11_FUNC_NO == 5)
			ISR(INT5_vect) {
				EncoderArray[11]++;
			}
		#elif (ENCODER11_FUNC_NO == 6)
			ISR(INT6_vect) {
				EncoderArray[11]++;
			}
		#elif (ENCODER11_FUNC_NO == 7)
			ISR(INT7_vect) {
				EncoderArray[11]++;
			}
		#endif
	#endif
#endif

#if defined(USE_ENCODER12)
	#if (ENCODER12_MODE == 'T')
		#if (ENCODER12_FUNC_NO == 1)
			ISR(TIMER1_CAPT_vect) {
				EncoderArray[12]++;
			}
		#elif (ENCODER12_FUNC_NO == 3)
			ISR(TIMER3_CAPT_vect) {
				EncoderArray[12]++;
			}
		#elif (ENCODER12_FUNC_NO == 4)
			ISR(TIMER4_CAPT_vect) {
				EncoderArray[12]++;
			}
		#elif (ENCODER12_FUNC_NO == 5)
			ISR(TIMER5_CAPT_vect) {
				EncoderArray[12]++;
			}
		#endif
	#elif (ENCODER12_MODE == 'E')
		#if (ENCODER12_FUNC_NO == 0)
			ISR(INT0_vect) {
				EncoderArray[12]++;
			}
		#elif (ENCODER12_FUNC_NO == 1)
			ISR(INT1_vect) {
				EncoderArray[12]++;
			}
		#elif (ENCODER12_FUNC_NO == 2)
			ISR(INT2_vect) {
				EncoderArray[12]++;
			}
		#elif (ENCODER12_FUNC_NO == 3)
			ISR(INT3_vect) {
				EncoderArray[12]++;
			}
		#elif (ENCODER12_FUNC_NO == 4)
			ISR(INT4_vect) {
				EncoderArray[12]++;
			}
		#elif (ENCODER12_FUNC_NO == 5)
			ISR(INT5_vect) {
				EncoderArray[12]++;
			}
		#elif (ENCODER12_FUNC_NO == 6)
			ISR(INT6_vect) {
				EncoderArray[12]++;
			}
		#elif (ENCODER12_FUNC_NO == 7)
			ISR(INT7_vect) {
				EncoderArray[12]++;
			}
		#endif
	#endif
#endif

#endif
