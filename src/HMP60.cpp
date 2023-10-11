
#include <HMP60.h>
#include "socket_mqtt.h"

HMP60::HMP60(uint8_t nodeAddress)
    : humTempNode(nodeAddress),
      HUM(&humTempNode, 256, true),
      TEMP(&humTempNode, 257, true),
      humTempStatus(&humTempNode, 512, true)
{
    humTempNode.begin(9600);
}

int HMP60::getTemperature() {
	if(getStatus() == -1)
	{
		return -1;
	}
	Sleep(5);
    return TEMP.read() / 10;
}

int HMP60::getHumidity() {
	if(getStatus() == -1)
	{
		return -1;
	}
	Sleep(5);
    return HUM.read() / 10;
}
int HMP60::getStatus() {
	int status = humTempStatus.read();
	if(status != 1)
	{
		return -1;
	}
    return status;
}
