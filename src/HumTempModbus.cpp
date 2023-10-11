#include "HumTempModbus.h"

HumTempModbus::HumTempModbus(uint8_t nodeAddress)
    : humTempNode(nodeAddress),
      HUM(&humTempNode, 256, false),
      TEMP(&humTempNode, 257, false),
      humTempStatus(&humTempNode, 512, false)
{
    humTempNode.begin(9600);
}

int HumTempModbus::getTemperature() {
	if(getStatus() == -1)
	{
		return -1;
	}
    return TEMP.read() / 10;
}

int HumTempModbus::getHumidity() {
	if(getStatus() == -1)
	{
		return -1;
	}
    return HUM.read() / 10;
}

int HumTempModbus::getStatus() {
	if(humTempStatus.read() != 1)
	{
		return -1;
	}
    return humTempStatus.read();
}


