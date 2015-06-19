/*
 * BuzzerDef.h
 *
 * Created: 2014/06/19 17:54:58
 *  Author: tatsuro
 */ 


#ifndef BUZZERDEF_H_
#define BUZZERDEF_H_

#include <stdbool.h>

#define BUZZER_ON	(true)
#define BUZZER_OFF	(false)

extern bool BuzzerStatus;

extern void BuzzerInitialize(void);
extern void BuzzerUpdate(void);

#endif /* BUZZERDEF_H_ */