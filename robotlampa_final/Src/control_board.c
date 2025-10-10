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

  // gomb változók 

  uint8_t bt_up = 0;
  uint8_t bt_down = 0;
  uint8_t bt_enter = 0;
  uint8_t bt_mode = 0;

 // private függvények 

 // public függvények 

 void control_board_init(void)
 {
	segment_Init();
	buttons_init(10); //debounce time in ms
	set_buttons_variables(&bt_up, &bt_down, &bt_enter, &bt_mode);	
 }

 void control_board_main(void) // ideiglenes sketchi verzio
 {
	button_read(); // kiolvasás
	//menü
	//szegmens kiirás

 }





