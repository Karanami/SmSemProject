/*
 * mainThreadEntry.cpp
 *
 *  Created on: Jan 24, 2024
 *      Author: user
 */

#include "FreeRTOS.h"
#include "task.h"
#include "extern_vars.hpp"
#include "app_freertos.h"
#include "main.h"

void mainTaskEntry(void *argument)
{
	front_adc.init();
	right_encoder.init();
	left_encoder.init();

	int i = 0;
	while(1)
	{
		anglspd1 = right_encoder.getAngleSpeed(0.1f);
		anglspd2 = left_encoder.getAngleSpeed(0.1f);
		//left_speed_ctrl.setDuty((float)i);
		//right_speed_ctrl.setDuty((float)i);
		if(front_adc.canRequest())
			front_adc.requestData();
		if(front_adc.canRead())
			front_adc.readData();
		led1.toggle();
		vTaskDelay(1000);
		i++;
		if(i > 100) i = 0;
	}
}
