/*
 * Button.cpp
 *
 *  Created on: 10.10.2023
 *      Author: jpj1
 */

#include "Button.h"

Button::Button(DigitalIoPin* _btn, bool _long_press, uint32_t _delay) :
	btn(_btn),
	btn_was_pressed(false),
	long_press(_long_press),
	delay(_delay),
	start_time(0)
{
}


bool Button::read(){
	bool btn_pressed = btn->read();
	bool state = btn_pressed && !btn_was_pressed;
	if(long_press){
		// Start delay timer if button was not pressed in previous cycle but now is is --> first press
		if(state){
			start_time = get_ticks();
		}
		// Return true if button is still pressed and delay has passed
		else if(btn_pressed && (get_ticks() - start_time) >= delay){
			state =  true;
		}
	}

	btn_was_pressed = btn_pressed;
	return state;
}


