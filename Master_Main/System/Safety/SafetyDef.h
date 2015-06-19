/*
 * SafetyDef.h
 *
 * Created: 2014/06/19 19:47:40
 *  Author: tatsuro
 */ 


#ifndef SAFETYDEF_H_
#define SAFETYDEF_H_

#include <stdbool.h>
#include "../../globalDef.h"

#if defined(USE_POWER_CHECK)
extern volatile bool powerLost;
#endif
extern void (*SafetyInitialize[6])(void);

extern void SafetySetup(void);
extern void SafetyChecker(void);

#endif /* SAFETYDEF_H_ */