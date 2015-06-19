/*
 * Sensor.c
 *
 * Created: 2014/09/07 8:56:30
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include "../../globalDef.h"
#include "./SensorDef.h"

#if defined(USE_SENSOR)

bool SensorArray[USING_SENSOR];

void SensorInitialize() {
	uint8_t loop;

	#if (USING_SENSOR > 0)
		cbi(*SENSOR_0_PORT.DDR, SENSOR_0_BIT);
		sbi(*SENSOR_0_PORT.PORT, SENSOR_0_BIT);
	#endif
	#if (USING_SENSOR > 1)
		cbi(*SENSOR_1_PORT.DDR, SENSOR_1_BIT);
		sbi(*SENSOR_1_PORT.PORT, SENSOR_1_BIT);
	#endif
	#if (USING_SENSOR > 2)
		cbi(*SENSOR_2_PORT.DDR, SENSOR_2_BIT);
		sbi(*SENSOR_2_PORT.PORT, SENSOR_2_BIT);
	#endif
	#if (USING_SENSOR > 3)
		cbi(*SENSOR_3_PORT.DDR, SENSOR_3_BIT);
		sbi(*SENSOR_3_PORT.PORT, SENSOR_3_BIT);
	#endif
	#if (USING_SENSOR > 4)
		cbi(*SENSOR_4_PORT.DDR, SENSOR_4_BIT);
		sbi(*SENSOR_4_PORT.PORT, SENSOR_4_BIT);
	#endif
	
	for(loop=0; loop<USING_SENSOR; loop++) {
		SensorArray[loop] = SENSOR_OFF;
	}
}

void GetSensorStatus(void) {
	#if (USING_SENSOR > 0)
		if( !(*SENSOR_0_PORT.PIN & (1<<SENSOR_0_BIT)))	SensorArray[0] = SENSOR_ON;
		else											SensorArray[0] = SENSOR_OFF;
	#endif
	#if (USING_SENSOR > 1)
		if( !(*SENSOR_1_PORT.PIN & (1<<SENSOR_1_BIT)))	SensorArray[1] = SENSOR_ON;
		else											SensorArray[1] = SENSOR_OFF;
	#endif
	#if (USING_SENSOR > 2)
		if( !(*SENSOR_2_PORT.PIN & (1<<SENSOR_2_BIT)))	SensorArray[2] = SENSOR_ON;
		else											SensorArray[2] = SENSOR_OFF;
	#endif
	#if (USING_SENSOR > 3)
		if( !(*SENSOR_3_PORT.PIN & (1<<SENSOR_3_BIT)))	SensorArray[3] = SENSOR_ON;
		else											SensorArray[3] = SENSOR_OFF;
	#endif
	#if (USING_SENSOR > 4)
		if( !(*SENSOR_4_PORT.PIN & (1<<SENSOR_4_BIT)))	SensorArray[4] = SENSOR_ON;
		else											SensorArray[4] = SENSOR_OFF;
	#endif
}

#endif
