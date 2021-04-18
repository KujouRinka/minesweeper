//
// Created by KujouRinka on 2021/4/7.
//

#include <iostream>
#include <cstdlib>
#include <conio.h>

#include "Controller.h"

/**
 * To start a game.
 *
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
 * Process user's operation while gaming.
 *
 * needs to be overwritten.
 */
void Controller::InGameProcess(Controller *controller) {
    /* should receive command here */
    int command;
    while ((command = getch()) != EOF && command != 'q') {    // read cmd from keyboard
        switch (command) {
            case '1':   // click block
                controller->Click();
                break;
            case '2':   // flag block
                controller->Flag();
                break;
            case '3':   // question block
                controller->Question();
                break;
            case 'h':   // left move cursor
            case 'a':
                controller->CurLeftMov();
                break;
            case 'l':   // right move cursor
            case 'd':
                controller->CurRightMov();
                break;
            case 'j':   // down move cursor
            case 's':
                controller->CurDownMov();
                break;
            case 'k':   // up move cursor
            case 'w':
                controller->CurUpMov();
                break;
            case 'z':   // hint this block;
                controller->Hint();
                break;
            default:;
        }
    }
}

/**
 * Do clean work to finish game.
 *
 * needs to be overwritten.
 */
void Controller::FinishGame(Controller *controller) {
    delete controller;
    exit(0);
}