/*
 * Encoder.h
 *
 * Created: 2014/06/19 18:15:25
 *  Author: tatsuro
 */ 


#ifndef ENCODER_H_
#define ENCODER_H_

#include "../../globalDef.h"

#if defined(USE_TIMER1)
	static void EncoderTimerInitialize0(void);
#endif
#if defined(USE_TIMER3)
static void EncoderTimerInitialize1(void);
#endif
#if defined(USE_TIMER4)
static void EncoderTimerInitialize2(void);
#endif
#if defined(USE_TIMER5)
static void EncoderTimerInitialize3(void);
#endif

#endif /* ENCODER_H_ */