/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbxx_hal.h"

#include "stm32wbxx_ll_system.h"
#include "stm32wbxx_ll_gpio.h"
#include "stm32wbxx_ll_exti.h"
#include "stm32wbxx_ll_bus.h"
#include "stm32wbxx_ll_cortex.h"
#include "stm32wbxx_ll_rcc.h"
#include "stm32wbxx_ll_utils.h"
#include "stm32wbxx_ll_pwr.h"
#include "stm32wbxx_ll_dma.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define QSPI_IO1_Pin LL_GPIO_PIN_8
#define QSPI_IO1_GPIO_Port GPIOB
#define QSPI_IO0_Pin LL_GPIO_PIN_9
#define QSPI_IO0_GPIO_Port GPIOB
#define M_LEFT_A_Pin LL_GPIO_PIN_0
#define M_LEFT_A_GPIO_Port GPIOC
#define VBAT_Pin LL_GPIO_PIN_2
#define VBAT_GPIO_Port GPIOC
#define IMU_INT1_Pin LL_GPIO_PIN_3
#define IMU_INT1_GPIO_Port GPIOC
#define LED1_Pin LL_GPIO_PIN_0
#define LED1_GPIO_Port GPIOA
#define LED2_Pin LL_GPIO_PIN_1
#define LED2_GPIO_Port GPIOA
#define QSPI_NCS_Pin LL_GPIO_PIN_2
#define QSPI_NCS_GPIO_Port GPIOA
#define QSPI_CLK_Pin LL_GPIO_PIN_3
#define QSPI_CLK_GPIO_Port GPIOA
#define QSPI_IO3_Pin LL_GPIO_PIN_6
#define QSPI_IO3_GPIO_Port GPIOA
#define QSPI_IO2_Pin LL_GPIO_PIN_7
#define QSPI_IO2_GPIO_Port GPIOA
#define M_LEFT_PWM_Pin LL_GPIO_PIN_8
#define M_LEFT_PWM_GPIO_Port GPIOA
#define M_LEFT_DIRECTION_Pin LL_GPIO_PIN_9
#define M_LEFT_DIRECTION_GPIO_Port GPIOA
#define LED3_Pin LL_GPIO_PIN_5
#define LED3_GPIO_Port GPIOC
#define LED4_Pin LL_GPIO_PIN_2
#define LED4_GPIO_Port GPIOB
#define UART_RX_Pin LL_GPIO_PIN_10
#define UART_RX_GPIO_Port GPIOB
#define UART_TX_Pin LL_GPIO_PIN_11
#define UART_TX_GPIO_Port GPIOB
#define NM_SLEEP_Pin LL_GPIO_PIN_0
#define NM_SLEEP_GPIO_Port GPIOB
#define M_RIGHT_A_Pin LL_GPIO_PIN_1
#define M_RIGHT_A_GPIO_Port GPIOB
#define IMU_INT2_Pin LL_GPIO_PIN_4
#define IMU_INT2_GPIO_Port GPIOE
#define M_RIGHT_DIRECTION_Pin LL_GPIO_PIN_6
#define M_RIGHT_DIRECTION_GPIO_Port GPIOC
#define M_RIGHT_PWM_Pin LL_GPIO_PIN_10
#define M_RIGHT_PWM_GPIO_Port GPIOA
#define SPI_EX_NCS1_Pin LL_GPIO_PIN_10
#define SPI_EX_NCS1_GPIO_Port GPIOC
#define SPI_EX_NCS2_Pin LL_GPIO_PIN_11
#define SPI_EX_NCS2_GPIO_Port GPIOC
#define SPI_EX_INT1_Pin LL_GPIO_PIN_12
#define SPI_EX_INT1_GPIO_Port GPIOC
#define SPI_EX_INT2_Pin LL_GPIO_PIN_0
#define SPI_EX_INT2_GPIO_Port GPIOD
#define SPI_SCK_Pin LL_GPIO_PIN_3
#define SPI_SCK_GPIO_Port GPIOB
#define SPI_MOSI_Pin LL_GPIO_PIN_4
#define SPI_MOSI_GPIO_Port GPIOB
#define SPI_MISO_Pin LL_GPIO_PIN_5
#define SPI_MISO_GPIO_Port GPIOB
#define SPI_IMU_NCS_Pin LL_GPIO_PIN_7
#define SPI_IMU_NCS_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
