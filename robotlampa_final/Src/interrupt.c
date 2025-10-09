/*
 * interrupt.c
 *
 * Created: 2025. 10. 09. 17:25:16
 *  Author: bagob
 */ 

#include "interrupt.h"
#include "port_config.h"
#include "stddef.h"

void (*pcint_c_callback_pointer)(void) = NULL;


 void set_pcint_Callback(uint8_t port ,void (*Callback_function)(void) )
 {
		pcint_c_callback_pointer = Callback_function;
	 /*
	switch(port)
	{
		case 1 : pcint_c_callback_pointer = Callback_function; break;
		default : break;
	} */
 }
 /*
 void ideiglenes_isr(void)
 {

	 


 } */

 void pcint_init(void)	// ideiglenes 
 {
	
	 PCICR |= (1 << PCIE1);	    // Enged�lyezz�k a PCINT1 megszak�t�scsoportot (PCINT[14:8], azaz PORTC)

				// Enged�lyezz�k a PC0�PC3 l�bakon a pin change interruptot
				// (PCINT8�PCINT11)
	 PCMSK1 |= (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10) | (1 << PCINT11);

	
	 //DDRC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3));	 // Be�ll�tjuk a PORTC biteket bemenetre (biztons�g kedv��rt)

					// (Opcion�lisan) felh�z�ellen�ll�sokat bekapcsolhatunk, ha kell:
					// PORTC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3);

					// Glob�lis megszak�t�sok enged�lyez�se
	 sei();
 }

 ISR(PCINT1_vect)
 {
	 //if(pcint_c_callback_pointer) pcint_c_callback_pointer(); // ha tett�nk bele callbacket h�vja meg 
	 pcint_c_callback_pointer();

 }