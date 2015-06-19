/*
 * Input.h
 *
 * Created: 2014/07/26 13:36:50
 *  Author: tatsuro
 */ 


#ifndef INPUT_H_
#define INPUT_H_

// SW
void SwitchInitialize(void);
uint8_t GetDipSwitchStatus(void);
bool GetSwitchStatus(uint8_t no);

// EX
void ExInitialize(void);


#endif /* INPUT_H_ */