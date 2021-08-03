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
        EASY, NORMAL, HARD,
    };

    enum BLOCKTYPE {
        EMPTY = 0,
        MINE = 99,
        QUESTIONED = 253,
        FLAGGED = 254,
        UNREVEALED = 255,
    };

    struct MField {
    public:
        typedef std::array<std::array<uint8_t, 30>, 30> Map;

        MField() = default;

        explicit MField(LEVEL level);
        explicit MField(const MField *initializedMap);
        MField(uint16_t cRow, uint16_t cLine, uint16_t cMines);

        int GetRow() const;
        int GetLine() const;
        int GetMines() const;
        int &GetMines();
        const Map *GetMap() const;
        Map *GetMap();

    private:
        uint16_t row;   // Row of minefield
        uint16_t line;  // Line of minefield

        /*
         * numberOfMine has two different meaning.
         * In minefield: number of mine.
         * In showPlayerField: unrevealed blocks.
         */
        uint16_t numberOfMines;
        uint16_t questioned = 0;
        Map mineMap{};  // Minefield map

        void resetMap(uint8_t value=BLOCKTYPE::EMPTY);
    };

    typedef MField Minefield;
    typedef MField *MinefieldPtr;

    void generateMine(MinefieldPtr emptyField);

    uint8_t typeAround(const uint16_t &row, const uint16_t &line,
                       MinefieldPtr emptyField, BLOCKTYPE blockType);

    void pictureMap(MinefieldPtr minedField);
    MinefieldPtr coveredMap(MinefieldPtr minefield);

}

#endif //MINESWEEPER_MAPGENERATOR_H
