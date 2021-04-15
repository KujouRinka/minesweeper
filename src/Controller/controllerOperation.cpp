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
Controller::Controller::Controller(MapGenerator::Minefield field) {
    minefield = field;
    showPlayerField = new MapGenerator::MField(minefield);
}

/**
 * This method use MineField to create map showing
 * to user.
 */
void Controller::Controller::generateEmptyMap() {
    if (showPlayerField != nullptr)
        delete showPlayerField;
    showPlayerField = new MapGenerator::MField(minefield);
}

/**
 * Do click block operation.
 */
void Controller::Controller::Click() {

}

/**
 * Do "flag" block operation.
 */
void Controller::Controller::Flag() {

}

/**
 * Do "question" block operation.
 */
void Controller::Controller::Question() {

}

/**
 * Do clean work.
 *
 * needs to be overwritten.
 */
Controller::Controller::~Controller() {
    delete minefield;
    delete showPlayerField;
}
