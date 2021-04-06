//
// Created by KujouRinka on 2021/4/5.
//

/*
 * This package is used to process user operation
 */


#ifndef MINESWEEPER_CONTROLLER_H
#define MINESWEEPER_CONTROLLER_H

#include "../MapGenerator/MapGenerator.h"

namespace Controller {

    void InitGame(MapGenerator::Minefield minefield);

    void InGameProcess();

}

#endif //MINESWEEPER_CONTROLLER_H
