/*
 * DIO_Driver.h
 *
 * Created: 27/8/2022 7:21:10 PM
 *  Author: Muhannad Shmouty
 */ 


#ifndef DIO_DRIVER_H_
#define DIO_DRIVER_H_

#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

#define PORT_OUTPUT 0xFF
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2

#define LOW 0
#define HIGH 1

#define PIN_00 0
#define PIN_01 1
#define PIN_02 2
#define PIN_03 3
#define PIN_04 4
#define PIN_05 5
#define PIN_06 6
#define PIN_07 7
#include <stdint.h>
#include "../../Utilities/bitManipulation.h"
#include "../../Utilities/registers.h"

void SetPortDirection(uint8_t Port, uint8_t Direction);
void SetPortValue(uint8_t Port, uint8_t Value);
void SetPinDirection(uint8_t Port, uint8_t Pin, uint8_t Direction);
void TogglePin(uint8_t Port, uint8_t Pin);
void SetPinValue(uint8_t Port, uint8_t Pin, uint8_t Value);
uint8_t ReadPinValue(uint8_t Port ,uint8_t Pin);

#endif /* DIO_DRIVER_H_ */