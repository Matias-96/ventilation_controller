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
	VentilationSystem(
			VentilationFan *_fan,
			SDP610 *_pressure_sensor,
			MODE mode = MANUAL,
			int _fan_speed = 0,
			int _target_pressure = 0);

	enum MODE{AUTO, MANUAL};
	enum ERROR{FAN_NOT_SPINNING = 0, PRESSURE_NOT_REACHED = 1, I2C_ERROR = 2};

	void tick();
	void adjust();
	void set_mode(MODE mode);
	void set_speed(int speed);
	void set_target_pressure(int pressure);
	uint8_t error() const;
	int get_pressure() const;
	int get_speed() const;
	MODE get_mode() const;

private:
	VentilationFan *fan;
	SDP610 *pressure_sensor;
	MODE mode;
	int target_pressure;
	int pressure;
	int fan_speed;
	const int time_to_reach_target_pressure = 10000;
	volatile int counter;
	uint8_t error_codes;

	void set_error(ERROR error);
	void unset_error(ERROR error);

};




#endif /* VENTILATIONSYSTEM_H_ */
