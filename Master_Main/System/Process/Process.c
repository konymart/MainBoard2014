/*
 * Process.c
 *
 * Created: 2014/06/19 18:31:04
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "./Process.h"
#include "./ProcessDef.h"
#include "../../globalDef.h"
#if defined(USE_ENCODER)
	#include "../../Input/Encoder/EncoderDef.h"
#endif
#if defined(USE_MU)
	#include "../../Communication/RemoteControl/RCClassic.h"
	#include "../../Communication/RemoteControl/RCReceiveDef.h"
#endif
#if defined(USE_SWITCH)
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
#if defined(USE_SAFETY)
	#include "../../System/Safety/SafetyDef.h"
#endif
#if defined(USE_HUB)
#if defined(USE_RS485)
	#include "../../Communication/RS485/RS485Def.h"
#endif
#endif


/*
 * 必要な変数を以下に記述
 */
/************************************************************/
// Tire Control
static TireControlStatus LeftTire;
static TireControlStatus RightTire;
static TireControlStatus FrontTire;
static TireControlStatus Steering;

static bool tmpBackUnitStatus;
static bool BackUnitDowned;


static bool FrontTireDown;
static uint8_t FrontTireStatus;

static enum SLOPE_LOCK_STATUS Slope;
static enum SLOPE_LOCK_STATUS tmpSlope;

// Belt
static uint8_t BeltStatus;


static bool LeftLimitSwPush;
static bool LeftLimitSwPushed;
static bool RightLimitSwPush;
static bool RightLimitSwPushed;
static uint8_t LeftLimitSwCount;
static uint8_t RightLimitSwCount;


// Button Push Flag
static bool ProcessIncrementButtonPush;
static bool ProcessIncrementButtonPushed;
static bool ProcessDecrementButtonPush;
static bool ProcessDecrementButtonPushed;
static bool ArmButtonPush;
static bool ArmButtonPushed;
static bool BeltButtonPush;
static bool BeltButtonPushed;
static bool BeltBackButtonPush;
static bool BeltBackButtonPushed;	
static bool BackUnitUpButtonPush;
static bool BackUnitUpButtonPushed;
static bool PetitFlatPlaneLockButtonPush;
static bool PetitFlatPlaneLockButtonPushed;
static bool FrontTireUpDownButtonPush;
static bool FrontTireUpDownButtonPushed;

static bool FirstInitialized = false;

static uint8_t TireTable[120];

/************************************************************/

#if defined(USE_MU)
	static union controllerData* controller;
#endif
#if defined(USE_SENSOR_HUB)
	static union SensorData* Sensor;
#endif
#if defined(USE_SUB_PROCESS)
	static int currentProcess;
	static void (*ProcessFunctions[USING_PROCESS])(void);
#endif

void ProcessJobInitialize(void) {
	uint8_t i;
	/*
	 * 以下に宣言した変数の初期化を記述する
	 */
	/*******************************************************/
	LeftTire.Tire = _BRAKE;
	LeftTire.Status = BRAKE;
	LeftTire.Pwm = BRAKE_PWM;
	LeftTire.Count = 0;
	LeftTire.UpSpan = PWM_UP_CHANGE_SPAN;
	LeftTire.DownSpan = PWM_DOWN_CHANGE_SPAN;
	LeftTire.Act = FREE;
	LeftTire.MaxPwm = LTIRE_MAX_PWM;
	LeftTire.MotorNo = 0;
	
	RightTire.Tire = _BRAKE;
	RightTire.Status = BRAKE;
	RightTire.Pwm = BRAKE_PWM;
	RightTire.Count = 0;
	RightTire.UpSpan = PWM_UP_CHANGE_SPAN;
	RightTire.DownSpan = PWM_DOWN_CHANGE_SPAN;
	RightTire.Act = FREE;
	RightTire.MaxPwm = RTIRE_MAX_PWM;
	RightTire.MotorNo = 1;
	
	FrontTire.Tire = _BRAKE;
	FrontTire.Status = BRAKE;
	FrontTire.Pwm = BRAKE_PWM;
	FrontTire.Count = 0;
	FrontTire.UpSpan = PWM_UP_CHANGE_SPAN;
	FrontTire.DownSpan = PWM_DOWN_CHANGE_SPAN;
	FrontTire.Act = FREE;
	FrontTire.MaxPwm = FTIRE_MAX_PWM;
	FrontTire.MotorNo = 5;
	
	Steering.Tire = _BRAKE;
	Steering.Status = BRAKE;
	Steering.Pwm = BRAKE_PWM;
	Steering.Count = 0;
	Steering.UpSpan = STEERING_PWM_UP_SPAN;
	Steering.DownSpan = STEERING_PWM_DOWN_SPAN;
	Steering.Act = FREE;
	Steering.MaxPwm = STEERING_MAX_PWM;
	Steering.MotorNo = 2;
	

	BackUnitDowned = false;
	
	FrontTireDown = false;
	FrontTireStatus = 0;

	// Belt
	BeltStatus = BRAKE;
	
	
	LeftLimitSwPush = false;
	LeftLimitSwPushed = false;
	RightLimitSwPush = false;
	RightLimitSwPushed = false;
	LeftLimitSwCount = 0;
	RightLimitSwCount = 0;


	// Button Push Flag
	ProcessIncrementButtonPush = false;
	ProcessIncrementButtonPushed = false;
	ProcessDecrementButtonPush = false;
	ProcessDecrementButtonPushed = false;
	ArmButtonPush = false;
	ArmButtonPushed = false;
	BeltButtonPush = false;
	BeltButtonPushed = false;
	BeltBackButtonPush = false;
	BeltBackButtonPushed = false;	
	BackUnitUpButtonPush = false;
	BackUnitUpButtonPushed = false;
	PetitFlatPlaneLockButtonPush = false;
	PetitFlatPlaneLockButtonPushed = false;
	FrontTireUpDownButtonPush = false;
	FrontTireUpDownButtonPushed = false;
	
	
	TIRE_A = AIR_OFF;
	tmpBackUnitStatus = TIRE_A;
	
	LOCK_A0_S = AIR_ON;
	LOCK_A0_DS = AIR_OFF;
	F_LOCK_A = AIR_ON;
	Slope = _FLAT_PLANE_LOCK;
	tmpSlope = _FLAT_PLANE_LOCK;
	
	/*******************************************************/
	
	if(!FirstInitialized){
		currentProcess = 0;	
		for(i = 0; i < 120; i++){
			TireTable[i] = TireDownFunction(i);
		}
				
		#if (USING_PROCESS > 0)
			ProcessFunctions[0] = ProcessJob0;
		#endif
		#if (USING_PROCESS > 1)
			ProcessFunctions[1] = ProcessJob1;
		#endif
		#if (USING_PROCESS > 2)
			ProcessFunctions[2] = ProcessJob2;
		#endif
		#if (USING_PROCESS > 3)
			ProcessFunctions[3] = ProcessJob3;
		#endif
			FirstInitialized = true;
	}		
}

