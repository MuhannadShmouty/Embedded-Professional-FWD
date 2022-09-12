/*
 * Interrupt.h
 *
 * Created: 9/9/2022 4:31:05 PM
 *  Author: Muhannad Shmouty
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "../DIO_Driver/DIO_Driver.h"

// External Interrupt Request 0
#define EXT_INT_0 __vector_1
// External Interrupt Request 1
#define EXT_INT_1 __vector_2
// External Interrupt Request 2
#define EXT_INT_2 __vector_3
// Timer/Counter1 Compare Match A
#define TMR1_INT_CMPA __vector_7

#define ISR(INT_VECT)void INT_VECT(void) __attribute__ ((signal, used));\
void INT_VECT(void)

typedef enum {INT_0, INT_1, INT_2}EXTI_t;
typedef enum {RISING, FALLING, PIN_CHANGE, LOW_LEVEL}STATE_t;
	
void GIE_Enable(void);
void EXTI_Enable(EXTI_t interrupt_reqNum, STATE_t triggerState);
void EXTI_Disable(EXTI_t interrupt_reqNum);
void Time1_InterruptEnable(void);

#endif /* INTERRUPT_H_ */