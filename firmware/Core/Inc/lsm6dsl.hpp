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

class Lsm6dsl
{
	public:
		Lsm6dsl(SPI_HandleTypeDef *hspi, GpioOut *ncs, GpioIn *it1, GpioIn *it2);

	private:
		SPI_HandleTypeDef *hspi;
		GpioOut *ncs;
		GpioIn *it1;
		GpioIn *it2;
};

#endif /* INC_LSM6DSL_HPP_ */