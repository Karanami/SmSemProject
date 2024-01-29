/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main_task.cpp
  * @brief          : handles mission choosing and activation as well
  * 				  as other task's suspension and activation
  ******************************************************************************
  */

#include "FreeRTOS.h"
#include "task.h"
#include "extern_vars.hpp"
#include "app_freertos.h"
#include "main.h"
#include "cstring"
#include "algorithm"
#include "usart.h"
#include "array"

volatile static bool it_state;

static float duty_kek = 0.f;
char cmd[8] = { 0 };

char data [128] = { 0 };

void mainTaskEntry(void *argument)
{
	// engine init
	right_encoder.init();
	right_speed_ctrl.init();
	left_encoder.init();
	left_speed_ctrl.init();
	nm_sleep.off();

	// front init
	front_adc.init();

	//other init
	led1.off();
	led2.off();
	led3.off();
	led4.off();

	HAL_UART_Receive_IT(&hlpuart1, (uint8_t*)cmd, 5);

	//int i = 0;
	while(true)
	{
		size_t size = sprintf(data, "speed: %i, set_speed: %i\n\r", (uint32_t)speed, (uint32_t)set_speed);
		HAL_UART_Transmit(&hlpuart1, (uint8_t*)data, strlen(data), 100);
		left_speed_ctrl.setDuty(duty_kek);
		//it_state = spi_ex_int1.read();

		front_adc.init();
		front_adc.requestData();
		vTaskDelay(1);
		front_adc.readData();

		static std::array<float, 16> coefs = { -8, -7, -6, -5, -4, -3, -2, -1, 1, 2, 3, 4, 5, 6, 7, 8 };
		follow_deviation = 0;
		for(size_t i = 0; i < 16; i++)
		{
			uint16_t buff = (uint16_t)(front_adc.data()[i * 2]) << 8 | (uint16_t)(front_adc.data()[i * 2 + 1]);
			if (buff > 32)
			{
				follow_deviation += coefs[i];
			}
		}

		front_adc.data();

		led1.toggle();
		vTaskDelay(100);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(cmd[0] == 's' || cmd[0] == 'S')
	{
		int set = atoi(cmd + 1);
		set = std::clamp(set, 500, 3500);
		set_speed = (float)set;
	}
	HAL_UART_Receive_IT(&hlpuart1, (uint8_t*)cmd, 5);
}
