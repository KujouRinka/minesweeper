//
// Created by KujouRinka on 2021/4/5.
//

/*
 * This package is used to generate a MineField
*/

#ifndef MINESWEEPER_RANDOMMINE_H
#define MINESWEEPER_RANDOMMINE_H

namespace MapGenerator {

    struct MField{
        uint16_t width;
        uint16_t length;
        uint16_t numberOfMines;
        void *mineMap{};
    };

    typedef MField *Minefield;

    void generateMine(Minefield emptyField);

    void pictureMap(Minefield minedField);

    Minefield coveredMap(Minefield minefield);

}

#endif //MINESWEEPER_RANDOMMINE_H
