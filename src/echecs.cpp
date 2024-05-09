#include <string>
#include <vector>
#include <iostream>
#include "../core/board.h"

using namespace std;

int main() {
    Board chessBoard;
    chessBoard.initGame();

    printQuit();
    cout << chessBoard.canonical_position() << endl;
    return EXIT_SUCCESS;
}