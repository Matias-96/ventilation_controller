/*
 * MonitorEdit.h
 *
 *  Created on: 11.10.2023
 *      Author: Matias
 */

#ifndef MONITOREDIT_H_
#define MONITOREDIT_H_

#include "LiquidCrystal.h"
#include "PropertyEdit.h"
#include <string>

class MonitorEdit : public PropertyEdit {
public:
    MonitorEdit(LiquidCrystal *lcd_, std::string unit1, std::string unit2, std::string unit3, std::string unit4);
    ~MonitorEdit();
    void setValues(int value1, int value2, int value3, int value4);
    int getValue(int valueNumber);

    void increment() override;
    void decrement() override;
    void accept() override;
    void cancel() override;
    void setFocus(bool focus) override;
    bool getFocus() override;
    void display() override;

private:
    LiquidCrystal *lcd;
    std::string units[4];
    int values[4];
};

#endif /* MONITOREDIT_H_ */


