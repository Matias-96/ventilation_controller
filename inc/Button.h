/*
 * Button.h
 *
 *  Created on: 10.10.2023
 *      Author: jpj1
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "DigitalIoPin.h"
#include <cstdint>
#include "main.h"

class Button{
public:
	Button(DigitalIoPin* _btn, bool _long_press = false, uint32_t _delay = 1000);
	bool read();

private:
	DigitalIoPin *btn;
	bool btn_was_pressed;
	bool long_press;
	uint32_t delay;
	uint32_t start_time;

};





#endif /* BUTTON_H_ */
