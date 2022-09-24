/*
 * Application.c
 *
 * Created: 27/8/2022 7:06:08 PM
 * Author : Muhannad Shmouty
 */ 

#include "Application.h"

volatile uint8_t counter = 0;

APP_ERROR_t appInit(void)
{	
	
	// Initialize Output Pins
	LED_init(DIO_PORTA, LED_1);
	
	// Initialize Input Pins
	ButtonInit(DIO_PORTB, BUTTON, NormalInupt);	
	
	return APP_OK;
}

APP_ERROR_t appLoop(void) {
	if (ButtonRead(DIO_PORTB, LED_1) == HIGH) {
		LED_TOGGLE(DIO_PORTA, LED_1);
		while(ButtonRead(DIO_PORTB, LED_1) == HIGH);
	}
	return APP_OK;
}
