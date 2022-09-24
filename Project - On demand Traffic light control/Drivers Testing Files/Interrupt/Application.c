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
	SetPortDirection(DIO_PORTA, PORT_OUTPUT);
	
	
	// Enable Global Interrupt
	GIE_Enable();
	
	// Enable external interrupt on pin 2 in PORTD (INT_0)
	EXTI_Enable(INT_0, RISING);
	EXTI_Enable(INT_2, FALLING);
	
	
	return APP_OK;
}

APP_ERROR_t appLoop(void) {	
	SetPortValue(DIO_PORTA, counter);
	return APP_OK;
}

ISR(EXT_INT_0) {
	counter--;
}

ISR(EXT_INT_2) {
	counter++;
}