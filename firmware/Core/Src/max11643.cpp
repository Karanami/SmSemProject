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
	ncs->off();
	std::fill(tx_data_buff.begin(), tx_data_buff.end(), 0);
	for(auto& it : rx_data_buffs)
		std::fill(it.begin(), it.end(), 0);
};

void Max11643::init()
{
	// reset
	tx_data_buff[0] = 0b0001'0'000;
//	SpiDmaRequest request1 { &tx_data_buff[0], nullptr, 1, cs, nullptr };

	// setup - internal, ref always on
	tx_data_buff[1] = 0b01'10'10'00;
//	SpiDmaRequest request2 { &tx_data_buff[1],  nullptr, 1, cs, nullptr };

	// request scanning of channel 0 trough 15
//	tx_data_buff[2] = 0b1'1111'000;
//	SpiDmaRequest request3 { &tx_data_buff[2],  nullptr, 1, cs, &pending_req };

//	request1.send();
//	request2.send();
//	request3.send();

	SpiDmaRequest request { tx_data_buff.begin(), nullptr, 2, ncs, &pending_req };
	request.send();
}

void Max11643::readData()
{
	// intentional uint16* to uint8*
	SpiDmaRequest request1 { nullptr, (uint8_t*)(rx_data_buffs[current_data_index].data()), 32, ncs, nullptr };

//	// request scanning of channel 0 trough 15
//	tx_data_buff[0] = 0b1'1111'000;
//	SpiDmaRequest request2 { tx_data_buff.begin(), nullptr, 1, ncs, &pending_req };

	request1.send();
//	request2.send();
}

bool Max11643::canRead()
{
	return it->read();
}

void Max11643::requestData()
{
//	// intentional uint16* to uint8*
//	SpiDmaRequest request1 { nullptr, (uint8_t*)(rx_data_buffs[current_data_index].data()), 32, ncs, nullptr };

	// request scanning of channel 0 trough 15
	tx_data_buff[0] = 0b1'1111'000;
	SpiDmaRequest request2 { tx_data_buff.begin(), nullptr, 1, ncs, &pending_req };

//	request1.send();
	request2.send();
}

bool Max11643::canRequest()
{
	return !(pending_req || it->read());
}

const Max11643::array_type& Max11643::data()
{
	//size_t i = current_data_index;
	current_data_index ^= 1;
	return rx_data_buffs[current_data_index];
}
