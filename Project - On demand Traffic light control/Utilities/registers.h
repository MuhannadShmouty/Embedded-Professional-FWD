/*
 * registers.h
 *
 * Created: 27/8/2022 7:15:21 PM
 *  Author: Muhannad Shmouty
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_

/************** DIO Registers **************/
/*  PORTA Register */
#define DDRA *((uint8_t volatile *) 0x3A)		// Data Direction for PORTA
#define PORTA *((uint8_t volatile *) 0x3B)		// PORTA DATA Register
#define PINA *((uint8_t volatile *) 0x39)		// PORTA INPUT register

/* PORTB REGISTER   */
#define DDRB *((uint8_t volatile *) 0x37)		// Data Direction for PORTB
#define PORTB *((uint8_t volatile *) 0x38)		// PORTB DATA Register
#define PINB *((uint8_t volatile *) 0x36)		// PORTB INPUT register

/* PORTC REGISTER   */
#define DDRC *((uint8_t volatile *) 0x34)		// Data Direction for PORTC
#define PORTC *((uint8_t volatile *) 0x35)		// PORTC DATA Register
#define PINC *((uint8_t volatile *) 0x33)		// PORTC INPUT register


/* PORTD REGISTER   */
#define DDRD *((uint8_t volatile *) 0x31)		// Data Direction for PORTD
#define PORTD *((uint8_t volatile *) 0x32)		// PORTD DATA Register
#define PIND *((uint8_t volatile *) 0x30)		// PORTD INPUT register



#define TIMSK *((uint8_t volatile *) 0x59)   // Timer Interrupt Mask Register
#define TIFR  *((uint8_t volatile *) 0x58)   // Timer Interrupt flag register
#define SFIOR *((uint8_t volatile *) 0x50)   // Special Functions IO register

// TIMSK Bits
#define TOIE0   0			// Timer/Counter0 Overflow Interrupt Enable
#define OCIE0   1			// Timer/Counter0 Output Compare Match Interrupt Enable
#define TOIE1   2			// Timer/Counter1, Overflow Interrupt Enable
#define OCIE1B  3			// Timer/Counter1, Output Compare B Match Interrupt Enable
#define OCIE1A  4			// Timer/Counter1, Output Compare A Match Interrupt Enable
#define TICIE1  5			// Timer/Counter1, Input Capture Interrupt Enable
#define TOIE2   6			// Timer/Counter2 Overflow Interrupt Enable
#define OCIE2   7			// Timer/Counter2 Output Compare Match Interrupt Enable

// TIFR Bits
#define TOV0    0			// Timer/Counter0 Overflow Flag
#define OCF0    1			// Output Compare Flag 0
#define TOV1    2			// Timer/Counter1, Overflow Flag
#define OCF1B   3			// Timer/Counter1, Output Compare B Match Flag
#define OCF1A   4			// Timer/Counter1, Output Compare A Match Flag
#define ICF1    5			// Timer/Counter1, Input Capture Flag
#define TOV2    6			// Timer/Counter2 Overflow Flag
#define OCF2    7			// Output Compare Flag 2

/*
 * Timer0 Registers  (8-bit Timer)
 */
#define TCCR0 *((uint8_t volatile *) 0x53)       // Timer/Counter0 Control Register
#define TCNT0 *((uint8_t volatile *) 0x52)       // Timer/Counter0 Register
#define OCR0  *((uint8_t volatile *) 0x5C)       // Output compare Register
// TCCR0 Bits
#define CS00  0		// CS02:0 Clock Select
#define CS01  1		// CS02:0 Clock Select
#define CS02  2		// CS02:0 Clock Select
#define WGM01 3		// WGM01:0 Waveform Generation Mode
#define COM00 4		// COM01:0 Compare Match Output Mode
#define COM01 5		// COM01:0 Compare Match Output Mode
#define WGM00 6		// WGM01:0 Waveform Generation Mode
#define FOC0  7		// Force Output Compare

/*
 * Timer1 Registers  (16-bit Timer)
 */

#define TCCR1A *((uint8_t volatile *) 0x4F)       // Timer/Counter1 Control Register A
#define TCCR1B *((uint8_t volatile *) 0x4E)       // Timer/Counter1 Control Register B
#define TCNT1H *((uint8_t volatile *) 0x4D)       // Timer/Counter1 (High)
#define TCNT1L *((uint8_t volatile *) 0x4C)       // Timer/Counter1 (Low)
#define OCR1AH *((uint8_t volatile *) 0x4B)       // Output Compare Register 1 A (High)
#define OCR1AL *((uint8_t volatile *) 0x4A)       // Output Compare Register 1 A (Low)
#define OCR1BH *((uint8_t volatile *) 0x49)       // Output Compare Register 1 B (High)
#define OCR1BL *((uint8_t volatile *) 0x48)       // Output Compare Register 1 B (Low)
#define ICR1H  *((uint8_t volatile *) 0x47)       // Input Capture Register 1 (High)
#define ICR1L  *((uint8_t volatile *) 0x46)       // Input Capture Register 1 (Low)


// TCCR1A Bits

#define WGM10	0
#define WGM11	1

// TCCR1B Bits
#define CS10	0
#define CS11	1
#define CS12	2
#define WGM12	3
#define WGM13	4

/*
*	Interrupt registers
*/

#define SREG_REG		*((uint8_t volatile *) 0x5F)
#define GIE_BIT			7


#define MCUCR  *((uint8_t volatile *)  0x55)			// MCU Control Register
#define MCUCSR  *((uint8_t volatile *)  0x54)		// MCU Control and Status Register
#define GICR  *((uint8_t volatile *)  0x5B)			// General Interrupt Control Register
#define GIFR  *((uint8_t volatile *)  0x5A)			// General Interrupt Flag Register


#define ISC00			0
#define ISC01			1
#define ISC10			2
#define ISC11			3
#define ISC2			6


#define INT_0_BIT	6
#define INT_1_BIT	7
#define INT_2_BIT	5





#endif /* REGISTERS_H_ */