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

#include "motor_drive.h"
#include "gpio.h"
#include "port_config.h"


//extern uint32_t step_n;
extern int input_pos;
//uint8_t tmp_enable = 0;

int main(void)
{
	timers_init();
	control_board_init();
	dmx_usart_init();
	timer_init_tmp();
	//PB1 kimenet 
	PORT_Init(&DDRB,PORTB1, OUTPUT);  // timer output --> motor pulse 
	PORT_Init(&MOTOR_DIR_DIR,MOTOR_DIR_PIN, OUTPUT);
	PORT_Init(&TMP_DIR,TMP_PIN, OUTPUT);

    while (1) 
    {	 
		   static uint8_t tmp_dir = 1;
		dmx_usart_send(); // step n legelöl 		
	    motor_main(); 

		// timer 
	static uint32_t tmp_current_time = 0;
	tmp_current_time = millis();

	static uint32_t tmp_time_0 = 0;
	static uint16_t tmp_interval_0 = 10000;	//10mp 

	if ((uint32_t)(tmp_current_time - tmp_time_0)>= tmp_interval_0)
	{
		tmp_time_0 = tmp_current_time;

		
		if(input_pos) input_pos = 0;
		else  input_pos = 10000;
		//if((input_pos == 200) || (input_pos == 0) )	tmp_dir ^=0x01;
		
	} 
	
    }
}
