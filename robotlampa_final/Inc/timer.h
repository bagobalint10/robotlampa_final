/*
 * timer.h
 *
 * Created: 2025. 10. 09. 23:32:37
 *  Author: bagob
 */ 


#ifndef TIMER_H_
#define TIMER_H_

		#include <avr/io.h>
		#include <avr/interrupt.h>

		void timer_setup(uint8_t timer, uint8_t mode, uint8_t prescaler, uint8_t interrupt_type);
		


#endif /* TIMER_H_ */