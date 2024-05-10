/**
 * @file echecs.cpp
 * @brief Main file for the chess game redirecting to the core
 */
#include <string>
#include <vector>
#include <iostream>
#include "../core/board.h"

using namespace std;

int main() {
    printBegin();
    
    Board chessBoard;
    chessBoard.initGame();

    printQuit();
    cout << chessBoard.canonical_position() << endl;
    return EXIT_SUCCESS;
}