/*
 * Process.h
 *
 * Created: 2014/06/19 18:31:24
 *  Author: tatsuro
 */ 


#ifndef PROCESS_H_
#define PROCESS_H_

#include "../../globalDef.h"
#include "../../Output/Motor/MotorDef.h"
#include <stdbool.h>

 /*=====================================================================================*/
/*  
 *	Defines
 */
 /*====================================================================================*/

// For Check Defines
#define CTRL_CHECK		(1)
#define POWER_CHECK		(1)


// MotorDefines
#define LTIRE_MOTOR_NO		(0)
#define RTIRE_MOTOR_NO		(1)
#define LTIRE				MotorArray[LTIRE_MOTOR_NO]					// For Left Tire
#define RTIRE				MotorArray[RTIRE_MOTOR_NO]					// For Right Tire
#define STEERING_M			MotorHubArray[0]				// For Turning Motor
#define F_BELT_M			MotorHubArray[1]				// For Belt Motor
#define B_BELT_M			MotorHubArray[2]				// For Back Unit Belt Motor
#define FRONT_TIRE			MotorHubArray[3]

#define BRAKE_PWM			(100)


// Tire Control Defines
#define LTIRE_MAX_PWM		(30)
#define RTIRE_MAX_PWM		(30)
#define FTIRE_MAX_PWM		(20)

// kakuzai
#define K_LTIRE_MAX_PWM		(35)
#define K_RTIRE_MAX_PWM		(35)

// Slope
#define S_LTIRE_MAX_PWM			(20)
#define S_RTIRE_MAX_PWM			(20)
#define LTIRE_SLOPE_BACK_PWM	(7)
#define RTIRE_SLOPE_BACK_PWM	(7)

// Sub Slope
#define SS_LTIRE_MAX_PWM	(15)
#define SS_RTIRE_MAX_PWM	(15)

// Steering Tire Pwm
#define LTIRE_STEERING_MAX_PWM		(20)
#define RTIRE_STEERING_MAX_PWM		(20)

// Tire Pwm Change Span
#define PWM_UP_CHANGE_SPAN		(2)
#define PWM_DOWN_CHANGE_SPAN	(1)

// Steering Defines
#define STEERING_MAX_PWM		(30)
#define STEERING_PWM_UP_SPAN	(2)
#define STEERING_PWM_DOWN_SPAN	(2)
#define STEERING_LEFT_PWM		(10)
#define STEERING_RIGHT_PWM		(12)
#define SS_STEERING_LEFT_PWM	(20)
#define SS_STEERING_RIGHT_PWM	(20)

// Belt Defines
#define F_BELT_PWM		(65)
#define B_BELT_PWM		(30)

// Emergency Stop!
#define USE_TIRE_STOP		(1)

enum TIRE_STATUS{
	_FOR_UP,
	_FOR_DOWN,
	_FOR_MAX,
	_FOR_MIN,
	_BACK_UP,
	_BACK_DOWN,
	_BACK_MAX,
	_BACK_MIN,
	_BRAKE
};

typedef struct {
	enum TIRE_STATUS Tire;
	signed char Pwm;
	uint16_t Count;
	uint8_t Status;
	uint8_t UpSpan;
	uint8_t DownSpan;
	uint8_t p;
	uint8_t MaxPwm;
	uint8_t Act;
	uint8_t MotorNo;
}TireControlStatus;

// Air Cylinder Defines
#define LOCK_A0_S		AirHubArray[0]		// For Lock AirCylinder Stroke
#define LOCK_A0_DS		AirHubArray[1]		// For Lock AirCylinder Down Stroke
#define ARM_A			AirHubArray[2]		// For Arm AirCylinder
#define F_LOCK_A		AirHubArray[3]		// For AirCylinder Tire Lock 
#define TIRE_A			AirHubArray[4]		// For Belt Up Down AirCylinder
#define PETIT_LOCK_A0_S	AirHubArray[5]		// For Slope Air Cylinder
#define FRONT_TIRE_A	AirHubArray[6]

enum SLOPE_LOCK_STATUS{
	_FREE,
	_FLAT_PLANE_LOCK,
	_SLOPE_LOCK
};	


// Lead SW
#define TIRE_FRONT_SW	SwitchArray[2]
#define TIRE_REAR_SW	SwitchArray[3]

#define BACK_UNIT_DOWN_SPAN		(15)

// Limit SW
#define STEERING_LEFT_SW	SwitchArray[4]
#define STEERING_RIGHT_SW	SwitchArray[5]


// Led Defines
#define SPACE_MODE		(1)
#define FULL_COLOR_MODE	(0)

// Mode
#define _ZR			0x01
#define _FLAT		0x02
#define _SLOPE		0x04
#define _FREE		0x08
#define _FTIRE		0x10
#define _BACKUNIT	0x20
#define _ARM		0x40


// Controller Defines
#define PROCESS_INC_BUTTON					controller->detail.Button.START			// Process Increment
#define PROCESS_DEC_BUTTON					controller->detail.Button.SELECT		// Process Decrement
#define TIRE_STATUS_RESET_BUTTON			controller->detail.Button.HOME			// Tire Stop
#define ARM_BUTTON							controller->detail.Button.X				// Arm Up Down
#define ACCEL_BUTTON						controller->detail.Button.A				// For
#define BACK_BUTTON							controller->detail.Button.B				// Back
#define STEERING_LEFT_BUTTON				controller->detail.Button.L				// Steering Left Turn
#define STEERING_RIGHT_BUTTON				controller->detail.Button.R				// Steering Right Turn
#define BELT_BACK_BUTTON					controller->detail.Button.ZL			// Belt Back Role
#define FRONT_TIRE_UP_DOWN_BUTTON			controller->detail.Button.ZL			// Front Tire Up Down
#define PETIT_FLAT_PLANE_LOCK_BUTTON		controller->detail.Button.ZR			// Small Flat Plane Lock
#define BELT_BUTTON							controller->detail.Button.Y				// Belt On Off
#define FLAT_PLANE_LOCK_BUTTON				controller->detail.Button.LEFT			// Normal Road Lock
#define SLOPE_LOCK_BUTTON					controller->detail.Button.UP			// Slope Lock
#define LOCK_FREE_BUTTON					controller->detail.Button.RIGHT			// Lock Free
#define BACK_UNIT_UP_DOWN_BUTTON			controller->detail.Button.DOWN			// Back Unit Up Down

//==============================================================================
// End Defines


 /*============================================================================*/
/* 
 *	Function Prototype
 */ 
 /*============================================================================*/

static void TireControl(TireControlStatus *t);
static void SteeringControl();
static void ResetProcessChange(void);
static uint8_t TireDownFunction(uint8_t x);
static uint8_t SolveTireDownFunction(uint8_t y);
static void ModeLedControl(void);

static void UserTasks(void);
#if (USING_PROCESS > 0)
static void ProcessJob0(void);
#endif
#if (USING_PROCESS > 1)
static void ProcessJob1(void);
#endif
#if (USING_PROCESS > 2)
static void ProcessJob2(void);
#endif
#if (USING_PROCESS > 3)
static void ProcessJob3(void);
#endif

static void AllActuatorReset(void);


#endif /* PROCESS_H_ */