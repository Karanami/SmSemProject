/*
 * common.cpp
 *
 *  Created on: Jan 12, 2024
 *      Author: Piotr Lesicki
 */


#include "common.hpp"
#include <algorithm>

//	┏┓  •  ┳
//	┃┓┏┓┓┏┓┃┏┓
//	┗┛┣┛┗┗┛┻┛┗
//	  ┛

GpioIn::GpioIn(const GPIO_Typedef *gpio, uint16_t pin) : gpio(gpio), pin(pin), inv(0) { }

GpioIn::GpioIn(const GPIO_Typedef *gpio, uint16_t pin, bool inv) : gpio(gpio), pin(pin), inv(inv ? pin : 0) { }

inline bool GpioIn::read()
{
	return bool(gpio->IDR & pin ^ inv);
}

//	┏┓  •  ┏┓   
//	┃┓┏┓┓┏┓┃┃┓┏╋
//	┗┛┣┛┗┗┛┗┛┗┻┗
//	  ┛         

GpioOut::GpioOut(const GPIO_Typedef *gpio, uint16_t pin) : gpio(gpio), pin(pin), inv(0) { }

GpioOut::GpioOut(const GPIO_Typedef *gpio, uint16_t pin, bool inv) : gpio(gpio), pin(pin), inv(inv ? pin : 0) { }

inline void GpioOut::on()
{
	gpio->ODR = gpio->ODR & ~inv | (pin ^ inv);
}

inline void GpioOut::off()
{
	gpio->ODR = gpio->ODR & ~(pin ^ inv) | inv;
}

inline void GpioOut::toggle()
{
	gpio->ODR ^= pin;
}

//	┏┓      ┓
//	┣ ┏┓┏┏┓┏┫┏┓┏┓
//	┗┛┛┗┗┗┛┗┻┗ ┛
//

Encoder::Encoder(const LPTIM_Typedef *lptim, float ratio) : lptim(lptim), ratio(ratio)
{
	LL_LPTIM_EnableResetAfterRead(lptim);
}

Encoder::Encoder(const LPTIM_Typedef *lptim, float gear_ratio, float encoder_ratio) : lptim(lptim), ratio(gear_ratio * encoder_ratio)
{
	LL_LPTIM_EnableResetAfterRead(lptim);
}

inline float Encoder::getAngleSpeed()
{
	return float(LL_LPTIM_GetCounter(this->lptim)) * ratio;
}

//	┏┓      ┏┓
//	┃┃┓┏┏┏┳┓┃┃┓┏╋
//	┣┛┗┻┛┛┗┗┗┛┗┻┗
//

PwmOut::PwmOut(const TIM_Typedef *tim, PwmOutCh channel) : tim(tim)
{
	switch (channel)
	{
	case PwmOutCh::_1:
		this->channel_cmp_reg = &TIM_Typedef::CCR1;
		break;
	case PwmOutCh::_2:
		this->channel_cmp_reg = &TIM_Typedef::CCR2;
		break;
	case PwmOutCh::_3:
		this->channel_cmp_reg = &TIM_Typedef::CCR3;
		break;
	case PwmOutCh::_4:
		this->channel_cmp_reg = &TIM_Typedef::CCR4;
		break;
	case PwmOutCh::_5:
		this->channel_cmp_reg = &TIM_Typedef::CCR5;
		break;
	case PwmOutCh::_6:
		this->channel_cmp_reg = &TIM_Typedef::CCR6;
		break;
	}
}

void setDuty(float duty)
{
	duty = std::clamp(duty, 0.f, 100.f);
	uint32_t cmp = uint32_t(float(LL_TIM_GetAutoReload(tim)) * duty);
	tim->*channel_cmp_reg = cmp;
}