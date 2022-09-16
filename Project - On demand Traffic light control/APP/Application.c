/*
 * Application.c
 *
 * Created: 27/8/2022 7:06:08 PM
 * Author : Muhannad Shmouty
 */ 




#include "Application.h"


volatile uint8_t time_s = 0, EXTI_0_time_s = 0;
volatile APP_MODE state = APP_NORMAL_START;
volatile CARS_LEDs_STATE carsLED = GREEN;
volatile uint8_t fullCycleTime = 20;
bool isFinished = false;

void appInit(void)
{
	LED_init(DIO_PORTA, CARS_RED_LED);
	LED_init(DIO_PORTA, CARS_YELLOW_LED);
	LED_init(DIO_PORTA, CARS_GREEN_LED);
	
	LED_init(DIO_PORTB, PEDESTRIANS_RED_LED);
	LED_init(DIO_PORTB, PEDESTRIANS_YELLOW_LED);
	LED_init(DIO_PORTB, PEDESTRIANS_GREEN_LED);
	// Enable external interrupt on pin 2 in PORTD (INT_0)
	EXTI_Enable(INT_0, PIN_CHANGE);
	// Enable timer1 on CTC mode with Prescaler of 64
	timer1Enable(CTC, Prescaler);
	
	// Fire Timer/Counter1 Compare Match A Interrupt every 1 second
	fireEvery_ms(1000);
	
	// Enable Global Interrupt
	GIE_Enable();
	// Enable Interrupt for Timer 1
	Time1_InterruptEnable();
}

