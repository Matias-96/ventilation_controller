/*
 * DecimalEdit.h
 *
 *  Created on: 2.10.2023
 *      Author: Matias
 */

#ifndef DECIMALEDIT_H_
#define DECIMALEDIT_H_

#include "PropertyEdit.h"
#include "LiquidCrystal.h"
#include <string>

class DecimalEdit: public PropertyEdit {
public:
	DecimalEdit(LiquidCrystal *lcd_, std::string editTitle, double minValue,
			double maxValue, double step);
	virtual ~DecimalEdit();
	void increment();
	void decrement();
	void accept();
	void cancel();
	void setFocus(bool focus);
	bool getFocus();
	void display();
	double getValue();
	void setValue(double value);

private:
	void save();
	void displayEditValue();
	LiquidCrystal *lcd;
	std::string title;
	double value;
	double edit;
	double minValue;
	double maxValue;
	double step;
	bool focus;
};

#endif /* DECIMALEDIT_H_ */
