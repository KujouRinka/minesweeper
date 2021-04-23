//
// Created by KujouRinka on 2021/4/7.
//

#include <iostream>
#include <cstdlib>
#include "Controller.h"

#define DEBUG 0

void Controller::Controller::printDebug(const std::string &par, uint16_t x, uint16_t y) {
    std::cout << "you " + par + " ("
              << x << ", " << y
              << ")" + std::string(10, ' ');
    std::cout << this->getMineField()->GetMines() << " " << this->getShowedField()->GetMines() << std::endl;
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
Controller::Controller::getMineField() const {
    return this->minefield;
}

std::unique_ptr<MapGenerator::Minefield> &
Controller::Controller::getShowedField() {
    return this->showPlayerField;
}

/**
 * Receive and parse command and convert it to valid operation.
 * @param command
 * Int value, except a int value which can be converted to char.
 */
void Controller::Controller::SendCmd(int command) {
    switch (command) {
        case '1':   // click block
            this->click();
            break;
        case '2':   // flag block
            this->flag();
            break;
        case '3':   // question block
            this->question();
            break;
        case 75:
        case 'h':   // left move cursor
        case 'a':
            this->curLeftMov();
            break;
        case 80:
        case 'j':   // down move cursor
        case 's':
            this->curDownMov();
            break;
        case 72:
        case 'k':   // up move cursor
        case 'w':
            this->curUpMov();
            break;
        case 77:
        case 'l':   // right move cursor
        case 'd':
            this->curRightMov();
            break;
        case 'z':   // hint this block;
            this->hint();
            break;
        default:;
    }
    this->showMap();
    this->showCursor();
}

/**
 * This function is just a temporary solution to make output.
 * @param controller
 */
void Controller::Controller::showMap() {
    auto map = this->getShowedField()->GetMap();
    auto row = this->getMineField()->GetRow();
    auto line = this->getMineField()->GetLine();

    system("cls");
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < line; ++j) {
            uint8_t blockValue = (*map)[i][j];
            if (blockValue == MapGenerator::BLOCKTYPE::UNREVEALED)
                printf("  @");
            else if (blockValue == MapGenerator::BLOCKTYPE::FLAGGED)
                printf("  f");
            else if (blockValue == MapGenerator::BLOCKTYPE::QUESTIONED)
                printf("  ?");
            else if (blockValue == 0)
                printf("   ");
            else
                printf("%3d", (*map)[i][j]);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/**
 * Show where the cursor are.
 */
void Controller::Controller::showCursor() const {
    std::cout << "\rcursor at :("
              << this->cursor.x << ", " << this->cursor.y
              << ")";
}

/**
 * Do click block operation cursor pointing to.
 */
void Controller::Controller::click() {
    this->click(this->cursor.x, this->cursor.y);
}

/**
 * Do click block operation on specific block.
 * @param x
 * @param y
 */
void Controller::Controller::click(uint16_t x, uint16_t y) {

    if (isOut(x, y) || (*this->getShowedField()->GetMap())[x][y] == MapGenerator::BLOCKTYPE::FLAGGED)
        return;
    if (isClickedMine(x, y))   // clicked on mine.
        finishGame(false);
    // recalculate unrevealed block here.
    recursionClick(x, y);

    /* if meet this condition, player win. */
    if (getMineField()->GetMines() == getShowedField()->GetMines()) {
        this->showMap();    // show map before end this game.
        finishGame(true);
    }
}

/**
 * Do "flag" block operation.
 * If this is a "unflagged" block then flag it and vice versa.
 */
void Controller::Controller::flag() {
    uint8_t blockValue = (*this->getShowedField()->GetMap())[this->cursor.x][this->cursor.y];
    if (blockValue == MapGenerator::BLOCKTYPE::UNREVEALED) {
        (*this->getShowedField()->GetMap())[this->cursor.x][this->cursor.y] = MapGenerator::BLOCKTYPE::FLAGGED;
    } else if (blockValue == MapGenerator::BLOCKTYPE::FLAGGED) {
        (*this->getShowedField()->GetMap())[this->cursor.x][this->cursor.y] = MapGenerator::BLOCKTYPE::UNREVEALED;
    }
}

/**
 * Do "question" block operation.
 */
void Controller::Controller::question() {
    uint8_t blockValue = (*this->getShowedField()->GetMap())[this->cursor.x][this->cursor.y];
    if (blockValue == MapGenerator::BLOCKTYPE::UNREVEALED) {
        (*this->getShowedField()->GetMap())[this->cursor.x][this->cursor.y] = MapGenerator::BLOCKTYPE::QUESTIONED;
    } else if (blockValue == MapGenerator::BLOCKTYPE::QUESTIONED) {
        (*this->getShowedField()->GetMap())[this->cursor.x][this->cursor.y] = MapGenerator::BLOCKTYPE::UNREVEALED;
    }
}

/**
 * Auto click block around according flag surrounding.
 */
void Controller::Controller::hint() {
    uint8_t flagAround =
            MapGenerator::typeAround(this->cursor.x, this->cursor.y,
                                     this->getShowedField().get(), MapGenerator::BLOCKTYPE::FLAGGED);
    if (flagAround == (*this->getMineField()->GetMap())[this->cursor.x][this->cursor.y]) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (!(i == 0 && j == 0))
                    click(this->cursor.x + i, this->cursor.y + j);
            }
        }
    } else {
        // hint failed
    }
}

/**
 * Next four methods below are used to move cursor.
 */
void Controller::Controller::curLeftMov() {
    if (!isOut(this->cursor.x, this->cursor.y - 1))
        --this->cursor.y;
}

void Controller::Controller::curRightMov() {
    if (!isOut(this->cursor.x, this->cursor.y + 1))
        ++this->cursor.y;
}

void Controller::Controller::curUpMov() {
    if (!isOut(this->cursor.x - 1, this->cursor.y))
        --this->cursor.x;
}

void Controller::Controller::curDownMov() {
    if (!isOut(this->cursor.x + 1, this->cursor.y))
        ++this->cursor.x;
}

/**
 * Draw console.
 */
void Controller::Controller::draw() {

}

/**
 * Click a block and four blocks around it if no mine there.
 * @param x
 * @param y
 */
void Controller::Controller::recursionClick(uint16_t x, uint16_t y) {
    if (!isOut(x, y) && (*getShowedField()->GetMap())[x][y] == MapGenerator::BLOCKTYPE::UNREVEALED) {
        --getShowedField()->GetMines();
        (*getShowedField()->GetMap())[x][y] = (*getMineField()->GetMap())[x][y];
        if ((*getMineField()->GetMap())[x][y] == 0) {
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
    return (*getMineField()->GetMap())[x][y] == 99;
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
