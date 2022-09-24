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

#define Prescaler					64
#define CARS_RED_LED				PIN_00
#define CARS_YELLOW_LED				PIN_01
#define CARS_GREEN_LED				PIN_02
#define PEDESTRIANS_RED_LED			PIN_00
#define PEDESTRIANS_YELLOW_LED		PIN_01
#define PEDESTRIANS_GREEN_LED		PIN_02
#define BUTTON						PIN_02
#define SHORT_PRESS_TIME			2

typedef enum {APP_NORMAL_START, APP_NORMAL_MODE, APP_PEDESTRIAN_START, APP_PEDESTRIAN_MODE} APP_MODE;
typedef enum {GREEN, YELLOW, RED} CARS_LEDs_STATE;
typedef enum {APP_OK, APP_ERROR}APP_ERROR_t;
	
APP_ERROR_t appInit(void);
APP_ERROR_t appLoop(void);
void Turn_Off_All_LEDS(void);

#endif /* APPLICATION_H_ */