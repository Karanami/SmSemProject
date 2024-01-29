/*
 * spi_api.cpp
 *
 *  Created on: Jan 13, 2024
 *      Author: Piotr Lesicki
 */


#include "spi_api.hpp"

#include "FreeRTOS.h"
#include "queue.h"
#include "spi.h"
#include <cstring>
#include "common.hpp"

//	┏┓  •┳┓     ┳┓          ┓┏     ┓┓
//	┗┓┏┓┓┃┃┏┳┓┏┓┣┫┏┓┏┓┓┏┏┓┏╋┣┫┏┓┏┓┏┫┃┏┓┏┓
//	┗┛┣┛┗┻┛┛┗┗┗┻┛┗┗ ┗┫┗┻┗ ┛┗┛┗┗┻┛┗┗┻┗┗ ┛
//	  ┛              ┗

class SpiDmaRequestHandler
{
	public:
		SpiDmaRequestHandler() = delete;
		SpiDmaRequestHandler(const SpiDmaRequestHandler&) = delete;
		SpiDmaRequestHandler& operator=(SpiDmaRequestHandler const&) = delete;

		using Sdrh = SpiDmaRequestHandler;

		static void putRequest(SpiDmaRequest *request)
		{
			xQueueSend(Sdrh::queue, (void*)request, (TickType_t)0);
		}
		static void peekRequestFromISR(SpiDmaRequest *request)
		{
			xQueuePeekFromISR(Sdrh::queue, (void*)request);
		}
		static void getRequestFromISR(SpiDmaRequest *request)
		{
			xQueueReceiveFromISR(Sdrh::queue, (void*)request, nullptr);
		}
		static uint32_t requestCountFromISR()
		{
			return uxQueueMessagesWaitingFromISR(Sdrh::queue);
		}

	private:
		static inline StaticQueue_t static_queue;
		static inline uint8_t queue_stotage[sizeof(SpiDmaRequest) * 8];
		static inline char queue_name[32] = "SpiDmaReqHandleQueue";

		static inline QueueHandle_t queue = xQueueCreateStatic(8, sizeof(SpiDmaRequest), queue_stotage, &static_queue);
};

//	┏┓  •┳┓     ┳┓
//	┗┓┏┓┓┃┃┏┳┓┏┓┣┫┏┓┏┓┓┏┏┓┏╋
//	┗┛┣┛┗┻┛┛┗┗┗┻┛┗┗ ┗┫┗┻┗ ┛┗
//	  ┛              ┗

SpiDmaRequest::SpiDmaRequest(uint8_t *tx_data, uint8_t *rx_data, size_t size, GpioOut *cs, std::atomic<bool> *pending_request) : tx_data(tx_data), rx_data(rx_data), size(size), cs(cs), pending_request(pending_request) { }

void SpiDmaRequest::send()
{
	SpiDmaRequestHandler::putRequest(this);
	if(this->pending_request != nullptr)
	{
		this->pending_request->store(true);
	}
	if(hspi1.State == HAL_SPI_STATE_READY)
	{
		this->cs->on();
		if(this->tx_data != nullptr && this->rx_data != nullptr)
			HAL_SPI_TransmitReceive_DMA(&hspi1, this->tx_data, this->rx_data, this->size);
		else if(this->tx_data != nullptr)
			HAL_SPI_Transmit_DMA(&hspi1, this->tx_data, this->size);
		else if(this->rx_data != nullptr)
			HAL_SPI_Receive_DMA(&hspi1, this->rx_data, this->size);
	}
}

//	┳
//	┃┏┓╋┏┓┏┓┏┓┓┏┏┓╋
//	┻┛┗┗┗ ┛ ┛ ┗┻┣┛┗
//				┛

static void handleCallback(SPI_HandleTypeDef *hspi)
{
	SpiDmaRequest request_buff { nullptr, nullptr, 0, nullptr, nullptr };
	SpiDmaRequestHandler::getRequestFromISR(&request_buff);
	request_buff.cs->off();
	if(request_buff.pending_request != nullptr)
	{
		request_buff.pending_request->store(false);
	}
	if(SpiDmaRequestHandler::requestCountFromISR() != 0)
	{
		SpiDmaRequestHandler::peekRequestFromISR(&request_buff);
		request_buff.cs->on();
		if(request_buff.tx_data != nullptr && request_buff.rx_data != nullptr)
			HAL_SPI_TransmitReceive_DMA(&hspi1, request_buff.tx_data, request_buff.rx_data, request_buff.size);
		else if(request_buff.tx_data != nullptr)
			HAL_SPI_Transmit_DMA(&hspi1, request_buff.tx_data, request_buff.size);
		else if(request_buff.rx_data != nullptr)
			HAL_SPI_Receive_DMA(&hspi1, request_buff.rx_data, request_buff.size);
	}
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	handleCallback(hspi);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	handleCallback(hspi);
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
	handleCallback(hspi);
}

