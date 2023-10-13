/*
 * socket_mqtt.h
 *
 *  Created on: 11.10.2023
 *      Author: jpj1
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <cstdint>


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




#endif /* MAIN_H_ */
