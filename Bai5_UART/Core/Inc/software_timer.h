/*
 * software_timer.h
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "tim.h"

extern uint16_t flag_timer2;

void timer_init();
void setTimer2(uint16_t duration);
void setTimerColon(uint16_t timer);
uint8_t isFlagColon();
void setTimerClock(uint16_t timer);
uint8_t isFlagClock();
uint8_t isTimer2Flag();

#endif /* INC_SOFTWARE_TIMER_H_ */
