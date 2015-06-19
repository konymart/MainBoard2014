/*
 * RS485_Data.h
 *
 * Created: 2014/06/17 20:25:09
 *  Author: tatsuro
 */ 


#ifndef RS485_DATA_H_
#define RS485_DATA_H_

#include <avr/io.h>

#if defined(USE_RS485)

#if defined(USE_MOTOR_HUB)
typedef struct {
	uint8_t addr;
	uint8_t data[4];
} st_Motor;
#endif

#if defined(USE_LED_HUB)
typedef struct {
	uint8_t addr;
	uint8_t data[4];
} st_Led;
#endif

#if defined(USE_AIR_HUB)
typedef struct {
	uint8_t addr;
	uint8_t data;
} st_Air;
#endif

#if defined(USE_SENSOR_HUB)
#define SENSORDATA_DEFAULT_LENGTH	(10)

union SensorData{
	struct {
		struct{
			uint8_t SW0:1;
			uint8_t SW1:1;
			uint8_t SW2:1;
			uint8_t SW3:1;
			uint8_t SW4:1;
			uint8_t SW5:1;
			uint8_t SW6:1;
			uint8_t SW7:1;
		}__attribute__ ((packed)) Switch;
		struct{
			uint8_t Sensor0:1;
			uint8_t Sensor1:1;
			uint8_t Sensor2:1;
			uint8_t Sensor3:1;
			uint8_t Sensor4:1;
			uint8_t Sensor5:1;
			uint8_t Sensor6:1;
			uint8_t Sensor7:1;
		}__attribute__ ((packed)) Sensor;
		struct{
			uint16_t Encoder0:16;
			uint16_t Encoder1:16;
			uint16_t Encoder2:16;
			uint16_t Encoder3:16;
		}__attribute__ ((packed)) Encoder;
	}__attribute__ ((packed)) detail;
	
	uint8_t buf[SENSORDATA_DEFAULT_LENGTH];
};
#endif

#endif

#endif /* RS485_DATA_H_ */