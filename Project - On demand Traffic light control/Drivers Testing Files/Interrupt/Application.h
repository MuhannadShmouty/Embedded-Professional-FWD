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
#include "../ECUAL/LED_Driver/LED_Driver.h"
#include "../ECUAL/Button_Driver/Button_Driver.h"
#include "../MCAL/TMIER_DRIVER/TIMER_DRIVER.h"
#include "../MCAL/INTERRUPT_Driver/Interrupt.h"

#define BUTTON						PIN_02

typedef enum {APP_OK, APP_ERROR}APP_ERROR_t;
	
APP_ERROR_t appInit(void);
APP_ERROR_t appLoop(void);

#endif /* APPLICATION_H_ */