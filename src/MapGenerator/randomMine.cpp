//
// Created by KujouRinka on 2021/4/5.
//

#include <random>
#include <ctime>
#include "MapGenerator.h"

/**
 * Use random header to generate some mines.
 * Write a fully initialize map to Controller::minefield
 *
 * @param emptyField
 * A pointer of MField which just initialize map size.
 * */
void MapGenerator::generateMine(MinefieldPtr emptyField) {
    std::default_random_engine generator(static_cast<uint_fast32_t>(time(nullptr)));
    std::uniform_int_distribution<uint16_t> forRow(0, emptyField->GetRow() - 1);
    std::uniform_int_distribution<uint16_t> forLine(0, emptyField->GetLine() - 1);
    uint16_t mines = emptyField->GetMines();
    uint16_t generated = 0;

    MapGenerator::MField::Map *map = emptyField->GetMap();
    while (generated < mines) {
        uint16_t row = forRow(generator);
        uint16_t line = forLine(generator);
        if ((*map)[row][line] != 0)
            continue;
        (*map)[row][line] = 99;
        generated++;
    }

    for (int i = 0; i < emptyField->GetRow(); ++i) {
        for (int j = 0; j < emptyField->GetLine(); ++j) {
            if ((*map)[i][j] != 99)
                (*map)[i][j] = typeAround(i, j, emptyField, BLOCKTYPE::MINE);
        }
    }
}

/**
 * This function is used to calculate mines around a block.
 */
uint8_t MapGenerator::typeAround(const uint16_t &row, const uint16_t &line,
                                 MinefieldPtr emptyField, BLOCKTYPE blockType) {
    MField::Map *map = emptyField->GetMap();
    int blocks = 0;
    for (int i = row - 1; i <= row + 1; ++i)
        for (int j = line - 1; j <= line + 1; ++j) {
            if (i >= 0 && j >= 0 && i < emptyField->GetRow() && j < emptyField->GetLine()) {
                if (!(i == row && j == line) && (*map)[i][j] == blockType) {
                    ++blocks;
                }
            }
        }
    return blocks;
}

void MapGenerator::pictureMap(MinefieldPtr minedField) {
    /* calculate quantity of mines around a block */
}

MapGenerator::MinefieldPtr
MapGenerator::coveredMap(MinefieldPtr minefield) {
    /* generate map that is shown to user */
    return nullptr;
}