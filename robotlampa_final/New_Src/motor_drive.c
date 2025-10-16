/*
 * motor_drive.c
 *
 * Created: 2025. 10. 14. 16:33:07
 *  Author: bagob
 */ 

 #include "motor_drive.h"
 #include <avr/interrupt.h>
 #include "port_config.h"
 #include "gpio.h"

 ///
 static uint16_t time_levels[ARRAY_ELEMENT] = {10000, 8000, 6500, 5000, 2000, 500, 400, 300, 200, 100};  //test
 static int current_level = 0;

 static int pos_diff = 0;
		int input_pos = 0;
 static int current_pos = 0;
 static uint8_t direction = 0;
 static uint8_t direction_pin = 0;

 static uint8_t motor_enable = 0;
 static uint8_t tim_refresh_complete = 2;
 extern uint8_t tmp_enable;
 ///

 static volatile uint16_t pwm_freq = 1200; // p�lda kezdeti TOP (pl. 40000 -> 50 Hz with 16MHz/8) � tetsz�s szerint �ll�that�

 static volatile uint16_t freq_array[5] = {40000,30000,20000,10000,5000};	//kb 20000 -> 80ms

 uint32_t step_n = 0;

 static void update_top_and_duty(void)
 {
	 volatile uint16_t *top = &pwm_freq;
	 step_n ++;

	 if (*top == 0) {
		 *top = 1;
	 }

	 ICR1 = *top;
 }

 void timer_init_tmp(void)
 {

	 TCCR1A = 0;
	 TCCR1B = 0;

	 TCCR1A |= (1 << COM1A1) | (0 << COM1A0) | (1 << WGM11);

	 TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS12) | (0 << CS11) | (0 << CS10); // prescaler = 1

	 update_top_and_duty();

	 TIMSK1 |= (1 << TOIE1);

	 OCR1A = TIM_COMPARE;  // kit�lt�s 
	 ICR1 = 10000;// kezd� freki 

	 sei();

 }

 void motor_code(void)
 {

  // eddig 
	 // motor sebedseg szabalyzas
	 PORT_Write(&TMP_PORT,TMP_PIN,1);

	  
	 if(motor_enable && direction)  
	 {
		 pos_diff = (input_pos - current_pos)-1; // -1 hogy ne l�pjen 1 el t�bbet ! 

		 //tim ovf it
		 if ((pos_diff > current_level) && (current_level < 9))	  current_level++;
		 else if((pos_diff < current_level) && (current_level > 0))	 current_level--;

		 current_pos++;

		 ICR1 = time_levels[current_level];
	 }
	 else if(motor_enable && (!direction))
	 {
		 pos_diff = (current_pos - input_pos)-1 ; //  -1 hogy ne l�pjen 1 el t�bbet !	//  -- ez m�s csak 

		 //tim ovf it
		 if ((pos_diff > current_level) && (current_level < 9))	  current_level++;
		 else if((pos_diff < current_level) && (current_level > 0))	 current_level--;

		 current_pos--;	   // -- meg ez m�s 

		 //if(current_level<0)current_level = 0;
		 ICR1 = time_levels[current_level];
	 } 

	 if ((!current_level) && motor_enable)  // ha lenull�z�dott a sebess�g  // 1 el k�s�bb reszeteljen 
	 {
		motor_enable = 0;	// motor tilt�sa -> main b�l lehet �jra ind�tani 
		tim_refresh_complete=0;	// kikapcsol�shoz 

		//tim_refresh_complete++;
       //kimenet tilt�sa 
		//OCR1A = 0;  // kit�lt�s = 0 --> avr n�l kis impulzus nemj� !! 
			//helyette : 
		//TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0)); //  PWM lev�laszt�sa 
		//PORTB &= ~(1 << PORTB1);	// kimenet 0 ra �ll�t�sa   
	 } 

	 tim_refresh_complete++;

	 if (tim_refresh_complete > 2)
	 {
		 tim_refresh_complete = 2;
	 }
	 
	PORT_Write(&TMP_PORT,TMP_PIN,0); 

	/////
	  	
 }

 void motor_main(void)
 {
	//main iranyvaltas
	static uint16_t tim_count = 0;
	
	static uint8_t tmp_blink = 0;
	

	tim_count = ((uint16_t)(TCNT1H << 8)) | ((uint16_t) TCNT1L); 
	//PORT_Write(&MOTOR_DIR_PORT,MOTOR_DIR_PIN,tmp_blink); // test --> diff = 0

	if((!motor_enable) && (input_pos != current_pos) && ( tim_count > 20) && ( tim_count < 200))		//�ll a motor	+ menni k�ne
	{
		if(input_pos>current_pos)	direction = 1, direction_pin = 1;	  //pozitiv
		else 	 direction = 0, direction_pin = 0;						  //negat�v
		motor_enable = 1;
		tim_refresh_complete = 0;

		

		PORT_Write(&MOTOR_DIR_PORT,MOTOR_DIR_PIN,1);
		// port
		//PORT_Write(&MOTOR_DIR_PORT,MOTOR_DIR_PIN,direction_pin);
		//OCR1A = 10; // kit�lt�s --> itt nemj� ez a m�dszer 
		//TCNT1H = (uint8_t)(8000 >> 8);	 // timer 0 �z�sa  8000
		//TCNT1L = (uint8_t) 8000;
		//TCNT1H = 0;	 // timer 0 �z�sa  8000
		//TCNT1L = 0;

		TCCR1A |= (1 << COM1A1) | (0 << COM1A0); // PWM kimenet enged�lyez�se

	}else if((!current_level) && (!motor_enable) && ( tim_count > 20) && ( tim_count < 200) )		 //&& ( tim_count > 20)
	{	  // tim_refresh_complete > 1 &&
		//reset kimenet
		TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0)); //  PWM lev�laszt�sa
		PORTB &= ~(1 << PORTB1);					// kimenet 0 ra �ll�t�sa
		 

		// tim refresh tulcsordul�s
	}

	if( tim_count > 100)	tmp_blink ^= 0x01;
	
	//PORT_Write(&MOTOR_DIR_PORT,MOTOR_DIR_PIN,tmp_blink);
	
	 
 }


 ISR(TIMER1_OVF_vect)
 {
	 //update_top_and_duty();
	 motor_code();
 }