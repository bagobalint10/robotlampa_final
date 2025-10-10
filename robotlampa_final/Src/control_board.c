/*
 * control_board.c
 *
 * Created: 2025. 10. 10. 16:52:46
 *  Author: bagob
 */ 

 #include "control_board.h"

  #include "segment_write_digit.h"
  #include "buttons.h"

 ///// ideiglenes  - gomb olvasás + segment write 

 //#include "gpio.h"

 //#include "port_config.h"
 //#include "interrupt.h"
 #include "timer.h"
 #define F_CPU 16000000UL
 #include <util/delay.h>
 //


 // gomb olvasás változó
 volatile uint8_t buttons = 0;
 //
 
  int villog = 0;	 // ideiglenes 

 // private függvények 



 // public függvények 

 void control_board_init_tmp(void)
 {
	segment_Init();
	buttons_init();	
 }

 void control_board_tmp(void) // ideiglenes sketchi verzio
 {
		 //segment_write_digit(0x01,'d', 0, villog);
		 #define TEST_BUTTONS buttons
		 
		 segment_write_digit(0x01,(uint8_t) (((TEST_BUTTONS&0x01) && 0x01)+48), 0, villog);
 }





