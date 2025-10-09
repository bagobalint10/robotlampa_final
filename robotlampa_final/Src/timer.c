/*
 * timer.c
 *
 * Created: 2025. 10. 09. 23:33:02
 *  Author: bagob
 */ 

 #include "timer.h"
 #include "port_config.h"

 void timer_setup(uint8_t timer, uint8_t mode, uint8_t prescaler, uint8_t interrupt_type){
		 
	 switch (timer)
	 {
	 case 0:
				TCCR0A = 0;   // 1. Alaphelyzet
				TCCR0B = 0;
				TIMSK0 = 0;
				
				TCCR0A = mode;	  // 2. Timer mód beállítása
				TCCR0B = prescaler;   // 3. Prescaler beállítása
				TIMSK0 = interrupt_type;	// 4. Interrupt beállítása
				
				if(interrupt_type != TIMER0_INT_NONE) {	 // 5. Globális interrupt engedélyezése, ha kell
					sei();
				}

				break;
	 case 1: break;
	 case 2: break;
	 default: break;
	 }
	 
 }