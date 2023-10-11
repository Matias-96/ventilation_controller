/*
 * StringEdit.cpp
 *
 *  Created on: 7.10.2023
 *      Author: Matias
 */

#include "StringEdit.h"

StringEdit::StringEdit(LiquidCrystal *lcd_, const std::string &editTitle, const std::vector<std::string> &options)
    : lcd(lcd_), title(editTitle), options(options), selectedIndex(0), focus(false) {
}

StringEdit::~StringEdit() {
}

void StringEdit::increment() {
    if (focus) {
        selectedIndex = (selectedIndex + 1) % options.size();
    }
}

void StringEdit::decrement() {
    if (focus) {
        selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
    }
}

void StringEdit::accept() {
	// redundant
}

void StringEdit::cancel() {
    // redundant
}

void StringEdit::setFocus(bool focus) {
    this->focus = focus;
}

bool StringEdit::getFocus() {
    return focus;
}

void StringEdit::display() {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print(title);

    if (focus) {
        lcd->setCursor(0, 1);
        lcd->print("-> " + options[selectedIndex]);
    } else {
        lcd->setCursor(0, 1);
        lcd->print("   " + options[selectedIndex]);
    }
}

std::string StringEdit::getValue() {
    return options[selectedIndex];
}
