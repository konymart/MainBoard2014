/*
 * SystemDefines.h
 *
 * Created: 2014/06/17 20:23:02
 *  Author: tatsuro
 */ 


#ifndef SYSTEMDEFINES_H_
#define SYSTEMDEFINES_H_


#include <avr/io.h>
#include "../globalDef.h"

/************************************************************************/
// * 機能の使用不使用の選択
// * コメントアウトすることでその機能を使用できなくする．
/************************************************************************/

// Number of Subprocess
#define USE_SUB_PROCESS
#if defined(USE_SUB_PROCESS)
	#define USING_PROCESS		(8)
#endif

// TIMER
/*
 * このプログラムではタイマを安全装置，モータのPWM，サーボモータの制御，フォトインタラプタの監視など様々な用途に使用している．
 * しかし，ひとつのタイマに設定できる分周比はひとつであり固定であるから，きちんとタイマの割り振りを考えて動作種別，および分周比を決める必要がある．
 * たとえば，PWMに使用する場合には8ビット高速PWM動作で動かす必要があり，サーボを動かす場合にはICRを用いて16ビットの高速PWMにして動かす必要がある．
 * また，安全装置の場合にはカウントが0から最大まで計数する時間が500msよりも大きくなるよう分周比を決める必要がある．
 */

#define USE_TIMER
#if defined(USE_TIMER)
	#if defined(TCNT0)
		#define USE_TIMER0
	#endif
	#if defined(USE_TIMER0)
		#define TIMER0_WGM	(0x03)
		#define TIMER0_CS	(0x04)
	#endif
	#if defined(TCNT1)
		#define USE_TIMER1
	#endif
	#if defined(USE_TIMER1)
		#define TIMER1_WGM	(0x05)
		#define TIMER1_CS	(0x03)
	#endif
	#if defined(TCNT2)
		#define USE_TIMER2
	#endif
	#if defined(USE_TIMER2)
		#define TIMER2_WGM	(0x00)
		#define TIMER2_CS	(0x03)
	#endif
	#if defined(TCNT3)
		#define USE_TIMER3
	#endif
	#if defined(USE_TIMER3)
		#define TIMER3_WGM	(0x05)
		#define TIMER3_CS	(0x02)
	#endif
	#if defined(TCNT4)
		#define USE_TIMER4
	#endif
	#if defined(USE_TIMER4)
		#define TIMER4_WGM	(0x05)
		#define TIMER4_CS	(0x02)
	#endif
	#if defined(TCNT5)
		#define USE_TIMER5
	#endif
	#if defined(USE_TIMER5)
		#define TIMER5_WGM	(0x00)
		#define TIMER5_CS	(0x01)
	#endif
#endif

// UART
//#define USE_UART

// EX-INT
#define USE_EXINT

// PC-INT
//#define USE_PCINT

// MU
/*
 * データを受信している場合にLEDを点灯させたい場合はLEDを有効にする必要がある．
 */
#define USE_MU
#if defined(USE_MU)
	#define MU_UART_NO		(0)
	#define MU_LED_NO		(0)
	#define CTRL_CHECK		(1)  // コントローラーが切れた時にリセットする。0にすれば無効化
#endif

// SWITCH
#define USE_SWITCH
#if defined(USE_SWITCH)
	#define USING_SWITCH	(8)
#endif

// Sensor
#define USE_SENSOR
#if defined(USE_SENSOR)
	#define USING_SENSOR	(4)
#endif

// DIP SWITCH
#define USE_DIP_SWITCH

// ENCODER
/*
 * 使用するために，TIMERとEXINTを有効にする必要がある．
 */
