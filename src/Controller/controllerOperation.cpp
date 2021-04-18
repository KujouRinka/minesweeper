//
// Created by KujouRinka on 2021/4/7.
//

#include <iostream>
#include "Controller.h"

void Controller::Controller::printDebug(const std::string &par) const {
    std::cout << "\ryou " + par + " ("
              << this->cursor.x << ", " << this->cursor.y
              << ")" + std::string(10, ' ');
}

/**
 * This method helps to initialize user struct.
 *
 * @param field
 * A initialized Minefield
 */
Controller::Controller::Controller(MapGenerator::Minefield field) {
    this->minefield = field;
    this->showPlayerField =
            new MapGenerator::MField(this->minefield);
}

/**
 * This method use MineField to create map showing
 * to user.
 */

MapGenerator::Minefield
Controller::Controller::GetMineField() const {
    return this->minefield;
}

MapGenerator::Minefield
Controller::Controller::GetShowedField() {
    return this->showPlayerField;
}

/**
 * Do click block operation.
 */
void Controller::Controller::Click() {
    printDebug("clicked");
    if (isClickedMine())
        finishGame(false);
    // recalculate block here.
    if (GetMineField()->GetMines() == GetShowedField()->GetSize() - GetShowedField()->GetMines())
        finishGame(true);
}

/**
 * Do "flag" block operation.
 */
void Controller::Controller::Flag() {
    printDebug("flagged");
}

/**
 * Do "question" block operation.
 */
void Controller::Controller::Question() {
    printDebug("questioned");
}

/**
 * Auto click block around according flag surrounding.
 */
void Controller::Controller::Hint() {
    printDebug("hint");
}

/**
 * Next four methods below are used to move cursor.
 */
void Controller::Controller::CurLeftMov() {
    if (!isOut(this->cursor.x, this->cursor.y - 1))
        --this->cursor.y;
}

void Controller::Controller::CurRightMov() {
    if (!isOut(this->cursor.x, this->cursor.y + 1))
        ++this->cursor.y;
}

void Controller::Controller::CurUpMov() {
    if (!isOut(this->cursor.x - 1, this->cursor.y))
        --this->cursor.x;
}

void Controller::Controller::CurDownMov() {
    if (!isOut(this->cursor.x + 1, this->cursor.y))
        ++this->cursor.x;
}

/**
 * Draw console.
 */
void Controller::Controller::Draw() {

}

/**
 * To check if next position of cursor move out of bounds.
 * @param x
 * @param y
 * @return
 */
bool Controller::Controller::isOut(uint16_t x, uint16_t y) const {
    return x < 0 || x >= this->showPlayerField->GetLine()
           || y < 0 || y >= this->showPlayerField->GetRow();
}

bool Controller::Controller::isClickedMine() const {
    return (*GetMineField()->GetMap())
           [this->cursor.x][this->cursor.y] == 99;
}

void Controller::Controller::finishGame(bool result) {
    if (result)
        std::cout << "you win" << std::endl;
    else
        std::cout << "you lost" << std::endl;
    FinishGame(this);
}

void Controller::Controller::generateEmptyMap() {
    if (this->showPlayerField != nullptr)
        delete this->showPlayerField;
    this->showPlayerField = new MapGenerator::MField(this->minefield);
}

/**
 * Do clean work.
 *
 * needs to be overwritten.
 */
Controller::Controller::~Controller() {
    delete this->minefield;
    delete this->showPlayerField;
}

