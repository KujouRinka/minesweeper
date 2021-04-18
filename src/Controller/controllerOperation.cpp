//
// Created by KujouRinka on 2021/4/7.
//

#include <iostream>
#include "Controller.h"

void Controller::Controller::printDebug(const std::string &par) const {
    std::cout << "\ryou " + par + " (" << cursor.x << ", " << cursor.y << ")" + std::string(10, ' ');
}

/**
 * This method helps to initialize user struct.
 *
 * @param field
 * A initialized Minefield
 */
Controller::Controller::Controller(MapGenerator::Minefield field) {
    minefield = field;
    showPlayerField = new MapGenerator::MField(minefield);
}

/**
 * This method use MineField to create map showing
 * to user.
 */

MapGenerator::Minefield
Controller::Controller::GetMineField() const {
    return minefield;
}

MapGenerator::Minefield
Controller::Controller::GetShowedField() {
    return showPlayerField;
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
    if (!isOut(cursor.x, cursor.y - 1))
        --cursor.y;
}

void Controller::Controller::CurRightMov() {
    if (!isOut(cursor.x, cursor.y + 1))
        ++cursor.y;
}

void Controller::Controller::CurUpMov() {
    if (!isOut(cursor.x - 1, cursor.y))
        --cursor.x;
}

void Controller::Controller::CurDownMov() {
    if (!isOut(cursor.x + 1, cursor.y))
        ++cursor.x;
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
    return x < 0 || x >= showPlayerField->GetLine() || y < 0 || y >= showPlayerField->GetRow();
}

bool Controller::Controller::isClickedMine() const {
    return (*GetMineField()->GetMap())[cursor.x][cursor.y] == 99;
}

void Controller::Controller::finishGame(bool result) {
    if (result)
        std::cout << "you win" << std::endl;
    else
        std::cout << "you lost" << std::endl;
    FinishGame(this);
}

void Controller::Controller::generateEmptyMap() {
    if (showPlayerField != nullptr)
        delete showPlayerField;
    showPlayerField = new MapGenerator::MField(minefield);
}

/**
 * Do clean work.
 *
 * needs to be overwritten.
 */
Controller::Controller::~Controller() {
    delete minefield;
    delete showPlayerField;
}

