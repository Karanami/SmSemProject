/*
 * pid.cpp
 *
 *  Created on: Jan 28, 2024
 *      Author: lenovo
 */

#include "pid.hpp"

Pid::Pid(float kp, float ki, float kd, float dt)
{
	pid_instance.Kp = kp;
	pid_instance.Ki = ki;// * dt;
	pid_instance.Kd = kd;// / dt;
	arm_pid_init_f32(&pid_instance, 1);
#ifdef DEBUG
	_kp = kp;
	_ki = ki;
	_kd = kd;
	_dt = dt;
#endif
}

void Pid::setKp(float kp)
{
	pid_instance.Kp = kp;
	arm_pid_init_f32(&pid_instance, 0);
#ifdef DEBUG
	_kp = kp;
#endif
}

void Pid::setKi(float ki, float dt)
{
	pid_instance.Ki = ki * dt;
	arm_pid_init_f32(&pid_instance, 0);
#ifdef DEBUG
	_ki = pid_instance.Ki;
#endif
}

void Pid::setKd(float kd, float dt)
{
	pid_instance.Kd = kd / dt;
	arm_pid_init_f32(&pid_instance, 0);
#ifdef DEBUG
	_kd = pid_instance.Kd;
#endif
}

float Pid::update(float error)
{
#ifdef DEBUG
//	if(pid_instance.Kp != _kp)
//	{
//		_kp = pid_instance.Kp;
//	}
//	if(pid_instance.Ki != _ki)
//	{
//		pid_instance.Ki = pid_instance.Ki * _dt;
//		_ki = pid_instance.Ki;
//	}
//	if(pid_instance.Ki != _ki)
//	{
//		pid_instance.Kd = pid_instance.Kd / _dt;
//		_kd = pid_instance.Kd;
//	}
	arm_pid_init_f32(&pid_instance, 0);
#endif

	return arm_pid_f32(&pid_instance, error);
}
