/*
 * LogEdit.cpp
 *
 *  Created on: 11.10.2023
 *      Author: Matias
 */

// LogEdit.cpp

#include <LogEdit.h>

LogEdit::LogEdit(LiquidCrystal *lcd_, const std::string &editTitle, const std::vector<std::string> &options)
    : lcd(lcd_), title(editTitle), options(options), selectedIndex(0), focus(false) {
}

LogEdit::~LogEdit() {
}

void LogEdit::increment() {
    if (focus) {
        selectedIndex = (selectedIndex + 1) % options.size();
    }
}

void LogEdit::decrement() {
    if (focus) {
        selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
    }
}

void LogEdit::accept() {
    // Redundant
}

void LogEdit::cancel() {
    // Redundant
}

void LogEdit::setFocus(bool focus) {
    this->focus = focus;
}

bool LogEdit::getFocus() {
    return focus;
}

void LogEdit::display() {
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print(title);

    if (focus) {
        lcd->setCursor(0, 1);
        char status[6];
        snprintf(status, sizeof(status), ": %d", statusValues[selectedIndex]);
        lcd->print("-> " + options[selectedIndex] + status);
    } else {
        lcd->setCursor(0, 1);
    }
}

std::string LogEdit::getSelectedValue() {
    return options[selectedIndex];
}

void LogEdit::setValues(const std::vector<int> &values) {
    statusValues = values;
}




