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

int VentilationFan::readFan() {
	return status->read();
}

void VentilationFan::setSpeed(int speed) {
	if(speed > 100){
		speed = 100;
	}
	else if(speed < 0){
		speed = 0;
	}
	motor->write(speed * 10);
}

int VentilationFan::getSpeed() {
    return speed;
}
