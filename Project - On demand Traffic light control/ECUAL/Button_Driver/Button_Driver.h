/*
 * Button_Driver.h
 *
 * Created: 1/9/2022 3:02:40 PM
 *  Author: Muhannad Shmouty
 */ 


#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_

#include "../../MCAL/DIO_Driver/DIO_Driver.h"

#define NormalInupt 3

void ButtonInit(uint8_t Port, uint8_t Pin, uint8_t InputState);
uint8_t ButtonRead(uint8_t Port, uint8_t Pin);

#endif /* BUTTON_DRIVER_H_ */