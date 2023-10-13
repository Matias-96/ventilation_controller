/*
 * LogEdit.h
 *
 *  Created on: 11.10.2023
 *      Author: Matias
 */

// LogEdit.h

#ifndef LOGEDIT_H_
#define LOGEDIT_H_

#include <string>
#include <vector>
#include "PropertyEdit.h"
#include "LiquidCrystal.h"

class LogEdit : public PropertyEdit {
public:
    LogEdit(LiquidCrystal *lcd_, const std::string &editTitle, const std::vector<std::string> &options);
    ~LogEdit();
    void increment() override;
    void decrement() override;
    void accept() override;
    void cancel() override;
    void setFocus(bool focus) override;
    bool getFocus() override;
    void display() override;
    std::string getSelectedValue();
    void setValues(const std::vector<int> &values);

private:
    LiquidCrystal *lcd;
    std::string title;
    std::vector<std::string> options;
    std::vector<int> statusValues;
    int selectedIndex;
    bool focus;
};

#endif /* LOGEDIT_H_ */