void appLoop(void) {
	// Generate state machine scheme
	switch (state){
		
		case APP_NORMAL_START:
			/* 
			 *	Initialize the elements to start the normal mode
			 */
			
			// Enable external Interrupt
			EXTI_Enable(INT_0, PIN_CHANGE);
			
			// Initialize time
			time_s = 0;
			
			// Turn off all LEDs preparing for App start
			Turn_Off_All_LEDS();
			
			// Proceed to the next state
			state = APP_NORMAL_MODE;
			break;
		
		case APP_NORMAL_MODE:		
			/*
			 *	Perform the normal mode of cars traffic lights
			 */
			
			// Set the full cycle time
			fullCycleTime = 20;
		
			
			if (time_s < 5) {
				// Do this while in the range of the First 5 seconds
				// Green LED is ON for cars to pass
				LED_ON(DIO_PORTA, CARS_GREEN_LED);
				LED_OFF(DIO_PORTA, CARS_YELLOW_LED);
				LED_OFF(DIO_PORTA, CARS_RED_LED);
				// Set the cars traffic lights state to Green
				carsLED = GREEN;
			} else if (time_s < 10) {
				// Do this while in the range of the Second 5 seconds
				// Yellow LED is blinking to notify the cars
				LED_OFF(DIO_PORTA, CARS_GREEN_LED);
				LED_OFF(DIO_PORTA, CARS_RED_LED);
				
				// Blink Yellow LED
				if (time_s % 2 == 1) {
					// Yellow LED is ON during odd seconds
					LED_ON(DIO_PORTA, CARS_YELLOW_LED);
				} else {
					// Yellow LED is OFF during even seconds
					LED_OFF(DIO_PORTA, CARS_YELLOW_LED);
				}
				// Set the cars traffic lights state to Yellow
				carsLED = YELLOW;
				
			} else if (time_s < 15) {
				// Do this while in the range of the Third 5 seconds
				
				// Turn ON red LED to stop cars
				LED_OFF(DIO_PORTA, CARS_YELLOW_LED);
				LED_OFF(DIO_PORTA, CARS_GREEN_LED);
				LED_ON(DIO_PORTA, CARS_RED_LED);
				// Set the cars traffic lights state to Red
				carsLED = RED;
				
			} else if (time_s < 20) {
				// Do this while in the range of the Fourth 5 seconds
				// Yellow LED is blinking to notify the cars
				LED_OFF(DIO_PORTA, CARS_GREEN_LED);
				LED_OFF(DIO_PORTA, CARS_RED_LED);
				
				// Blink Yellow LED
				if (time_s % 2 == 1) {
					// Yellow LED is ON during odd seconds
					LED_ON(DIO_PORTA, CARS_YELLOW_LED);
				} else {
					// Yellow LED is OFF during even seconds
					LED_OFF(DIO_PORTA, CARS_YELLOW_LED);
				}
				// Set the cars traffic lights state to Yellow
				carsLED = YELLOW;
			}
			break;
		
		case APP_PEDESTRIAN_START:
			/*
			 *	Initialize the elements to pedestrian mode
			 */
		
			// disable external interrupt so that no more presses will make effect
			EXTI_Disable(INT_0);
			
			// Initialize time
			time_s = 0;
			
			// Turn off All LEDs for pedestrians mode start
			Turn_Off_All_LEDS();
			
			// Proceed to the next state
			state = APP_PEDESTRIAN_MODE;
			break;
			
		case APP_PEDESTRIAN_MODE:
			/*
			 *	Perform the pedestrian mode for traffic lights
			 */
			
			// Set the full cycle time
			fullCycleTime = 25;
		
			switch (carsLED) {
				case RED:
					// Turn off Yellow LED Lights
					LED_OFF(DIO_PORTA, CARS_YELLOW_LED);
					LED_OFF(DIO_PORTB, PEDESTRIANS_YELLOW_LED);
					
					// Cars are stopped, pedestrians can cross
					if (time_s < 5) {
						// Do this while in the range of the First 5 seconds
						
						// Turn ON green LED for pedestrians, they can cross
						LED_ON(DIO_PORTB, PEDESTRIANS_GREEN_LED);
						
						// Turn ON red LED for cars, to stay stopped
						LED_ON(DIO_PORTA, CARS_RED_LED);
						
					} else if (time_s < 10) {
						// Do this while in the range of the Second 5 seconds
						
						LED_OFF(DIO_PORTB, PEDESTRIANS_GREEN_LED);
						LED_OFF(DIO_PORTA, CARS_RED_LED);
						
						// Blink both yellow LEDs
						if (time_s % 2 == 1) {
							// Yellow LEDs are ON during odd seconds
							LED_ON(DIO_PORTA, CARS_YELLOW_LED);
							LED_ON(DIO_PORTB, PEDESTRIANS_YELLOW_LED);
						} else {
							// Yellow LEDs are OFF during even seconds
							LED_OFF(DIO_PORTA, CARS_YELLOW_LED);
							LED_OFF(DIO_PORTB, PEDESTRIANS_YELLOW_LED);
						}
					}
					
					// Process is finished if time passed 10 seconds
					if (time_s >= 10)
						isFinished = true;
					break;
				case YELLOW:
					// Cars are alerted
					
					// Turn Off pedestrian red led
					LED_OFF(DIO_PORTB, PEDESTRIANS_RED_LED);
					// Turn Off Cars green led
					LED_OFF(DIO_PORTA, CARS_GREEN_LED);
					
					if (time_s < 5) {
						// Do this while in the range of the First 5 seconds
						
						// Blink both yellow LEDs
						if (time_s % 2 == 1) {
							// Yellow LEDs are ON during odd seconds
							LED_ON(DIO_PORTA, CARS_YELLOW_LED);
							LED_ON(DIO_PORTB, PEDESTRIANS_YELLOW_LED);
						} else {
							// Yellow LEDs are OFF during even seconds
							LED_OFF(DIO_PORTA, CARS_YELLOW_LED);
							LED_OFF(DIO_PORTB, PEDESTRIANS_YELLOW_LED);
						}
						
					} else {
						// Time has passed 5 seconds
						// reset time
						time_s = 0;
						
						// Switch to Red cars LED mode
						carsLED = RED;						
					}
					break;
					
				case GREEN:
					// Cars are moving
					LED_ON(DIO_PORTA, CARS_GREEN_LED);
					if (time_s < 2) {
						// Do this while in the range of 2 seconds
						
						// Pedestrians Red LED is ON to prevent crossing while cars are moving
						LED_ON(DIO_PORTB, PEDESTRIANS_RED_LED);
					} else {
						// Time has passed 2 seconds
						// reset time
						time_s = 0;
						
						// Switch to Yellow cars LED mode
						carsLED = YELLOW;
					}
				break;
			}
		
			if (isFinished) {
				// Pedestrian Mode sequence is finished
				isFinished = false;
				
				// Proceed to start the normal mode
				state = APP_NORMAL_START;
			}
			break;
	}
}

ISR(TMR1_INT_CMPA) {
	time_s = ((time_s + 1) % fullCycleTime);
	EXTI_0_time_s++;
}

ISR(EXT_INT_0) {
	// Pin is high, Rising edge
	if (ReadPinValue(DIO_PORTD, BUTTON) == HIGH) {
		// reset counting time
		EXTI_0_time_s = 0;
	}
	
	// Pin is low, Falling edge
	if (ReadPinValue(DIO_PORTD, BUTTON) == LOW) {
		// Only allow to switch to Pedestrian mode on short presses
		if (EXTI_0_time_s < SHORT_PRESS_TIME){
			state = APP_PEDESTRIAN_START;
		}
	}
}

void Turn_Off_All_LEDS() {
	LED_OFF(DIO_PORTA, CARS_RED_LED);
	LED_OFF(DIO_PORTA, CARS_YELLOW_LED);
	LED_OFF(DIO_PORTA, CARS_GREEN_LED);
	LED_OFF(DIO_PORTB, PEDESTRIANS_RED_LED);
	LED_OFF(DIO_PORTB, PEDESTRIANS_YELLOW_LED);
	LED_OFF(DIO_PORTB, PEDESTRIANS_GREEN_LED);	
}