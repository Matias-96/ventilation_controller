/*
 * VentilationFan.h
 *
 *  Created on: 29.9.2023
 *      Author: Matias Näppä
 */

#ifndef VENTILATIONFAN_H_
#define VENTILATIONFAN_H_

#include "ModbusRegister.h"

class VentilationFan {
public:
	VentilationFan(ModbusRegister *readRegister, ModbusRegister *writeRegister,int speed, bool spinning);
	virtual ~VentilationFan();
	bool readFan();
	void setSpeed(float speed);
private:
	int speed;
	bool spinning;
	ModbusRegister *status; //readRegister
	ModbusRegister *motor; //writeRegister
};

#endif /* VENTILATIONFAN_H_ */
