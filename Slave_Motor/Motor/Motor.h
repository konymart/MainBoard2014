/*
 * Motor.h
 *
 * Created: 2014/07/26 13:37:01
 *  Author: tatsuro
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include <stdbool.h>

#define NO_DATA_IN_LINE		(true)
#define DATA_IN_LINE		(false)

// Global
void MotorInitialize(void);
void MotorDrive(void);

// Static
static void m(uint8_t no, uint8_t select, uint8_t pwm);
static uint8_t AddressSetter(void);
static void RS485_DataInitialize(void);

// Typedef
typedef struct {
	uint8_t addr;
	uint8_t data[4];
}RS485_Motor;

#endif /* MOTOR_H_ */