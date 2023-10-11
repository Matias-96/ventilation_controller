/*
 * Button.cpp
 *
 *  Created on: 10.10.2023
 *      Author: jpj1
 */



#include "Button.h"

Button::Button(DigitalIoPin* _btn) : btn(_btn), last_state(false){

}


bool Button::read(){
	bool state = btn->read();
	bool return_value = state && !last_state;
	last_state = state;
	return return_value;
}


