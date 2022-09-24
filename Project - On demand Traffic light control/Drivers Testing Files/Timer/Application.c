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
	
	// Enable timer1 on CTC mode with Prescaler of 64
	timer1Enable(CTC, PRESCALER);
	
	// Fire Timer/Counter1 Compare Match A Interrupt every 1 second
	fireEvery_ms(1000);
	
	// Enable Global Interrupt
	GIE_Enable();
	// Enable Interrupt for Timer 1
	Time1_InterruptEnable();
	
	return APP_OK;
}

APP_ERROR_t appLoop(void) {	
	SetPortValue(DIO_PORTA, counter);
	return APP_OK;
}

ISR(TMR1_INT_CMPA) {
	counter++;
}