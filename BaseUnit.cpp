#include "BaseUnit.h"

BaseUnit::BaseUnit(int cordX, int cordY) {
    this->cordX = cordX;
    this->cordY = cordY;
    this->selected = false;
}

int BaseUnit::gerCordX() {
    return this->cordX;
}

int BaseUnit::getCordY() {
    return this->cordY;
}

void BaseUnit::setCordX(int cordX) {
    this->cordX = cordX;
}

void BaseUnit::setCordY(int cordY) {
    this->cordY = cordY;
}

bool BaseUnit::getSelected() {
    return this->selected;
}

void BaseUnit::setSelected(bool select) {
    this->selected = select;
}
