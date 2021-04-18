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

    struct Controller {
    public:
        Controller() = default;

        explicit Controller(MapGenerator::MinefieldPtr field);

        const std::unique_ptr<MapGenerator::Minefield> &GetMineField() const;

        std::unique_ptr<MapGenerator::Minefield> &GetShowedField();

        ~Controller();

        void Click();

        void Flag();

        void Question();

        void Hint();

        void CurLeftMov();

        void CurRightMov();

        void CurUpMov();

        void CurDownMov();

        void Draw();

    private:
        struct {
            uint16_t x = 0;
            uint16_t y = 0;
        } cursor;

        std::unique_ptr<MapGenerator::Minefield> minefield{nullptr};

        std::unique_ptr<MapGenerator::Minefield> showPlayerField{nullptr};

        void generateEmptyMap();

        bool isOut(uint16_t x, uint16_t y) const;

        bool isClickedMine() const;

        void finishGame(bool result);

        void printDebug(const std::string &par) const;
    };

    Controller *InitGame();

    void InGameProcess(Controller *controller);

    void FinishGame(Controller *controller);

}

#endif //MINESWEEPER_CONTROLLER_H
