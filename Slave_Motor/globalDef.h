/*
 * globalDef.h
 *
 * Created: 2014/07/26 13:31:55
 *  Author: tatsuro
 */ 


#ifndef GLOBALDEF_H_
#define GLOBALDEF_H_

#define sbi(addr, bit) addr |= (1 << bit)
#define cbi(addr, bit) addr &= ~(1 << bit)

typedef struct{
	uint8_t *ddr;
	uint8_t *port;
	uint8_t bit;
}io;

typedef struct {
	uint8_t *ddr;
	uint8_t bit;
	uint8_t *ocr;
}timer;

typedef struct {
	io d1;
	io d2;
	timer pwm;
}Motor;

#endif /* GLOBALDEF_H_ */