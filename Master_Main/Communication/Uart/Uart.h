/*
 * Uart.h
 *
 * Created: 2014/06/17 20:28:14
 *  Author: tatsuro
 */ 


#ifndef UART_H_
#define UART_H_


#if (defined(UDR0) || defined(UDR))
static void UartInitialize0(uint8_t option, uint16_t baudrate);
static void UartSend0(uint8_t sendData);
static void UartReceive0(uint8_t* receiveData);
#endif
#if defined(UDR1)
static void UartInitialize1(uint8_t option, uint16_t baudrate);
static void UartSend1(uint8_t sendData);
static void UartReceive1(uint8_t* receiveData);
#endif
#if defined(UDR2)
static void UartInitialize2(uint8_t option, uint16_t baudrate);
static void UartSend2(uint8_t sendData);
static void UartReceive2(uint8_t* receiveData);
#endif
#if defined(UDR3)
static void UartInitialize3(uint8_t option, uint16_t baudrate);
static void UartSend3(uint8_t sendData);
static void UartReceive3(uint8_t* receiveData);
#endif


#endif /* UART_H_ */