#define USE_ENCODER
#if defined(USE_ENCODER)
	#define USING_ENCODER				(6)
	
	#if (USING_ENCODER > 0)
		#define USE_ENCODER0
	#endif
	#if defined(USE_ENCODER0)
		#define ENCODER0_MODE			'E'
		#define ENCODER0_FUNC_NO		(0)
		#if (ENCODER0_MODE == 'P')
			#define ENCODER0_PCINT_BIT	(12)
		#endif
	#endif
	#if (USING_ENCODER > 1)
		#define USE_ENCODER1
	#endif
	#if defined(USE_ENCODER1)
		#define ENCODER1_MODE			'E'
		#define ENCODER1_FUNC_NO		(1)
		#if (ENCODER1_MODE == 'P')
			#define ENCODER1_PCINT_BIT	(15)
		#endif
	#endif
	#if (USING_ENCODER > 2)
		#define USE_ENCODER2
	#endif
	#if defined(USE_ENCODER2)
		#define ENCODER2_MODE			'E'
		#define ENCODER2_FUNC_NO		(4)
		#if (ENCODER2_MODE == 'P')
			#define ENCODER2_PCINT_BIT	(23)
		#endif
	#endif
	#if (USING_ENCODER > 3)
		#define USE_ENCODER3
	#endif
	#if defined(USE_ENCODER3)
		#define ENCODER3_MODE			'E'
		#define ENCODER3_FUNC_NO		(5)
		#if (ENCODER3_MODE == 'P')
			#define ENCODER3_PCINT_BIT	(15)
		#endif
	#endif
	#if (USING_ENCODER > 4)
		#define USE_ENCODER4
	#endif
	#if defined(USE_ENCODER4)
		#define ENCODER4_MODE			'E'
		#define ENCODER4_FUNC_NO		(6)
		#if (ENCODER4_MODE == 'P')
			#define ENCODER4_PCINT_BIT	(0)
		#endif
	#endif
	#if (USING_ENCODER > 5)
		#define USE_ENCODER5
	#endif
	#if defined(USE_ENCODER5)
		#define ENCODER5_MODE			'E'
		#define ENCODER5_FUNC_NO		(7)
		#if (ENCODER5_MODE == 'P')
			#define ENCODER5_PCINT_BIT	(0)
		#endif
	#endif
#endif


// AIR
#define USE_AIR
#if defined(USE_AIR)
	#define USING_AIR		(4)
	#if (USING_AIR > 0)
		#define USE_AIR00
	#endif
	#if (USING_AIR > 1)
		#define USE_AIR01
	#endif
	#if (USING_AIR > 2)
		#define USE_AIR02
	#endif
	#if (USING_AIR > 3)
		#define USE_AIR03
	#endif
	#if (USING_AIR > 4)
		#define USE_AIR04
	#endif
	#if (USING_AIR > 5)
		#define USE_AIR05
	#endif
	#if (USING_AIR > 6)
		#define USE_AIR06
	#endif
	#if (USING_AIR > 7)
		#define USE_AIR07
	#endif
	#if (USING_AIR > 8)
		#define USE_AIR08
	#endif
	#if (USING_AIR > 9)
		#define USE_AIR09
	#endif
#endif

// LED
#define USE_LED
#if defined(USE_LED)
	#define USING_LED	(4)
	#if (USING_LED > 0)
		#define USE_LED00
	#endif
	#if (USING_LED > 1)
		#define USE_LED01
	#endif
	#if (USING_LED > 2)
		#define USE_LED02
	#endif
	#if (USING_LED > 3)
		#define USE_LED03
	#endif
	#if (USING_LED > 4)
		#define USE_LED04
	#endif
	#if (USING_LED > 5)
		#define USE_LED05
	#endif
	#if (USING_LED > 6)
		#define USE_LED06
	#endif
	#if (USING_LED > 7)
		#define USE_LED07
	#endif
	#if (USING_LED > 8)
		#define USE_LED08
	#endif
	#if (USING_LED > 9)
		#define USE_LED09
	#endif
	#if (USING_LED > 10)
		#define USE_LED10
	#endif
	#if (USING_LED > 11)
		#define USE_LED11
	#endif
	#if (USING_LED > 12)
		#define USE_LED12
	#endif
	#if (USING_LED > 13)
		#define USE_LED13
	#endif
	#if (USING_LED > 14)
		#define USE_LED14
	#endif
	#if (USING_LED > 15)
		#define USE_LED15
	#endif
	#if (USING_LED > 16)
		#define USE_LED16
	#endif
	#if (USING_LED > 17)
		#define USE_LED17
	#endif
	#if (USING_LED > 18)
		#define USE_LED18
	#endif
	#if (USING_LED > 19)
		#define USE_LED19
	#endif
	#if (USING_LED > 20)
		#define USE_LED20
	#endif
