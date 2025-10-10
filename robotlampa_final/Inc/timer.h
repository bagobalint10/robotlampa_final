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
		
		uint32_t millis(void);
		void timers_init(void);

		


#endif /* TIMER_H_ */