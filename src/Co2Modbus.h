/*
 * Co2Modbus.h
 *
 *  Created on: 7.10.2023
 *      Author: Matias
 */

#ifndef CO2_MODBUS_H
#define CO2_MODBUS_H

#include "ModbusMaster.h"
#include "ModbusRegister.h"

class Co2Modbus {
public:
	Co2Modbus(ModbusMaster *node, uint16_t co2Register,
			uint16_t statusRegister);
	~Co2Modbus();

	int getCo2Value();
	int getStatus();

private:
	ModbusRegister co2Register_;
	ModbusRegister statusRegister_;
};

#endif // CO2_MODBUS_H
