/*
 * RS485Def.h
 *
 * Created: 2014/06/17 20:25:33
 *  Author: tatsuro
 */ 


#ifndef RS485DEF_H_
#define RS485DEF_H_

#include <stdbool.h>

#if defined(USE_RS485)

#include "./RS485_Data.h"

#define NO_DATA_IN_LINE		(true)
#define DATA_IN_LINE		(false)

extern volatile bool LineStatus;
#if defined(USE_SENSOR_HUB)
	extern volatile bool SensorDataReceived;
	extern volatile bool SensorBoardLost;
#endif
#if defined(USE_SAFETY)
	extern volatile uint16_t SensorTimerCount;
#endif

void RS485Initialize(uint8_t baud);
void RS485_Select(uint8_t option);

#if defined(USE_MOTOR_HUB)
#ifndef FREE
#define FREE		(0x00)
#endif
#ifndef FOR
#define FOR			(0x01)
#endif
#ifndef BACK
#define BACK		(0x02)
#endif
#ifndef BRAKE
#define BRAKE		(0x03)
#endif
struct MotorHub{
	uint8_t status;
	uint8_t pwm;
};
extern struct MotorHub MotorHubArray[USING_MOTOR_HUB];
void MotorHubUpdate(void);
#endif

#if defined(USE_LED_HUB)
extern volatile bool LedHubArray[USING_LED_HUB];
void LedHubUpdate(void);
#endif

#if defined(USE_AIR_HUB)
extern volatile bool AirHubArray[USING_AIR_HUB];
void AirHubUpdate(void);
#endif

#if defined(USE_SENSOR_HUB)
void DummyDataSet(void);
union SensorData *GetSensorData(void);
void GetSensorDataCommand(void);
void ClearHubEncoder0(void);
void ClearHubEncoder1(void);
void ClearHubEncoder2(void);
void ClearHubEncoder3(void);
#endif

#endif

#endif /* RS485DEF_H_ */