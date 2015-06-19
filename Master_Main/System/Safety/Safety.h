/*
 * Safety.h
 *
 * Created: 2014/06/19 19:47:26
 *  Author: tatsuro
 */ 


#ifndef SAFETY_H_
#define SAFETY_H_

#if defined(USE_TIMER0)
static void SafetyInitialize0(void);
#endif
#if defined(USE_TIMER1)
static void SafetyInitialize1(void);
#endif
#if defined(USE_TIMER2)
static void SafetyInitialize2(void);
#endif
#if defined(USE_TIMER3)
static void SafetyInitialize3(void);
#endif
#if defined(USE_TIMER4)
static void SafetyInitialize4(void);
#endif
#if defined(USE_TIMER5)
static void SafetyInitialize5(void);
#endif

#endif /* SAFETY_H_ */