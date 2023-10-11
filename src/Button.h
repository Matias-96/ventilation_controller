/*
 * Button.h
 *
 *  Created on: 10.10.2023
 *      Author: jpj1
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "DigitalIoPin.h"

class Button{
public:
	Button(DigitalIoPin* _btn);
	bool read();

private:
	DigitalIoPin *btn;
	bool last_state;
};





#endif /* BUTTON_H_ */