#endif

// MOTOR
/*
 * 使用するために，TIMERを有効にする必要がある．
 */
#define USE_MOTOR
#if defined(USE_MOTOR)
	#define USING_MOTOR	(2)
	#if (USING_MOTOR > 0)
		#define USE_MOTOR00
	#endif
	#if defined(USE_MOTOR00)
		#define MOTOR00_TIMER_NO	(0)
		#define MOTOR00_PWM_PORT	('A')
	#endif
	#if (USING_MOTOR > 1)
		#define USE_MOTOR01
	#endif
	#if defined(USE_MOTOR01)
		#define MOTOR01_TIMER_NO	(1)
		#define MOTOR01_PWM_PORT	('A')
	#endif
	#if (USING_MOTOR > 2)
		#define USE_MOTOR02
	#endif
	#if defined(USE_MOTOR02)
		#define MOTOR02_TIMER_NO	(1)
		#define MOTOR02_PWM_PORT	('A')
	#endif
	#if (USING_MOTOR > 3)
		#define USE_MOTOR03
	#endif
	#if defined(USE_MOTOR03)
		#define MOTOR03_TIMER_NO	(2)
		#define MOTOR03_PWM_PORT	('A')
	#endif
	#if (USING_MOTOR > 4)
		#define USE_MOTOR04
	#endif
	#if defined(USE_MOTOR04)
		#define MOTOR04_TIMER_NO	(2)
		#define MOTOR04_PWM_PORT	('B')
	#endif
	#if (USING_MOTOR > 5)
		#define USE_MOTOR05
	#endif
	#if defined(USE_MOTOR05)
		#define MOTOR05_TIMER_NO	(4)
		#define MOTOR05_PWM_PORT	('C')
	#endif
	#if (USING_MOTOR > 6)
		#define USE_MOTOR06
	#endif
	#if defined(USE_MOTOR06)
		#define MOTOR06_TIMER_NO	(4)
		#define MOTOR06_PWM_PORT	('B')
	#endif
	#if (USING_MOTOR > 7)
		#define USE_MOTOR07
	#endif
	#if defined(USE_MOTOR07)
		#define MOTOR07_TIMER_NO	(4)
		#define MOTOR07_PWM_PORT	('A')
	#endif
	#if (USING_MOTOR > 8)
		#define USE_MOTOR08
	#endif
	#if defined(USE_MOTOR08)
		#define MOTOR08_TIMER_NO	(3)
		#define MOTOR08_PWM_PORT	('B')
	#endif
	#if (USING_MOTOR > 9)
		#define USE_MOTOR09
	#endif
	#if defined(USE_MOTOR09)
		#define MOTOR09_TIMER_NO	(3)
		#define MOTOR09_PWM_PORT	('A')
	#endif
	#if (USING_MOTOR > 10)
//		#define USE_MOTOR10
	#endif
	#if (USING_MOTOR > 11)
//		#define USE_MOTOR11
	#endif
	#if (USING_MOTOR > 12)
//		#define USE_MOTOR12
	#endif
	#if (USING_MOTOR > 13)
//		#define USE_MOTOR13
	#endif
	#if (USING_MOTOR > 14)
//		#define USE_MOTOR14
	#endif
#endif

// SERVO
/*
 * サーボモータを駆動するために指定できるタイマは16ビットタイマである必要がある．
 */
