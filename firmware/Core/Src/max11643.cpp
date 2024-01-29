/*
 * max11643.cpp
 *
 *  Created on: Jan 13, 2024
 *      Author: Piotr Lesicki
 */


#include "max11643.hpp"
#include "spi_api.hpp"
#include "common.hpp"

Max11643::Max11643(SPI_HandleTypeDef *hspi, GpioOut *ncs, GpioIn *it) : hspi(hspi), ncs(ncs), it(it), pending_req(false)
{
	std::fill(tx_data_buff.begin(), tx_data_buff.end(), 0);
	for(auto& it : rx_data_buffs)
		std::fill(it.begin(), it.end(), 0);
};

void Max11643::init()
{
	// reset
	tx_data_buff[0] = 0b0001'0'000;

	// setup - external, ref off
	tx_data_buff[1] = 0b01'10'01'00;

	// avg - external, ref off
	tx_data_buff[2] = 0b001'0'00'00;

	SpiDmaRequest request1 { tx_data_buff.begin() + 0, nullptr, 1, ncs, &pending_req };
	request1.send();
	SpiDmaRequest request2 { tx_data_buff.begin() + 1, nullptr, 1, ncs, &pending_req };
	request2.send();
	SpiDmaRequest request3 { tx_data_buff.begin() + 2, nullptr, 1, ncs, &pending_req };
	request3.send();
}

void Max11643::readData()
{
	// intentional uint16* to uint8*
	SpiDmaRequest request { nullptr, rx_data_buffs[current_data_index].begin(), 32, ncs, nullptr };

	request.send();
}

bool Max11643::canRead()
{
	return it->read();
}

void Max11643::requestData()
{
	// clear fifo
	tx_data_buff[0] = 0b0001'1'000;
	// request scanning of channel 0 trough 15
	tx_data_buff[1] = 0b1'1111'00'0;

	SpiDmaRequest request1 { tx_data_buff.begin() + 0, nullptr, 1, ncs, &pending_req };
	request1.send();
	SpiDmaRequest request2 { tx_data_buff.begin() + 1, nullptr, 1, ncs, &pending_req };
	request2.send();
}

bool Max11643::canRequest()
{
	return !(pending_req || it->read());
}

const Max11643::array_type& Max11643::data()
{
	//size_t i = current_data_index;
	//current_data_index ^= 1;
	return rx_data_buffs[current_data_index];
}
