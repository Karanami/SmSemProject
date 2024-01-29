/**
  ******************************************************************************
  * @file           : dsp_callback.cpp
  * @brief          : dsp timer callback
  ******************************************************************************
  */

#include <filters.hpp>
#include "FreeRTOS.h"
#include "task.h"
#include "extern_vars.hpp"
#include "app_freertos.h"
#include "main.h"
#include "arm_math.h"
#include "pid.hpp"

static float period = (float)dsp_timer_period / 1000.f;

static float set_follow = 0.f;

static Pid speed_right_pid(0.10f, 0.02f, 0.004f, period);
static Pid speed_left_pid(speed_right_pid);
static Pid follow_pid(0.10f, 0.02f, 0.004f, period);

KalmanFilter1D speed_filter_right(1.f, 0.f, 100.f, 100.f, 9.f, 1); //period
KalmanFilter1D speed_filter_left(speed_filter_right);

EmaLowPass speed_filter_right_lp(0.45f);
EmaLowPass speed_filter_left_lp(speed_filter_right_lp);

//in ms
uint32_t dsp_timer_period = 50;

float set_speed = 500.f;
float speed;
float left_speed_duty;
float right_speed_duty;

float a_right = 0.f;
float a_left = 0.f;

float follow_deviation = 0.f;

float right_spd;
float left_spd;

void dspTimerCallback(void* arguments)
{
	float right_speed = right_encoder.getAngleSpeed(period);
	float left_speed = left_encoder.getAngleSpeed(period);

	right_speed = speed_filter_right_lp.update(right_speed);
	left_speed = speed_filter_left_lp.update(left_speed);
	speed_filter_right.predict(0.f);
	speed_filter_left.predict(0.f);
	speed_filter_right.correct(right_speed);
	speed_filter_left.correct(left_speed);
	right_spd = right_speed = speed_filter_right.getPredition();
	left_spd = left_speed	= speed_filter_left.getPredition();

	speed = right_speed;//(right_speed + left_speed) / 2;

//	float speed_error 		= set_speed - speed;
	float follow_error 		= set_follow - follow_deviation;

	float duty_diff	 		= follow_pid.update(follow_error);

	float left_speed_error 	= set_speed - left_speed;
	float right_speed_error = set_speed - right_speed;

	left_speed_duty 	= speed_left_pid.update(left_speed_error);
	right_speed_duty 	= speed_right_pid.update(right_speed_error);

	left_speed_duty 	+= duty_diff;
	right_speed_duty 	-= duty_diff;

	left_speed_ctrl.setDuty(left_speed_duty);
	right_speed_ctrl.setDuty(right_speed_duty);
}
