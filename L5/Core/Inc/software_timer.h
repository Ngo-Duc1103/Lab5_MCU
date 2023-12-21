/*
 * software_timer.h
 *
 *  Created on: Dec 21, 2023
 *      Author: HELLO
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer_REPEAT_flag;
extern int timer_LED_flag;

void setTimer_REPEAT(int duration);
void setTimer_LED(int duration);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
