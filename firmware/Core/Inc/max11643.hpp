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
		Max11643(SPI_HandleTypeDef *hspi, GpioOut *ncs, GpioIn *it);

		using array_type = std::array<uint16_t, 16>;

		void init();
		void requestData();
		bool canRequest();
		void readData();
		bool canRead();
		const array_type& data();

	private:
		SPI_HandleTypeDef *hspi;
		GpioOut *ncs;
		GpioIn *it;

		std::array<array_type, 2> rx_data_buffs;
		//array_type tx_data_buff;
		std::array<uint8_t, 16> tx_data_buff;
		size_t current_data_index = 0;

		std::atomic<bool> pending_req;
};


#endif /* INC_MAX11643_HPP_ */
