//
// Created by KujouRinka on 2021/4/5.
//

#include <random>
#include "MapGenerator.h"

/**
 * Use random header to generate some mines.
 * Write a fully initialize map to Controller::minefield
 *
 * @param emptyField
 * A pointer of MField which just initialize map size.
 * */
void MapGenerator::generateMine(Minefield emptyField) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> forRow(0, emptyField->GetRow() - 1);
    std::uniform_int_distribution<int> forLine(0, emptyField->GetLine() - 1);
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

    // This lambda is used to calculate mines around a block.
    auto mineAround = [map, emptyField](const uint16_t &row, const uint16_t &line) -> uint8_t {
        int mines = 0;
        for (int i = row - 1; i <= row + 1; ++i)
            for (int j = line - 1; j <= line + 1; ++j) {
                if (i >= 0 && j >= 0 && i < emptyField->GetRow() && j < emptyField->GetLine()) {
                    if (!(i == row && j == line) && (*map)[i][j] == 99) {
                        ++mines;
                    }
                }
            }
        return mines;
    };

    for (int i = 0; i < emptyField->GetRow(); ++i) {
        for (int j = 0; j < emptyField->GetLine(); ++j) {
            if ((*map)[i][j] != 99)
                (*map)[i][j] = mineAround(i, j);
        }
    }
}

void MapGenerator::pictureMap(Minefield minedField) {
    /* calculate quantity of mines around a block */
}

MapGenerator::Minefield
MapGenerator::coveredMap(Minefield minefield) {
    /* generate map that is shown to user */
    return nullptr;
}