/*
 * interrupt.c
 *
 * Created: 2025. 10. 09. 17:25:16
 *  Author: bagob
 */ 

#include "interrupt.h"
#include "port_config.h"
#include "stddef.h"

void (*pcint_b_callback_pointer)(void) = NULL;
void (*pcint_c_callback_pointer)(void) = NULL;
void (*pcint_d_callback_pointer)(void) = NULL;


 void set_pcint_Callback(uint8_t port ,void (*Callback_function)(void) )
 {
	 
	switch(port)
	{
		case 0 : pcint_b_callback_pointer = Callback_function; break;
		case 1 : pcint_c_callback_pointer = Callback_function; break;
		case 2 : pcint_d_callback_pointer = Callback_function; break;
		default : break;
	} 
 }


 void pcint_init(uint8_t port, uint8_t mask)  //pcint init hal 
 {

	switch (port)
	{
	case 0 :											// B
				PCICR |= (1 << PCIE0);					// enable port B pcint 
				PCMSK0 |= PCMSK0_VALID_MASK & mask;		// port B pin mask 
				sei();	
				break;
	case 1 :											// C
				PCICR |= (1 << PCIE1);					// enable port B pcint
				PCMSK1 |= PCMSK1_VALID_MASK & mask;		// port B pin mask
				sei();
				break;
	case 2 :											// D
				PCICR |= (1 << PCIE2);					// enable port B pcint
				PCMSK2 |= PCMSK2_VALID_MASK & mask;		// port B pin mask
				sei();
				break;
	default:	break;
	}	 
 }

 ISR(PCINT0_vect)
 {
	if(pcint_b_callback_pointer) pcint_b_callback_pointer(); // ha tettünk bele callbacket hívja meg 
 }
 ISR(PCINT1_vect)
 {
	if(pcint_c_callback_pointer) pcint_c_callback_pointer(); // ha tettünk bele callbacket hívja meg 
 }
 ISR(PCINT2_vect)
 {
	if(pcint_d_callback_pointer) pcint_d_callback_pointer(); // ha tettünk bele callbacket hívja meg 
 }