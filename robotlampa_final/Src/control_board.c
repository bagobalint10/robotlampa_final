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

  // gomb v�ltoz�k 

  static uint8_t bt_up = 1;
  static uint8_t bt_down = 1;
  static uint8_t bt_enter = 1;
  static uint8_t bt_mode = 1;

  //lcd v�ltoz�k

  static uint8_t lcd_buffer[4] = "abcd";
  static uint8_t lcd_dot_buffer[4] = {1,1,0,0};
  static uint8_t lcd_enable = 1;
  
 // private f�ggv�nyek 


 static void menu(void)
 {
	// gomb felfut� �l olvas�s 
	// gomb l�ptet�s fel-le 
	// v�g�rt�kek megfog�sa 
	//men� kiirat�s men� v�ltoz� 

	static int menu_n = 0;							// 0-3 f�men� 	
	static const char *menu_string[6]=	{	"rst ",
											"a   ",
											"lamp",
											"run ",
											"on  ",
											"off "  };	

	// felfut� �l olvas�s 
	static uint8_t bt_up_tmp = 1;
	static uint8_t bt_down_tmp = 1;
	static uint8_t bt_enter_tmp = 1;
	static uint8_t bt_mode_tmp = 1; 
	//

	if(bt_up^bt_up_tmp)	 // �l detekt�l�s
	{
		menu_n -= !bt_up ;		// l�ptet�s, lefut� �ln�k
		bt_up_tmp = bt_up;  
	}
	if(bt_down^bt_down_tmp)	 // �l detekt�l�s 
	{
		menu_n += !bt_down ;	// l�ptet�s, lefut� �ln�k
		bt_down_tmp = bt_down;	
	}

	if(menu_n < 0) menu_n = 0;
	if(menu_n > 3) menu_n = 3;

	
	//
	switch(menu_n)
	{
	case 0: 
				break;
	default: break;
	}

	// menu_n --> buffer 

	const char *menu_pointer;
	menu_pointer = menu_string[menu_n];

	for (int i = 0; i<4; i++)  //str_copy
	{
		lcd_buffer[i] = *(menu_pointer+i);
	}

 }
 // public f�ggv�nyek 

 void control_board_init(void)
 {
	buttons_init(10); //debounce time in ms
	set_buttons_variables(&bt_up, &bt_down, &bt_enter, &bt_mode);
	lcd_init(4);	// 4x4 = 16ms refresh time 
 }

 void control_board_main(void) // ideiglenes sketchi verzio
 {
	button_read(); // kiolvas�s
	menu();	 // gomb -->  string , dot, enable
	lcd_write_buffer(lcd_buffer,lcd_dot_buffer,lcd_enable);	  

 }