//#define USE_SERVO
#if defined(USE_SERVO)
	#define USING_SERVO		(4)
	#if (USING_SERVO > 0)
		#define USE_SERVO0
	#endif
	#if defined(USE_SERVO0)
		#define SERVO0_TIMER_NO		(1)
		#define SERVO0_DEGREE_PORT	('A')
	#endif
	#if (USING_SERVO > 1)
		#define USE_SERVO1
	#endif
	#if defined(USE_SERVO1)
		#define SERVO1_TIMER_NO		(1)
		#define SERVO1_DEGREE_PORT	('A')
	#endif
	#if (USING_SERVO > 2)
		#define USE_SERVO2
	#endif
	#if defined(USE_SERVO2)
		#define SERVO2_TIMER_NO		(1)
		#define SERVO2_DEGREE_PORT	('A')
	#endif
	#if (USING_SERVO > 3)
		#define USE_SERVO3
	#endif
	#if defined(USE_SERVO3)
		#define SERVO3_TIMER_NO		(1)
		#define SERVO3_DEGREE_PORT	('A')
	#endif
#endif

// SAFETY
/*
 * 使用するために，タイマを有効にする必要がある．
 * 電源の導通を表示したい場合には，LEDを有効にする必要がある．
 *
 * 特別な事情がない限り，この機能を無効にしないこと！！
 *
 */
#define USE_SAFETY
#if defined(USE_SAFETY)
	#define SAFETY_TIMER_NO		(2)
	#define USE_BUZZER
	#define USE_POWER_CHECK
	#if defined(USE_POWER_CHECK)
		#define POWER_CHECK			(1)		// パワーチェックのリセットを行うか。0にすれば無効化
		#define SAFETY_LED_NO		(3)
	#endif
#endif


/************************************************************************/
// それぞれの機能で使用するポートとピンを設定                              */
// 機能を使用しないときはコメントアウト                                    */
/************************************************************************/

/*
 * DIPスイッチのための設定
 */
#if (defined(USE_DIP_SWITCH) || defined(USE_MU))
	#define DIP_0_PORT		IO.PF
	#define DIP_0_BIT		PF4
	#define DIP_1_PORT		IO.PF
	#define DIP_1_BIT		PF5
	#define DIP_2_PORT		IO.PF
	#define DIP_2_BIT		PF6
	#define DIP_3_PORT		IO.PF
	#define DIP_3_BIT		PF7
#endif

/*
 * Switch入力のための設定
 */
#if defined(USE_SWITCH)
	#if (USING_SWITCH > 0)
		#define SWITCH_0_PORT	IO.PA
		#define SWITCH_0_BIT	PA3
	#endif
	#if (USING_SWITCH > 1)
		#define SWITCH_1_PORT	IO.PA
		#define SWITCH_1_BIT	PA2
	#endif
	#if (USING_SWITCH > 2)
		#define SWITCH_2_PORT	IO.PG
		#define SWITCH_2_BIT	PG1
	#endif
	#if (USING_SWITCH > 3)
		#define SWITCH_3_PORT	IO.PC
		#define SWITCH_3_BIT	PC0
	#endif
	#if (USING_SWITCH > 4)
		#define SWITCH_4_PORT	IO.PC
		#define SWITCH_4_BIT	PC1
	#endif
	#if (USING_SWITCH > 5)
		#define SWITCH_5_PORT	IO.PC
		#define SWITCH_5_BIT	PC2
	#endif
	#if (USING_SWITCH > 6)
		#define SWITCH_6_PORT	IO.PC
		#define SWITCH_6_BIT	PC3
	#endif
	#if (USING_SWITCH > 7)
		#define SWITCH_7_PORT	IO.PC
		#define SWITCH_7_BIT	PC4
	#endif
	#if (USING_SWITCH > 8)
		#define SWITCH_8_PORT	IO.PD
		#define SWITCH_8_BIT	PD3
	#endif
#endif

/*
 * Sensorのための設定
 */
