/*
 * port_config.h
 *
 * Created: 2025. 10. 07. 21:01:13
 *  Author: bagob
 */ 






#ifndef PORT_CONFIG_H_
#define PORT_CONFIG_H_

	#include <avr/io.h>

	// port config shift registerhez

	#define SR_LATCH_PORT PORTD		// --> D6
	#define SR_LATCH_PIN PORTD6
	#define SR_LATCH_DIR DDRD

	#define SR_DATA_PORT PORTD		// --> D7
	#define SR_DATA_PIN PORTD7
	#define SR_DATA_DIR DDRD

	#define SR_CLOCK_PORT PORTD		// --> D5
	#define SR_CLOCK_PIN PORTD5
	#define SR_CLOCK_DIR DDRD
	 /*	  pinout shift register 
  
	data	-		d0x80 -> d7
	clock -		d0x20 -> d5
	latch	- 		d0x40 -> d6
	*/

	// port config a gombokhoz 

	#define BTN_UP_PORT PORTC		// --> C0  
	#define BTN_UP_PIN PORTC0
	#define BTN_UP_DIR DDRC
	#define BTN_UP_PIN_IN PINC		// bemenet olvasáshoz 

	#define BTN_DOWN_PORT PORTC		// --> C1
	#define BTN_DOWN_PIN PORTC1
	#define BTN_DOWN_DIR DDRC
	#define BTN_DOWN_PIN_IN PINC		

	#define BTN_ENTER_PORT PORTC		// --> C2
	#define BTN_ENTER_PIN PORTC2
	#define BTN_ENTER_DIR DDRC
	#define BTN_ENTER_PIN_IN PINC		

	#define BTN_MODE_PORT PORTC		// --> C30
	#define BTN_MODE_PIN PORTC3
	#define BTN_MODE_DIR DDRC
	#define BTN_MODE_PIN_IN PINC
	
	#define BTN_COMMON_PIN_IN PINC // csak ha az összes gomb  egy porton van 	

	//
	/*
			gomb bekotes:	 (egy port ra a pinchange miatt majd)

							Up 		- 	A0 - PC0 - 0x01 	
							Down 	- 	A1 - PC1 - 0x02
							Enter	-	A2 - PC2 - 0x04 
							Mode 	- 	A3 - PC3 - 0x08
	*/
	//

	// interruptok 

	#define PCINT_B 0
	#define PCINT_C 1
	#define PCINT_D 2

	//pcint valid mask--> amiket használhatok 
	#define PCMSK0_VALID_MASK  0b00111111  // PB0–PB5, ha XTAL1/2-t nem használod
	#define PCMSK1_VALID_MASK  0b00111111  // PC0–PC5
	#define PCMSK2_VALID_MASK  0xFF        // PD0–PD7




	// logic

	#define OUTPUT 1
	#define INPUT 0



#endif /* PORT_CONFIG_H_ */