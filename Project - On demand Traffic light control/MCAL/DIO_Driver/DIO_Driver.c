/*
 * DIO_Driver.c
 *
 * Created: 27/8/2022 7:21:24 PM
 *  Author: Muhannad Shmouty
 */ 

#include "DIO_Driver.h"




void SetPortDirection(uint8_t Port, uint8_t Direction) {
	// Set the direction of the entire port directly
	switch (Port) {
		case DIO_PORTA:
		DDRA = Direction;
		break;
		case DIO_PORTB:
		DDRB = Direction;
		break;
		case DIO_PORTC:
		DDRC = Direction;
		break;
		case DIO_PORTD:
		DDRD = Direction;
		break;
	}
}

void SetPortValue(uint8_t Port, uint8_t Value) {
	// Set entire port value directly
	switch (Port) {
		case DIO_PORTA:
		PORTA = Value;
		break;
		case DIO_PORTB:
		PORTB = Value;
		break;
		case DIO_PORTC:
		PORTC = Value;
		break;
		case DIO_PORTD:
		PORTD = Value;
		break;
	}
}

void SetPinDirection(uint8_t Port, uint8_t Pin, uint8_t Direction) {
	// Set the direction of a Pin
	// INPUT --> 0
	// OUTPUT -- > 1
	
	switch (Port) {
		case DIO_PORTA:
		switch (Direction) {
			case INPUT:
			RESET_BIT(DDRA, Pin);
			break;
			case OUTPUT:
			SET_BIT(DDRA, Pin);
			break;
			case INPUT_PULLUP:
			// To activate internal Input Pull up resistor
			// Set pin as input, then set the pin HIGH
			RESET_BIT(DDRA, Pin);
			SET_BIT(PORTA, Pin);
			break;
		}
		break;

		case DIO_PORTB:
		switch (Direction) {
			case INPUT:
			RESET_BIT(DDRB, Pin);
			break;
			case OUTPUT:
			SET_BIT(DDRB, Pin);
			break;
			case INPUT_PULLUP:
			// To activate internal Input Pull up resistor
			// Set pin as input, then set the pin HIGH
			RESET_BIT(DDRB, Pin);
			SET_BIT(PORTB, Pin);
			break;
		}
		break;

		case DIO_PORTC:
		switch (Direction) {
			case INPUT:
			RESET_BIT(DDRC, Pin);
			break;
			case OUTPUT:
			SET_BIT(DDRC, Pin);
			break;
			case INPUT_PULLUP:
			// To activate internal Input Pull up resistor
			// Set pin as input, then set the pin HIGH
			RESET_BIT(DDRC, Pin);
			SET_BIT(PORTC, Pin);
			break;
		}
		break;

		case DIO_PORTD:
		switch (Direction) {
			case INPUT:
			RESET_BIT(DDRD, Pin);
			break;
			case OUTPUT:
			SET_BIT(DDRD, Pin);
			break;
			case INPUT_PULLUP:
			// To activate internal Input Pull up resistor
			// Set pin as input, then set the pin HIGH
			RESET_BIT(DDRD, Pin);
			SET_BIT(PORTD, Pin);
			break;
		}
		break;
	}	
}

void SetPinValue(uint8_t Port, uint8_t Pin, uint8_t Value) {
	// Set bit to 1 to set pin as HIGH
	// Reset bit to 0 to set pin as LOW
	switch (Port) {
		case DIO_PORTA:
		switch (Value) {
			case LOW:
			RESET_BIT(PORTA, Pin);
			break;
			case HIGH:
			SET_BIT(PORTA, Pin);
			break;
		}
		break;

		case DIO_PORTB:
		switch (Value) {
			case LOW:
			RESET_BIT(PORTB, Pin);
			break;
			case HIGH:
			SET_BIT(PORTB, Pin);
			break;
		}
		break;

		case DIO_PORTC:
		switch (Value) {
			case LOW:
			RESET_BIT(PORTC, Pin);
			break;
			case HIGH:
			SET_BIT(PORTC, Pin);
			break;
		}
		break;

		case DIO_PORTD:
		switch (Value) {
			case LOW:
			RESET_BIT(PORTD, Pin);
			break;
			case HIGH:
			SET_BIT(PORTD, Pin);
			break;
		}
		break;
	}
}

uint8_t ReadPinValue(uint8_t Port ,uint8_t Pin) {
	// Read the pin state from PINx registers
	uint8_t pinState = 0;
	switch (Port) {
		case DIO_PORTA:
		pinState = GET_BIT(PINA, Pin);
		break;
		case DIO_PORTB:
		pinState = GET_BIT(PINB, Pin);
		break;
		case DIO_PORTC:
		pinState = GET_BIT(PINC, Pin);
		break;
		case DIO_PORTD:
		pinState = GET_BIT(PIND, Pin);
		break;
	}
	return pinState;
}

void TogglePin(uint8_t Port, uint8_t Pin) {
	// Toggle the pin state HIGH<-->LOW
	switch (Port) {
		case DIO_PORTA:
		TOGGLE_BIT(PORTA, Pin);
		break;
		case DIO_PORTB:
		TOGGLE_BIT(PORTB, Pin);
		break;
		case DIO_PORTC:
		TOGGLE_BIT(PORTC, Pin);
		break;
		case DIO_PORTD:
		TOGGLE_BIT(PORTD, Pin);
		break;
	}
}