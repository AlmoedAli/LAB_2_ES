/*
 * software_timer.c
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#include "software_timer.h"

#define TIMER_CYCLE_2 1


uint16_t flag_timer2 = 0;
uint16_t timer2_counter = 0;
uint16_t timer2_MUL = 0;

// lab 2_4
uint16_t timerColon = 0;
uint16_t flag_timerColon = 0;
uint16_t timerClock = 0;
uint16_t flag_timerClock = 0;

void timer_init(){
	HAL_TIM_Base_Start_IT(&htim2);
}

void setTimer2(uint16_t duration){
	timer2_MUL = duration/TIMER_CYCLE_2;
	timer2_counter = timer2_MUL;
	flag_timer2 = 0;
}

void setTimerColon(uint16_t timer)
{
	timerColon = timer;
	flag_timerColon = 0;
}

uint8_t isFlagColon()
{
	if(flag_timerColon == 1)
	{
		flag_timerColon = 0;
		return 1;
	}
	return 0;
}

void setTimerClock(uint16_t timer)
{
	timerClock = timer;
	flag_timerClock = 0;
}

uint8_t isFlagClock()
{
	if(flag_timerClock == 1)
	{
		flag_timerClock = 0;
		return 1;
	}
	return 0;
}

uint8_t isTimer2Flag()
{
	if(flag_timer2 == 1)
	{
		flag_timer2 = 0;
		return 1;
	}
	return 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		if(timer2_counter > 0){
			timer2_counter--;
			if(timer2_counter == 0) {
				flag_timer2 = 1;
				timer2_counter = timer2_MUL;
			}
		}
		if(timerColon > 0){
			timerColon--;
			if(timerColon == 0) {
				flag_timerColon = 1;
				timerColon = 250;
			}
		}
		if(timerClock > 0){
			timerClock--;
			if(timerClock == 0) {
				flag_timerClock = 1;
				timerClock = 1000;
			}
		}
	}
	led7_Scan();
}

