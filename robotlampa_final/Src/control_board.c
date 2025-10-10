/*
 * control_board.c
 *
 * Created: 2025. 10. 10. 16:52:46
 *  Author: bagob
 */ 

 #include "control_board.h"

 #include "buttons.h"
 #include "timer.h"
 #include "lcd_driver.h"

  // gomb változók 

  static uint8_t bt_up = 0;
  static uint8_t bt_down = 0;
  static uint8_t bt_enter = 0;
  static uint8_t bt_mode = 0;

  //lcd változók

  static uint8_t lcd_buffer[4] = "abcd";
  static uint8_t lcd_dot_buffer[4] = {1,1,0,0};
  static uint8_t lcd_enable = 1;
  
 // private függvények 

 // public függvények 

 void control_board_init(void)
 {
	buttons_init(10); //debounce time in ms
	set_buttons_variables(&bt_up, &bt_down, &bt_enter, &bt_mode);
	lcd_init(5);	
 }

 void control_board_main(void) // ideiglenes sketchi verzio
 {
	button_read(); // kiolvasás
	//menü	--> bufferbe string beiras / gomb olvasás
	lcd_write_buffer(lcd_buffer,lcd_dot_buffer,lcd_enable);	 // 5x4 = 20ms refresh time  

 }





