/*
 * Co2Modbus.cpp
 *
 *  Created on: 7.10.2023
 *      Author: Matias
 */

#include "Co2Modbus.h"

Co2Modbus::Co2Modbus(ModbusMaster* node, uint16_t co2Register, uint16_t statusRegister)
    : co2Register_(node, co2Register, false), statusRegister_(node, statusRegister, false) {
}

Co2Modbus::~Co2Modbus() {}

int Co2Modbus::getCo2Value() {
    int value = co2Register_.read();
    return (value >= 0) ? value : -1; // Return -1 on read error
}

int Co2Modbus::getStatus() {
    int status = statusRegister_.read();
    return (status == 0) ? 0 : -1; // Return -1 if status is not OK
}



