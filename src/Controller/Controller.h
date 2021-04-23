//
// Created by KujouRinka on 2021/4/5.
//

/*
 * This package is used to process user operation
 */


#ifndef MINESWEEPER_CONTROLLER_H
#define MINESWEEPER_CONTROLLER_H

#include <string>
#include <memory>

#include "draw.h"
#include "../MapGenerator/MapGenerator.h"

namespace Controller {

    struct Controller;

    Controller *InitGame();

    void InGameProcess(Controller *controller);

    void FinishGame(Controller *controller);

    struct Controller {
    public:
        Controller() = default;

        explicit Controller(MapGenerator::MinefieldPtr field);

        void SendCmd(int command);

    private:
        struct cursorS {
            uint16_t x = 0;
            uint16_t y = 0;
        } cursor;

        std::unique_ptr<MapGenerator::Minefield> minefield{nullptr};

        std::unique_ptr<MapGenerator::Minefield> showPlayerField{nullptr};

        const std::unique_ptr<MapGenerator::Minefield> &getMineField() const;

        std::unique_ptr<MapGenerator::Minefield> &getShowedField();

        void showMap();

        void showCursor() const;

        void click();

        void click(uint16_t x, uint16_t y);

        void flag();

        void question();

        void hint();

        void curLeftMov();

        void curRightMov();

        void curUpMov();

        void curDownMov();

        void draw();

        void recursionClick(uint16_t x, uint16_t y);

        bool isOut(uint16_t x, uint16_t y) const;

        bool isClickedMine(uint16_t x, uint16_t y) const;

        void finishGame(bool result);

        void generateEmptyMap();

        void printDebug(const std::string &par, uint16_t x, uint16_t y);
    };

}

#endif //MINESWEEPER_CONTROLLER_H
