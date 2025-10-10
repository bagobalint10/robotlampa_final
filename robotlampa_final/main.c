/*
 * robotlampa_final.c
 *
 * Created: 2025. 10. 09. 14:43:11
 * Author : bagob
 */ 

#include <avr/io.h>

#include "control_board.h"
//#include "timer.h"
//#include "port_config.h"
//#include "interrupt.h"




int main(void)
{

	control_board_init_tmp();

    while (1) 
    {	 

		control_board_tmp();		// ideiglenes 

    }
}
