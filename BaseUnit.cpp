#include "BaseUnit.h"

BaseUnit::BaseUnit() {
    this->cordX = 0;
    this->cordY = 0;
    this->name = "BaseUnit";
    this->selected = false;
}

BaseUnit::BaseUnit(int cordX, int cordY, std::string name) {
    this->cordX = cordX;
    this->cordY = cordY;
    this->name = name;
    this->selected = false;
}

int BaseUnit::getCordX() {
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

bool BaseUnit::getMoving() {
    return this->moving;
}

void BaseUnit::setMoving(bool move) {
    this->moving = move;
}

std::string BaseUnit::getName() {
    return this->name;
}