void SystemProcess(void) {
	while(1) {
		sei();

		#if defined(USE_SWITCH)
			GetSwitchStatus();
		#endif
		#if defined(USE_SENSOR)
			GetSensorStatus();
		#endif
		#if defined(USE_MU)
			controller = GetControllerData();
		#endif
		#if defined(USE_SENSOR_HUB)
			Sensor = GetSensorData();
		#endif
		

#if CTRL_CHECK
		if(!CtrlLost){
#endif
#if POWER_CHECK
			if(!powerLost){				
#endif
/*
 * 以下にメインのプロセスを記述
 */
/********************************************/
				UserTasks();
/********************************************/

#if POWER_CHECK
			}
			else{
				ProcessJobInitialize(); // 変数の初期化
				controller = ControllerDataReset();  // コントローラーの初期化
			}	
#endif
#if CTRL_CHECK
		}
		else{
			AllActuatorReset();  // 全アクチュエータのリセットと変数の初期化
		}	
#endif	
		ModeLedControl();

		#if defined(USE_DATALINE_CHECK)
		if(LineStatus == NO_DATA_IN_LINE){
			LedArray[DATALINE_LED_NO] = LED_ON;
		}
		else {
			LedArray[DATALINE_LED_NO] = LED_OFF;
		}
		#endif
		
		#if defined(USE_POWER_CHECK)
			SafetyChecker();
		#endif
		#if defined(USE_MOTOR)
			MotorUpdate();
		#endif
		#if defined(USE_AIR)
			AirUpdate();
		#endif
		#if defined(USE_BUZZER)
			BuzzerUpdate();
		#endif
		#if defined(USE_LED)
			LedUpdate();
		#endif
		#if defined(USE_SERVO)
			ServoUpdate();
		#endif		
		#if defined(USE_SENSOR_HUB)
		if(SensorDataReceived || SensorBoardLost){
		#endif
			#if defined(USE_SENSOR_HUB)
				DummyDataSet();
			#endif
			#if defined(USE_MOTOR_HUB)
				MotorHubUpdate();
			#endif
			#if defined(USE_LED_HUB)
				LedHubUpdate();
			#endif
			#if defined(USE_AIR_HUB)
				AirHubUpdate();
			#endif
		#if defined(USE_SENSOR_HUB)
		}		
		#endif
		#if defined(USE_SENSOR_HUB)
		if(!SensorBoardLost){
			GetSensorDataCommand();
		}		
		#endif		
	}
}

