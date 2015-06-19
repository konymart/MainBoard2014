/*
 * Motor.h
 *
 * Created: 2014/06/19 17:55:44
 *  Author: tatsuro
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

static void MotorStatusChecker(uint8_t* status, uint8_t* pwm);

#if defined(USE_TIMER0)
static void PwmTimerInitialize0(uint8_t port);
#endif
#if defined(USE_TIMER1)
static void PwmTimerInitialize1(uint8_t port);
#endif
#if defined(USE_TIMER2)
static void PwmTimerInitialize2(uint8_t port);
#endif
#if defined(USE_TIMER3)
static void PwmTimerInitialize3(uint8_t port);
#endif
#if defined(USE_TIMER4)
static void PwmTimerInitialize4(uint8_t port);
#endif
#if defined(USE_TIMER5)
static void PwmTimerInitialize5(uint8_t port);
#endif

#if defined(USE_MOTOR00)
static void SetActionMotor0(uint8_t status, uint8_t pwm);
#endif
#if defined(USE_MOTOR01)
static void SetActionMotor1(uint8_t status, uint8_t pwm);
#endif
#if defined(USE_MOTOR02)
static void SetActionMotor2(uint8_t status, uint8_t pwm);
#endif
#if defined(USE_MOTOR03)
static void SetActionMotor3(uint8_t status, uint8_t pwm);
#endif
#if defined(USE_MOTOR04)
static void SetActionMotor4(uint8_t status, uint8_t pwm);
#endif
#if defined(USE_MOTOR05)
static void SetActionMotor5(uint8_t status, uint8_t pwm);
#endif
#if defined(USE_MOTOR06)
static void SetActionMotor6(uint8_t status, uint8_t pwm);
#endif
#if defined(USE_MOTOR07)
static void SetActionMotor7(uint8_t status, uint8_t pwm);
#endif
#if defined(USE_MOTOR08)
static void SetActionMotor8(uint8_t status, uint8_t pwm);
#endif
#if defined(USE_MOTOR09)
static void SetActionMotor9(uint8_t status, uint8_t pwm);
#endif
#if defined(USE_MOTOR10)
static void SetActionMotor10(uint8_t status, uint8_t pwm);
#endif
#if defined(USE_MOTOR11)
static void SetActionMotor11(uint8_t status, uint8_t pwm);
#endif
#if defined(USE_MOTOR12)
static void SetActionMotor12(uint8_t status, uint8_t pwm);
#endif
#if defined(USE_MOTOR13)
static void SetActionMotor13(uint8_t status, uint8_t pwm);
#endif
#if defined(USE_MOTOR14)
static void SetActionMotor14(uint8_t status, uint8_t pwm);
#endif

#endif /* MOTOR_H_ */