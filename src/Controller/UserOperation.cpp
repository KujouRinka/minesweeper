//
// Created by KujouRinka on 2021/4/7.
//

#include <iostream>
#include <conio.h>

#include "Controller.h"

/**
 * To start a game.
 */
Controller::Controller *Controller::InitGame() {
    int method;     // ask player to decide default or custom.
    std::cout << "method:";     // need to add more details here
    std::cin >> method;
    MapGenerator::MinefieldPtr mField;
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
 * Receive command from keyboard then send it to a Controller.
 */
void Controller::InGameProcess(Controller *controller) {
    int command;
    controller->SendCmd('i');   // show unclicked map.
    while ((command = getch()) != EOF && command != 'q') {    // read cmd from keyboard
           controller->SendCmd(command);
    }
}

/**
 * Do clean work to finish game.
 *
 * needs to be overwritten.
 */
void Controller::FinishGame(Controller *controller) {
    delete controller;
}