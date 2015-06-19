/*
 * Led.h
 *
 * Created: 2014/06/19 17:55:16
 *  Author: tatsuro
 */ 


#ifndef LED_H_
#define LED_H_

#include <avr/io.h>
#include <stdbool.h>
#include "./LedDef.h"

#if defined(USE_LED01) && defined(USE_LED02) && defined(USE_LED03) && defined(USE_LED04)
static void Led4bitPack0(uint8_t value);
#endif
#if defined(USE_LED05) && defined(USE_LED06) && defined(USE_LED07) && defined(USE_LED08)
static void Led4bitPack1(uint8_t value);
#endif
#if defined(USE_LED09) && defined(USE_LED10) && defined(USE_LED11) && defined(USE_LED12)
static void Led4bitPack2(uint8_t value);
#endif
#if defined(USE_LED13) && defined(USE_LED14) && defined(USE_LED15) && defined(USE_LED16)
static void Led4bitPack3(uint8_t value);
#endif
#if defined(USE_LED17) && defined(USE_LED18) && defined(USE_LED19) && defined(USE_LED20)
static void Led4bitPack4(uint8_t value);
#endif

#if defined(USE_LED00)
static void LED0(bool status);
#endif
#if defined(USE_LED01)
static void LED1(bool status);
#endif
#if defined(USE_LED02)
static void LED2(bool status);
#endif
#if defined(USE_LED03)
static void LED3(bool status);
#endif
#if defined(USE_LED04)
static void LED4(bool status);
#endif
#if defined(USE_LED05)
static void LED5(bool status);
#endif
#if defined(USE_LED06)
static void LED6(bool status);
#endif
#if defined(USE_LED07)
static void LED7(bool status);
#endif
#if defined(USE_LED08)
static void LED8(bool status);
#endif
#if defined(USE_LED09)
static void LED9(bool status);
#endif
#if defined(USE_LED10)
static void LED10(bool status);
#endif
#if defined(USE_LED11)
static void LED11(bool status);
#endif
#if defined(USE_LED12)
static void LED12(bool status);
#endif
#if defined(USE_LED13)
static void LED13(bool status);
#endif
#if defined(USE_LED14)
static void LED14(bool status);
#endif
#if defined(USE_LED15)
static void LED15(bool status);
#endif
#if defined(USE_LED16)
static void LED16(bool status);
#endif
#if defined(USE_LED17)
static void LED17(bool status);
#endif
#if defined(USE_LED18)
static void LED18(bool status);
#endif
#if defined(USE_LED19)
static void LED19(bool status);
#endif
#if defined(USE_LED20)
static void LED20(bool status);
#endif

#endif /* LED_H_ */