/*
 * software_timer.h
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "tim.h"
#include "software_timer.h"

extern uint16_t flag_timer2;

extern uint16_t flag1;
extern uint16_t flag2;
extern uint16_t flag3;
extern uint16_t state1;
extern uint16_t state2;
extern uint16_t state3;
extern uint16_t timer1;
extern uint16_t timer2;
extern uint16_t timer3;

extern uint16_t ledState;
extern uint16_t ledFlag;

void timer_init();
void setTimer2(uint16_t duration);

#endif /* INC_SOFTWARE_TIMER_H_ */
