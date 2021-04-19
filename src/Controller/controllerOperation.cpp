//
// Created by KujouRinka on 2021/4/7.
//

#include <iostream>
#include "Controller.h"

void Controller::Controller::printDebug(const std::string &par, uint16_t x, uint16_t y) {
    std::cout << "you " + par + " ("
              << x << ", " << y
              << ")" + std::string(10, ' ');
    std::cout << this->GetMineField()->GetMines() << " " << this->GetShowedField()->GetMines() << std::endl;
}

/**
 * This method helps to initialize Controller struct.
 *
 * @param field
 * A initialized Minefield
 */
Controller::Controller::Controller(MapGenerator::MinefieldPtr field) {
    this->minefield.reset(field);
    this->showPlayerField.reset(new MapGenerator::MField(this->minefield.get()));
}

/**
 * This method use MineField to create map showing
 * to user.
 */

const std::unique_ptr<MapGenerator::Minefield> &
Controller::Controller::GetMineField() const {
    return this->minefield;
}

std::unique_ptr<MapGenerator::Minefield> &
Controller::Controller::GetShowedField() {
    return this->showPlayerField;
}

/**
 * Do click block operation cursor pointing to.
 */
void Controller::Controller::Click() {
    this->Click(this->cursor.x, this->cursor.y);
}

/**
 * Do click block operation on specific block.
 * @param x
 * @param y
 */
void Controller::Controller::Click(uint16_t x, uint16_t y) {

    if (isOut(x, y))
        return;
    if (isClickedMine(x, y))
        finishGame(false);
    // recalculate unrevealed block here.
    recursionClick(x, y);

    printDebug("clicked", this->cursor.x, this->cursor.y);

    /* if meet this condition, player win. */
    if (GetMineField()->GetMines() == GetShowedField()->GetMines())
        finishGame(true);
}

/**
 * Do "flag" block operation.
 * If this is a "unflagged" block then flag it and vice versa.
 */
void Controller::Controller::Flag() {
    uint8_t blockValue = (*GetShowedField()->GetMap())[this->cursor.x][this->cursor.y];
    if (blockValue == MapGenerator::BLOCKTYPE::UNREVEALED) {
        printDebug("flagged", this->cursor.x, this->cursor.y);
        (*GetShowedField()->GetMap())[this->cursor.x][this->cursor.y] = MapGenerator::BLOCKTYPE::FLAGGED;
    } else if (blockValue == MapGenerator::BLOCKTYPE::FLAGGED) {
        printDebug("unflagged", this->cursor.x, this->cursor.y);
        (*GetShowedField()->GetMap())[this->cursor.x][this->cursor.y] = MapGenerator::BLOCKTYPE::UNREVEALED;
    }
}

/**
 * Do "question" block operation.
 */
void Controller::Controller::Question() {

    uint8_t blockValue = (*GetShowedField()->GetMap())[this->cursor.x][this->cursor.y];
    if (blockValue == MapGenerator::BLOCKTYPE::UNREVEALED) {
        (*GetShowedField()->GetMap())[this->cursor.x][this->cursor.y] = MapGenerator::BLOCKTYPE::QUESTIONED;
        printDebug("questioned", this->cursor.x, this->cursor.y);
    } else if (blockValue == MapGenerator::BLOCKTYPE::QUESTIONED) {
        (*GetShowedField()->GetMap())[this->cursor.x][this->cursor.y] = MapGenerator::BLOCKTYPE::UNREVEALED;
        printDebug("unquestioned", this->cursor.x, this->cursor.y);
    }
}

/**
 * Auto click block around according flag surrounding.
 */
void Controller::Controller::Hint() {
    // this function has some problem.
    printDebug("hint", this->cursor.x, this->cursor.y);

    uint8_t flagAround =
            MapGenerator::typeAround(this->cursor.x, this->cursor.y,
                                     this->GetShowedField().get(), MapGenerator::BLOCKTYPE::FLAGGED);
    if (flagAround == (*this->GetMineField()->GetMap())[this->cursor.x][this->cursor.y]) {
        std::cout << "hint success" << std::endl;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (!(i == 0 && j == 0) &&
                    (*this->GetShowedField()->GetMap())[this->cursor.x + i][this->cursor.y + j] != 99) {
                    this->Click(this->cursor.x + i, this->cursor.y + j);
                }
            }
        }
    } else {
        std::cout << "hint fail" << std::endl;
    }
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
 * Click a block and four blocks around it if no mine there.
 * @param x
 * @param y
 */
void Controller::Controller::recursionClick(uint16_t x, uint16_t y) {
    if (!isOut(x, y) && (*GetShowedField()->GetMap())[x][y] == MapGenerator::BLOCKTYPE::UNREVEALED) {
        --GetShowedField()->GetMines();
        (*GetShowedField()->GetMap())[x][y] = (*GetMineField()->GetMap())[x][y];
        if ((*GetMineField()->GetMap())[x][y] == 0) {
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if (!(i == 0 && j == 0)) {
                        recursionClick(x + i, y + j);
                    }
                }
            }
        }
    }
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

bool Controller::Controller::isClickedMine(uint16_t x, uint16_t y) const {
    return (*GetMineField()->GetMap())[x][y] == 99;
}

void Controller::Controller::finishGame(bool result) {
    std::cout << std::endl;
    if (result)
        std::cout << "you win" << std::endl;
    else
        std::cout << "you lost" << std::endl;
    FinishGame(this);
}

void Controller::Controller::generateEmptyMap() {
    this->showPlayerField.reset(new MapGenerator::MField(this->minefield.get()));
}
