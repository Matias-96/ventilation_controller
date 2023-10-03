
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
	if(HumpTmpBodbus.getStatus() == -1)
	{
		return "Error";
	}
    return TEMP.read() / 10;
}

int HumTempModbus::getHumidity() {
	if(HumpTmpBodbus.getStatus() == -1)
	{
		return "Error";
	}
    return HUM.read() / 10;
}

int HumTempModbus::getStatus() {
	if(HumpTempStatus.read() == -1)
	{
		return -1;
	}
	else if(HumpTempStatus.read() == 1){
		return -1;
	}
    return humTempStatus.read();
}
