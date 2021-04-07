//
// Created by KujouRinka on 2021/4/7.
//

#include "Controller.h"

/**
 * This method helps to initialize user struct.
 *
 * @param field
 * A initialized Minefield
 */
Controller::Player::Player(MapGenerator::Minefield field) {
    minefield = field;
    showPlayerField = MapGenerator::MField(minefield);
}

/**
 * This method use MineField to create map showing
 * to user.
 */
void Controller::Player::generateEmptyMap() {
    showPlayerField = MapGenerator::MField(minefield);
}