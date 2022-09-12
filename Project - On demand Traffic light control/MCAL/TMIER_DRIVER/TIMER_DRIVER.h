/*
 * TIMER_DRIVER.h
 *
 * Created: 1/9/2022 3:33:04 PM
 *  Author: Muhannad Shmouty
 */ 


#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

#define freq 1000000
typedef enum {Normal, CTC, Fast_PWM, PC_Fast_PWM} TIMER_MODE;


#define Tmr0_Res 256

void timer0Enable(TIMER_MODE ModeOfOperation, uint16_t prescaler);
void timer0_delay_ms(uint16_t time_ms);
void timer0Disable();

void timer1Enable(TIMER_MODE ModeOfOperation, uint16_t prescaler);
void fireEvery_ms(uint16_t time_ms);


#endif /* TIMER_DRIVER_H_ */