static void UserTasks(void){
	
// Process Change 
/**********************************************************************/
	// Startでプロセスをインクリメント、Selectでデクリメント
	if(PROCESS_INC_BUTTON){
		ProcessIncrementButtonPush = true;
	}
	else{
		if(ProcessIncrementButtonPush){
			ProcessIncrementButtonPushed = true;
		}
		ProcessIncrementButtonPush = false;					
	}
			
	if(PROCESS_DEC_BUTTON){
		ProcessDecrementButtonPush = true;
	}
	else{
		if(ProcessDecrementButtonPush){
			ProcessDecrementButtonPushed = true;
		}
		ProcessDecrementButtonPush = false;					
	}			
			
	if(ProcessIncrementButtonPushed){
		
		currentProcess++;
		if(currentProcess > 3){
			currentProcess = 0;
		}
					
		ResetProcessChange();
		if(currentProcess == 1){
			F_BELT_M.status = BACK;
			F_BELT_M.pwm = F_BELT_PWM;
			B_BELT_M.status = BACK;
			B_BELT_M.pwm = B_BELT_PWM;
			BeltStatus = FOR;
		}		
		if(currentProcess == 3){
			FRONT_TIRE_A = AIR_ON;
		}
		ProcessIncrementButtonPushed = false;
	}
				
	if(ProcessDecrementButtonPushed){
		if(currentProcess > 0){
			currentProcess-=1;
		}
		else{
			currentProcess = 3;
		}
		ResetProcessChange();
					
		ProcessDecrementButtonPushed = false;
	}
				

/**********************************************************************/
// End Process Change


// Main Process
//==================================================================================================================================//
				
	ProcessFunctions[currentProcess]();			// This is Sub Process
				
				
// Back Unit Up Down
//---------------------------------------------------------------------//
	if(BACK_UNIT_UP_DOWN_BUTTON && !FLAT_PLANE_LOCK_BUTTON && !LOCK_FREE_BUTTON){
		BackUnitUpButtonPush = true;
	}
	else{
		if(BackUnitUpButtonPush){
			BackUnitUpButtonPushed = true;
		}
		BackUnitUpButtonPush = false;
	}
				
	if(BackUnitUpButtonPushed){
		TIRE_A = !TIRE_A;
		BackUnitUpButtonPushed = false;
	}
//--------------------------------------------------------------------//
// End Back Unit up Down


				
// Tire Reset
//---------------------------------------------------------------------//
#if USE_TIRE_STOP
	if(TIRE_STATUS_RESET_BUTTON){
		LeftTire.Pwm = 0;
		RightTire.Pwm = 0;
		LeftTire.Tire = _BRAKE;
		RightTire.Tire = _BRAKE;
					
		BeltStatus = BRAKE;
		F_BELT_M.status = BRAKE;
		F_BELT_M.pwm = BRAKE_PWM;
		B_BELT_M.status = BRAKE;
		B_BELT_M.pwm = BRAKE_PWM;
	}
#endif
//---------------------------------------------------------------------//
// End Tire Reset

	TireControl(&LeftTire);
	TireControl(&RightTire);
	TireControl(&FrontTire);
				
	if(TIRE_A == AIR_OFF && tmpBackUnitStatus == AIR_ON){
		BackUnitDowned = true;
	}
				
	if(BackUnitDowned){
		Steering.Tire = _BRAKE;
		Steering.Pwm = 0;
		BackUnitDowned = false;
	}			
	tmpBackUnitStatus = TIRE_A;	
	
	
	if(!TIRE_A && currentProcess != 3){
		SteeringControl();
	}	
	else if(TIRE_A || currentProcess == 3){
		if(currentProcess == 3){
			if(STEERING_LEFT_BUTTON){
				STEERING_M.status = FOR;
				STEERING_M.pwm = STEERING_LEFT_PWM;
			}
			else if(STEERING_RIGHT_BUTTON){
				STEERING_M.status = BACK;
				STEERING_M.pwm = STEERING_RIGHT_PWM;
			}
			else{
				STEERING_M.status = BRAKE;
				STEERING_M.pwm = BRAKE_PWM;
			}
		}	
		else{
			if(STEERING_LEFT_BUTTON){
				STEERING_M.status = FOR;
				STEERING_M.pwm = SS_STEERING_LEFT_PWM;
			}
			else if(STEERING_RIGHT_BUTTON){
				STEERING_M.status = BACK;
				STEERING_M.pwm = SS_STEERING_RIGHT_PWM;
			}
			else{
				STEERING_M.status = BRAKE;
				STEERING_M.pwm = BRAKE_PWM;
			}
		}		
	}					
				
	if(controller->detail.Button.Y && currentProcess == 3){
		FRONT_TIRE.status = FOR;
		FRONT_TIRE.pwm = 20;
	}
	
	if(currentProcess == 3 && BACK_BUTTON){
		LTIRE.status = BACK;
		LTIRE.pwm = LTIRE_SLOPE_BACK_PWM;
		RTIRE.status = BACK;
		RTIRE.pwm = RTIRE_SLOPE_BACK_PWM;
		
		LeftTire.Tire = _BRAKE;
		LeftTire.Pwm = 0;
		RightTire.Tire = _BRAKE;
		RightTire.Pwm = 0;
	}
	
	
	if(STEERING_LEFT_SW && STEERING_M.status == FOR){
		STEERING_M.status = BRAKE;
		STEERING_M.pwm = BRAKE_PWM;
	}
				
	if(STEERING_RIGHT_SW && STEERING_M.status == BACK){
		STEERING_M.status = BRAKE;
		STEERING_M.pwm = BRAKE_PWM;
	}
	
	if(STEERING_LEFT_SW){
		if(!LeftLimitSwPushed){
			LeftLimitSwPush = true;
			LeftLimitSwPushed = true;
		}		
	}
	else {
		LeftLimitSwPushed = false;
	}
	
	if(STEERING_RIGHT_SW){
		if(!RightLimitSwPushed){
			RightLimitSwPush = true;
			RightLimitSwPushed = true;
		}		
	}
	else {
		RightLimitSwPushed = false;
	}
	
	if(LeftLimitSwPush){
		LeftLimitSwCount++;
	}
	
	if(LeftLimitSwCount >= BACK_UNIT_DOWN_SPAN){
		LeftLimitSwCount = 0;
		LeftLimitSwPush = false;
		TIRE_A = AIR_OFF;
	}
	
	if(RightLimitSwPush){
		RightLimitSwCount++;
	}
	
	if(RightLimitSwCount >= BACK_UNIT_DOWN_SPAN){
		RightLimitSwCount = 0;
		RightLimitSwPush = false;
		TIRE_A = AIR_OFF;
	}
//===========================================================================================================================//
// End MainProcess																												
}


