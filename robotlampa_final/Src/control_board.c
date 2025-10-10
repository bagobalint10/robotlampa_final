/*
 * control_board.c
 *
 * Created: 2025. 10. 10. 16:52:46
 *  Author: bagob
 */ 

 #include "control_board.h"

 ///// ideiglenes  - gomb olvasás + segment write 

 #include "gpio.h"
 #include "segment_write_digit.h"
 #include "port_config.h"
 #include "interrupt.h"
 #define F_CPU 16000000UL
 #include <util/delay.h>
 //


 // gomb olvasás változó
 volatile uint8_t buttons = 0;
 //

 // private függvények 

  static void pcint_c_callback(void)			// pcint_C lekezekése
  {
	  buttons = PORT_Read(&BTN_COMMON_PIN_IN);	//C port beolvasás
  }


 static void buttons_init(void)
 {
	 // gomb pinek bemenet + pullup  - init

	 PORT_Init(&BTN_UP_DIR,BTN_UP_PIN,0);		// PC0 - input
	 PORT_Write(&BTN_UP_PORT,BTN_UP_PIN,1);		// P0 - pull up

	 PORT_Init(&BTN_DOWN_DIR,BTN_DOWN_PIN,0);	// PC1
	 PORT_Write(&BTN_DOWN_PORT,BTN_DOWN_PIN,1);

	 PORT_Init(&BTN_ENTER_DIR,BTN_ENTER_PIN,0); // PC2
	 PORT_Write(&BTN_UP_PORT,BTN_ENTER_PIN,1);

	 PORT_Init(&BTN_MODE_DIR,BTN_MODE_PIN,0);	// PC3
	 PORT_Write(&BTN_MODE_PORT,BTN_MODE_PIN,1);

	 // pcint  callback beállítása gombokra

	 set_pcint_Callback(PCINT_C, pcint_c_callback);		// Callback fgv. beállítása 
	 pcint_init(PCINT_C, 0b00001111);					// C portra enable , maszkolás 4 gombra 
 } 



 // public függvények 

 void control_board_init_tmp(void)
 {
	segment_Init();
	buttons_init();	
 }




 void control_board_tmp(void) // ideiglenes sketchi verzio
 {


 }