#if defined(USE_SENSOR)
	#if (USING_SENSOR > 0)
		#define SENSOR_0_PORT	IO.PF
		#define SENSOR_0_BIT	PF0
	#endif
	#if (USING_SENSOR > 1)
		#define SENSOR_1_PORT	IO.PF
		#define SENSOR_1_BIT	PF1
	#endif
	#if (USING_SENSOR > 2)
		#define SENSOR_2_PORT	IO.PF
		#define SENSOR_2_BIT	PF2
	#endif
	#if (USING_SWITCH > 3)
		#define SENSOR_3_PORT	IO.PF
		#define SENSOR_3_BIT	PF3
	#endif
	#if (USING_SWITCH > 4)
		#define SENSOR_4_PORT	IO.PC
		#define SENSOR_4_BIT	PC1
	#endif
#endif

/*
 * ENCODERのための設定
 */
#if defined(USE_ENCODER)
	#if defined(USE_ENCODER0)
		#define ENCODER_0_PORT		IO.PD
		#define ENCODER_0_BIT		PD0
	#endif
	#if defined(USE_ENCODER1)
		#define ENCODER_1_PORT		IO.PD
		#define ENCODER_1_BIT		PD1
	#endif
	#if defined(USE_ENCODER2)
		#define ENCODER_2_PORT		IO.PE
		#define ENCODER_2_BIT		PE4
	#endif
	#if defined(USE_ENCODER3)
		#define ENCODER_3_PORT		IO.PE
		#define ENCODER_3_BIT		PE5
	#endif
	#if defined(USE_ENCODER4)
		#define ENCODER_4_PORT		IO.PE
		#define ENCODER_4_BIT		PE6
	#endif
	#if defined(USE_ENCODER5)
		#define ENCODER_5_PORT		IO.PE
		#define ENCODER_5_BIT		PE7
	#endif
	#if defined(USE_ENCODER6)
		#define ENCODER_6_PORT		IO.PD
		#define ENCODER_6_BIT		PD3
	#endif
	#if defined(USE_ENCODER7)
		#define ENCODER_7_PORT		IO.PD
		#define ENCODER_7_BIT		PD1
	#endif
	#if defined(USE_ENCODER8)
		#define ENCODER_8_PORT		IO.PD
		#define ENCODER_8_BIT		PD1
	#endif
	#if defined(USE_ENCODER9)
		#define ENCODER_9_PORT		IO.PD
		#define ENCODER_9_BIT		PD1
	#endif
	#if defined(USE_ENCODER10)
		#define ENCODER_10_PORT		IO.PD
		#define ENCODER_10_BIT		PD1
	#endif
	#if defined(USE_ENCODER11)
		#define ENCODER_11_PORT		IO.PD
		#define ENCODER_11_BIT		PD1
	#endif
	#if defined(USE_ENCODER12)
		#define ENCODER_12_PORT		IO.PD
		#define ENCODER_12_BIT		PD1
	#endif
#endif

/*
 * エアのための設定
 */
#if defined(USE_AIR)
	#if defined(USE_AIR00)
		#define AIR_0_PORT		IO.PD
		#define AIR_0_BIT		PD5
	#endif
	#if defined(USE_AIR01)
		#define AIR_1_PORT		IO.PD
		#define AIR_1_BIT		PD6
	#endif
	#if defined(USE_AIR02)
		#define AIR_2_PORT		IO.PD
		#define AIR_2_BIT		PD7
	#endif
	#if defined(USE_AIR03)
		#define AIR_3_PORT		IO.PG
		#define AIR_3_BIT		PG0
	#endif
	#if defined(USE_AIR04)
		#define AIR_4_PORT		IO.PF
		#define AIR_4_BIT		PF5
	#endif
	#if defined(USE_AIR05)
		#define AIR_5_PORT		IO.PF
		#define AIR_5_BIT		PF4
	#endif
	#if defined(USE_AIR06)
		#define AIR_6_PORT		IO.PF
		#define AIR_6_BIT		PF3
	#endif
	#if defined(USE_AIR07)
		#define AIR_7_PORT		IO.PF
		#define AIR_7_BIT		PF2
	#endif
	#if defined(USE_AIR08)
		#define AIR_8_PORT		IO.PF
		#define AIR_8_BIT		PF1
	#endif
	#if defined(USE_AIR09)
		#define AIR_9_PORT		IO.PF
		#define AIR_9_BIT		PF0
	#endif
