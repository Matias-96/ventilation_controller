/*
 * VentilationSystem.h
 *
 *  Created on: 29.9.2023
 *      Author: jpj1
 */

#ifndef VENTILATIONSYSTEM_H_
#define VENTILATIONSYSTEM_H_

#include "VentilationFan.h"
#include "SDP610.h"
#include <cstdint>


class VentilationSystem{
public:
	enum ERROR{FAN_NOT_SPINNING = 0, PRESSURE_NOT_REACHED = 1, I2C_ERROR = 2};
	VentilationSystem(
			VentilationFan *_fan,
			SDP610 *_pressure_sensor,
			bool _auto_mode = false,
			int _target_pressure = 0);

	void tick();
	void adjust();
	void set_mode(bool mode);
	void set_speed(int speed);
	void set_target_pressure(int pressure);
	uint8_t error() const;
	int get_pressure() const;
	int get_speed() const;
	int get_target_pressure() const;
	bool get_mode() const;

private:
	VentilationFan *fan;
	SDP610 *pressure_sensor;
	bool auto_mode;
	int target_pressure;
	float fan_speed;
	int pressure;

	const int time_to_reach_target_pressure = 30000;
	uint8_t error_codes;
	volatile int counter;

	float last_error = 0;
	float last_integral = 0;
	int previous_fan_value = 0;


	void set_error(ERROR error);
	void unset_error(ERROR error);

};




#endif /* VENTILATIONSYSTEM_H_ */
