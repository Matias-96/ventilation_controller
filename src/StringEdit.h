/*
 * StringEdit.h
 *
 *  Created on: 7.10.2023
 *      Author: Matias
 */

#ifndef STRINGEDIT_H_
#define STRINGEDIT_H_

#include <string>
#include <vector>
#include "PropertyEdit.h"
#include "LiquidCrystal.h"

class StringEdit : public PropertyEdit {
public:
    StringEdit(LiquidCrystal *lcd_, const std::string &editTitle, const std::vector<std::string> &options);
    ~StringEdit();
    void increment() override;
    void decrement() override;
    void accept() override;
    void cancel() override;
    void setFocus(bool focus) override;
    bool getFocus() override;
    void display() override;
    std::string getValue();

private:
    LiquidCrystal *lcd;
    std::string title;
    std::vector<std::string> options;
    int selectedIndex;
    bool focus;
};


#endif /* STRINGEDIT_H_ */
