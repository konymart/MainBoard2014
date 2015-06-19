/*
 * EncoderDef.h
 *
 * Created: 2014/06/19 18:15:35
 *  Author: tatsuro
 */ 


#ifndef ENCODERDEF_H_
#define ENCODERDEF_H_

#include <avr/io.h>
#include <stdbool.h>
#include "../../globalDef.h"

extern volatile uint16_t EncoderArray[USING_ENCODER];

extern bool jumpSoundFlag;

extern void EncoderSetup(void);
extern void EncoderInitialize(void);

#if defined(USE_ENCODER0)
	void ClearEncoder0(void);
#endif
#if defined(USE_ENCODER1)
	void ClearEncoder1(void);
#endif
#if defined(USE_ENCODER2)
	void ClearEncoder2(void);
#endif
#if defined(USE_ENCODER3)
	void ClearEncoder3(void);
#endif
#if defined(USE_ENCODER4)
	void ClearEncoder4(void);
#endif
#if defined(USE_ENCODER5)
	void ClearEncoder5(void);
#endif
#if defined(USE_ENCODER6)
	void ClearEncoder6(void);
#endif
#if defined(USE_ENCODER7)
	void ClearEncoder7(void);
#endif
#if defined(USE_ENCODER8)
	void ClearEncoder8(void);
#endif
#if defined(USE_ENCODER9)
	void ClearEncoder9(void);
#endif

#endif /* ENCODERDEF_H_ */