#if defined(USE_SUB_PROCESS)
#if (USING_PROCESS > 0)
/*
 * スラロームモード
 */
static void ProcessJob0(void) {
	LeftTire.MaxPwm = LTIRE_MAX_PWM;
	RightTire.MaxPwm = RTIRE_MAX_PWM;
	Steering.UpSpan = STEERING_PWM_UP_SPAN;
	
	if(ACCEL_BUTTON){
		LeftTire.Act = FOR;
		RightTire.Act = FOR;
		FrontTire.Act = FOR;
	}
	else if(BACK_BUTTON){
		LeftTire.Act = BACK;
		RightTire.Act = BACK;
		FrontTire.Act = BACK;
	}
	else {
		LeftTire.Act = FREE;
		RightTire.Act = FREE;
		FrontTire.Act = FREE;
	}
	
	F_BELT_M.status = BRAKE;
	F_BELT_M.pwm = BRAKE_PWM;
	B_BELT_M.status = BRAKE;
	B_BELT_M.pwm = BRAKE_PWM;
	BeltStatus = BRAKE;
	
	
	if(ARM_BUTTON){
		ArmButtonPush = true;
	}
	else {
		if(ArmButtonPush){
			ArmButtonPushed = true;
		}
		ArmButtonPush = false;
	}
	
	if(ArmButtonPushed){
		ARM_A = !ARM_A;	
		ArmButtonPushed = false;
	}
	
	if(FRONT_TIRE_UP_DOWN_BUTTON){
		FrontTireUpDownButtonPush = true;
	}
	else{
		if(FrontTireUpDownButtonPush){
			FrontTireUpDownButtonPushed = true;
		}
		FrontTireUpDownButtonPush = false;
	}	
	
	if(FrontTireUpDownButtonPushed){
		FRONT_TIRE_A = !FRONT_TIRE_A;
		FrontTireUpDownButtonPushed = false;
	}
	
	if(Slope == _SLOPE_LOCK && tmpSlope == _FREE){
		PETIT_LOCK_A0_S = AIR_OFF;
	}
	
	LOCK_A0_S = AIR_ON;
	LOCK_A0_DS = AIR_OFF;
	F_LOCK_A = AIR_ON;
}
#endif

#if (USING_PROCESS > 1)
/*
 * 角材モード
 */
