/*
 * interrupt.h
 *
 * Created: 2025. 10. 09. 16:56:21
 *  Author: bagob
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

	#include <avr/io.h>
	#include <avr/interrupt.h>

	void set_pcint_Callback(uint8_t port ,void (*Callback_function)(void) );
	void pcint_init(void);
	



#endif /* INTERRUPT_H_ */