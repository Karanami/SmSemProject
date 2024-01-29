/*
 * lsm6dsl.hpp
 *
 *  Created on: Jan 13, 2024
 *      Author: Piotr Lesicki
 */

#ifndef INC_LSM6DSL_HPP_
#define INC_LSM6DSL_HPP_

#include "main.h"
#include "spi.h"
#include "common.hpp"

#ifdef __cplusplus

class Lsm6dsl
{
	public:
		/**
		  * @brief Lsm6dsl Constructor
		  * @param hspi - SPI_HandleTypeDef - spi handle
		  * @param ncs - slave select gpio
		  * @param it1 - slave's first interrupt signal
		  * @param it2 - slave's second interrupt signal
		  */
		Lsm6dsl(SPI_HandleTypeDef *hspi, GpioOut *ncs, GpioIn *it1, GpioIn *it2);

		/**
		  * @brief Lsm6dsl initializer, initializes the rest of the
		  * perf, which couldn't be initialized in the constructor
		  * @retval none
		  */
		void init();
	private:
		SPI_HandleTypeDef *hspi;
		GpioOut *ncs;
		GpioIn *it1;
		GpioIn *it2;
};

#endif

#endif /* INC_LSM6DSL_HPP_ */
