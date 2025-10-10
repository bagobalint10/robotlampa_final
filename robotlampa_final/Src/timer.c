/*
 * timer.c
 *
 * Created: 2025. 10. 09. 23:33:02
 *  Author: bagob
 */ 

 #include "timer.h"
 #include "port_config.h"

 void timer_init(uint8_t timer, uint8_t mode, uint8_t prescaler){
		 
	 switch (timer)
	 {
		 case 0:
					TCCR0A = 0;				 // 1. Alaphelyzet
					TCCR0B = 0;

					TCCR0A = mode;			// 2. Timer mód beállítása
					TCCR0B = prescaler;		// 3. Prescaler beállítása
					break;
		 case 1: break;
		 case 2: break;
		 default: break;
	 }
	 
 }

 void timer_set_value(uint8_t timer, uint8_t value)
 {
	 switch (timer)
	 {
		 case 0: OCR0A = value; break;
		 default: break;
	 }
 }