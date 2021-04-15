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

    struct Controller {
    public:
        Controller() = default;

        explicit Controller(MapGenerator::Minefield field);

        ~Controller();


        void Click();

        void Flag();

        void Question();

    private:
        struct cursor {
            uint16_t x = 0;
            uint16_t y = 0;
        };

        // excepted to replace it by smart pointer.
        MapGenerator::Minefield minefield = nullptr;

        MapGenerator::Minefield showPlayerField = nullptr;

        void generateEmptyMap();
    };

    Controller *InitGame();

    void InGameProcess();

    void FinishGame(Controller *controller);

}

#endif //MINESWEEPER_CONTROLLER_H
