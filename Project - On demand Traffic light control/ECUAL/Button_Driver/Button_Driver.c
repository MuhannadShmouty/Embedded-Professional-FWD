/*
 * Button_Driver.c
 *
 * Created: 1/9/2022 3:02:22 PM
 *  Author: Muhannad Shmouty
 */ 


#include "Button_Driver.h"

void ButtonInit(uint8_t Port, uint8_t Pin, uint8_t InputState) {
	// Set Pin as Input
	// Select whether to activate internal input pull up resistor or not
	
	switch (InputState){
		case NormalInupt:
		SetPinDirection(Port, Pin, INPUT);
		break;
		case INPUT_PULLUP:
		SetPinDirection(Port, Pin, INPUT_PULLUP);
		break;
	}
}

uint8_t ButtonRead(uint8_t Port, uint8_t Pin) {
	return ReadPinValue(Port, Pin);
}