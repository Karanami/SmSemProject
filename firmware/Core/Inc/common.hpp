/**
  ******************************************************************************
  * @file           : common.h
  * @brief          : wrappers for basic control of the build in peripherals
  ******************************************************************************
  ******************************************************************************
  */

#ifndef INC_COMMON_HPP_
#define INC_COMMON_HPP_

#ifdef __cplusplus

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
		/**
		  * @brief GpioIn Constructor
		  * @param gpio - GPIO_TypeDef gpio's register
		  * @param pin - gpio pin
		  */
		GpioIn(GPIO_TypeDef *gpio, uint16_t pin);
		/**
		  * @brief GpioIn Constructor
		  * @param gpio - GPIO_TypeDef gpio's register
		  * @param pin - gpio pin
		  * @param inv - if true, 0 on the input would be interpreted as 1
		  */
		GpioIn(GPIO_TypeDef *gpio, uint16_t pin, bool inv);

		/**
		 * @brief read channel state
		 * @retval bool - value of the channel if inv was set to
		 * true return negated value
		 */
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
		/**
		  * @brief GpioOut Constructor
		  * @param gpio - GPIO_TypeDef gpio's register
		  * @param pin - gpio pin
		  */
		GpioOut(GPIO_TypeDef *gpio, uint16_t pin);
		/**
		  * @brief GpioIn Constructor
		  * @param gpio - GPIO_TypeDef gpio's register
		  * @param pin - gpio pin
		  * @param inv - if true, setting the channel ON will output 0 and
		  * setting the channel OFF will output 1
		  */
		GpioOut(GPIO_TypeDef *gpio, uint16_t pin, bool inv);
		/**
		 * @brief set channel logic state to HIGH, LOW if inv was set to true
		 * @retval none
		 */
		void on();
		/**
		 * @brief set channel logic state to LOW, HIGH if inv was set to true
		 * @retval none
		 */
		void off();
		/**
		 * @brief toggle the channel state
		 * @retval none
		 */
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
		/**
		  * @brief Encoder Constructor
		  * @param hlptim - LPTIM_HandleTypeDef lptimer handle
		  * @param ratio - encoder pulse count to wheel revolutions ratio
		  */
		Encoder(LPTIM_HandleTypeDef *hlptim, float ratio);
		//Encoder(LPTIM_HandleTypeDef *hlptim, float gear_ratio, float encoder_ratio);

		/**
		  * @brief Encoder initializer, initializes the rest of the
		  * perf, which couldn't be initialized in the constructor
		  * @retval none
		  */
		void init();
		/**
		  * @brief calculates current speed based on the timer input
		  * @param dt - value of the passed time in seconds
		  * @retval angle speed in rads per second
		  */
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
		/**
		  * @brief PwmOut Constructor
		  * @param htim - TIM_HandleTypeDef - timer handler
		  * @param channel - PwmOutCh - pwm channel _1 to _6
		  */
		PwmOut(TIM_HandleTypeDef *htim, PwmOutCh channel);

		/**
		  * @brief Encoder initializer, initializes the rest of the
		  * perf, which couldn't be initialized in the constructor
		  * @retval none
		  */
		void init();
		/**
		  * @brief pwm duty set as a percentage value
		  * @param duty value from 0.0f to 100.f
		  * @retval none
		  */
		void setDuty(float duty);
	private:
		float arr;
		TIM_HandleTypeDef *htim;
		uint32_t channel;
		__IO uint32_t TIM_TypeDef::*channel_cmp_reg;
};

#endif

#endif /* INC_COMMON_HPP_ */
