/*
 * AirDef.h
 *
 * Created: 2014/06/19 17:54:28
 *  Author: tatsuro
 */ 


#ifndef AIRDEF_H_
#define AIRDEF_H_

#include <stdbool.h>

#define AIR_ON	(true)
#define AIR_OFF	(false)

extern bool AirArray[USING_AIR];

extern void AirInitialize(void);
extern void AirUpdate(void);

#endif /* AIRDEF_H_ */