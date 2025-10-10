/*
 * robotlampa_final.c
 *
 * Created: 2025. 10. 09. 14:43:11
 * Author : bagob
 */ 

#include <avr/io.h>

#include "control_board.h"
#include "timer.h"
#include "port_config.h"

static int villog = 0;


int main(void)
{


	control_board_init_tmp();

	//timer interrupt
	timer_setup(TIMER0, TIMER0_NORMAL, TIMER0_PRESCALE_1024, TIMER0_INT_OVF);	
	//

    while (1) 
    {	 

		control_board_tmp(); // ideiglenes 

    }
}



ISR(TIMER0_OVF_vect)
{
	

	static unsigned int overflow = 0;
	overflow++;
	if(!(overflow%60))	villog = !villog;
	//segment_write_digit(0x01,'a',0,villog);
	
}