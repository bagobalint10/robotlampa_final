/*
 * robotlampa_final.c
 *
 * Created: 2025. 10. 09. 14:43:11
 * Author : bagob
 */ 

#include <avr/io.h>

#include "control_board.h"
#include "timer.h"
#include "dmx_usart.h"


int main(void)
{
	timers_init();
	control_board_init();
	dmx_usart_init();
	
    while (1) 
    {	 

		control_board_main(); // menü,cím,lcd,relé kezelés
		dmx_usart_send();		
	
    }
}
