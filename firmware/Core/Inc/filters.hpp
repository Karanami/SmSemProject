/**
  ******************************************************************************
  * @file           : filters.hpp
  * @brief          : different filters decelerations
  ******************************************************************************
  */

#ifndef INC_FILTERS_HPP_
#define INC_FILTERS_HPP_

#include "main.h"
#include "arm_math.h"

class KalmanFilter1D
{
	public:
		/*
		 * @brief Kalman filter constructor
		 * @param state transition matrix
		 * @param control input matrix
		 * @param standard deviation
		 * @param process noise co-variance
		 * @param measurement noise co-variance
		 * @param
		 */
		KalmanFilter1D(float A, float B, float P, float Q, float R, float H);

		/*
		 * @brief predict state
		 * @param control signal
		 * @retval none
		 */
		void predict(float u);
		/*
		 * @brief correct prediction
		 * @param real sensor measurement
		 * @retval none
		 */
		void correct(float y);
		/*
		 * @brief get predicted and corrected state ( current value )
		 * @retval predicted and corrected state
		 */
		float getPredition();

		float A = 0;
		float B = 0;
		float P = 0;
		float Q = 0;
		float R = 0;
		float H = 0;

	private:
		float x = 0;    //state
		float xp = 0;	//predicted state
};

class EmaLowPass
{
	public:
		/*
		 * @brief EMA Low pass filter constructor
		 * @param alpha coefficient
		 */
		EmaLowPass(float alpha);
		/*
		 * @brief EMA Low pass filter update
		 * @param sampled value
		 * @retval filter output
		 */
		float update(float x);

	private:
		float y = 0.f;
		float alpha = 0.5f;
		float beta = 0.5f;
};

#endif /* INC_FILTERS_HPP_ */
