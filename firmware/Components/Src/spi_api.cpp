/*
 * spi_api.cpp
 *
 *  Created on: Jan 13, 2024
 *      Author: Piotr Lesicki
 */


#include <spi_api.hpp>
#include "tx_api.h"
#include <cstring>

//	┏┓  •┳┓     ┳┓          ┓┏     ┓┓
//	┗┓┏┓┓┃┃┏┳┓┏┓┣┫┏┓┏┓┓┏┏┓┏╋┣┫┏┓┏┓┏┫┃┏┓┏┓
//	┗┛┣┛┗┻┛┛┗┗┗┻┛┗┗ ┗┫┗┻┗ ┛┗┛┗┗┻┛┗┗┻┗┗ ┛
//	  ┛              ┗

class SpiDmaRequestHandler
{
	public:
		SpiDmaRequestHandler(const SpiDmaRequestHandler&) = delete;
		SpiDmaRequestHandler& operator=(SpiDmaRequestHandler const&) = delete;

		void putRequest(SpiDmaRequest const &request);
		constexpr SpiDmaRequest getRequest();

		constexpr SpiDmaRequestHandler * const getInstance();

	private:
		SpiDmaRequestHandler();

		TX_QUEUE queue;
		uint8_t data_pool[sizeof(SpiDmaRequest) * 8];

		static inline SpiDmaRequestHandler instance;
};

SpiDmaRequestHandler::SpiDmaRequestHandler()
{
	tx_queue_create(&this->queue, "sdh_queue", sizeof(SpiDmaRequest), (void*)data_pool, sizeof(data_pool));
}

constexpr SpiDmaRequestHandler * const SpiDmaRequestHandler::getInstance()
{
	return (SpiDmaRequestHandler const *)(&SpiDmaRequestHandler::instance);
}

void SpiDmaRequestHandler::putRequest(SpiDmaRequest const &request)
{
	tx_queue_send(&this->queue, (void*)&request, TX_NO_WAIT);
}

static SpiDmaRequestHandler *spi_dma_request_handler = SpiDmaRequestHandler::getInstance();

//	┏┓  •┳┓     ┳┓
//	┗┓┏┓┓┃┃┏┳┓┏┓┣┫┏┓┏┓┓┏┏┓┏╋
//	┗┛┣┛┗┻┛┛┗┗┗┻┛┗┗ ┗┫┗┻┗ ┛┗
//	  ┛              ┗

SpiDmaRequest::SpiDmaRequest(std::atomic<GpioOut> *cs, std::atomic<bool> *pending_request) : cs(cs), pending_request(pending_request) { }

void SpiDmaRequest::send()
{
	this->pending_request->store(true);
	spi_dma_request_handler->putRequest(*this);
}

//	┳
//	┃┏┓╋┏┓┏┓┏┓┓┏┏┓╋
//	┻┛┗┗┗ ┛ ┛ ┗┻┣┛┗
//				┛

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{

}