/*
 * LED_Driver.h
 *
 * Created: 31/8/2022 7:59:50 PM
 *  Author: Muhannad Shmouty
 */ 


#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_


#include "../../MCAL/DIO_Driver/DIO_Driver.h"


void LED_init(uint8_t LED_PORT, uint8_t LED_PIN);
void LED_ON(uint8_t LED_PORT, uint8_t LED_PIN);
void LED_OFF(uint8_t LED_PORT, uint8_t LED_PIN);
void LED_TOGGLE(uint8_t LED_PORT, uint8_t LED_PIN);


#endif /* LED_DRIVER_H_ */