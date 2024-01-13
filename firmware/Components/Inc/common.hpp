/*
 * common.hpp
 *
 *  Created on: Jan 12, 2024
 *      Author: Piotr Lesicki
 */

#ifndef INC_COMMON_HPP_
#define INC_COMMON_HPP_

#include "main.h"
#include "gpio.h"
#include "lptim.h"
#include "tim.h"

//	┏┓  •  ┳
//	┃┓┏┓┓┏┓┃┏┓
//	┗┛┣┛┗┗┛┻┛┗
//	  ┛

struct GpioIn
{
	public:
		GpioIn(const GPIO_Typedef *gpio, uint16_t pin);
		GpioIn(const GPIO_Typedef *gpio, uint16_t pin, bool inv);

		bool read();

	private:
		GPIO_Typedef *gpio;
		uint16_t pin;
		uint16_t inv;
};

//	┏┓  •  ┏┓
//	┃┓┏┓┓┏┓┃┃┓┏╋
//	┗┛┣┛┗┗┛┗┛┗┻┗
//	  ┛

struct GpioOut
{
	public:
		GpioOut(const GPIO_Typedef *gpio, uint16_t pin);
		GpioOut(const GPIO_Typedef *gpio, uint16_t pin, bool inv);

		void on();
		void off();
		void toggle();

	private:
		GPIO_Typedef *gpio;
		uint16_t pin;
		uint16_t inv;
};


//	┏┓  •  ┳┳┓•
//	┃┓┏┓┓┏┓┃┃┃┓┏┏
//	┗┛┣┛┗┗┛┛ ┗┗┛┗
//	  ┛

#define PORT(LABEL) LABEL##_GPIO_Port
#define PIN(LABEL) LABEL##Pin

//	┏┓      ┓
//	┣ ┏┓┏┏┓┏┫┏┓┏┓
//	┗┛┛┗┗┗┛┗┻┗ ┛
//

struct Encoder
{
	public:
		Encoder(const LPTIM_Typedef *lptim, float ratio);
		Encoder(const LPTIM_Typedef *lptim, float gear_ratio, float encoder_ratio);

		float getAngleSpeed();

	private:
		const LPTIM_Typedef *lptim;
		float ratio;
};

//	┏┓      ┏┓
//	┃┃┓┏┏┏┳┓┃┃┓┏╋
//	┣┛┗┻┛┛┗┗┗┛┗┻┗
//

enum struct PwmOutCh : uint32_t
{
	_1,
	_2,
	_3,
	_4,
	_5,
	_6
};

struct PwmOut
{
	public:
		PwmOut(const TIM_Typedef *tim, PwmOutCh channel);

		void setDuty(float duty);
	private:
		const TIM_Typedef *tim;
		uint32_t TIM_Typedef::*channel_cmp_reg;
};

#endif /* INC_COMMON_HPP_ */
