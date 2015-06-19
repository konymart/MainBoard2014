/*
 * Output.h
 *
 * Created: 2014/06/21 10:09:50
 *  Author: tatsuro
 */ 


#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <stdbool.h>

#define NO_DATA_IN_LINE		(true)
#define DATA_IN_LINE		(false)

typedef struct {
	uint8_t addr;
	uint8_t data[4];
}RS485_Output;

void OutputInitialize(void);
void OutputUpdate(void);
static uint8_t AddressSetter();
static void OutputDataInitialize();

#endif /* OUTPUT_H_ */