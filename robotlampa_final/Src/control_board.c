/*
 * control_board.c
 *
 * Created: 2025. 10. 10. 16:52:46
 *  Author: bagob
 */ 

 #include "control_board.h"

 #include "segment_write_digit.h"
 #include "buttons.h"
 #include "timer.h"


  int villog = 0;	 // ideiglenes 

  // gomb változók 

  uint8_t bt_up = 0;
  uint8_t bt_down = 0;
  uint8_t bt_enter = 0;
  uint8_t bt_mode = 0;

 // private függvények 

 // public függvények 

 void control_board_init_tmp(void)
 {
	segment_Init();
	buttons_init(10); //debounce time in ms
	set_buttons_variables(&bt_up, &bt_down, &bt_enter, &bt_mode);	
 }

 void control_board_tmp(void) // ideiglenes sketchi verzio
 {
	button_read(); // kiolvasás

		  // pergés test code 
		  static uint8_t szamlal = 0;
		  static uint8_t prev_button = 0;

		  if (prev_button^bt_mode)
		  {
			prev_button = bt_mode;
			szamlal++;
		  }

		  //




	
		   segment_write_digit(0x01,szamlal+48, 0, 1);
		   
		   segment_write_digit(0x02,bt_down+48, 0, 1);
		   
		   segment_write_digit(0x04,bt_enter+48, 0, 1);
		   
		   segment_write_digit(0x08,bt_mode+48, 0, 1);
		   


		 //segment_write_digit(0x01,'d', 0, villog);
		 /*#define TEST_BUTTONS buttons
		 
		 segment_write_digit(0x01,(uint8_t) (((TEST_BUTTONS&0x01) && 0x01)+48), 0, villog);	*/
 }