static void ProcessJob1(void) {
	LeftTire.MaxPwm = K_LTIRE_MAX_PWM;
	RightTire.MaxPwm = K_RTIRE_MAX_PWM;	
	Steering.UpSpan = STEERING_PWM_UP_SPAN;
	
	if(ACCEL_BUTTON){
		LeftTire.Act = FOR;
		RightTire.Act = FOR;
	}
	else if(BACK_BUTTON){
		LeftTire.Act = BACK;
		RightTire.Act = BACK;
	}
	else {
		LeftTire.Act = FREE;
		RightTire.Act = FREE;
	}	
	FrontTire.Act = FREE;
	
	if(BELT_BACK_BUTTON){
		BeltBackButtonPush = true;
	}
	else {
		if(BeltBackButtonPush){
			BeltBackButtonPushed = true;
		}
		BeltBackButtonPush = false;
	}
	
	if(BELT_BUTTON){
		BeltButtonPush = true;
	}
	else {
		if(BeltButtonPush){
			BeltButtonPushed = true;
		}
		BeltButtonPush = false;
	}
		
	if(BeltButtonPushed){
		if(BeltStatus == BRAKE || BeltStatus == FREE){
			BeltStatus = FOR;
			F_BELT_M.status = BACK;
			F_BELT_M.pwm = F_BELT_PWM;
			B_BELT_M.status = BACK;
			B_BELT_M.pwm = B_BELT_PWM;
		}
		else if(BeltStatus == FOR || BeltStatus == BACK){
			BeltStatus = BRAKE;
			F_BELT_M.status = BRAKE;
			F_BELT_M.pwm    = BRAKE_PWM;
			B_BELT_M.status = BRAKE;
			B_BELT_M.pwm    = BRAKE_PWM;
		}
		
		BeltButtonPushed = false;
	}
	else if(BeltBackButtonPushed){
		if(BeltStatus == BRAKE || BeltStatus == FREE){
			BeltStatus = BACK;
			F_BELT_M.status = FOR;
			F_BELT_M.pwm = F_BELT_PWM;
			B_BELT_M.status = FOR;
			B_BELT_M.pwm = B_BELT_PWM;
		}
		else if(BeltStatus == FOR || BeltStatus == BACK){
			BeltStatus = BRAKE;
			F_BELT_M.status = BRAKE;
			F_BELT_M.pwm    = BRAKE_PWM;
			B_BELT_M.status = BRAKE;
			B_BELT_M.pwm    = BRAKE_PWM;
		}
		
		BeltBackButtonPushed = false;
	}		
		
	
	if(TIRE_REAR_SW){
		TIRE_A = AIR_OFF;
	}
	if(TIRE_FRONT_SW){
		TIRE_A = AIR_ON;
	}
	
	LOCK_A0_S = AIR_ON;
	LOCK_A0_DS = AIR_OFF;
	ARM_A = AIR_OFF;
	F_LOCK_A = AIR_OFF;  // 角材ロック解除
	FRONT_TIRE_A = AIR_OFF;
}
#endif

#if (USING_PROCESS > 2)
static void ProcessJob2(void) {
	LeftTire.MaxPwm = SS_LTIRE_MAX_PWM;
	RightTire.MaxPwm = SS_RTIRE_MAX_PWM;
	Steering.UpSpan = 1;
	
	if(ACCEL_BUTTON){
		LeftTire.Act = FOR;
		RightTire.Act = FOR;
		FrontTire.Act = FOR;
	}
	else if(BACK_BUTTON){
		LeftTire.Act = BACK;
		RightTire.Act = BACK;
		FrontTire.Act = BACK;
	}
	else {
		LeftTire.Act = FREE;
		RightTire.Act = FREE;
		FrontTire.Act = FREE;
	}	
	
	F_BELT_M.status = BRAKE;
	F_BELT_M.pwm = BRAKE_PWM;
	B_BELT_M.status = BRAKE;
	B_BELT_M.pwm = BRAKE_PWM;
	BeltStatus = BRAKE;
	
	
	if(ARM_BUTTON){
		ArmButtonPush = true;
	}
	else {
		if(ArmButtonPush){
			ArmButtonPushed = true;
		}
		ArmButtonPush = false;
	}
	
	if(ArmButtonPushed){
		ARM_A = !ARM_A;	
		ArmButtonPushed = false;
	}
	
	if(FRONT_TIRE_UP_DOWN_BUTTON){
		FrontTireUpDownButtonPush = true;
	}
	else{
		if(FrontTireUpDownButtonPush){
			FrontTireUpDownButtonPushed = true;
		}
		FrontTireUpDownButtonPush = false;
	}	
	
	if(FrontTireUpDownButtonPushed){
		FRONT_TIRE_A = !FRONT_TIRE_A;
		FrontTireUpDownButtonPushed = false;
	}
	
	if(Slope == _SLOPE_LOCK && tmpSlope == _FREE){
		PETIT_LOCK_A0_S = AIR_OFF;
	}
	
	LOCK_A0_S = AIR_ON;
	LOCK_A0_DS = AIR_OFF;
	F_LOCK_A = AIR_ON;
}
#endif

