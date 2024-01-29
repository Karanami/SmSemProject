/**
  ******************************************************************************
  * @file           : fir.hpp
  * @brief          : fir wrapper
  ******************************************************************************
  */

#ifndef INC_FIR_HPP_
#define INC_FIR_HPP_

#include "arm_math.h"

class Fir
{
	public:
		Fir();

		float update();

	private:
		arm_fir_instance_f32 instance;
};


#endif /* INC_FIR_HPP_ */
