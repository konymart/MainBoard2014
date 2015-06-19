/*
 * RS485.h
 *
 * Created: 2014/06/17 20:25:21
 *  Author: tatsuro
 */ 


#ifndef RS485_H_
#define RS485_H_

#include <stdbool.h>

#if defined(USE_RS485)

#define RS485_RE	(0x00)
#define RS485_SE	(0x01)

static void RS485_putchar(uint8_t data);
static void RS485_getchar(uint8_t *data);

#if defined(USE_MOTOR_HUB)
static void MotorHubInitialize(void);
#endif

#if defined(USE_LED_HUB)
static void LedHubInitialize(void);
#endif

#if defined(USE_AIR_HUB)
static void AirHubInitialize(void);
#endif

#if defined(USE_SENSOR_HUB)
static void ce(uint8_t no);
#endif

#endif


#endif /* RS485_H_ */