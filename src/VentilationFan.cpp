/*
 * VentilationFan.cpp
 *
 *  Created on: 29.9.2023
 *      Author: Matias Näppä
 */

#include "ModbusRegister.h"
#include "VentilationFan.h"

VentilationFan::VentilationFan(ModbusRegister *readRegister,
		ModbusRegister *writeRegister, int speed = 0, bool spinning = false) :
		status(readRegister), motor(writeRegister) {
}

VentilationFan::~VentilationFan() {
	// Auto-generated destructor stub
}

// When read periodically if the value is zero after two reads it means that the
// fan is stopped.

bool VentilationFan::readFan() {
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

void VentilationFan::setSpeed(int speed) {
	motor->write(speed);
}

int VentilationFan::getSpeed() {
    return speed;
}
