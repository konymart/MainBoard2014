/*
 * Setup.h
 *
 * Created: 2014/06/19 19:49:23
 *  Author: tatsuro
 */ 


#ifndef SETUP_H_
#define SETUP_H_

#include <avr/io.h>
#include "../../globalDef.h"

static void IORegSetup(void);

#if defined(USE_TIMER)
	static void TimerRegSetup(void);
	static void TimerSetup(void);
#endif

#if (defined(USE_UART) || defined(USE_MU))
	static void UartRegSetup(void);
#endif

#if defined(USE_EXINT)
	static void ExintRegSetup(void);
#endif

#if defined(USE_PCINT)
	static void PcintRegSetup(void);
#endif

#endif /* SETUP_H_ */