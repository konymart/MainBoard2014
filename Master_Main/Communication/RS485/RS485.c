/*
 * RS485.c
 *
 * Created: 2014/06/17 20:24:45
 *  Author: tatsuro
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef WDT_RESET
	#include <avr/wdt.h>
#endif
#include <stdbool.h>
#include "../../globalDef.h"
#include "../../Output/Led/LedDef.h"

#if defined(USE_RS485)

#include "../Uart/UartDef.h"
#include "../RingBuffer/RingBufferDef.h"
#include "./RS485.h"
#include "./RS485Def.h"
#include "./RS485_Data.h"

#if defined(USE_MOTOR_HUB)
#include "../../Output/Motor/MotorDef.h"

static volatile st_Motor MotorData[((USING_MOTOR_HUB - 1) >> 2) + 1];
struct MotorHub MotorHubArray[USING_MOTOR_HUB];
#endif

#if defined(USE_LED_HUB)
static volatile st_Led LedData[((USING_LED_HUB - 1) >> 4) + 1];
volatile bool LedHubArray[USING_LED_HUB];
#endif

#if defined(USE_AIR_HUB)
static volatile st_Air AirData[((USING_AIR_HUB - 1) >> 3) + 1];
volatile bool AirHubArray[USING_AIR_HUB];
#endif

static volatile uint8_t val;
static volatile uint8_t phase;
static volatile uint8_t count;
static volatile bool addrCheck = false;
static volatile char packet[10];
static volatile char check[] = "DR=";
static volatile char StartCode[] = "%$";
static volatile bool StartCodeCheck = false;
static volatile char EndCode[] = "\r\n";
static volatile bool EndCodeCheck = false;
volatile bool LineStatus = NO_DATA_IN_LINE;

#if defined(USE_SENSOR_HUB)
#if defined(USE_SAFETY)
volatile uint16_t SensorTimerCount;
#endif
static volatile bool SensorDataReceive = true;
volatile bool SensorDataReceived = true;
volatile bool SensorBoardLost = false;
union SensorData sensor;
union SensorData keep;
#endif

static Uart_Ring_Type RingBuffer;


void RS485Initialize(uint8_t baud){
	val = 0;
	phase = 0;
	count = 0;
	
	UartInitialize[RS485_UART_NO](UART_RE | UART_TE | UART_RXCIE | UART_TXCIE | UART_UDRIE , baud);
	sbi(*RS485_SELECT_PORT.DDR, RS485_SELECT_BIT);
	
	RS485_Select(RS485_RE);
	
	RingBufferInitialize(&RingBuffer);
	
	#if defined(USE_MOTOR_HUB)
		MotorHubInitialize();
	#endif
	
	#if defined(USE_LED_HUB)
		LedHubInitialize();
	#endif
	
	#if defined(USE_AIR_HUB)
		AirHubInitialize();
	#endif
}

static void RS485_putchar(uint8_t data){
	cli();
	RS485_Select(RS485_SE);
	UartSend[RS485_UART_NO](data);
	RS485_Select(RS485_RE);
	sei();
}

static void RS485_getchar(uint8_t *data){
	cli();
	RS485_Select(RS485_RE);
	UartReceive[RS485_UART_NO](data);
	sei();
}

void RS485_Select(uint8_t option){
	if(option){
		sbi(*RS485_SELECT_PORT.PORT, RS485_SELECT_BIT);
	}		
	else{
		cbi(*RS485_SELECT_PORT.PORT, RS485_SELECT_BIT);
	}			
}

#if defined(USE_MOTOR_HUB)

static void MotorHubInitialize(void){
	volatile uint8_t i, j;
	
	for(i = 0; i < USING_MOTOR_HUB; i++){
		MotorHubArray[i].status = 0x00;
		MotorHubArray[i].pwm = 0x00;
	}
	
	for(i = 0; i < ((USING_MOTOR_HUB - 1) >> 2) + 1; i++){
		for(j = 0; j < 4; j++){
			MotorData[i].data[j] = 0x00;
		}		
		MotorData[i].addr = 0x20;
		MotorData[i].addr |= i;
	}
}

void MotorHubUpdate(void){
	volatile uint8_t i; 
	
	for(i = 0; i < USING_MOTOR_HUB; i++){
		MotorData[i>>2].data[i%4]  = MotorHubArray[i].status;
		MotorData[i>>2].data[i%4] |= (PwmSetter(MotorHubArray[i].pwm) & ~(0x03));
	}
	
	for(i = 0; i < ((USING_MOTOR_HUB - 1) >> 2) + 1; i++){
		RingSetChar('%', &RingBuffer);
		RingSetChar('$', &RingBuffer);
		RingSetChar('@', &RingBuffer);
		RingSetChar(MotorData[i].addr, &RingBuffer);
		RingSetChar('D', &RingBuffer);
		RingSetChar('R', &RingBuffer);
		RingSetChar('=', &RingBuffer);
		RingSetChar(MotorData[i].data[0], &RingBuffer);
		RingSetChar(MotorData[i].data[1], &RingBuffer);
		RingSetChar(MotorData[i].data[2], &RingBuffer);
		RingSetChar(MotorData[i].data[3], &RingBuffer);
		RingSetChar('\r', &RingBuffer);
		RingSetChar('\n', &RingBuffer);
	}
}

#endif


#if defined(USING_LED_HUB)

static void LedHubInitialize(void){
	volatile uint8_t i, j;
	
	for(i = 0; i < USING_LED_HUB; i++){
		LedHubArray[i] = 0x00;
	}
	
	for(i = 0; i < ((USING_LED_HUB - 1) >> 4) + 1; i++){
		for(j = 0; j < 4; j++){
			LedData[i].data[j] = 0x00;
		}
		LedData[i].addr =  0x40;
		LedData[i].addr |= i;
	}
}

void LedHubUpdate(void){
	volatile uint8_t i, j;
	
	for(i = 0; i < ((USING_LED_HUB - 1) >> 4) + 1; i++){
		for(j = 0; j < 4; j++){
			LedData[i].data[j] = 0x00;
		}		
	}
	
	for(i = 0; i < USING_LED_HUB; i++){
		LedData[i>>4].data[i>>2] |= LedHubArray[i] << (i%4);
	}
	
	for(i = 0; i < ((USING_LED_HUB - 1) >> 4) + 1; i++){
		RingSetChar('%', &RingBuffer);
		RingSetChar('$', &RingBuffer);
		RingSetChar('@', &RingBuffer);
		RingSetChar(LedData[i].addr, &RingBuffer);
		RingSetChar('D', &RingBuffer);
		RingSetChar('R', &RingBuffer);
		RingSetChar('=', &RingBuffer);
		RingSetChar(LedData[i].data[0], &RingBuffer);
		RingSetChar(LedData[i].data[1], &RingBuffer);
		RingSetChar(LedData[i].data[2], &RingBuffer);
		RingSetChar(LedData[i].data[3], &RingBuffer);
		RingSetChar('\r', &RingBuffer);
		RingSetChar('\n', &RingBuffer);
	}
}

#endif


#if defined(USE_AIR_HUB)

static void AirHubInitialize(void){
	volatile uint8_t i;
	
	for(i = 0; i < USING_AIR_HUB; i++){
		AirHubArray[i] = 0x00;
	}
	
	for(i = 0; i < ((USING_AIR_HUB - 1) >> 3) + 1; i++){
		AirData[i].data = 0x00;
		
		AirData[i].addr =  0x80;
		AirData[i].addr |= i;
	}
}

void AirHubUpdate(void){
	volatile uint8_t i;
	
	for(i = 0; i < ((USING_AIR_HUB - 1) >> 3) + 1; i++){
		AirData[i].data = 0x00;
	}
	
	for(i = 0; i < USING_AIR_HUB; i++){
		AirData[i>>3].data |= (uint8_t)(AirHubArray[i] << (i%8));
	}
	
	for(i = 0; i < ((USING_AIR_HUB - 1) >> 3) + 1; i++){
		RingSetChar('%', &RingBuffer);
 		RingSetChar('$', &RingBuffer);
		RingSetChar('@', &RingBuffer);
		RingSetChar(AirData[i].addr, &RingBuffer);
		RingSetChar('D', &RingBuffer);
		RingSetChar('R', &RingBuffer);
		RingSetChar('=', &RingBuffer);
		RingSetChar(AirData[i].data, &RingBuffer);
		RingSetChar('\r', &RingBuffer);
		RingSetChar('\n', &RingBuffer);
	}
}

#endif

#if defined(USE_SENSOR_HUB)

void DummyDataSet(void){
	uint8_t i;
	for(i=0;i<19; i++){
		RingSetChar(' ', &RingBuffer);
	}
}

union SensorData *GetSensorData(void){
	uint8_t i;
	cli();
	for(i = 0; i < SENSORDATA_DEFAULT_LENGTH; i++){
		keep.buf[i] = sensor.buf[i];
	}
	sei();
	return &keep;
}

void GetSensorDataCommand(void){
	uint16_t i;
	if(SensorDataReceived){
		cli();
#ifdef WDT_RESET
		wdt_reset();
#endif
#ifndef SIMULATION_MODE
		for(i = 0; i < 200; i++);
#endif
		RS485_putchar('%');
		RS485_putchar('$');
		RS485_putchar('@');
		RS485_putchar(0xA0);
		RS485_putchar('D');
		RS485_putchar('S');
		RS485_putchar('\r');
		RS485_putchar('\n');
#ifdef WDT_RESET
		wdt_reset();
#endif
		SensorDataReceived = false;
#ifdef USE_SAFETY
		SensorTimerCount = 0;
#endif
#ifndef SIMULATION_MODE
		for(i = 0; i < 500; i++);
#endif
		sei();
	}	
}

void ClearHubEncoder0(void){
	ce(0);
}

void ClearHubEncoder1(void){
	ce(1);
}

void ClearHubEncoder2(void){
	ce(2);
}

void ClearHubEncoder3(void){
	ce(3);
}

static void ce(uint8_t no){
	uint16_t i;
	while(!SensorDataReceived);
#ifndef SIMULATION_MODE
	for(i = 0; i < 200; i++);
#endif
	cli();
	DummyDataSet();
#ifdef WDT_RESET
	wdt_reset();
#endif
	RS485_putchar('%');
	RS485_putchar('$');
	RS485_putchar('@');
	RS485_putchar(0xA0);
	RS485_putchar('C');
	RS485_putchar('E');
	RS485_putchar('=');
	RS485_putchar(no);
	RS485_putchar('\r');
	RS485_putchar('\n');
#ifdef WDT_RESET
	wdt_reset();
#endif
	sei();
}	
#endif


// Initerrupt
/*----------------------------------------------------------------------------*/
ISR(USART1_RX_vect){
	#if defined(USE_SENSOR_HUB)
		uint8_t i;
	#endif
	val = UDR1;
	
	if(phase == 1){
		if(addrCheck){
			if(val == 0x01){
				phase = 2;
				count = 0;
			}
			else{
				phase = 0;
			}
			addrCheck = false;
		}
		else if(val == '@' && !addrCheck){
			addrCheck = true;
		}
	}		
	else if(phase == 2){
		packet[count] = val;
		if(count < 2){
			if(val != check[count]){
				phase = 0;
				#if defined(USE_SENSOR_HUB)
					SensorBoardLost = true;
				#endif
			}		
		}
		else if(count >= 12){
			phase = 0;
			#if defined(USE_SENSOR_HUB)
				for(i = 0; i < SENSORDATA_DEFAULT_LENGTH; i++){
					sensor.buf[i] = packet[i+3];
				}
				SensorDataReceive = true;
				SensorBoardLost = false;
				SensorTimerCount = 0;
				LedArray[SENSOR_LED_NO] = LED_ON;
				wdt_reset();
			#endif
		}
		count++;
	}
	
	if(StartCodeCheck){
		if(val == '$'){
			StartCodeCheck = false;
			phase = 1;
			count = 0;
			LineStatus = DATA_IN_LINE;
		}
	}
	else{
		if(val == '%'){
			StartCodeCheck = true;
		}
	}
	
	if(EndCodeCheck){
		if(val == '\n'){
			EndCodeCheck = false;
			LineStatus = NO_DATA_IN_LINE;
			#if defined(USE_SENSOR_HUB)
				if(SensorDataReceive){
					SensorDataReceived = true;
					SensorDataReceive = false;
				}
			#endif
		}
	}
	else {
		if(val == '\r'){
			EndCodeCheck = true;
		}
	}
}

ISR(USART1_UDRE_vect){
	unsigned char c;
	static uint16_t i;
	
	if(LineStatus == NO_DATA_IN_LINE){
		#if defined(USE_SENSOR_HUB)
		if(SensorDataReceived){
		#endif
			if(RingPutChar(&c, &RingBuffer)){
				RS485_Select(RS485_SE);
				UDR1 = c;
				#ifndef SIMULATION_MODE
					for(i=0; i<250; i++);
				#endif
			}
			else{
				goto Error;
			}
		#if defined(USE_SENSOR_HUB)
		}		
		else {
			goto Error;
		}
		#endif
	}	
	else{
Error:
		stop_uart1tx_interrupt();
	}
}

ISR(USART1_TX_vect){
	RS485_Select(RS485_RE);
	start_uart1tx_interrupt();
}

#endif
/*----------------------------------------------------------------------------*/