#endif

/*
 * ブザーのための設定
 */
#if defined(USE_BUZZER)
	#define BUZZER_PORT		IO.PA
	#define BUZZER_BIT		PA1
#endif

/*
 * モータのための設定
 */
#if defined(USE_MOTOR)
	#if defined(USE_MOTOR00)
		#define MOTOR_00_D1_PORT	IO.PB
		#define MOTOR_00_D1_BIT		PB2
		#define MOTOR_00_D2_PORT	IO.PB
		#define MOTOR_00_D2_BIT		PB3
		#define MOTOR_00_PWM_OCR	TIMER.T0.OCRA
	#endif
	#if defined(USE_MOTOR01)
		#define MOTOR_01_D1_PORT	IO.PG
		#define MOTOR_01_D1_BIT		PG3
		#define MOTOR_01_D2_PORT	IO.PG
		#define MOTOR_01_D2_BIT		PG4
		#define MOTOR_01_PWM_OCR	TIMER.T1.OCRA
	#endif
	#if defined(USE_MOTOR02)
		#define MOTOR_02_D1_PORT	IO.PF
		#define MOTOR_02_D1_BIT		PF4
		#define MOTOR_02_D2_PORT	IO.PF
		#define MOTOR_02_D2_BIT		PF5
		#define MOTOR_02_PWM_OCR	TIMER.T1.OCRA
	#endif
	#if defined(USE_MOTOR03)
		#define MOTOR_03_D1_PORT	IO.PF
		#define MOTOR_03_D1_BIT		PF6
		#define MOTOR_03_D2_PORT	IO.PF
		#define MOTOR_03_D2_BIT		PF7
		#define MOTOR_03_PWM_OCR	TIMER.T2.OCRA
	#endif
	#if defined(USE_MOTOR04)
		#define MOTOR_04_D1_PORT	IO.PK
		#define MOTOR_04_D1_BIT		PK0
		#define MOTOR_04_D2_PORT	IO.PK
		#define MOTOR_04_D2_BIT		PK1
		#define MOTOR_04_PWM_OCR	TIMER.T2.OCRB
	#endif
	#if defined(USE_MOTOR05)
		#define MOTOR_05_D1_PORT	IO.PK
		#define MOTOR_05_D1_BIT		PK2
		#define MOTOR_05_D2_PORT	IO.PK
		#define MOTOR_05_D2_BIT		PK3
		#define MOTOR_05_PWM_OCR	TIMER.T4.OCRC
	#endif
	#if defined(USE_MOTOR06)
		#define MOTOR_06_D1_PORT	IO.PK
		#define MOTOR_06_D1_BIT		PK4
		#define MOTOR_06_D2_PORT	IO.PK
		#define MOTOR_06_D2_BIT		PK5
		#define MOTOR_06_PWM_OCR	TIMER.T4.OCRB
	#endif
	#if defined(USE_MOTOR07)
		#define MOTOR_07_D1_PORT	IO.PK
		#define MOTOR_07_D1_BIT		PK6
		#define MOTOR_07_D2_PORT	IO.PK
		#define MOTOR_07_D2_BIT		PK7
		#define MOTOR_07_PWM_OCR	TIMER.T4.OCRA
	#endif
	#if defined(USE_MOTOR08)
		#define MOTOR_08_D1_PORT	IO.PA
		#define MOTOR_08_D1_BIT		PA0
		#define MOTOR_08_D2_PORT	IO.PA
		#define MOTOR_08_D2_BIT		PA1
		#define MOTOR_08_PWM_OCR	TIMER.T3.OCRB
	#endif
	#if defined(USE_MOTOR09)
		#define MOTOR_09_D1_PORT	IO.PA
		#define MOTOR_09_D1_BIT		PA2
		#define MOTOR_09_D2_PORT	IO.PA
		#define MOTOR_09_D2_BIT		PA3
		#define MOTOR_09_PWM_OCR	TIMER.T3.OCRA
	#endif
	#if defined(USE_MOTOR10)
		#define MOTOR_10_D1_PORT	IO.PA
		#define MOTOR_10_D1_BIT		PA5
		#define MOTOR_10_D2_PORT	IO.PJ
		#define MOTOR_10_D2_BIT		PA6
	#endif
	#if defined(USE_MOTOR11)
		#define MOTOR_11_D1_PORT	IO.PA
		#define MOTOR_11_D1_BIT		PA5
		#define MOTOR_11_D2_PORT	IO.PA
		#define MOTOR_11_D2_BIT		PA6
	#endif
	#if defined(USE_MOTOR12)
		#define MOTOR_12_D1_PORT	IO.PJ
		#define MOTOR_12_D1_BIT		PJ5
		#define MOTOR_12_D2_PORT	IO.PJ
		#define MOTOR_12_D2_BIT		PJ6
	#endif
	#if defined(USE_MOTOR13)
		#define MOTOR_13_D1_PORT	IO.PC
		#define MOTOR_13_D1_BIT		PC7
		#define MOTOR_13_D2_PORT	IO.PJ
		#define MOTOR_13_D2_BIT		PJ0
	#endif
	#if defined(USE_MOTOR14)
		#define MOTOR_14_D1_PORT	IO.PC
		#define MOTOR_14_D1_BIT		PC1
		#define MOTOR_14_D2_PORT	IO.PC
		#define MOTOR_14_D2_BIT		PC2
	#endif
