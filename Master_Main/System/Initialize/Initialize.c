/*
 * Initialize.c
 *
 * Created: 2014/06/19 18:28:49
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "./InitializeDef.h"
#include "../Process/ProcessDef.h"
#include "../../globalDef.h"
#if defined(USE_MU)
	#include "../../Communication/Mu/MuDef.h"
	#include "../../Communication/RemoteControl/RCReceiveDef.h"
#endif
#if defined(USE_HUB)
#if defined(USE_RS485)
	#include "../../Communication/RS485/RS485Def.h"
#endif
#endif
#if defined(USE_ENCODER)
	#include "../../Input/Encoder/EncoderDef.h"
#endif
#if (defined(USE_SWITCH) || defined(USE_DIP_SWITCH))
	#include "../../Input/Switch/SwitchDef.h"
#endif
#if defined(USE_SENSOR)
	#include "../../Input/Sensor/SensorDef.h"
#endif
#if defined(USE_AIR)
	#include "../../Output/Air/AirDef.h"
#endif
#if defined(USE_BUZZER)
	#include "../../Output/Buzzer/BuzzerDef.h"
#endif
#if defined(USE_LED)
	#include "../../Output/Led/LedDef.h"
#endif
#if defined(USE_MOTOR)
	#include "../../Output/Motor/MotorDef.h"
#endif
#if defined(USE_SERVO)
	#include "../../Output/Servo/ServoDef.h"
#endif
#if defined(USE_EMERGENCY_SWITCH)
	#include "../../System/Emergency/EmergencyDef.h"
#endif
#if defined(USE_SAFETY)
	#include "../../System/Safety/SafetyDef.h"
#endif
#if defined(WDT_RESET)
	#include "../../System/WDT/WDT.h"
#endif

void SystemInitialize(void) {
	cli();
	
	#if defined(USE_MU)
// Setting for Receive Data
		CtrlDataInitialize();	// RCReceive.c
// Initialize for MU
		MuInitialize();			// Mu.c
	#endif
	#if defined(USE_ENCODER)
// Initialize for Encoder
		EncoderInitialize();	// Encoder.c
	#endif
	#if defined(USE_SWITCH)
// Initialize for Switch
		SwitchInitialize();		// Switch.c
	#endif
	#if defined(USE_DIP_SWITCH)
		DipSwitchInitialize();	// Switch.c
	#endif
	#if defined(USE_SENSOR)
		SensorInitialize();
	#endif
	#if defined(USE_AIR)
// Initialize for Air Actuator
		AirInitialize();		// Air.c
		AirUpdate();			// Air.c
	#endif
	#if defined(USE_BUZZER)
// Initialize for Buzzer Actuator
		BuzzerInitialize();		// Buzzer.c
		BuzzerUpdate();			// Buzzer.c
	#endif
	#if defined(USE_LED)
// Initialize for LED
		LedInitialize();		// Led.c
		LedUpdate();			// Led.c
	#endif
	#if defined(USE_MOTOR)
// Initialize for Motor Actuator
		MotorInitialize();		// Motor.c
		MotorUpdate();			// Motor.c
	#endif
	#if defined(USE_SERVO)
// Initialize for Servo Motor Actuator
		ServoInitialize();		// Servo.c
		ServoUpdate();			// Servo.c
	#endif

	#if defined(USE_SAFETY)
// Initialize for Safety Function
		SafetyInitialize[SAFETY_TIMER_NO]();	// Safety.c
	#endif
	
	#if defined(USE_HUB)
	#if defined(USE_RS485)
		RS485Initialize(12);
	#endif
	#endif
	
	#if defined(WDT_RESET)
		WDTInitialize();
	#endif
	
// Initialize Process Job
	ProcessJobInitialize();		// Process.c
}
