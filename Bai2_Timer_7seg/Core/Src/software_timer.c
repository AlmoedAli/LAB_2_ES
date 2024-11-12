/*
 * software_timer.c
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#include "software_timer.h"

#define TIMER_CYCLE_2 1

//software timer variable
uint16_t flag_timer2 = 0;
uint16_t timer2_counter = 0;
uint16_t timer2_MUL = 0;

uint16_t flag1 = 0;
uint16_t flag2 = 0;
uint16_t flag3 = 0;
uint16_t state1 = 0;
uint16_t state2 = 0;
uint16_t state3 = 0;
uint16_t timer1 = 0;
uint16_t timer2 = 0;
uint16_t timer3 = 0;


/**
  * @brief  Init timer interrupt
  * @param  None
  * @retval None
  */
void timer_init(){
	HAL_TIM_Base_Start_IT(&htim2);
}


/**
  * @brief  Set duration of software timer interrupt
  * @param  duration Duration of software timer interrupt
  * @retval None
  */
void setTimer2(uint16_t duration){
	timer2_MUL = duration/TIMER_CYCLE_2;
	timer2_counter = timer2_MUL;
	flag_timer2 = 0;

	flag1=0;
	flag2=0;
	flag3=0;
	state1=0;
	state2=0;
	state3=0;
	timer1 = 2;
	timer2 = 2;
	timer3 = 5;
}

/**
  * @brief  Timer interrupt routine
  * @param  htim TIM Base handle
  * @note	This callback function is called by system
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		if(timer2_counter > 0){
			timer2_counter--;
			if(timer2_counter == 0) {
				flag_timer2 = 1;
				timer2_counter = timer2_MUL;
			}
		}
		if(timer1 > 0){
			timer1--;
			if(timer1 <= 0){
				flag1 = 1;
				timer1 = 2000;
			}
		}
		if(timer2 > 0){
			timer2--;
			if(timer2 <= 0){
				flag2 = 1;
				if(state2 == 0){
					timer2 = 2000;
				} else {
					timer2 = 4000;
				}
			}
		}
		if(timer3 > 0){
			timer3--;
			if(timer3 <= 0){
				flag3 = 1;
				if(state3 == 0){
					timer3 = 5000;
				} else {
					timer3 = 1000;
				}
			}
		}
		// 1ms interrupt here
		led7_Scan();
	}
}

