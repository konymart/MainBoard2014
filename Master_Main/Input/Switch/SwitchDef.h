/*
 * SwitchDef.h
 *
 * Created: 2014/06/19 18:26:10
 *  Author: tatsuro
 */ 


#ifndef SWITCHDEF_H_
#define SWITCHDEF_H_

#include <stdbool.h>
#include "../../globalDef.h"

#if (defined(USE_DIP_SWITCH) || defined(USE_MU))
	#define DIP_0	(0x01)
	#define DIP_1	(0x02)
	#define DIP_2	(0x04)
	#define DIP_3	(0x08)
#endif

#if defined(USE_SWITCH)
#define SWITCH_ON		(true)
#define SWITCH_OFF		(false)
#endif

#if defined(USE_SWITCH)
extern bool SwitchArray[USING_SWITCH];
extern void SwitchInitialize(void);
extern void GetSwitchStatus(void);
extern void SwitchStatusReset(void);
#endif

#if (defined(USE_DIP_SWITCH) || defined(USE_MU))
extern void DipSwitchInitialize(void);
extern uint8_t GetDipSwitchStatus(void);
#endif

#endif /* SWITCHDEF_H_ */