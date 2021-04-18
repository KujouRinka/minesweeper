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
    this->blocks = this->row * this->line;
    cleanMap();
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
    row = cRow;
    line = cLine;
    numberOfMines = cMines;
    blocks = cRow * cLine;
    cleanMap();
    generateMine(this);
}

/**
 * Use a initialize MField to generate map showing to user.
 *
 * @param initializedMap
 * A initialized Minefield
 */
MapGenerator::MField::MField(MapGenerator::MField *initializedMap) {
    row = initializedMap->row;
    line = initializedMap->line;
    blocks = initializedMap->blocks;
    numberOfMines = 0;
    cleanMap();
}

int MapGenerator::MField::GetRow() const {
    return row;
}

int MapGenerator::MField::GetLine() const {
    return line;
}

int MapGenerator::MField::GetMines() const {
    return numberOfMines;
}

int MapGenerator::MField::GetSize() const {
    return blocks;
}

MapGenerator::MField::Map *MapGenerator::MField::GetMap() const {
    return const_cast<Map *>(&mineMap);
}

void MapGenerator::MField::cleanMap() {
    for (auto &i : mineMap)
        std::fill(i.begin(), i.end(), 0);
}

MapGenerator::MField::~MField() {
    //delete mineMap;
    // do some clean work.
}
