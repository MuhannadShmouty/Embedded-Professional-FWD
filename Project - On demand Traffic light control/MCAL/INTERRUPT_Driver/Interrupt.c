/*
 * Interrupt.c
 *
 * Created: 9/9/2022 4:30:54 PM
 *  Author: Muhannad Shmouty
 */ 
#include "Interrupt.h"

void GIE_Enable(void) {
	/*	Enable Global Interrupt	 */
	SET_BIT(SREG_REG, GIE_BIT);
}

void Time1_InterruptEnable(void) {
	SET_BIT(TIMSK, OCIE1A);
}

void EXTI_Enable(EXTI_t interrupt_reqNum, STATE_t triggerState) {
	switch (interrupt_reqNum) {
		case INT_0:
		switch (triggerState) {
			case LOW_LEVEL:
			RESET_BIT(MCUCR, ISC00);
			RESET_BIT(MCUCR, ISC01);
			break;
			case PIN_CHANGE:
			SET_BIT(MCUCR, ISC00);
			RESET_BIT(MCUCR, ISC01);
			break;
			case FALLING:
			RESET_BIT(MCUCR, ISC00);
			SET_BIT(MCUCR, ISC01);
			break;
			case RISING:
			SET_BIT(MCUCR, ISC00);
			SET_BIT(MCUCR, ISC01);
			break;
		}
		// Enable Interrupt on external interrupt pin INT_0
		SET_BIT(GICR, INT_0_BIT);
		break;
		case INT_1:
		switch (triggerState) {
			case LOW_LEVEL:
			RESET_BIT(MCUCR, ISC10);
			RESET_BIT(MCUCR, ISC11);
			break;
			case PIN_CHANGE:
			SET_BIT(MCUCR, ISC10);
			RESET_BIT(MCUCR, ISC11);
			break;
			case FALLING:
			RESET_BIT(MCUCR, ISC10);
			SET_BIT(MCUCR, ISC11);
			break;
			case RISING:
			SET_BIT(MCUCR, ISC10);
			SET_BIT(MCUCR, ISC11);
			break;
		}
		// Enable Interrupt on external interrupt pin INT_1
		SET_BIT(GICR, INT_1_BIT);
		break;
		case INT_2:
		switch(triggerState) {
			case RISING:
			SET_BIT(MCUCSR, ISC2);
			break;
			case FALLING:
			RESET_BIT(MCUCSR, ISC2);
			break;
		}
		// Enable Interrupt on external interrupt pin INT_1
		SET_BIT(GICR, INT_2_BIT);
		break;
	}
}


void EXTI_Disable(EXTI_t interrupt_reqNum) {
	switch (interrupt_reqNum) {
		case INT_0:
		RESET_BIT(GICR, INT_0_BIT);
		break;
		case INT_1:
		RESET_BIT(GICR, INT_1_BIT);
		break;
		case INT_2:
		RESET_BIT(GICR, INT_2_BIT);
	}
}
