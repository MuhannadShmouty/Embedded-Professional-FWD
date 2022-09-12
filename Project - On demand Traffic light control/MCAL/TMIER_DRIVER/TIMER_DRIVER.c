/*
 * TIMER_DRIVER.c
 *
 * Created: 1/9/2022 3:33:16 PM
 *  Author: Muhannad Shmouty
 */ 

#include "../DIO_Driver/DIO_Driver.h"
#include "TIMER_DRIVER.h"

uint16_t Globalprescaler0, Globalprescaler1;

void timer0Enable(TIMER_MODE ModeOfOperation, uint16_t prescaler) {
	
	
	/*
	**	Choosing Mode of Timer0 Operation by changing the WGM00 and WGM01 bits	
	**	in TCCR0 register per Datasheet page 78
	**	|--------------------------------------|
	**	|   WGM01 |	WGM00 |	Mode			   |
	**  |--------------------------------------|
	**	|    0	  |	  0	  |	Normal			   |
	**	|    0	  |	  1	  |	PWM, Phase Correct |
	**	|    1	  |	  0	  |	CTC				   |
	**	|    1	  |	  1	  |	Fast PWM		   |
	**  |--------------------------------------|
	*/
	switch (ModeOfOperation)
	{
		case Normal:
			RESET_BIT(TCCR0, WGM00);
			RESET_BIT(TCCR0, WGM01);
			break;
		case PC_Fast_PWM:
			SET_BIT(TCCR0, WGM00);
			RESET_BIT(TCCR0, WGM01);
			break;
		case Fast_PWM:
			SET_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);
			break;
		case CTC:
			RESET_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);
			break;
	}
	
	/*
	**	Choosing Prescaler of Timer0 Operation by changing the
	**	CS00, CS01 and CS02 bits in TCCR0 register per Datasheet page 79
	**	|-----------------------------------------------------------------------------------|
	**	|   CS02 |	CS01  | CS00  |						 Prescaler						    |
	**  |-----------------------------------------------------------------------------------|
	**	|     0  |   0    |   0   |			No clock source (Timer/Counter stopped).		|
	**	|     0  |   0    |   1   |					  No prescaling							|
	**	|     0  |   1    |   0   |					       CLK/8							|
	**	|     0  |   1    |   1   |						   CLK/64						    |
	**  |     1  |   0    |   0   |						   CLK/265							|
	**	|     1  |   0    |   1   |						  CLK/1024                          |
	**	|     1  |   1    |   0   |  External clock source on T0 pin. Clock on falling edge |
	**	|     1  |   1    |   1   |  External clock source on T0 pin. Clock on rising edge. |
	**  |-----------------------------------------------------------------------------------|
	*/
	Globalprescaler0 = prescaler;
	switch (prescaler) {
		case 1:
			// No prescaler
			SET_BIT(TCCR0, CS00);
			RESET_BIT(TCCR0, CS01);
			RESET_BIT(TCCR0, CS02);
			break;
		case 8:
			// Prescaler CLK/8
			RESET_BIT(TCCR0, CS00);
			SET_BIT(TCCR0, CS01);
			RESET_BIT(TCCR0, CS02);
			break;
		case 64:
			// Prescaler CLK/64
			SET_BIT(TCCR0, CS00);
			SET_BIT(TCCR0, CS01);
			RESET_BIT(TCCR0, CS02);
			break;
		case 1024:
			// Prescaler CLK/1024
			SET_BIT(TCCR0, CS00);
			RESET_BIT(TCCR0, CS01);
			SET_BIT(TCCR0, CS02);
			break;
	}

}

void timer0_delay_ms(uint16_t time_ms) {
	TCNT0 = 0x00;
	uint16_t nOvf =  ((time_ms * (freq/1000) + Globalprescaler0*256) - 1) / Globalprescaler0 / 256;
	int overFlowCounter = 0;
	
	while (overFlowCounter < nOvf) {
		while ((TIFR & (1<<TOV0)) == 0);
		// Clear the overflow flag
		TIFR |= (1<<0);
		overFlowCounter++;
	}
}   

void timer1Enable(TIMER_MODE ModeOfOperation, uint16_t prescaler) {
	TCNT1L = 0;
	TCNT1H = 0;
	RESET_BIT(TIFR, OCF1A);
	switch (ModeOfOperation)
	{
		case Normal:
		RESET_BIT(TCCR1A, WGM10);
		RESET_BIT(TCCR1A, WGM11);
		RESET_BIT(TCCR1B, WGM12);
		RESET_BIT(TCCR1B, WGM13);
		break;
		case CTC:
		RESET_BIT(TCCR1A, WGM10);
		RESET_BIT(TCCR1A, WGM11);
		SET_BIT(TCCR1B, WGM12);
		RESET_BIT(TCCR1B, WGM13);
		break;
		case PC_Fast_PWM:
		break;
		case Fast_PWM:
		break;
		
	}
	
	Globalprescaler1 = prescaler;
	switch (prescaler) {
		case 1:
		// No prescaler
		SET_BIT(TCCR1B, CS10);
		RESET_BIT(TCCR1B, CS11);
		RESET_BIT(TCCR1B, CS12);
		break;
		case 8:
		// Prescaler CLK/8
		RESET_BIT(TCCR1B, CS10);
		SET_BIT(TCCR1B, CS11);
		RESET_BIT(TCCR1B, CS12);
		break;
		case 64:
		// Prescaler CLK/64
		SET_BIT(TCCR1B, CS10);
		SET_BIT(TCCR1B, CS11);
		RESET_BIT(TCCR1B, CS12);
		break;
		case 256:
		// Prescaler CLK/256
		RESET_BIT(TCCR1B, CS10);
		RESET_BIT(TCCR1B, CS11);
		SET_BIT(TCCR1B, CS12);
		break;
		case 1024:
		// Prescaler CLK/1024
		SET_BIT(TCCR1B, CS10);
		RESET_BIT(TCCR1B, CS11);
		SET_BIT(TCCR1B, CS12);
		break;
	}
}

void fireEvery_ms(uint16_t time_ms) {
	*((uint16_t*)&TCNT1L) = 0;
	*((uint16_t*)&OCR1AL) = time_ms * (freq/1000) / Globalprescaler1;	
}