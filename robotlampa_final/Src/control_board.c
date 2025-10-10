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
 #include "timer.h"
 #define F_CPU 16000000UL
 #include <util/delay.h>
 //


 // gomb olvasás változó
 volatile uint8_t buttons = 0;
 //
 static void timer_0_callback(void);
 static int villog = 0;	 // ideiglenes 




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

 static void timers_init()
 {
	timer_init(TIMER0, TIMER0_CTC, TIMER0_PRESCALE_64);
	timer_int_init(TIMER0, TIMER0_INT_COMP_A);
	timer_set_value(TIMER0, 249);							// 1ms idõzítés (sys thick)
	set_timer_int_Callback(TIMER0,timer_0_callback);
 }

static void timer_0_callback(void)
 {
	 static unsigned int i = 0;
	 i++;

	 if (i >= 1000)
	 {
		 villog ^= 0x01;
		 i = 0;
	 }	 	 
 }



 // public függvények 

 void control_board_init_tmp(void)
 {
	segment_Init();
	buttons_init();	
	timers_init();
 }




 void control_board_tmp(void) // ideiglenes sketchi verzio
 {
		 segment_write_digit(0x01,'d', 0, villog);
 }




