/*
 * VentilationSystem.cpp
 *
 *  Created on: 29.9.2023
 *      Author: jpj1
 */


#include "VentilationSystem.h"
#include <cmath>


VentilationSystem::VentilationSystem(
	VentilationFan *_fan,
	SDP610 *_pressure_sensor,
	bool _auto_mode,
	int _target_pressure) :
		fan(_fan),
		pressure_sensor(_pressure_sensor),
		auto_mode(_auto_mode),
		target_pressure(_target_pressure),
		fan_speed(0),
		error_codes(0),
		counter(0)
{

}


void VentilationSystem::tick(){
	counter++;
}

void VentilationSystem::adjust(){
	int i2c_error = 0;
	int measured_pressure = pressure_sensor->read(i2c_error);
	if(i2c_error){
		set_error(ERROR::I2C_ERROR);
	}
	else {
		unset_error(ERROR::I2C_ERROR);
		pressure = measured_pressure;
	}

	if(auto_mode && !i2c_error){
		if(measured_pressure >= target_pressure){
			unset_error(ERROR::PRESSURE_NOT_REACHED);
			counter = 0;
		}
		else if(counter >= time_to_reach_target_pressure){
			set_error(ERROR::PRESSURE_NOT_REACHED);
			counter = 0;
		}

		if(target_pressure > 0){
			float KP = 0.25;
			float KI = 0.09;
			float KD = 0.1;
			//float diff = target_pressure - measured_pressure;
			float error = target_pressure - measured_pressure;
			float integral = last_integral + error * 2;
			float derivative = (error - last_error) / 2;
			float output = KP*error + KI*integral + KD*derivative;
			last_error = error;
			last_integral = integral;
			fan_speed = output;

			//diff = diff / 2.0f;

			//if(target_pressure < 10 && fan_speed < 10){
			//	fan_speed += 10;
			//}
			//fan_speed += diff;
			if(fan_speed > 100.0){
				fan_speed = 100.0;
			}
			else if(fan_speed < 0){
				fan_speed = 0;
			}
			fan->setSpeed(fan_speed);
		}
		else {
			fan->setSpeed(0);
			fan_speed = 0;
		}
	}
	else {
		fan->setSpeed(fan_speed);
	}

	// In either of these conditions fan is supposed to spin
	if(target_pressure > 0 || fan_speed > 0){
		int new_fan_value = fan->readFan();
		if(previous_fan_value == 0 && new_fan_value == 0)
			set_error(ERROR::FAN_NOT_SPINNING);
		else
			unset_error(ERROR::FAN_NOT_SPINNING);
		previous_fan_value = new_fan_value;
	}
	else
		unset_error(ERROR::FAN_NOT_SPINNING);
}

void VentilationSystem::set_mode(bool mode){
	this->auto_mode = mode;
	counter = 0;
	if(!auto_mode){
		unset_error(ERROR::PRESSURE_NOT_REACHED);
	}
}

void VentilationSystem::set_speed(int speed){
	if(speed < 0){
		fan_speed = 0;
	}
	else if(speed > 100){
		fan_speed = 100;
	}
	else {
		fan_speed = speed;
	}
}

void VentilationSystem::set_target_pressure(int pressure){
	if(pressure < 0){
		target_pressure = 0;
	}
	else if(pressure > SDP610::MAX_PRESSURE_Pa){
		target_pressure = SDP610::MAX_PRESSURE_Pa;
	}
	else {
		target_pressure = pressure;
	}
}

uint8_t VentilationSystem::error() const{
	return error_codes;
}

int VentilationSystem::get_pressure() const{
	return pressure;
}

int VentilationSystem::get_speed() const{
	return fan_speed;
}

int VentilationSystem::get_target_pressure() const {
	return target_pressure;
}

bool VentilationSystem::get_mode() const {
	return auto_mode;
}

void VentilationSystem::set_error(ERROR error){
	error_codes |= 1 << error;
}

void VentilationSystem::unset_error(ERROR error){
	error_codes &= ~(1 << error);
}


