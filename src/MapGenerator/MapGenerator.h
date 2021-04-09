//
// Created by KujouRinka on 2021/4/5.
//

/*
 * This package is used to generate a MineField
*/

#ifndef MINESWEEPER_MAPGENERATOR_H
#define MINESWEEPER_MAPGENERATOR_H

#include <cstdint>
#include <array>

namespace MapGenerator {

    enum LEVEL {
        EASY, NORMAL, HARD
    };

    struct MField {
    public:

        typedef std::array<std::array<uint8_t, 30>, 30> Map;

        MField() = default;

        explicit MField(LEVEL level);

        explicit MField(MField *initializedMap);

        MField(uint16_t cRow, uint16_t cLine, uint16_t cMines);

        int GetRow() const;

        int GetLine() const;

        int GetMines() const;

        Map *GetMap() const;

        ~MField();

    private:
        uint16_t row;
        uint16_t line;
        uint16_t numberOfMines;
        uint16_t questioned = 0;
        Map mineMap{};

        void cleanMap();
    };

    typedef MField *Minefield;

    void generateMine(Minefield emptyField);

    void pictureMap(Minefield minedField);

    Minefield coveredMap(Minefield minefield);

}

#endif //MINESWEEPER_MAPGENERATOR_H
