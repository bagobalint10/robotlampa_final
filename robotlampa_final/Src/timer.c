/*
 * timer.c
 *
 * Created: 2025. 10. 09. 23:33:02
 *  Author: bagob
 */ 

 #include "timer.h"
 #include "interrupt.h"
 #include "port_config.h"


  static volatile uint32_t Millis = 0;
  static void timer_0_callback(void);



 //// private 

 static void timer_init(uint8_t timer, uint8_t mode, uint8_t prescaler){
		 
	 switch (timer)
	 {
		 case 0:
					TCCR0A = 0;				 // 1. Alaphelyzet
					TCCR0B = 0;

					TCCR0A = mode;			// 2. Timer mód beállítása
					TCCR0B = prescaler;		// 3. Prescaler beállítása
					break;
		 case 1: break;
		 case 2: break;
		 default: break;
	 }
	 
 }

 static void timer_set_value(uint8_t timer, uint8_t value)
 {
	 switch (timer)
	 {
		 case 0: OCR0A = value; break;
		 default: break;
	 }
 }


 static void timer_0_callback(void)
 {
	 Millis++;
 }


  ///////////////  public 

 void timers_init()
  {
	  timer_init(TIMER0, TIMER0_CTC, TIMER0_PRESCALE_64);
	  timer_int_init(TIMER0, TIMER0_INT_COMP_A);
	  timer_set_value(TIMER0, 249);							// 1ms idõzítés (sys thick)
	  set_timer_int_Callback(TIMER0,timer_0_callback);
  }

 uint32_t millis(void)
 {
	 uint32_t m;
	 cli();				// megszakítás tiltás olvasás idejére --> több órajel kiolvasni 32 bitet
	 m = Millis;
	 sei();

	 return m;
 }

