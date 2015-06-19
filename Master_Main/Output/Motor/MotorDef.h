/*
 * MotorDef.h
 *
 * Created: 2014/06/19 17:56:36
 *  Author: tatsuro
 */ 


#ifndef MOTORDEF_H_
#define MOTORDEF_H_

#include "../../globalDef.h"

#define FREE		(0x00)
#define FOR			(0x01)
#define BACK		(0x02)
#define BRAKE		(0x03)

struct Motor {
	uint8_t status;
	uint8_t pwm;
};

extern struct Motor MotorArray[USING_MOTOR];

extern void MotorSetup(void);
extern void MotorInitialize(void);
extern void MotorUpdate(void);
extern uint8_t PwmSetter(uint8_t duty);

#endif /* MOTORDEF_H_ */