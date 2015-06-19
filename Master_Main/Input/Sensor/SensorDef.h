/*
 * SensorDef.h
 *
 * Created: 2014/09/07 8:56:46
 *  Author: tatsuro
 */ 


#ifndef SENSORDEF_H_
#define SENSORDEF_H_

#if defined(USE_SENSOR)

#define SENSOR_ON	(1)
#define SENSOR_OFF  (0)

extern bool SensorArray[USING_SENSOR];

void SensorInitialize();
void GetSensorStatus(void);

#endif

#endif /* SENSORDEF_H_ */