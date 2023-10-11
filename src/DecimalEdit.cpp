/*
 * DecimalEdit.cpp
 *
 *  Created on: 2.10.2023
 *      Author: Matias
 */

#include "DecimalEdit.h"
#include <cstdio>

DecimalEdit::DecimalEdit(LiquidCrystal *lcd_, std::string editTitle,
		double minValue, double maxValue, double step) :
		lcd(lcd_), title(editTitle), minValue(minValue), maxValue(maxValue), step(
				step) {
	value = minValue;
	edit = minValue;
	focus = false;
}

DecimalEdit::~DecimalEdit() {}

void DecimalEdit::increment() {
	if (edit < maxValue) {
		edit += step;
	}
}

void DecimalEdit::decrement() {
	if (edit > minValue) {
		edit -= step;
	}
}

void DecimalEdit::accept() {
	save();
}

void DecimalEdit::cancel() {
	edit = value;
}

void DecimalEdit::setFocus(bool focus) {
	this->focus = focus;
}

bool DecimalEdit::getFocus() {
	return this->focus;
}

void DecimalEdit::display() {
	lcd->clear();
	lcd->setCursor(0, 0);
	lcd->print(title);
	char s[17];
	if (focus) {
		snprintf(s, 17, "     [%4.1f]     ", edit);
	} else {
		snprintf(s, 17, "      %4.1f      ", edit);
	}
	lcd->print(s);
}

void DecimalEdit::save() {
	value = edit;
}

double DecimalEdit::getValue() {
	return value;
}

void DecimalEdit::setValue(double value) {
	edit = value;
	save();
}

