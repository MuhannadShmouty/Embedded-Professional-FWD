/*
 * Application.c
 *
 * Created: 27/8/2022 7:06:08 PM
 * Author : Muhannad Shmouty
 */ 

#include "Application.h"
uint8_t counter = 0;

APP_ERROR_t appInit(void)
{	// Initialize Input Pin
	SetPinDirection(DIO_PORTB, PIN_00, INPUT_PULLUP);
	// Initialize Output Pins
	SetPortDirection(DIO_PORTA, PORT_OUTPUT);
	return APP_OK;
}

APP_ERROR_t appLoop(void) {
	if (ReadPinValue(DIO_PORTB, BUTTON) == LOW) {
		counter++;
		while (ReadPinValue(DIO_PORTB, BUTTON) == LOW);
	}
	
	SetPortValue(DIO_PORTA, counter);
	return APP_OK;
}