#if (USING_PROCESS > 3)
static void ProcessJob3(void) {
	LeftTire.MaxPwm = S_LTIRE_MAX_PWM;
	RightTire.MaxPwm = S_RTIRE_MAX_PWM;
	Steering.UpSpan = STEERING_PWM_UP_SPAN;
	
	if(ACCEL_BUTTON){
		LeftTire.Act = FOR;
		RightTire.Act = FOR;
		FrontTire.Act = FOR;
	}
	else if(BACK_BUTTON){
		LeftTire.Act = BACK;
		RightTire.Act = BACK;
		FrontTire.Act = BACK;
	}
	else {
		LeftTire.Act = FREE;
		RightTire.Act = FREE;
		FrontTire.Act = FREE;
	}	
	
	if(ARM_BUTTON){
		ArmButtonPush = true;
	}
	else {
		if(ArmButtonPush){
			ArmButtonPushed = true;
		}
		ArmButtonPush = false;
	}
	
	if(ArmButtonPushed){
		ARM_A = !ARM_A;	
		ArmButtonPushed = false;
	}
	
		
// Slope Air Cylinder Control
//--------------------------------------------------------------------//
	tmpSlope = Slope;

	if(LOCK_FREE_BUTTON && !SLOPE_LOCK_BUTTON && !BACK_UNIT_UP_DOWN_BUTTON){
		LOCK_A0_S = AIR_OFF;
		LOCK_A0_DS = AIR_OFF;
	}
	else if(FLAT_PLANE_LOCK_BUTTON && !SLOPE_LOCK_BUTTON && !BACK_UNIT_UP_DOWN_BUTTON){
		LOCK_A0_S = AIR_ON;
		LOCK_A0_DS = AIR_OFF;
		FRONT_TIRE_A = AIR_OFF;
	}
	else if(SLOPE_LOCK_BUTTON && !FLAT_PLANE_LOCK_BUTTON && !LOCK_FREE_BUTTON){
		LOCK_A0_S = AIR_OFF;
		LOCK_A0_DS = AIR_ON;
	}
	
	if(LOCK_A0_S && !LOCK_A0_DS){
		// 平地ロック
		Slope = _FLAT_PLANE_LOCK;
	}
	else if(!LOCK_A0_S && LOCK_A0_DS){
		// 傾斜
		Slope = _SLOPE_LOCK;
	}
	else if(!LOCK_A0_S && !LOCK_A0_DS){
		// ロックフリー
		Slope = _FREE;
	}

	if(PETIT_FLAT_PLANE_LOCK_BUTTON){
		PetitFlatPlaneLockButtonPush = true;
	}
	else{
		if(PetitFlatPlaneLockButtonPush){
			PetitFlatPlaneLockButtonPushed = true;
		}
		PetitFlatPlaneLockButtonPush = false;
	}
	
	if(PetitFlatPlaneLockButtonPushed){
		PETIT_LOCK_A0_S = !PETIT_LOCK_A0_S;
		PetitFlatPlaneLockButtonPushed = false;
	}
	
	if(FRONT_TIRE_UP_DOWN_BUTTON){
		FrontTireUpDownButtonPush = true;
	}
	else{
		if(FrontTireUpDownButtonPush){
			FrontTireUpDownButtonPushed = true;
		}
		FrontTireUpDownButtonPush = false;
	}	
	
	if(FrontTireUpDownButtonPushed){
		FRONT_TIRE_A = !FRONT_TIRE_A;
		FrontTireUpDownButtonPushed = false;
	}
	
	if(Slope == _SLOPE_LOCK && tmpSlope == _FREE){
		PETIT_LOCK_A0_S = AIR_OFF;
	}
	
//--------------------------------------------------------------------//
	
	F_LOCK_A = AIR_ON;	// 角材ロック
}
#endif	

// 全アクチュエータのリセットと変数の初期化
static void AllActuatorReset(void){
	uint8_t i;
	
	// Actuator Reset
	#ifdef USE_MOTOR
	for(i = 0; i < USING_MOTOR; i++){
		MotorArray[i].status = BRAKE;
		MotorArray[i].pwm    = 100;
	}
	#endif
	#ifdef USE_AIR
	for(i = 0; i < USING_AIR; i++){
		AirArray[i] = AIR_OFF;
	}
	#endif
	#ifdef USE_MOTOR_HUB
	for(i = 0; i < USING_MOTOR_HUB; i++){
		MotorHubArray[i].status = BRAKE;
		MotorHubArray[i].pwm    = 100;
	}
	#endif
	#ifdef USE_AIR_HUB
	for(i = 0; i < USING_AIR_HUB; i++){
		AirHubArray[i] = AIR_OFF;
	}
	#endif
	#ifdef USE_MU
	controller = ControllerDataReset();
	#endif
	
	// Variable Reset
	ProcessJobInitialize();
}


