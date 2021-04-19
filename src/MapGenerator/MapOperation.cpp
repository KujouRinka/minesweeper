//
// Created by KujouRinka on 2021/4/6.
//

// This file contains methods of struct MField

#include <algorithm>
#include "MapGenerator.h"

/**
 * This is default method to generate size of Minefield.
 * There are three level of difficulty.
 *
 * @param level
 * EASY: 9 * 9 with 10 mines
 * NORMAL: 16 * 16 with 40 mines
 * HARD: 16 * 30 with 99 mines
*/
MapGenerator::MField::MField(LEVEL level) {
    if (level == EASY) {
        this->row = this->line = 9;
        this->numberOfMines = 10;
    } else if (level == NORMAL) {
        this->row = this->line = 16;
        this->numberOfMines = 40;
    } else if (level == HARD) {
        this->row = 16;
        this->line = 30;
        this->numberOfMines = 99;
    } else {
        exit(1);
    }
    this->resetMap();
    generateMine(this);
}

/**
 * This constructor is used to generate customized Minefield.
 * Both max values of row and line are uint16.
 *
 * @param cRow
 * Row of Minefield
 *
 * @param cLine
 * Line of Minefield
 *
 * @param cMines
 * Quantity of mines
 *
 * @example:
 * MField(foo, bar, 42);
 * Generate a Minefield with size of foo * bar and 42 mines.
 */
MapGenerator::MField::MField(uint16_t cRow, uint16_t cLine,
                             uint16_t cMines) {
    this->row = cRow;
    this->line = cLine;
    this->numberOfMines = cMines;
    this->resetMap();
    generateMine(this);
}

/**
 * Use a initialize MField to generate map showing to user.
 *
 * @param initializedMap
 * A initialized Minefield
 */
MapGenerator::MField::MField(const MapGenerator::MField *initializedMap) {
    this->row = initializedMap->row;
    this->line = initializedMap->line;
    this->numberOfMines = this->row * this->line;
    this->resetMap(BLOCKTYPE::UNREVEALED);
}

int MapGenerator::MField::GetRow() const {
    return this->row;
}

int MapGenerator::MField::GetLine() const {
    return this->line;
}

int MapGenerator::MField::GetMines() const {
    return this->numberOfMines;
}

int &MapGenerator::MField::GetMines() {
    return reinterpret_cast<int &>(this->numberOfMines);
}

const MapGenerator::MField::Map *
MapGenerator::MField::GetMap() const {
    return const_cast<Map *>(&this->mineMap);
}

MapGenerator::MField::Map *
MapGenerator::MField::GetMap() {
    return &this->mineMap;
}

/**
 * Set all elements in mineMap to zero.
 */
void MapGenerator::MField::resetMap(uint8_t value) {
    for (auto &i : this->mineMap)
        std::fill(i.begin(), i.end(), value);
}

MapGenerator::MField::~MField() {
    // do some clean work.
}
