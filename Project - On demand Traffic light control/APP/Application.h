/*
 * Application.h
 *
 * Created: 1/9/2022 2:22:25 PM
 *  Author: Muhannad Shmouty
 */ 


#ifndef APPLICATION_H_
#define APPLICATION_H_

#define F_CPU 1000000UL

#include <util/delay.h>

void appInit(void);
void appLoop(void);

typedef enum {APP_NORMAL_START, APP_NORMAL_MODE, APP_PEDESTRIAN_START, APP_PEDESTRIAN_MODE} APP_MODE;
typedef enum {GREEN, YELLOW, RED} CARS_LEDs_STATE;

void Turn_Off_All_LEDS(void);


#endif /* APPLICATION_H_ */