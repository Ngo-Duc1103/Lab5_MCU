/*
 * software_timer.c
 *
 *  Created on: Dec 21, 2023
 *      Author: HELLO
 */


#include "software_timer.h"

int timer_REPEAT_counter = 0;
int timer_REPEAT_flag = 0;
int timer_LED_counter = 0;
int timer_LED_flag = 0;
//int TIMER_CYCLE = 10;

void setTimer_REPEAT(int duration){
	timer_REPEAT_counter = duration;
	timer_REPEAT_flag = 0;
}
void setTimer_LED(int duration){
	timer_LED_counter = duration;
	timer_LED_flag = 0;
}

void timerRun(){
	if (timer_REPEAT_counter > 0){
		timer_REPEAT_counter--;
		if (timer_REPEAT_counter == 0) timer_REPEAT_flag = 1;
	}
	if (timer_LED_counter > 0){
		timer_LED_counter--;
		if(timer_LED_counter == 0) timer_LED_flag = 1;
	}
}
