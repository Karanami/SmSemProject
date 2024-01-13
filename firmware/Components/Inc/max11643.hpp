/*
 * Max11643.hpp
 *
 *  Created on: Jan 13, 2024
 *      Author: Piotr Lesicki
 */

#ifndef INC_MAX11643_HPP_
#define INC_MAX11643_HPP_

#include "main.h"
#include "spi.h"
#include "common.hpp"

#include <array>
#include <atomic>

class Max11643
{
	public:
		Max11643(SPI_HandleTypedef *hspi, GpioOut *cs, GpioIn *it);

		void requestData();
		bool canRequest();
		uint8_t getChannelAdc(uint32_t channel);

	private:
		SPI_HandleTypedef *spi;
		GpioOut *cs;
		GpioIn *it;

		uint8_t data[16];

		std::atomic<bool> pending_req;
};


#endif /* INC_MAX11643_HPP_ */