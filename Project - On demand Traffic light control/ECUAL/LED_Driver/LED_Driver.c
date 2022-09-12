/*
 * LED_Driver.c
 *
 * Created: 31/8/2022 8:00:00 PM
 *  Author: Muhannad Shmouty
 */ 

#include "LED_Driver.h"

void LED_init(uint8_t LED_PORT, uint8_t LED_PIN) {
	// Set LED pin as Output
	SetPinDirection(LED_PORT, LED_PIN, OUTPUT);
	SetPinValue(LED_PORT, LED_PIN, LOW);
}

void LED_ON(uint8_t LED_PORT, uint8_t LED_PIN) {
	// Set LED pin as High
	SetPinValue(LED_PORT, LED_PIN, HIGH);
}

void LED_OFF(uint8_t LED_PORT, uint8_t LED_PIN) {
	// Set LED pin as Low
	SetPinValue(LED_PORT, LED_PIN, LOW);
}

void LED_TOGGLE(uint8_t LED_PORT, uint8_t LED_PIN) {
	// Toggle the LED pin HIGH<-->LOW
	TogglePin(LED_PORT, LED_PIN);
}
