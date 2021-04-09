//
// Created by KujouRinka on 2021/4/7.
//

#include <iostream>
#include <cstdlib>
#include "Controller.h"

/**
 * To start a game.
 *
 */
Controller::Controller *Controller::InitGame() {
    int method;     // ask player to decide default or custom.
    std::cout << "method:";     // need to add more details here
    std::cin >> method;
    MapGenerator::Minefield mField;
    Controller *controller;
    std::cout << "mine:";
    switch (method) {
        case 0:
            int row, line, mine;
            std::cin >> row >> line >> mine;
            mField = new MapGenerator::MField(row, line, mine);
            break;
        case 1:
            int diff;
            std::cin >> diff;
            mField = new MapGenerator::MField(static_cast<MapGenerator::LEVEL>(diff));
            break;
        default:
            exit(1);
    }
    controller = new Controller(mField);
    return controller;
}

/**
 * Process user's operation while gaming.
 *
 * needs to be overwritten.
 */
void Controller::InGameProcess() {
 /* should receive command here */
}

/**
 * Do clean work to finish game.
 *
 * needs to be overwritten.
 */
void Controller::FinishGame(Controller *controller) {
    delete controller;
}