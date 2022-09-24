/*
 * Application.h
 *
 * Created: 1/9/2022 2:22:25 PM
 *  Author: Muhannad Shmouty
 */ 


#ifndef APPLICATION_H_
#define APPLICATION_H_

#define F_CPU 1000000UL
#include <stdbool.h>
#include "../MCAL/DIO_Driver/DIO_Driver.h"

#define BUTTON PIN_00
typedef enum {APP_OK, APP_ERROR}APP_ERROR_t;
	
APP_ERROR_t appInit(void);
APP_ERROR_t appLoop(void);


#endif /* APPLICATION_H_ */