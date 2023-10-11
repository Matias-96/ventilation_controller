/*
 * MonitorEdit.cpp
 *
 *  Created on: 11.10.2023
 *      Author: Matias
 */

/*
 * MonitorEdit.cpp
 */

#include "MonitorEdit.h"

MonitorEdit::MonitorEdit(LiquidCrystal *lcd_, std::string unit1, std::string unit2, std::string unit3, std::string unit4) :
    lcd(lcd_) {
    units[0] = unit1;
    units[1] = unit2;
    units[2] = unit3;
    units[3] = unit4;

    for (int i = 0; i < 4; i++) {
        values[i] = 0;
    }
}

MonitorEdit::~MonitorEdit() {}

void MonitorEdit::setValues(int value1, int value2, int value3, int value4) {
    values[0] = value1;
    values[1] = value2;
    values[2] = value3;
    values[3] = value4;
}

int MonitorEdit::getValue(int valueNumber) {
    if (valueNumber >= 0 && valueNumber < 4) {
        return values[valueNumber];
    }
    return 0;
}

void MonitorEdit::increment() {}

void MonitorEdit::decrement() {}

void MonitorEdit::accept() {}

void MonitorEdit::cancel() {}

void MonitorEdit::setFocus(bool focus) {}

bool MonitorEdit::getFocus() {return false;}

void MonitorEdit::display() {
    lcd->clear();

    for (int i = 0; i < 2; i++) {
        lcd->setCursor(0, i);
        char s[17];
        snprintf(s, 17, "%s %d %s %d", units[i * 2].c_str(), values[i * 2], units[i * 2 + 1].c_str(), values[i * 2 + 1]);
        lcd->print(s);
    }
}