#endif

/*
 * SERVOのための設定
 */
#if defined(USE_SERVO)
	#if defined(USE_SERVO0)
		#define SERVO0_DEGREE_OCR	 TIMER.T3.OCRB
	#endif
	#if defined(USE_SERVO1)
		#define SERVO1_DEGREE_OCR	 TIMER.T3.OCRA
	#endif
	#if defined(USE_SERVO2)
		#define SERVO2_DEGREE_OCR	 TIMER.T3.OCRC
	#endif
	#if defined(USE_SERVO3)
		#define SERVO3_DEGREE_OCR	 TIMER.T1.OCRA
	#endif
#endif

/*
 * LEDのための設定
 */
#if defined(USE_LED)
	#if defined(USE_LED00)
		#define LED_00_PORT		IO.PA
		#define LED_00_BIT		PA7
	#endif
	#if defined(USE_LED01)
		#define LED_01_PORT		IO.PA
		#define LED_01_BIT		PA6
	#endif
	#if defined(USE_LED02)
		#define LED_02_PORT		IO.PA
		#define LED_02_BIT		PA5
	#endif
	#if defined(USE_LED03)
		#define LED_03_PORT		IO.PA
		#define LED_03_BIT		PA4
	#endif
	#if defined(USE_LED04)
		#define LED_04_PORT		IO.PF
		#define LED_04_BIT		PF0
	#endif
	#if defined(USE_LED05)
		#define LED_05_PORT		IO.PF
		#define LED_05_BIT		PF1
	#endif
	#if defined(USE_LED06)
		#define LED_06_PORT		IO.PF
		#define LED_06_BIT		PF2
	#endif
	#if defined(USE_LED07)
		#define LED_07_PORT		IO.PF
		#define LED_07_BIT		PF3
	#endif
	#if defined(USE_LED08)
		#define LED_08_PORT		IO.PC
		#define LED_08_BIT		PC4
	#endif
	#if defined(USE_LED09)
		#define LED_09_PORT		IO.PC
		#define LED_09_BIT		PC5
	#endif
	#if defined(USE_LED10)
		#define LED_10_PORT		IO.PC
		#define LED_10_BIT		PC6
	#endif
	#if defined(USE_LED11)
		#define LED_11_PORT		IO.PC
		#define LED_11_BIT		PC7
	#endif
	#if defined(USE_LED12)
		#define LED_12_PORT		IO.PJ
		#define LED_12_BIT		PJ0
	#endif
	#if defined(USE_LED13)
		#define LED_13_PORT		IO.PJ
		#define LED_13_BIT		PJ1
	#endif
	#if defined(USE_LED14)
		#define LED_14_PORT		IO.PJ
		#define LED_14_BIT		PJ2
	#endif
	#if defined(USE_LED15)
		#define LED_15_PORT		IO.PJ
		#define LED_15_BIT		PJ5
	#endif
	#if defined(USE_LED16)
		#define LED_16_PORT		IO.PJ
		#define LED_16_BIT		PJ6
	#endif
	#if defined(USE_LED17)
		#define LED_17_PORT		IO.PC
		#define LED_17_BIT		PC7
	#endif
	#if defined(USE_LED18)
		#define LED_18_PORT		IO.PJ
		#define LED_18_BIT		PJ0
	#endif
	#if defined(USE_LED19)
		#define LED_19_PORT		IO.PC
		#define LED_19_BIT		PC1
	#endif
	#if defined(USE_LED20)
		#define LED_20_PORT		IO.PC
		#define LED_20_BIT		PC2
	#endif
