/*
 * Air.h
 *
 * Created: 2014/06/21 15:11:02
 *  Author: tatsuro
 */ 


#ifndef AIR_H_
#define AIR_H_

#include <stdbool.h>

#define NO_DATA_IN_LINE		(true)
#define DATA_IN_LINE		(false)

typedef struct {
	uint8_t addr;
	uint8_t data;
}RS485_Air;

void AirInitialize(void);
void AirUpdate(void);
static uint8_t AddressSetter();
static void AirDataInitialize();

#endif /* AIR_H_ */