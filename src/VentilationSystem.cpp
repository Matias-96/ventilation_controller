/*
 * VentilationSystem.cpp
 *
 *  Created on: 29.9.2023
 *      Author: jpj1
 */


#include "VentilationSystem.h"

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
		pressure(0),
		error_codes(0),
		counter(0)
{

}


void VentilationSystem::tick(){
	counter++;
}

void VentilationSystem::adjust(){
	// In either of these conditions fan is supposed to spin
	if(( auto_mode && target_pressure > 0) || fan_speed > 0){
		int new_fan_value = fan->readFan();
		if(previous_fan_value == 0 && new_fan_value == 0)
			set_error(ERROR::FAN_NOT_SPINNING);
		else if(new_fan_value < 0)// Reading the status value failed, indicate error even though fan might be spinning
			set_error(ERROR::FAN_NOT_SPINNING);
		else
			unset_error(ERROR::FAN_NOT_SPINNING);
		previous_fan_value = new_fan_value;
	}
	else{
		unset_error(ERROR::FAN_NOT_SPINNING);
	}

	// Measure pressure and update running average value if reading is successful
	int i2c_error = 0;
	int measured_pressure = pressure_sensor->read(i2c_error);
	if(i2c_error){
		set_error(ERROR::I2C_ERROR);
	}
	else {
		unset_error(ERROR::I2C_ERROR);

		int sum = 0;
		// Calculate running average of previous pressure measurements
		for(int i = 0; i < pressure_count - 1; i++){
			prev_pressure_measurements[i] = prev_pressure_measurements[i+1]; // Shift values
			sum += prev_pressure_measurements[i];
		}
		prev_pressure_measurements[pressure_count - 1] = measured_pressure;
		pressure = (sum + measured_pressure) / pressure_count;
	}

	if(auto_mode){
		// Check if target pressure is reached in auto mode and update error status
		if(pressure == target_pressure){
			unset_error(ERROR::PRESSURE_NOT_REACHED);
			counter = 0;
		}
		else if(counter >= time_to_reach_target_pressure){
			set_error(ERROR::PRESSURE_NOT_REACHED);
		}

		// Adjust fan speed if reading pressure sensor was successful
		if(!i2c_error){
			if(target_pressure > 0){
				float KP = 0.25;
				float KI = 0.03;
				float KD = 0.4;
				float error = target_pressure - pressure;

				float integral = last_integral + error * 3;
				float derivative = (error - last_error) / 3;
				float output = KP*error + KI*integral + KD*derivative;
				last_error = error;
				last_integral = integral;

				if(output > 100.0){
					output = 100.0;
				}
				else if(output < 0){
					output = 0;
				}
				fan_speed = output;
				fan->setSpeed(fan_speed);
			}
			else {
				fan->setSpeed(0);
				fan_speed = 0;
			}
		}
	}
	// Manual mode
	else {
		fan->setSpeed(fan_speed);
	}

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

void VentilationSystem::set_target_pressure(int new_pressure){
	if(new_pressure < 0){
		new_pressure = 0;
	}
	else if(new_pressure > MAX_PRESSURE){
		new_pressure = MAX_PRESSURE;
	}

	// If system is stopped, give a "kick" to system so it starts to adjust fan faster
	if(auto_mode && target_pressure == 0){
		last_integral = 300;
	}

	target_pressure = new_pressure;
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

uint8_t VentilationSystem::pressure_error() const{
	if(error_codes & (1 << PRESSURE_NOT_REACHED)){
		return 1;
	}
	return 0;
}

uint8_t VentilationSystem::sensor_error()const {
	if(error_codes & (1 << I2C_ERROR)){
		return 1;
	}
	return 0;

}

uint8_t VentilationSystem::fan_error() const{
	if(error_codes & (1 << FAN_NOT_SPINNING)){
		return 1;
	}
	return 0;

}