#endif

/*
 * safetyのための設定
 */
#if defined(USE_SAFETY)
	#if defined(USE_POWER_CHECK)
		#define SAFETY_READ_PORT	IO.PA
		#define SAFETY_READ_BIT		PA0
	#endif
#endif


/***********************************************************************
*
* 以降はハブ基板への設定に関しての記述である
*
***********************************************************************/


#define USE_HUB
#if defined(USE_HUB)

/*
 * RS485
 */
	#define USE_RS485
	#if defined(USE_RS485)
		#define RS485_UART_NO		(1)			// RS485で使用するUartの番号
		#define RS485_SELECT_PORT	IO.PD		// RS485の動作変更用のIOポート
		#define RS485_SELECT_BIT	PD4
		#define BUFFER_SIZE			(256)		// リングバッファのサイズ
		
		#define USE_DATALINE_CHECK				// RS485の伝送路の状態の確認
		#if defined(USE_DATALINE_CHECK)
			#define DATALINE_LED_NO		(2)		// 確認用LEDの番号
		#endif
	#endif

/*
 * MotorHub
 */
	#define USE_MOTOR_HUB	
	#if defined(USE_MOTOR_HUB)
		#define USING_MOTOR_HUB		(8)		// ハブ基板上で使用するモーターの数
	#endif

/*
 * LedHub
 */
	#define USE_LED_HUB	
	#if defined(USE_LED_HUB)
		#define USING_LED_HUB		(16)		// ハブ基板上で使用するLEDの数
	#endif
	
/*
 * AirHub
 */
	#define USE_AIR_HUB	
	#if defined(USE_AIR_HUB)
		#define USING_AIR_HUB		(8)		// ハブ基板上で使用するエアの数
	#endif
	
/*
 * SensorHub
 *
 * 使わないなら機能を無効にしたほうが速度が上がるよ
 * 
 */
	//#define USE_SENSOR_HUB
	#if defined(USE_SENSOR_HUB)
		#define SENSOR_LED_NO		(1)         // センサー基板からデータが来ているときに光らせるLEDの番号
	#endif
	
/*
 * Watch Dog Timer
 *
 * センサー基板の監視を行う
 * 有効にしなくてもよいが、場合によって使い分けたほうがいい
 * センサー基板をロストした時に再度見つけるまでリセットをかけ続けたいなら有効に、
 * ロストしたらセンサ基盤を放置しておきたいなら無効にするべきである
 * センサ基盤を使わないなら無効にしないと、延々とリセットがかけられ続けるよ
 *
 */
	#if defined(USE_SENSOR_HUB)
		#define WDT_RESET
		#ifdef WDT_RESET
			#define WDT_RESET_TIME	WDTO_500MS
		#endif
	#endif

#endif

#endif /* SYSTEMDEFINES_H_ */