/*
 * lsm6dsl.cpp
 *
 *  Created on: Jan 17, 2024
 *      Author: Piotr Lesicki
 */


#include <lsm6dsl.hpp>

Lsm6dsl::Lsm6dsl(SPI_HandleTypeDef *hspi, GpioOut *ncs, GpioIn *it1, GpioIn *it2) : hspi(hspi), ncs(ncs), it1(it1), it2(it2)
{
	ncs->off();
}