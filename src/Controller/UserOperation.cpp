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
    int command;
    while ((command = getch()) != EOF) {    // read cmd from keyboard
        switch (command) {
            case '1':   // click block
                break;
            case '2':   // flag block
                break;
            case '3':   // question block
                break;
            case 'h':   // left move cursor
            case 'a':
                break;
            case 'l':   // right move cursor
            case 'd':
                break;
            case 'j':   // down move cursor
            case 's':
                break;
            case 'k':   // up move cursor
            case 'w':
                break;
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
}