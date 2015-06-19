/*
 * globalDef.h
 *
 * Created: 2014/06/17 20:15:32
 *  Author: tatsuro
 */ 


#ifndef GLOBALDEF_H_
#define GLOBALDEF_H_


#include <avr/io.h>
#include <avr/wdt.h>
#include "./Defines/SystemDefines.h"		// 1st
#include "./Defines/RegisterDefines.h"		// 2nd
#include "./Defines/StructDefines.h"		// 3rd

#define cbi(addr, bit)	addr &= ~(1<<bit)
#define sbi(addr, bit)	addr |=  (1<<bit)
#define SIMULATION_MODE

extern struct st_io IO;
#if defined(USE_TIMER)
extern struct st_timer TIMER;
#endif
#if (defined(USE_UART) || defined(USE_MU))
extern struct st_usart USART;
#endif
#if defined(USE_EXINT)
extern struct st_exint EXINT;
#endif


#endif /* GLOBALDEF_H_ */