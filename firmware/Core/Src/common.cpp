/**
  ******************************************************************************
  * @file           : common.cpp
  * @brief          : wrappers for basic control of the build in peripherals
  ******************************************************************************
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

Encoder::Encoder(LPTIM_HandleTypeDef *hlptim, float ratio) : hlptim(hlptim), ratio(ratio) { }

//Encoder::Encoder(LPTIM_HandleTypeDef *hlptim, float gear_ratio, float encoder_ratio) : hlptim(hlptim), ratio(gear_ratio * encoder_ratio) { }

void Encoder::init()
{
	HAL_LPTIM_Counter_Start(hlptim, 0xffff);
	LL_LPTIM_EnableResetAfterRead(hlptim->Instance);
	LL_LPTIM_Enable(hlptim->Instance);
	LL_LPTIM_StartCounter(hlptim->Instance, LL_LPTIM_OPERATING_MODE_CONTINUOUS);
}

float Encoder::getAngleSpeed(float dt)
{
	return float(HAL_LPTIM_ReadCounter(hlptim)) * ratio / dt * 60.f;
}

//	┏┓      ┏┓
//	┃┃┓┏┏┏┳┓┃┃┓┏╋
//	┣┛┗┻┛┛┗┗┗┛┗┻┗
//

PwmOut::PwmOut(TIM_HandleTypeDef *tim, PwmOutCh channel) : htim(tim)
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
	arr = 10000.f;
	//HAL_TIM_PWM_Start(tim, uint32_t(channel));
}

void PwmOut::init()
{
	HAL_TIM_PWM_Start(htim, uint32_t(channel));
}
void PwmOut::setDuty(float duty)
{
	duty = std::clamp(duty, 0.f, 100.f);
	uint32_t cmp = uint32_t(arr * duty * 0.01);
	htim->Instance->*channel_cmp_reg = cmp;
}
