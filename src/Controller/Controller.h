//
// Created by KujouRinka on 2021/4/5.
//

/*
 * This package is used to process user operation
 */


#ifndef MINESWEEPER_CONTROLLER_H
#define MINESWEEPER_CONTROLLER_H

#include "../MapGenerator/MapGenerator.h"

namespace Controller {

    struct Player {
    public:
        Player() = default;

        explicit Player(MapGenerator::Minefield field);

    private:
        MapGenerator::Minefield minefield;
        MapGenerator::MField showPlayerField;

        void generateEmptyMap();
    };

    void InitGame(MapGenerator::Minefield minefield);

    void InGameProcess();

}

#endif //MINESWEEPER_CONTROLLER_H
