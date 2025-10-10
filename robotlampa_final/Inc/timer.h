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

		void timer_init(uint8_t timer, uint8_t mode, uint8_t prescaler);
		void timer_set_value(uint8_t timer, uint8_t value);
		


#endif /* TIMER_H_ */