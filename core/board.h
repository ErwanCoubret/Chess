/**
 * @file board.h
 * @brief Header file for the game board and its logic
 */

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

/**
 * @brief Check if the input is a valid move pattern
 * @param cmd The input command
 * @return true if the input is a valid move pattern, false otherwise
*/
bool correctMovementPattern(string const & cmd);

/**
 * @brief Check if the input is a valid kingside castling pattern
 * @param cmd The input command
 * @return true if the input is a valid kingside castling pattern, false otherwise
 * */
bool correctKingsideCastlingPattern(string const & cmd);

/**
 * @brief Check if the input is a valid queenside castling pattern
 * @param cmd The input command
 * @return true if the input is a valid queenside castling pattern, false otherwise
 * */
bool correctQueensideCastlingPattern(string const & cmd);

/**
 * @class Board
 * @brief Class representing the chess board and its logic
 */
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

    string invelidMoveReason = "";

    bool possibleEnPassant = false;
    string enPassantSquare = "";

    int nbMovesWithoutTaking = 0;
    string lastMovesWhite[5] = {"", "", "", "", ""};
    string lastMovesBlack[5] = {"", "", "", "", ""};
public:
    Board() :
        board(8, vector<Piece*>(8))
    {}

    // ------------------------------------------------
    //                 MOVE PIECES
    // ------------------------------------------------

    /**
     * @brief Check if the move is valid for a pawn
     * @param pawn The pawn to move
     * @param endPiece The piece at the destination square, eventually nullptr
     * @param start The start square
     * @param end The end square
    */
    bool checkPawnMove(Piece* pawn, Piece* endPiece, Square start, Square end);

    /**
     * @brief Check if the move is valid for a rook
     * @param rook The rook to move
     * @param endPiece The piece at the destination square, eventually nullptr
     * @param start The start square
     * @param end The end square
    */
    bool checkRookMove(Piece* rook, Piece* endPiece, Square start, Square end);

    /**
     * @brief Check if the move is valid for a knight
     * @param knight The knight to move
     * @param endPiece The piece at the destination square, eventually nullptr
     * @param start The start square
     * @param end The end square
    */
    bool checkKnightMove(Piece* knight, Piece* endPiece, Square start, Square end);

    /**
     * @brief Check if the move is valid for a bishop
     * @param bishop The bishop to move
     * @param endPiece The piece at the destination square, eventually nullptr
     * @param start The start square
     * @param end The end square
    */
    bool checkBishopMove(Piece* bishop, Piece* endPiece, Square start, Square end);

    /**
     * @brief Check if the move is valid for a queen
     * @param queen The queen to move
     * @param endPiece The piece at the destination square, eventually nullptr
     * @param start The start square
     * @param end The end square
    */
    bool checkQueenMove(Piece* queen, Piece* endPiece, Square start, Square end);

    /**
     * @brief Check if the move is valid for a king
     * @param king The king to move
     * @param endPiece The piece at the destination square, eventually nullptr
     * @param start The start square
     * @param end The end square
    */
    bool checkKingMove(Piece* king, Piece* endPiece, Square start, Square end);

    /**
     * @brief Check if the move is valid for a piece, redirect to the correct function
     * @param piece The piece to move
     * @param start The start square
     * @param end The end square
     * @return true if the move is valid, false otherwise
    */
    bool checkPieceMove(Piece* piece, Square start, Square end);

    // ------------------------------------------------
    //           CHECK, CHECKMATE & STALEMATE
    // ------------------------------------------------

    /**
     * @brief find the position of the king
     * @param isWhitePlaying true if it is the white player's turn, false otherwise
     * @return the position of the king
    */
    string findKingPosition(bool isWhitePlaying);

    /**
     * @brief Check if the king is in check
     * @param isWhitePlaying true if it is the white player's turn, false otherwise
     * @return true if the king is in check, false otherwise
    */
    bool isCheck(bool isWhitePlaying);

    /**
     * @brief Check if the king is in checkmate
     * @param isWhitePlaying true if it is the white player's turn, false otherwise
     * @return true if the king is in checkmate, false otherwise
    */
    bool isCheckmate(bool isWhitePlaying);

    /**
     * @brief Check if the game is in stalemate
     * @param isWhitePlaying true if it is the white player's turn, false otherwise
     * @return true if the game is in stalemate, false otherwise
    */
    bool isStalemate(bool isWhitePlaying);

    // ------------------------------------------------
    //             GAME INTERACTIONS
    // ------------------------------------------------

    /**
     * @brief Initialize the game, set the board and the pieces and begin the game loop
    */
    void initGame();

   /**
    * @brief Print the current 
   */
    void showBoard();

    /**
     * @brief Get the input from the player (move, quit, help, resign, draw)
     * @param isWhitePlaying true if it is the white player's turn, false otherwise
     * @return the input from the player
    */
    string getInput(bool isWhitePlaying);

    /**
     * @brief Check if the move is valid
     * @param input The input move
     * @param isWhitePlaying true if it is the white player's turn, false otherwise
     * @return true if the move is valid, false otherwise
    */
    bool validMove(string input, bool isWhitePlaying);

    /**
     * @brief Check if the kingside castling move is valid
     * @param isWhitePlaying true if it is the white player's turn, false otherwise
     * @return true if the kingside castling move is valid, false otherwise
    */
    bool validKingSideCastling(bool isWhitePlaying);

    /**
     * @brief Check if the queenside castling move is valid
     * @param isWhitePlaying true if it is the white player's turn, false otherwise
     * @return true if the queenside castling move is valid, false otherwise
    */
    bool validQueenSideCastling(bool isWhitePlaying);

    /**
     * @brief Switch the player's turn
    */
    void changePlayer();

    /**
     * @brief Resign the game
    */
    void resignGame();

    /**
     * @brief Draw the game
    */
    void drawGame();

    /**
     * @brief End the game and print information about the game
    */
    void endGame();

    /**
     * @brief Check if the input is a valid move pattern
     * @param cmd The input command
     * @return true if the input is a valid move pattern, false otherwise
    */
    bool processNormalMove(string input);

    /**
     * @brief Check if the input is a valid kingside castling pattern
     * @param cmd The input command
     * @return true if the input is a valid kingside castling pattern, false otherwise
    */
    bool processKingsideCastlingMove();

    /**
     * @brief Check if the input is a valid queenside castling pattern
     * @param cmd The input command
     * @return true if the input is a valid queenside castling pattern, false otherwise
    */
    bool processQueensideCastlingMove();

    /**
     * @brief handle the move input
     * @param input The input move
     * @return true if the move is valid, false otherwise
    */
    bool processMove(string input);

    /**
     * @brief start the game loop
    */
    void game();

    /**
     * @brief Get the canonical position of the board
     * @return the canonical position of the board
    */
    string canonical_position() const;
};
