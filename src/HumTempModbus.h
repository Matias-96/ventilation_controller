#ifndef HUMTEMPMODBUS_H_
#define HUMTEMPMODBUS_H_

#include "ModbusMaster.h"
#include "ModbusRegister.h"

class HumTempModbus {
private:
    ModbusMaster humTempNode;
    ModbusRegister HUM;
    ModbusRegister TEMP;
    ModbusRegister humTempStatus;

public:
    HumTempModbus(uint8_t nodeAddress = 241);
    int getTemperature();
    int getHumidity();
    int getStatus();
};

#endif  // HUMTEMPMODBUS_H_
