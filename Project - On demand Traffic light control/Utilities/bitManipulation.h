/*
 * bitManipulation.h
 *
 * Created: 27/8/2022 7:07:50 PM
 *  Author: Muhannad Shmouty
 */ 


#ifndef BITMANIPULATION_H_
#define BITMANIPULATION_H_


#define SET_BIT(byte, bit) ((byte) |= (1 << (bit)))
#define GET_BIT(byte, bit) ((byte) >> (bit) & 1)
#define RESET_BIT(byte, bit) ((byte) &= ~(1 << (bit)))
#define TOGGLE_BIT(byte, bit) ((byte) ^= (1 << (bit)))


#endif /* BITMANIPULATION_H_ */