/*
 * FSM.c
 *
 *  Created on: Dec 21, 2023
 *      Author: HELLO
 */


#include "FSM.h"
#include "stdio.h"

uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer;

uint32_t ADC_value;
uint8_t str[30];

uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;

int commandStatus = WAITING;
int uartStatus = WAIT_SEND;

char* get_command(){
	return (char*) buffer;
}

void clear_command(){
	for (int i = 0; i < MAX_BUFFER_SIZE; i++){
		buffer[i] = '\0';
	}
	index_buffer = 0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART2){
		buffer_flag = 1;
		HAL_UART_Transmit(&huart2 , &temp, 1, 50);
		HAL_UART_Receive_IT(&huart2, &temp, 1);
	}
}

void command_parser_fsm(){
	switch (commandStatus) {
		case WAITING:
			if (temp == '!'){
				commandStatus = COMMAND;
			}
			break;

		case COMMAND:
			if (temp == '#'){
				commandStatus = WAITING;
				uartStatus = RESPONE;
			}
			else {
				buffer[index_buffer++] = temp;
				if (index_buffer >= MAX_BUFFER_SIZE){
					commandStatus = WAITING;
					clear_command();
				}
			}
			break;

		default:
			break;
	}
}

void uart_communication_fsm(){
	switch (uartStatus) {
		case WAIT_SEND:
			break;

		case RESPONE:
			if (strcmp(get_command(), "RST") == 0){
				ADC_value = HAL_ADC_GetValue(&hadc1);
				HAL_UART_Transmit(&huart2, (void *)str,  sprintf(str, "\r\n!ADC=%d#", ADC_value), 1000);
				uartStatus = REPEAT;
				clear_command();
				setTimer_REPEAT(300);
			}
			else {
				uartStatus = WAIT_SEND;
			}
			clear_command();
			break;

		case REPEAT:
			if (timer_REPEAT_flag == 1){
				ADC_value = HAL_ADC_GetValue(&hadc1);
				HAL_UART_Transmit(&huart2, (void*) str,  sprintf(str, "\r\n!ADC=%d#", ADC_value), 1000);
				setTimer_REPEAT(300);
			}
			if (strcmp(get_command(), "OK") == 0){
				uartStatus = WAIT_SEND;
			}
			break;

		default:
			break;
	}
}
