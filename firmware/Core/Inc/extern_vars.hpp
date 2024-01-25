/*
 * extern_vars.hpp
 *
 *  Created on: Jan 24, 2024
 *      Author: user
 */

#ifndef INC_EXTERN_VARS_HPP_
#define INC_EXTERN_VARS_HPP_

#include "main.h"
#include "common.hpp"
#include "max11643.hpp"
#include "lsm6dsl.hpp"

#ifdef __cplusplus

extern GpioOut led1;
extern GpioOut led2;
extern GpioOut led3;
extern GpioOut led4;

extern GpioOut nm_sleep;
extern GpioOut m_right_direction;
extern GpioOut m_left_direction;

extern GpioOut spi_imu_ncs;
extern GpioIn spi_imu_int1;
extern GpioIn spi_imu_int2;

extern GpioOut spi_ex_ncs1;
extern GpioOut spi_ex_ncs2;
extern GpioIn spi_ex_int1;
extern GpioIn spi_ex_int2;

//extern constexpr float encoder_ratio;
extern Encoder left_encoder;
extern Encoder right_encoder;

extern PwmOut left_speed_ctrl;
extern PwmOut right_speed_ctrl;

extern Max11643 front_adc;

extern Lsm6dsl imu;

extern float anglspd1;
extern float anglspd2;

#endif

#endif /* INC_EXTERN_VARS_HPP_ */
