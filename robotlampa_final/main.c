/*
 * robotlampa_final.c
 *
 * Created: 2025. 10. 09. 14:43:11
 * Author : bagob
 */ 

#include <avr/io.h>

// ideiglenes 
#include "gpio.h"
#include "segment_write_digit.h"
#define F_CPU 16000000UL
#include <util/delay.h>

// port config a gombokhoz 

	#define BTN_UP PORTC		// --> C0  
	#define BTN_UP PORTC0
	#define BTN_UP DDRC
	#define BTN_UP PINC		// bemenet olvasáshoz 

	#define BTN_DOWN PORTC		// --> C1
	#define BTN_DOWN PORTC1
	#define BTN_DOWN DDRC
	#define BTN_DOWN PINC		

	#define BTN_ENTER PORTC		// --> C2
	#define BTN_ENTER PORTC2
	#define BTN_ENTER DDRC
	#define BTN_ENTER PINC		

	#define BTN_MODE PORTC		// --> C30
	#define BTN_MODE PORTC3
	#define BTN_MODE DDRC
	#define BTN_MODE PINC		



//
/*
		gomb bekotes:	 (egy port ra a pinchange miatt majd)

						Up 		- 	A0 - PC0 - 0x01 	
						Down 	- 	A1 - PC1 - 0x02
						Enter	-	A2 - PC2 - 0x04 
						Mode 	- 	A3 - PC3 - 0x08
*/
//

int main(void)
{
    // ideiglenes
	segment_Init();

	PORT_Init(&DDRC,PORTC0,0); // PC0 - input
	PORT_Write(&PORTC,PORTC0,1); // P0 - pullup?

	PORT_Init(&DDRC,PORTC1,0); // PC1
	PORT_Write(&PORTC,PORTC1,1); 

	PORT_Init(&DDRC,PORTC2,0); // PC2
	PORT_Write(&PORTC,PORTC2,1); 

	PORT_Init(&DDRC,PORTC3,0); // PC3
	PORT_Write(&PORTC,PORTC3,1); 
	//
    while (1) 
    {
		uint8_t buttons = 0;
		buttons = PORT_Read(&PINC);

		//segment_write_digit(0x01,'a', 0, 1);
		segment_write_digit(0x01,(uint8_t) (((buttons&0x01) && 0x01)+48), 0, 1);
		_delay_ms(1);
		segment_write_digit(0x02,(uint8_t) (((buttons&0x02) && 0x01)+48), 0, 1);
		_delay_ms(1);
		segment_write_digit(0x04,(uint8_t) (((buttons&0x04) && 0x01)+48), 0, 1);
		_delay_ms(1);
		segment_write_digit(0x08,(uint8_t) (((buttons&0x08) && 0x01)+48), 0, 1);
		_delay_ms(1);
    }
}

