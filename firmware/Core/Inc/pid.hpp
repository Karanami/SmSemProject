/*
 * pid.hpp
 *
 *  Created on: Jan 28, 2024
 *      Author: lenovo
 */

#ifndef INC_PID_HPP_
#define INC_PID_HPP_

#include "arm_math.h"

class Pid
{
	public:
		/*
		 * @brief PID regulator instance constructor
		 * @param kp
		 * @param ki
		 * @param kd
		 * @param time period for the regulator
		 */
		explicit Pid(float kp, float ki, float kd, float dt);

		void setKp(float kp);
		void setKi(float ki, float dt);
		void setKd(float kd, float dt);

		float update(float error);
	private:
		arm_pid_instance_f32 pid_instance;

#ifdef DEBUG
		float _kp;
		float _ki;
		float _kd;
		float _dt;
#endif
};


#endif /* INC_PID_HPP_ */
