/**
  ******************************************************************************
  * @file           : kalman_filter.cpp
  * @brief          : kalman filters declarations
  ******************************************************************************
  */

#include <filters.hpp>

KalmanFilter1D::KalmanFilter1D(float A, float B, float P, float Q, float R, float H) : A(A), B(B), P(P), Q(Q), R(R), H(H) { }

void KalmanFilter1D::predict(float u)
{
	xp = A * x + B * u;
	P = A * P * A + Q;
}

void KalmanFilter1D::correct(float y)
{
	float e = H * xp;
	float E = H * P * H;
	float z = y - e;
	float Z = R + E;
	float K = P * H / Z;

	x = xp + K * z;
	P = P - K * H * P;
}

float KalmanFilter1D::getPredition()
{
	return x;
}

EmaLowPass::EmaLowPass(float alpha)
{
	this->alpha = alpha;
	this->beta = 1 - alpha;
}

float EmaLowPass::update(float x)
{
	y = alpha * x + beta * y;
	return y;
}
