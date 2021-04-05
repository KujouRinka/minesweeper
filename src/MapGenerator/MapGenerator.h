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
        easy, normal, hard
    };

    struct MField {
        uint16_t row;
        uint16_t line;
        uint16_t numberOfMines;
        void *mineMap{};

        MField() = default;

        explicit MField(LEVEL level);

        MField(uint16_t cRow, uint16_t cLine, uint16_t cMines) :
                row(cRow), line(cLine), numberOfMines(cMines) {}
    };

    MField::MField(LEVEL level) {
        if (level == easy) {
            this->row = this->line = 9;
            this->numberOfMines = 10;
        } else if (level == normal) {
            this->row = this->line = 16;
            this->numberOfMines = 40;
        } else if (level == hard) {
            this->row = 16;
            this->line = 30;
            this->numberOfMines = 99;
        }
    }

    typedef MField *Minefield;

    void generateMine(Minefield emptyField);

    void pictureMap(Minefield minedField);

    Minefield coveredMap(Minefield minefield);

}

#endif //MINESWEEPER_RANDOMMINE_H