static void TireControl(TireControlStatus *t){
	if(t->Act == FOR){
		if(t->Tire == _BRAKE){
			t->Tire = _FOR_UP;
			t->Pwm = 0;
		}
		else if(t->Tire == _FOR_DOWN){
			t->Tire = _FOR_UP;
		}
	}
	else{
		if(t->Tire == _FOR_UP || t->Tire == _FOR_MAX){
			t->Tire = _FOR_DOWN;
			t->p = SolveTireDownFunction(t->Pwm);
		}
	}
	
	if(t->Act == BACK){
		if(t->Tire == _BRAKE){
			t->Tire = _BACK_UP;
			t->Pwm = 0;
		}
		else if(t->Tire == _BACK_DOWN){
			t->Tire = _BACK_UP;
		}
	}
	else {
		if(t->Tire == _BACK_UP || t->Tire == _BACK_MAX){
			t->Tire = _BACK_DOWN;
			t->p = SolveTireDownFunction(t->Pwm);
		}
	}
	
	if(t->Act == BRAKE){
		t->Tire = _BRAKE;
	}
	
	switch(t->Tire){
	  case _FOR_UP:
		t->Count += 1;
		if(t->Count >= t->UpSpan){
			t->Pwm += 1;
			t->Count = 0;
		}
		if(t->Pwm >= t->MaxPwm){
			t->Tire = _FOR_MAX;
		}
		t->Status = FOR;
		break;
	  case _FOR_DOWN:
	    t->Count += 1;
		if(t->Count >= t->DownSpan){
			t->p += 1;
			t->Pwm = TireTable[t->p];
			t->Count = 0;
		}
		t->Status = FOR;	
		if(t->Pwm <= 1){
			t->Pwm = 0;
			t->Tire = _BRAKE;
			t->Status = BRAKE;
		}	
		break;
      case _FOR_MAX:
		t->Status = FOR;
		t->Pwm = t->MaxPwm;
		
		break;
	  case _BACK_UP:
	    t->Count += 1;
		if(t->Count >= t->UpSpan){
			t->Pwm += 1;
			t->Count = 0;
		}
		if(t->Pwm >= t->MaxPwm){
			t->Tire = _BACK_MAX;
		}
		t->Status = BACK;
		break;
	  case _BACK_DOWN:
	    t->Count += 1;
		if(t->Count >= t->DownSpan){
			t->p += 1;
			t->Pwm = TireTable[t->p];
			t->Count = 0;
		}
		t->Status = BACK;
		if(t->Pwm <= 1){
			t->Pwm = 0;
			t->Tire = _BRAKE;
			t->Status = BRAKE;
		}		
		break;
	  case _BACK_MAX:
	    t->Status = BACK;
		t->Pwm = t->MaxPwm;
	    
		break;
	  case _BRAKE:
		t->Status = BRAKE;
		t->Pwm = BRAKE_PWM;
		break;
	  default:
	    break;
	}
	
	if(t->MotorNo == 2){
		STEERING_M.status = t->Status;
		STEERING_M.pwm = t->Pwm;
	}
	else if(t->MotorNo == 5){
		FRONT_TIRE.status = t->Status;
		FRONT_TIRE.pwm = t->Pwm;
	}
	else{
		MotorArray[t->MotorNo].status = t->Status;
		MotorArray[t->MotorNo].pwm = t->Pwm;
	}	
}

static void SteeringControl(void){
	if(STEERING_LEFT_BUTTON){
		STEERING_M.status = FOR;
		STEERING_M.pwm = 100;
		
		LeftTire.MaxPwm = LTIRE_STEERING_MAX_PWM;
		RightTire.MaxPwm = RTIRE_MAX_PWM;
	}
	else if(STEERING_RIGHT_BUTTON){
		STEERING_M.status = BACK;
		STEERING_M.pwm = 100;
		
		LeftTire.MaxPwm = LTIRE_MAX_PWM;
		RightTire.MaxPwm = RTIRE_STEERING_MAX_PWM;
	}
	else {
		STEERING_M.status = BRAKE;
		STEERING_M.pwm = BRAKE_PWM;
		
		LeftTire.MaxPwm = LTIRE_MAX_PWM;
		RightTire.MaxPwm = RTIRE_MAX_PWM;
	}
}

static void ResetProcessChange(void){
	F_BELT_M.status = BRAKE;
	F_BELT_M.pwm = BRAKE_PWM;
	B_BELT_M.status = BRAKE;
	B_BELT_M.pwm    = BRAKE_PWM;
	BeltStatus = BRAKE;
	
	ProcessIncrementButtonPush = false;
	ProcessIncrementButtonPushed = false;
	ProcessDecrementButtonPush = false;
	ProcessDecrementButtonPushed = false;
	ArmButtonPush = false;
	ArmButtonPushed = false;
	BeltButtonPush = false;
	BeltButtonPushed = false;
	BeltBackButtonPush = false;
	BeltBackButtonPushed = false;	
	BackUnitUpButtonPush = false;
	BackUnitUpButtonPushed = false;
	PetitFlatPlaneLockButtonPush = false;
	PetitFlatPlaneLockButtonPushed = false;
	FrontTireUpDownButtonPush = false;
	FrontTireUpDownButtonPushed = false;
	
	FrontTireDown = false;
}

static uint8_t TireDownFunction(uint8_t x){
	static const float a = 100.0 / (119 * 119);
	
	return (uint8_t)((x - 119) * (x - 119) * a);
}

static uint8_t SolveTireDownFunction(uint8_t y){
	return -(119 / 10.0) * sqrt(y) + 119;
}

#endif

