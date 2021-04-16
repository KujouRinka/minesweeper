#include <iostream>
#include "src/Controller/Controller.h"

using namespace std;

int main() {
    auto controller = Controller::InitGame();
    auto map = controller->GetMineField()->GetMap();
    auto row = controller->GetMineField()->GetRow();
    auto line = controller->GetMineField()->GetLine();
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < line; ++j) {
            printf("%3d", (*map)[i][j]);
        }
        cout << endl;
    }
    Controller::InGameProcess(controller);
    Controller::FinishGame(controller);
    return 0;
}
