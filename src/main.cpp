#include <iostream>
#include "Controller/Controller.h"

int main() {
    auto controller = Controller::InitGame();
    Controller::InGameProcess(controller);
    Controller::FinishGame(controller);
    return 0;
}
