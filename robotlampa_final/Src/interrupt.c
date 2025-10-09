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
	
	 PCICR |= (1 << PCIE1);	    // Engedélyezzük a PCINT1 megszakításcsoportot (PCINT[14:8], azaz PORTC)

				// Engedélyezzük a PC0–PC3 lábakon a pin change interruptot
				// (PCINT8–PCINT11)
	 PCMSK1 |= (1 << PCINT8) | (1 << PCINT9) | (1 << PCINT10) | (1 << PCINT11);

	
	 //DDRC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3));	 // Beállítjuk a PORTC biteket bemenetre (biztonság kedvéért)

					// (Opcionálisan) felhúzóellenállásokat bekapcsolhatunk, ha kell:
					// PORTC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3);

					// Globális megszakítások engedélyezése
	 sei();
 }

 ISR(PCINT1_vect)
 {
	 //if(pcint_c_callback_pointer) pcint_c_callback_pointer(); // ha tettünk bele callbacket hívja meg 
	 pcint_c_callback_pointer();

 }