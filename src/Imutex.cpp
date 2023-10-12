/*
 * Imutex.cpp
 *
 *  Created on: 21.9.2023
 *      Author: jpj1
 */



// implementation of interrupt locking “mutex”
#include "chip.h"
#include "Imutex.hpp"

Imutex::Imutex() : enable(false)
{
}
Imutex::~Imutex()
{
}
void Imutex::lock()
{
 enable = (__get_PRIMASK() & 1) == 0;
 __disable_irq();
}
void Imutex::unlock()
{
 if(enable) __enable_irq();
}




