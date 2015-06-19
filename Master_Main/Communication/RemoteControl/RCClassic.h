/*
 * RCClassic.h
 *
 * Created: 2014/06/17 20:37:13
 *  Author: tatsuro
 */ 


#ifndef RCCLASSIC_H_
#define RCCLASSIC_H_

#define RC_DATA_LENGTH	(4)
#define RC_DEFAULT_DATA	{0x00, 0x00, 0x77, 0x77}
#define RC_SAFETY_COUNT	(800)

union controllerData {
	struct {
		struct {
			unsigned int X:1;
			unsigned int A:1;
			unsigned int B:1;
			unsigned int Y:1;
			unsigned int UP:1;
			unsigned int RIGHT:1;
			unsigned int DOWN:1;
			unsigned int LEFT:1;
			unsigned int SELECT:1;
			unsigned int HOME:1;
			unsigned int START:1;
			unsigned int ZL:1;
			unsigned int ZR:1;
			unsigned int L:1;
			unsigned int R:1;
			unsigned int :1;
		} __attribute__ ((packed)) Button;
		struct {
			unsigned int Y:4;
			unsigned int X:4;
		} __attribute__ ((packed)) AnalogL;
		struct {
			unsigned int Y:4;
			unsigned int X:4;
		} __attribute__ ((packed)) AnalogR;
	} __attribute__ ((packed)) detail;
	
	uint8_t buf[RC_DATA_LENGTH];
};


#endif /* RCCLASSIC_H_ */