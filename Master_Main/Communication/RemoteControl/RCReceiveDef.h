/*
 * RCReceiveDef.h
 *
 * Created: 2014/06/17 20:37:02
 *  Author: tatsuro
 */ 


#ifndef RCRECEIVEDEF_H_
#define RCRECEIVEDEF_H_

#include <stdbool.h>

extern volatile bool CtrlLost;

extern void CtrlDataInitialize(void);
extern union controllerData* GetControllerData(void);
extern union controllerData* ControllerDataReset(void);


#endif /* RCRECEIVEDEF_H_ */