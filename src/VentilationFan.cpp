/*
 * VentilationFan.cpp
 *
 *  Created on: 29.9.2023
 *      Author: Matias Näppä
 */

#include "ModbusRegister.h"
#include "VentilationFan.h"
#include <cstdio>

VentilationFan::VentilationFan(ModbusRegister *readRegister,
		ModbusRegister *writeRegister, int speed = 0, bool spinning = false) :
		status(readRegister), motor(writeRegister) {
}

VentilationFan::~VentilationFan() {
	// Auto-generated destructor stub
}

// When read periodically if the value is zero after two reads it means that the
// fan is stopped.

int VentilationFan::readFan() {
	//printf("Fan reading: %d\n", status->read());
	return status->read();
	if (status->read() == 0) { // delay needed?
		if (status->read() == 0) {
			return false;
		} else {
			return true;
		}
	} else {
		return true;
	}
}

void VentilationFan::setSpeed(float speed) {
	motor->write(speed*10);
}