static void ModeLedControl(void){
	static bool ModeChanger = false;
	ModeChanger = !ModeChanger;
	
#if SPACE_MODE
	if(CtrlLost && powerLost){
		LedHubArray[0] = LED_ON;
		LedHubArray[1] = LED_OFF;
		LedHubArray[2] = LED_OFF;
		LedHubArray[3] = LED_ON;
	}
	else if(CtrlLost){
		LedHubArray[0] = LED_OFF;
		LedHubArray[1] = LED_ON;
		LedHubArray[2] = LED_OFF;
		LedHubArray[3] = LED_ON;
	}
	else if(powerLost){
		LedHubArray[0] = LED_ON;
		LedHubArray[1] = LED_ON;
		LedHubArray[2] = LED_OFF;
		LedHubArray[3] = LED_ON;
	}
	else{
#if SPACE_MODE
		switch(currentProcess){
			case 0:
				LedHubArray[0] = LED_OFF;
				LedHubArray[1] = LED_ON;
				LedHubArray[2] = LED_ON;
				LedHubArray[3] = LED_ON;
				break;
			case 1:
				LedHubArray[0] = LED_ON;
				LedHubArray[1] = LED_OFF;
				LedHubArray[2] = LED_ON;
				LedHubArray[3] = LED_ON;
				break;
			case 2:
				LedHubArray[0] = LED_OFF;
				LedHubArray[1] = LED_OFF;
				LedHubArray[2] = LED_OFF;
				LedHubArray[3] = LED_ON;
				break;
			case 3:
				LedHubArray[0] = LED_OFF;
				LedHubArray[1] = LED_OFF;
				LedHubArray[2] = LED_ON;
				LedHubArray[3] = LED_ON;
				break;
		}
#elif FULL_COLOR_MODE
		switch(currentProcess){
			case 0:
				LedHubArray[0] = LED_OFF;
				LedHubArray[1] = LED_ON;
				LedHubArray[2] = LED_ON;
				break;
			case 1:
				LedHubArray[0] = LED_ON;
				LedHubArray[1] = LED_OFF;
				LedHubArray[2] = LED_ON;
				break;
			case 2:
				LedHubArray[0] = LED_ON;
				LedHubArray[1] = LED_ON;
				LedHubArray[2] = LED_OFF;
				break;
		}
#endif
	}
#elif FULL_COLOR_MODE
	if(CtrlLost && powerLost){
		LedHubArray[0] = LED_ON;
		LedHubArray[1] = LED_ON;
		LedHubArray[2] = LED_ON;
	}
	else if(CtrlLost){
		LedHubArray[0] = LED_ON;
		LedHubArray[1] = LED_OFF;
		LedHubArray[2] = LED_OFF;
	}
	else if(powerLost){
		LedHubArray[0] = LED_OFF;
		LedHubArray[1] = LED_ON;
		LedHubArray[2] = LED_OFF;
	}
#endif

// リードスイッチ
	if(TIRE_FRONT_SW){
		LedHubArray[8] = LED_ON;
	}
	else{
		LedHubArray[8] = LED_OFF;
	}
	if(TIRE_REAR_SW){
		LedHubArray[9] = LED_ON;
	}
	else{
		LedHubArray[9] = LED_OFF;
	}
	
// リミットスイッチ
	if(STEERING_LEFT_SW){
		LedHubArray[10] = LED_ON;
	}
	else{
		LedHubArray[10] = LED_OFF;	
	}				
	if(STEERING_RIGHT_SW){
		LedHubArray[11] = LED_ON;
	}
	else{
		LedHubArray[11] = LED_OFF;
	}				
		
// ロックLed ( Parallel Communication )
		
	if(ModeChanger){
		LedHubArray[4] = LED_OFF;
		
		// 角材ロック
		if(!F_LOCK_A){
			LedHubArray[7] = LED_ON;
		}
		else{
			LedHubArray[7] = LED_OFF;
		}
		if(TIRE_A){
			LedHubArray[6] = LED_ON;
		}
		else{
			LedHubArray[6] = LED_OFF;
		}
		if(FRONT_TIRE_A){
			LedHubArray[5] = LED_ON;
		}
		else{
			LedHubArray[5] = LED_OFF;
		}
	}
	else{
		LedHubArray[4] = LED_ON;
		// ZRコマンド
		if(PETIT_LOCK_A0_S){
			LedHubArray[5] = LED_ON;
		}
		else{
			LedHubArray[5] = LED_OFF;
		}
		// 平地ロック
		if(LOCK_A0_S && !LOCK_A0_DS){
			LedHubArray[6] = LED_ON;
			LedHubArray[7] = LED_OFF;
		}
		else if(!LOCK_A0_S && LOCK_A0_DS){
		// 傾斜ロック
			LedHubArray[6] = LED_OFF;
			LedHubArray[7] = LED_ON;
		}
		else{
			LedHubArray[6] = LED_OFF;
			LedHubArray[7] = LED_OFF;
		}
	}
}	
