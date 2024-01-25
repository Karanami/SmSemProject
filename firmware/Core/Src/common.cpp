/*
 * common.cpp
 *
 *  Created on: Jan 12, 2024
 *      Author: Piotr Lesicki
 */


#include "common.hpp"
#include <algorithm>
#include <stm32wbxx_ll_lptim.h>

//	┏┓  •  ┳
//	┃┓┏┓┓┏┓┃┏┓
//	┗┛┣┛┗┗┛┻┛┗
//	  ┛

GpioIn::GpioIn(GPIO_TypeDef *gpio, uint16_t pin) : gpio(gpio), pin(pin), inv(0) { }

GpioIn::GpioIn(GPIO_TypeDef *gpio, uint16_t pin, bool inv) : gpio(gpio), pin(pin), inv(inv ? pin : 0) { }

bool GpioIn::read()
{
	return bool((gpio->IDR & pin) ^ inv);
}

//	┏┓  •  ┏┓   
//	┃┓┏┓┓┏┓┃┃┓┏╋
//	┗┛┣┛┗┗┛┗┛┗┻┗
//	  ┛         

GpioOut::GpioOut(GPIO_TypeDef *gpio, uint16_t pin) : gpio(gpio), pin(pin), inv(0) { }

GpioOut::GpioOut(GPIO_TypeDef *gpio, uint16_t pin, bool inv) : gpio(gpio), pin(pin), inv(inv ? pin : 0) { }

void GpioOut::on()
{
	gpio->ODR = (gpio->ODR & ~inv) | (pin ^ inv);
}

void GpioOut::off()
{
	gpio->ODR = (gpio->ODR & ~(pin ^ inv)) | inv;
}

void GpioOut::toggle()
{
	gpio->ODR = gpio->ODR ^ pin;
}

//	┏┓      ┓
//	┣ ┏┓┏┏┓┏┫┏┓┏┓
//	┗┛┛┗┗┗┛┗┻┗ ┛
//

Encoder::Encoder(LPTIM_HandleTypeDef *hlptim, float ratio) : hlptim(hlptim), ratio(ratio)
{
	LL_LPTIM_EnableResetAfterRead(hlptim->Instance);
}

Encoder::Encoder(LPTIM_HandleTypeDef *hlptim, float gear_ratio, float encoder_ratio) : hlptim(hlptim), ratio(gear_ratio * encoder_ratio)
{
	LL_LPTIM_EnableResetAfterRead(hlptim->Instance);
}

void Encoder::init()
{
	HAL_LPTIM_Counter_Start(hlptim, 0xffff);
}

float Encoder::getAngleSpeed(float dt)
{
	return float(HAL_LPTIM_ReadCounter(hlptim)) * 2.f * 3.1415927f * ratio / dt;
}

//	┏┓      ┏┓
//	┃┃┓┏┏┏┳┓┃┃┓┏╋
//	┣┛┗┻┛┛┗┗┗┛┗┻┗
//

PwmOut::PwmOut(TIM_HandleTypeDef *tim, PwmOutCh channel) : tim(tim)
{
	switch (channel)
	{
	case PwmOutCh::_1:
		this->channel_cmp_reg = &TIM_TypeDef::CCR1;
		break;
	case PwmOutCh::_2:
		this->channel_cmp_reg = &TIM_TypeDef::CCR2;
		break;
	case PwmOutCh::_3:
		this->channel_cmp_reg = &TIM_TypeDef::CCR3;
		break;
	case PwmOutCh::_4:
		this->channel_cmp_reg = &TIM_TypeDef::CCR4;
		break;
	case PwmOutCh::_5:
		this->channel_cmp_reg = &TIM_TypeDef::CCR5;
		break;
	case PwmOutCh::_6:
		this->channel_cmp_reg = &TIM_TypeDef::CCR6;
		break;
	}
	this->channel = uint32_t(channel);
	arr = 1000;
	//HAL_TIM_PWM_Start(tim, uint32_t(channel));
}

void PwmOut::init()
{
	HAL_TIM_PWM_Start(tim, uint32_t(channel));
}
void PwmOut::setDuty(float duty)
{
	duty = std::clamp(duty, 0.f, 100.f);
	uint32_t cmp = uint32_t(arr * duty * 0.01);
	tim->Instance->*channel_cmp_reg = cmp;
}
