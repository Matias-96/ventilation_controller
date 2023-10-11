/*
 * VentilationFan.h
 *
 *  Created on: 29.9.2023
 *      Author: Matias Näppä
 */

#include "ModbusRegister.h"

#ifndef VENTILATIONFAN_H_
#define VENTILATIONFAN_H_

class VentilationFan {
public:
	VentilationFan(ModbusRegister *readRegister, ModbusRegister *writeRegister, int speed, bool spinning);
	virtual ~VentilationFan();
	int readFan();
	void setSpeed(int speed);
	int getSpeed();
private:
	int speed;
	bool spinning;
	ModbusRegister *status; //readRegister
	ModbusRegister *motor; //writeRegister
};

#endif /* VENTILATIONFAN_H_ */
