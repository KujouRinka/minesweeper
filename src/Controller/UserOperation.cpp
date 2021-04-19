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
 * This function is just a temporary solution to make output.
 * @param controller
 */
void Controller::showMap(Controller *controller) {
    auto map = controller->GetShowedField()->GetMap();
    auto row = controller->GetMineField()->GetRow();
    auto line = controller->GetMineField()->GetLine();

    system("cls");
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < line; ++j) {
            uint8_t blockValue = (*map)[i][j];
            if (blockValue == MapGenerator::BLOCKTYPE::UNREVEALED)
                printf("  @");
            else if (blockValue == MapGenerator::BLOCKTYPE::FLAGGED)
                printf("  f");
            else if (blockValue == MapGenerator::BLOCKTYPE::QUESTIONED)
                printf("  ?");
            else
                printf("%3d", (*map)[i][j]);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Controller::showCursor(Controller *controller) {
    std::cout << "\rcursor at :("
              << controller->cursor.x << ", " << controller->cursor.y
              << ")";
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
                showMap(controller);
                break;
            case '2':   // flag block
                controller->Flag();
                showMap(controller);
                break;
            case '3':   // question block
                controller->Question();
                showMap(controller);
                break;
            case 'h':   // left move cursor
            case 'a':
                controller->CurLeftMov();
                showCursor(controller);
                break;
            case 'l':   // right move cursor
            case 'd':
                controller->CurRightMov();
                showCursor(controller);
                break;
            case 'j':   // down move cursor
            case 's':
                controller->CurDownMov();
                showCursor(controller);
                break;
            case 'k':   // up move cursor
            case 'w':
                controller->CurUpMov();
                showCursor(controller);
                break;
            case 'z':   // hint this block;
                controller->Hint();
                showMap(controller);
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