#include <iostream>
#include <vector>
#include <string>
#include <regex>

#include "interface.h"
#include "pieces.h"

using namespace std;

// ------------------------------------------------
//          PATTERN MATCHING FUNCTIONS
// ------------------------------------------------

bool correctMovementPattern(string const & cmd);

bool correctKingsideCastlingPattern(string const & cmd);

bool correctQueensideCastlingPattern(string const & cmd);

class Board {
private:
    // ------------------------------------------------
    //           BOARD STATE & GAME VARIABLES
    // ------------------------------------------------

    vector< vector<Piece*> > board;
    bool isWhitePlaying = true;
    bool isPlaying = true;
    bool check = false;
    bool checkmate = false;
    bool whiteWin = false;
    bool blackWin = false;
    bool possibleEnPassant = false;
    string enPassantSquare = "";
public:
    Board() :
        board(8, vector<Piece*>(8))
    {}

    // ------------------------------------------------
    //                 MOVE PIECES
    // ------------------------------------------------

    // ---- PAWN LOGIC ----
    bool checkPawnMove(Piece* pawn, Piece* endPiece, Square start, Square end);

    // ---- ROOK LOGIC ----
    bool checkRookMove(Piece* rook, Piece* endPiece, Square start, Square end);

    // ---- KNIGHT LOGIC ----
    bool checkKnightMove(Piece* knight, Piece* endPiece, Square start, Square end);

    // ---- BISHOP LOGIC ----
    bool checkBishopMove(Piece* bishop, Piece* endPiece, Square start, Square end);

    // ---- QUEEN LOGIC ----
    bool checkQueenMove(Piece* queen, Piece* endPiece, Square start, Square end);

    // ---- KING LOGIC ----
    bool checkKingMove(Piece* king, Piece* endPiece, Square start, Square end);

    // check if the move is valid for a specific piece
    bool checkPieceMove(Piece* piece, Square start, Square end);

    // ------------------------------------------------
    //               CHECK & CHECKMATE
    // ------------------------------------------------

    // find king position
    string findKingPosition(bool isWhitePlaying);

    // check if the king is in check
    bool isCheck(bool isWhitePlaying);

    // check if the king is in checkmate
    bool isCheckmate(bool isWhitePlaying);

    // ------------------------------------------------
    //             GAME INTERACTIONS
    // ------------------------------------------------

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

    // Start the game
    void startGame();

    // Print the board state as string
    string canonical_position() const;
};
