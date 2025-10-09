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

#include "port_config.h"
#include "interrupt.h"	  

void pcint_c_callback(void);
volatile uint8_t buttons = 0;

#include "timer.h"
static int villog = 0;


int main(void)
{
    // ideiglenes
	segment_Init();

	PORT_Init(&BTN_UP_DIR,BTN_UP_PIN,0); // PC0 - input
	PORT_Write(&BTN_UP_PORT,BTN_UP_PIN,1); // P0 - pullup?

	PORT_Init(&BTN_DOWN_DIR,BTN_DOWN_PIN,0); // PC1
	PORT_Write(&BTN_DOWN_PORT,BTN_DOWN_PIN,1); 

	PORT_Init(&BTN_ENTER_DIR,BTN_ENTER_PIN,0); // PC2
	PORT_Write(&BTN_UP_PORT,BTN_ENTER_PIN,1); 

	PORT_Init(&BTN_MODE_DIR,BTN_MODE_PIN,0); // PC3
	PORT_Write(&BTN_MODE_PORT,BTN_MODE_PIN,1); 
	//

	// it callback beállítása 
	set_pcint_Callback(PCINT_C, pcint_c_callback);
	pcint_init(PCINT_C, 0b00001111);
	//

	//timer interrupt
	timer_setup(TIMER0, TIMER0_NORMAL, TIMER0_PRESCALE_1024, TIMER0_INT_OVF);

	//
    while (1) 
    {	 

		/*
		segment_write_digit(0x01,(uint8_t) (((buttons&0x01) && 0x01)+48), 0, 1);
		_delay_ms(1);
		segment_write_digit(0x02,(uint8_t) (((buttons&0x02) && 0x01)+48), 0, 1);
		_delay_ms(1);
		segment_write_digit(0x04,(uint8_t) (((buttons&0x04) && 0x01)+48), 0, 1);
		_delay_ms(1);
		segment_write_digit(0x08,(uint8_t) (((buttons&0x08) && 0x01)+48), 0, 1);
		_delay_ms(1);
		*/
    }
}

void pcint_c_callback(void)
{
	// interrupt lekezekése 
	buttons = PORT_Read(&BTN_COMMON_PIN_IN);
}

ISR(TIMER0_OVF_vect)
{
	

	static unsigned int overflow = 0;
	overflow++;
	if(!(overflow%60))	villog = !villog;
	segment_write_digit(0x01,'a',0,villog);
	
}