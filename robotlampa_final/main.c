/*
 * robotlampa_final.c
 *
 * Created: 2025. 10. 09. 14:43:11
 * Author : bagob
 */ 

#include <avr/io.h>

#include "control_board.h"
#include "timer.h"

extern int villog;

int main(void)
{

	control_board_init_tmp();
	timers_init();

    while (1) 
    {	 
		/*
		static uint32_t tmp_current_time = 0;
		tmp_current_time = millis();

		static uint32_t tmp_time_0 = 0;
		static uint16_t tmp_interval_0 = 1000;

		if ((uint32_t)(tmp_current_time - tmp_time_0)>= tmp_interval_0)
		{
			tmp_time_0 = tmp_current_time;
			villog ^= 0x01;
		} */

		control_board_tmp();		// ideiglenes 
		



    }
}
