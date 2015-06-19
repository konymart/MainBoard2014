/*
 * globalDef.h
 *
 * Created: 2014/06/21 10:10:37
 *  Author: tatsuro
 */ 


#ifndef GLOBALDEF_H_
#define GLOBALDEF_H_

#define sbi(addr, bit) addr |= (1 << bit)
#define cbi(addr, bit) addr &= ~(1 << bit)

typedef struct {
	uint8_t *ddr;
	uint8_t *port;
	uint8_t bit;
}io;

#endif /* GLOBALDEF_H_ */