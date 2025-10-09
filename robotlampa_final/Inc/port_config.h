/*
 * port_config.h
 *
 * Created: 2025. 10. 07. 21:01:13
 *  Author: bagob
 */ 




 /*	  pinout 
  
  data	-		d0x80 -> d7
  clock -		d0x20 -> d5
  latch	- 		d0x40 -> d6  
  gombos láb -	c0x10 -> c4
*/

#ifndef PORT_CONFIG_H_
#define PORT_CONFIG_H_

	#include <avr/io.h>

	// pinout 
	#define SR_LATCH_PORT PORTD		// --> D6
	#define SR_LATCH_PIN PORTD6
	#define SR_LATCH_DIR DDRD

	#define SR_DATA_PORT PORTD		// --> D7
	#define SR_DATA_PIN PORTD7
	#define SR_DATA_DIR DDRD

	#define SR_CLOCK_PORT PORTD		// --> D5
	#define SR_CLOCK_PIN PORTD5
	#define SR_CLOCK_DIR DDRD


	// logic

	#define OUTPUT 1
	#define INPUT 0



#endif /* PORT_CONFIG_H_ */