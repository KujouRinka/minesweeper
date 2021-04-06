//
// Created by KujouRinka on 2021/4/5.
//

/*
 * This package is used to generate a MineField
*/

#ifndef MINESWEEPER_RANDOMMINE_H
#define MINESWEEPER_RANDOMMINE_H

#include <cstdint>

namespace MapGenerator {

    enum LEVEL {
        EASY, NORMAL, HARD
    };

    struct MField {
    public:
        uint16_t row;
        uint16_t line;
        uint16_t numberOfMines;
        void *mineMap{};

        MField() = default;

        explicit MField(LEVEL level);

        MField(uint16_t cRow, uint16_t cLine, uint16_t cMines);

    private:
        void generateEmptyMap();
    };

    typedef MField *Minefield;

    void generateMine(Minefield emptyField);

    void pictureMap(Minefield minedField);

    Minefield coveredMap(Minefield minefield);

}

#endif //MINESWEEPER_RANDOMMINE_H
