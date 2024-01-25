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
		GpioIn(GPIO_TypeDef *gpio, uint16_t pin);
		GpioIn(GPIO_TypeDef *gpio, uint16_t pin, bool inv);

		bool read();

	private:
		GPIO_TypeDef *gpio;
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
		GpioOut(GPIO_TypeDef *gpio, uint16_t pin);
		GpioOut(GPIO_TypeDef *gpio, uint16_t pin, bool inv);

		void on();
		void off();
		void toggle();

	private:
		GPIO_TypeDef *gpio;
		uint16_t pin;
		uint16_t inv;
};


//	┏┓  •  ┳┳┓•
//	┃┓┏┓┓┏┓┃┃┃┓┏┏
//	┗┛┣┛┗┗┛┛ ┗┗┛┗
//	  ┛

#define PORT(LABEL) 			(LABEL##_GPIO_Port)
#define PIN(LABEL) 				(LABEL##_Pin)

#define GPIO_OUT(LABEL, INV) 	GpioOut(PORT(LABEL), PIN(LABEL), INV)
#define GPIO_IN(LABEL, INV) 	GpioIn(PORT(LABEL), PIN(LABEL), INV)

//	┏┓      ┓
//	┣ ┏┓┏┏┓┏┫┏┓┏┓
//	┗┛┛┗┗┗┛┗┻┗ ┛
//

struct Encoder
{
	public:
		Encoder(LPTIM_HandleTypeDef *hlptim, float ratio);
		Encoder(LPTIM_HandleTypeDef *hlptim, float gear_ratio, float encoder_ratio);

		void init();
		float getAngleSpeed(float dt);

	private:
		LPTIM_HandleTypeDef *hlptim;
		float ratio;
};

//	┏┓      ┏┓
//	┃┃┓┏┏┏┳┓┃┃┓┏╋
//	┣┛┗┻┛┛┗┗┗┛┗┻┗
//

enum struct PwmOutCh : uint32_t
{
	_1 = TIM_CHANNEL_1,
	_2 = TIM_CHANNEL_2,
	_3 = TIM_CHANNEL_3,
	_4 = TIM_CHANNEL_4,
	_5 = TIM_CHANNEL_5,
	_6 = TIM_CHANNEL_6,
	//all = TIM_CHANNEL_ALL,
};

struct PwmOut
{
	public:
		PwmOut(TIM_HandleTypeDef *tim, PwmOutCh channel);

		void init();
		void setDuty(float duty);
	private:
		float arr;
		TIM_HandleTypeDef *tim;
		uint32_t channel;
		__IO uint32_t TIM_TypeDef::*channel_cmp_reg;
};

#endif /* INC_COMMON_HPP_ */
