/*
 * Max11643.hpp
 *
 *  Created on: Jan 13, 2024
 *      Author: Piotr Lesicki
 */

#ifndef INC_MAX11643_HPP_
#define INC_MAX11643_HPP_

#ifdef __cplusplus

#include "main.h"
#include "spi.h"
#include "common.hpp"

#include <array>
#include <atomic>

class Max11643
{
	public:
		/**
		 * @brief Max11643 Constructor
		 * @param hspi - spi handle
		 * @param ncs - slave select
		 * @param it - slave's select interrupt
		 */
		Max11643(SPI_HandleTypeDef *hspi, GpioOut *ncs, GpioIn *it);

		using array_type = std::array<uint8_t, 32>;

		/**
		  * @brief Max11643 initializer, initializes the rest of the
		  * perf, which couldn't be initialized in the constructor
		  * @retval none
		  */
		void init();
		/**
		  * @brief request data from slave
		  * @retval none
		  */
		void requestData();
		/**
		  * @brief checks if new data can be requested
		  * @retval bool - new data can be requested
		  */
		bool canRequest();
		/**
		  * @brief reads data form slave
		  * @retval none
		  */
		void readData();
		/**
		  * @brief checks if data is ready to be read from slave
		  * @retval bool - new data can be read
		  */
		bool canRead();
		/**
		  * @brief get raw data
		  * @retval const array_type& - raw data const reference
		  */
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

#endif

#endif /* INC_MAX11643_HPP_ */
