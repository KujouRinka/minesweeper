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
#include "../MapGenerator/MapGenerator.h"

namespace Controller {
    struct Controller;

    Controller *InitGame();

    void showMap(Controller *controller);

    void showCursor(Controller *controller);

    void InGameProcess(Controller *controller);

    void FinishGame(Controller *controller);

    struct Controller {
        friend void showCursor(Controller *controller);

    public:
        Controller() = default;

        explicit Controller(MapGenerator::MinefieldPtr field);

        const std::unique_ptr<MapGenerator::Minefield> &GetMineField() const;

        std::unique_ptr<MapGenerator::Minefield> &GetShowedField();

        void Click();

        void Click(uint16_t x, uint16_t y);

        void Flag();

        void Question();

        void Hint();

        void CurLeftMov();

        void CurRightMov();

        void CurUpMov();

        void CurDownMov();

        void Draw();

    private:
        struct cursorS {
            uint16_t x = 0;
            uint16_t y = 0;
        } cursor;

        std::unique_ptr<MapGenerator::Minefield> minefield{nullptr};

        std::unique_ptr<MapGenerator::Minefield> showPlayerField{nullptr};

        void generateEmptyMap();

        void recursionClick(uint16_t x, uint16_t y);

        void clickEight(uint16_t x, uint16_t y);

        bool isOut(uint16_t x, uint16_t y) const;

        bool isClickedMine(uint16_t x, uint16_t y) const;

        void finishGame(bool result);

        void printDebug(const std::string &par, uint16_t x, uint16_t y);
    };

}

#endif //MINESWEEPER_CONTROLLER_H
