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

 #include <stdlib.h> 

  // gomb változók 

  static uint8_t bt_up = 1;
  static uint8_t bt_down = 1;
  static uint8_t bt_enter = 1;
  static uint8_t bt_mode = 1;

  //lcd változók

  static uint8_t lcd_buffer[4] = "abcd";
  static uint8_t lcd_dot_buffer[4] = {1,1,0,0};
  static uint8_t lcd_enable = 1;

  // dmx adress 

  static int dmx_adress = 001;
  
 // private függvények 


 void push_string();
 static void menu(void)
 {
	// gomb felfutó él olvasás 
	// gomb léptetés fel-le 
	// végértékek megfogása 
	//menü kiiratás menü változó 

	static int menu_n = 1;		// 0-3 fõmenü 	
	static uint8_t sub_menu_f = 0;
	static int sub_menu_n = 0;
	static const char *menu_string[6]=	{	"rst ",
											"a   ",
											"lamp",
											"run ",
											"on  ",
											"off "  };
												
	static const char *sub_menu_string[3]=	{	"on  ",
												"off ",
												"b   "  }; //dmx

	// felfutó él olvasás 
	static uint8_t bt_up_tmp = 1;
	static uint8_t bt_down_tmp = 1;
	static uint8_t bt_enter_tmp = 1;
	static uint8_t bt_mode_tmp = 1; 
	//
	 uint8_t enter_f = 0; // dinamikus 
	 uint8_t mode_f = 0;
	 uint8_t up_f = 0; // dinamikus
	 uint8_t down_f = 0;
	 //
	 const char *menu_pointer;

	if(bt_up^bt_up_tmp)	 // él detektálás
	{
		up_f = !bt_up;		// léptetés, lefutó élnék
		bt_up_tmp = bt_up;  
	}
	if(bt_down^bt_down_tmp)	 // él detektálás 
	{
		down_f = !bt_down;	// léptetés, lefutó élnék
		bt_down_tmp = bt_down;	
	}
	if(bt_enter^bt_enter_tmp)	 // él detektálás
	{
		enter_f = !bt_enter;		 // csak lefutó 
		bt_enter_tmp = bt_enter;
	}
	if(bt_mode^bt_mode_tmp)	 // él detektálás
	{
		mode_f = !bt_mode;	 // csak lefutó 
		bt_mode_tmp = bt_mode;
	}
	//
	// hosszu gombnyomás ellenõrzések: enter, up, down 
	//

	

	
	//
	switch(menu_n)	// --> ha "ráléptem" az adott menüpontra 
	{
	case 0:		// reset 
				// reset();
				// kilépés --> reset állítja a flaget 
				break;

	case 1:		// DMX ADRESS
      
				if(sub_menu_f)  					// SUBMENU 
				{
					// UP-DOWN -->  dmx adress 
					// ENTER  --> mentés, hoszan 
					// MODE	 --> kilépés --> menü 
					if(mode_f) sub_menu_f = 0;
					if(up_f) dmx_adress++;
					if(down_f) dmx_adress--;

									    
				}
				else								// SIMA MENU		
				{
					// UP-DOWN -->  menu_n
					// ENTER  --> belépés --> submenü
					// MODE	 --> semmi 
					if(enter_f) sub_menu_f = 1;
					if(up_f) menu_n--;
					if(down_f) menu_n++;
				}
				// overflow guard
				if(menu_n < 1) menu_n = 1;	// ÁTTENNI MÁSHOVA
				if(menu_n > 2) menu_n = 2;

				if(sub_menu_n < 0) sub_menu_n = 0;	// ÁTTENNI MÁSHOVA
				if(sub_menu_n > 1) sub_menu_n = 1;

				/// string push 
				//const char *menu_pointer;

				if(sub_menu_f) menu_pointer = sub_menu_string[2];  					// SUBMENU	KIJELZÉS  --> dmx módba ne menjen!!
				else menu_pointer = menu_string[menu_n];

				for (int i = 0; i<4; i++)  //str_copy
				{
					lcd_buffer[i] = *(menu_pointer+i);
				}
				// adress convert string 
				
				char s_adress[3];

				//adresss kijelzés
				s_adress[2] = (dmx_adress%10)+48;  // egyes helyiertek 
				s_adress[1] = (dmx_adress/10%10)+48;
				s_adress[0] = (dmx_adress/100%10)+48;
				 
				for (int i = 1; i<4; i++)  //str_copy 1-3
				{
					lcd_buffer[i] = s_adress[i-1];
					// hátul tesztelõs 0 if 
				}

				break;

	case 2:		// LAMP
	
				if(sub_menu_f)  					// SUBMENU
				{
					// UP-DOWN -->  sub_menu_n,
					// ENTER  --> mentés, hoszan
					// MODE	 --> kilépés --> menü
					if(mode_f) sub_menu_f = 0;
					if(up_f) sub_menu_n--;
					if(down_f) sub_menu_n++;
				}
				else								// SIMA MENU
				{
					// UP-DOWN -->  menu_n
					// ENTER  --> belépés --> submenü
					// MODE	 --> semmi
					if(enter_f) sub_menu_f = 1;
					if(up_f) menu_n--;
					if(down_f) menu_n++;
				}
				// overflow guard 
				if(menu_n < 1) menu_n = 1;	// ÁTTENNI MÁSHOVA
				if(menu_n > 2) menu_n = 2;

				if(sub_menu_n < 0) sub_menu_n = 0;	// ÁTTENNI MÁSHOVA
				if(sub_menu_n > 1) sub_menu_n = 1;

				/// string push
				//const char *menu_pointer;

				if(sub_menu_f) menu_pointer = sub_menu_string[sub_menu_n];  					// SUBMENU	KIJELZÉS  --> dmx módba ne menjen!!
				else menu_pointer = menu_string[menu_n];

				for (int i = 0; i<4; i++)  //str_copy
				{
					lcd_buffer[i] = *(menu_pointer+i);
				}
				break;
	default: break;
	}

	



	 //
	

 }
 // public függvények 

 void control_board_init(void)
 {
	buttons_init(10); //debounce time in ms
	set_buttons_variables(&bt_up, &bt_down, &bt_enter, &bt_mode);
	lcd_init(4);	// 4x4 = 16ms refresh time 
 }

 void control_board_main(void) // ideiglenes sketchi verzio
 {
	button_read(); // kiolvasás
	menu();	 // gomb -->  string , dot, enable
	lcd_write_buffer(lcd_buffer,lcd_dot_buffer,lcd_enable);	  

 }





