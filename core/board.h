#include <iostream>
#include <vector>
#include <string>
#include <regex>

#include "interface.h"
#include "pieces.h"

using namespace std;

bool correctMovementPattern(string const & cmd);

bool correctKingsideCastlingPattern(string const & cmd);

bool correctQueensideCastlingPattern(string const & cmd);

class Board {
private:
    vector< vector<Piece*> > board;
    bool isWhitePlaying = true;
    bool isPlaying = true;
    bool isCheck = false;
    bool isCheckmate = false;
    bool whiteWin = false;
    bool blackWin = false;
    bool possibleEnPassant = false;
    string enPassantSquare = "";
public:
    Board() :
        board(8, vector<Piece*>(8))
    {}

    // Board initialization & launch the game
    void initGame();

    // Display the Chess board
    void showBoard();

    // Get the input from the player (move, quit, help, resign, draw)
    string getInput(bool isWhitePlaying);

    // check if the move is valid
    bool validMove(string input, bool isWhitePlaying);

    // check if the kingside castling move is valid
    bool validKingSideCastling(bool isWhitePlaying);

    // check if the queenside castling move is valid
    bool validQueenSideCastling(bool isWhitePlaying);

    // check if the move is valid for a specific piece
    bool checkMove(Piece* piece, Square start, Square end);

    // check if the king is in check
    bool checkCheck(bool isWhitePlaying);

    // check if the king is in checkmate
    bool checkCheckmate(bool isWhitePlaying);

    // Start the game
    void startGame();

    // Print the board state as string
    string canonical_position() const;
};
