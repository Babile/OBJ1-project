#include "BaseUnit.h"

BaseUnit::BaseUnit() {
    this->cordX = 0;
    this->cordY = 0;
	this->moveCordX = 0;
	this->moveCordY = 0;
    this->name = "BaseUnit";
    this->selected = false;
}

BaseUnit::BaseUnit(int cordX, int cordY, std::string name) {
    this->cordX = cordX;
    this->cordY = cordY;
    this->name = name;
	this->moveCordX = 0;
	this->moveCordY = 0;
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

int BaseUnit::getDestinationClickCordX() {
	return this->moveCordX;
}

int BaseUnit::getDestinationClickCordY() {
	return this->moveCordY;
}

void BaseUnit::setDestinationClickCordX(int cordX) {
	this->moveCordX = cordX;
}

void BaseUnit::setDestinationClickCordY(int cordY) {
	this->moveCordY = cordY;
}

void BaseUnit::setMoveCordX(int cordX) {
	this->moveCordX = cordX;
}

void BaseUnit::setMoveCordY(int cordY) {
	this->moveCordY = cordY;
}

std::string BaseUnit::getName() {
    return this->name;
}
