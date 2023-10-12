/*
 * socket_mqtt.h
 *
 *  Created on: 11.10.2023
 *      Author: jpj1
 */

#ifndef SOCKET_MQTT_H_
#define SOCKET_MQTT_H_


void Sleep(int ms);

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */

uint32_t get_ticks(void);
#ifdef __cplusplus
}
#endif




#endif /* SOCKET_MQTT_H_ */
