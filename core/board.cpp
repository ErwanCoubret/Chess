/**
 * @file board.cpp
 * @brief Implementation of the chess board functions & game logic
 */

#include "board.h"

// ------------------------------------------------
//          PATTERN MATCHING FUNCTIONS
// ------------------------------------------------

bool correctMovementPattern(string const & cmd) {
    regex mouvementPattern("[a-h][1-8][a-h][1-8]");
    return regex_match(cmd, mouvementPattern);
}

bool correctKingsideCastlingPattern(string const & cmd) {
    regex kingsideCastlingPattern("(O|o|0)-(O|o|0)");
    return regex_match(cmd, kingsideCastlingPattern);
}

bool correctQueensideCastlingPattern(string const & cmd) {
    regex queensideCastlingPattern("(O|o|0)-(O|o|0)-(O|o|0)");
    return regex_match(cmd, queensideCastlingPattern);
}

// ------------------------------------------------
//                 MOVE PIECES
// ------------------------------------------------

bool Board::checkPawnMove(Piece* pawn, Piece* endPiece, Square start, Square end) {
    // ----- WHITE PAWN LOGIC -----
    if (pawn->getColor() == Color::WHITE) {
        if (start.getColumn() == end.getColumn()) {
            // pawn is moving forward by one square
            if (
                end.getLine() == start.getLine() + 1 &&
                endPiece == nullptr
            ) {
                return true;
            }

            // pawn is moving forward by two squares from the initial position
            if (
                start.getLine() + 1 == 2 &&
                end.getLine() == start.getLine() + 2 &&
                endPiece == nullptr &&
                board[end.getLine() - 1][end.getColumn()] == nullptr
            ) {
                possibleEnPassant = true;
                return true;
            }
        } else {
            // pawn is capturing a piece
            if (
                endPiece != nullptr &&
                end.getLine() == start.getLine() + 1 &&
                abs(end.getColumn() - start.getColumn()) == 1 &&
                endPiece->getColor() != pawn->getColor()
            ) {
                return true;
            }

            // pawn is capturing a piece using en passant move
            if (
                possibleEnPassant &&
                endPiece == nullptr &&
                end.getLine() == start.getLine() + 1 &&
                abs(end.getColumn() - start.getColumn()) == 1 &&
                board[start.getLine()][end.getColumn()] != nullptr &&
                board[start.getLine()][end.getColumn()]->getPsymb() == 'P' &&
                board[start.getLine()][end.getColumn()]->getColor() != pawn->getColor()
            ) {
                return true;
            }

        }

        return false;
    } 

    // ----- BLACK PAWN LOGIC -----

    if (start.getColumn() == end.getColumn()) {
        // pawn is moving forward by one square
        if (
            end.getLine() == start.getLine() - 1 &&
            endPiece == nullptr
        ) {
            return true;
        }

        // pawn is moving forward by two squares from the initial position
        if (
            start.getLine() + 1 == 7 &&
            end.getLine() == start.getLine() - 2 &&
            endPiece == nullptr &&
            board[end.getLine() + 1][end.getColumn()] == nullptr
        ) {
            possibleEnPassant = true;
            return true;
        }
    } else {
        // pawn is capturing a piece
        if (
            endPiece != nullptr &&
            end.getLine() == start.getLine() - 1 &&
            abs(end.getColumn() - start.getColumn()) == 1 &&
            endPiece->getColor() != pawn->getColor()
        ) {
            return true;
        }

        // pawn is capturing a piece using en passant move
        if (
            possibleEnPassant &&
            endPiece == nullptr &&
            end.getLine() == start.getLine() - 1 &&
            abs(end.getColumn() - start.getColumn()) == 1 &&
            board[start.getLine()][end.getColumn()] != nullptr &&
            board[start.getLine()][end.getColumn()]->getPsymb() == 'P' &&
            board[start.getLine()][end.getColumn()]->getColor() != pawn->getColor()
        ) {
            return true;
        }
    }

    return false;
}

bool Board::checkRookMove(Piece* rook, Piece* endPiece, Square start, Square end) {
    // rook is moving vertically
    if (start.getColumn() == end.getColumn()) {
        // rook is moving up
        if (end.getLine() > start.getLine()) {
            for (int i = start.getLine() + 1; i < end.getLine(); i++) {
                if (board[i][end.getColumn()] != nullptr) {
                    return false;
                }
            }

            if (
                endPiece == nullptr ||
                endPiece->getColor() != rook->getColor()
            ) {
                return true;
            }

            return false;
        }

        // rook is moving down
        if (end.getLine() < start.getLine()) {
            for (int i = start.getLine() - 1; i > end.getLine(); i--) {
                if (board[i][end.getColumn()] != nullptr) {
                    return false;
                }
            }

            if (
                endPiece == nullptr ||
                endPiece->getColor() != rook->getColor()
            ) {
                return true;
            }

            return false;
        }
    }

    // rook is moving horizontally
    if (start.getLine() == end.getLine()) {
        // rook is moving right
        if (end.getColumn() > start.getColumn()) {
            for (int i = start.getColumn() + 1; i < end.getColumn(); i++) {
                if (board[end.getLine()][i] != nullptr) {
                    return false;
                }
            }

            if (
                endPiece == nullptr ||
                endPiece->getColor() != rook->getColor()
            ) {
                return true;
            }

            return false;
        }

        // rook is moving left
        if (end.getColumn() < start.getColumn()) {
            for (int i = start.getColumn() - 1; i > end.getColumn(); i--) {
                if (board[end.getLine()][i] != nullptr) {
                    return false;
                }
            }

            if (
                endPiece == nullptr ||
                endPiece->getColor() != rook->getColor()
            ) {
                return true;
            }

            return false;
        }
    }

    return false;
}

bool Board::checkKnightMove(Piece* knight, Piece* endPiece, Square start, Square end) {
    if (
        (abs(end.getLine() - start.getLine()) == 2 && abs(end.getColumn() - start.getColumn()) == 1) ||
        (abs(end.getLine() - start.getLine()) == 1 && abs(end.getColumn() - start.getColumn()) == 2)
    ) {
        if (
            endPiece == nullptr ||
            endPiece->getColor() != knight->getColor()
        ) {
            return true;
        }

        return false;
    }

    return false;
}

bool Board::checkBishopMove(Piece* bishop, Piece* endPiece, Square start, Square end) {
    // bishop is moving diagonally
    if (abs(end.getLine() - start.getLine()) == abs(end.getColumn() - start.getColumn())) {
        // bishop is moving up-right
        if (end.getLine() > start.getLine() && end.getColumn() > start.getColumn()) {
            for (int i = 1; i < end.getLine() - start.getLine(); i++) {
                if (board[start.getLine() + i][start.getColumn() + i] != nullptr) {
                    return false;
                }
            }

            if (
                endPiece == nullptr ||
                endPiece->getColor() != bishop->getColor()
            ) {
                return true;
            }

            return false;
        }

        // bishop is moving up-left
        if (end.getLine() > start.getLine() && end.getColumn() < start.getColumn()) {
            for (int i = 1; i < end.getLine() - start.getLine(); i++) {
                if (board[start.getLine() + i][start.getColumn() - i] != nullptr) {
                    return false;
                }
            }

            if (
                endPiece == nullptr ||
                endPiece->getColor() != bishop->getColor()
            ) {
                return true;
            }

            return false;
        }

        // bishop is moving down-right
        if (end.getLine() < start.getLine() && end.getColumn() > start.getColumn()) {
            for (int i = 1; i < start.getLine() - end.getLine(); i++) {
                if (board[start.getLine() - i][start.getColumn() + i] != nullptr) {
                    return false;
                }
            }

            if (
                endPiece == nullptr ||
                endPiece->getColor() != bishop->getColor()
            ) {
                return true;
            }

            return false;
        }

        // bishop is moving down-left
        if (end.getLine() < start.getLine() && end.getColumn() < start.getColumn()) {
            for (int i = 1; i < start.getLine() - end.getLine(); i++) {
                if (board[start.getLine() - i][start.getColumn() - i] != nullptr) {
                    return false;
                }
            }

            if (
                endPiece == nullptr ||
                endPiece->getColor() != bishop->getColor()
            ) {
                return true;
            }

            return false;
        }
    }

    return false;
}

bool Board::checkQueenMove(Piece* queen, Piece* endPiece, Square start, Square end) {
    // queen is moving vertically
    if (start.getColumn() == end.getColumn()) {
        // queen is moving up
        if (end.getLine() > start.getLine()) {
            for (int i = start.getLine() + 1; i < end.getLine(); i++) {
                if (board[i][end.getColumn()] != nullptr) {
                    return false;
                }
            }

            if (
                endPiece == nullptr ||
                endPiece->getColor() != queen->getColor()
            ) {
                return true;
            }

            return false;
        }

        // queen is moving down
        if (end.getLine() < start.getLine()) {
            for (int i = start.getLine() - 1; i > end.getLine(); i--) {
                if (board[i][end.getColumn()] != nullptr) {
                    return false;
                }
            }

            if (
                endPiece == nullptr ||
                endPiece->getColor() != queen->getColor()
            ) {
                return true;
            }

            return false;
        }
    }

    // queen is moving horizontally
    if (start.getLine() == end.getLine()) {
        // queen is moving right
        if (end.getColumn() > start.getColumn()) {
            for (int i = start.getColumn() + 1; i < end.getColumn(); i++) {
                if (board[end.getLine()][i] != nullptr) {
                    return false;
                }
            }

            if (
                endPiece == nullptr ||
                endPiece->getColor() != queen->getColor()
            ) {
                return true;
            }

            return false;
        }

        // queen is moving left
        if (end.getColumn() < start.getColumn()) {
            for (int i = start.getColumn() - 1; i > end.getColumn(); i--) {
                if (board[end.getLine()][i] != nullptr) {
                    return false;
                }
            }

            if (
                endPiece == nullptr ||
                endPiece->getColor() != queen->getColor()
            ) {
                return true;
            }

            return false;
        }
    }

    // queen is moving diagonally
    if (abs(end.getLine() - start.getLine()) == abs(end.getColumn() - start.getColumn())) {
        // queen is moving up-right
        if (end.getLine() > start.getLine() && end.getColumn() > start.getColumn()) {
            for (int i = 1; i < end.getLine() - start.getLine(); i++) {
                if (board[start.getLine() + i][start.getColumn() + i] != nullptr) {
                    return false;
                }
            }

            if (
                endPiece == nullptr ||
                endPiece->getColor() != queen->getColor()
            ) {
                return true;
            }

            return false;
        }

        // queen is moving up-left
        if (end.getLine() > start.getLine() && end.getColumn() < start.getColumn()) {
            for (int i = 1; i < end.getLine() - start.getLine(); i++) {
                if (board[start.getLine() + i][start.getColumn() - i] != nullptr) {
                    return false;
                }
            }

            if (
                endPiece == nullptr ||
                endPiece->getColor() != queen->getColor()
            ) {
                return true;
            }

            return false;
        }

        // queen is moving down-right
        if (end.getLine() < start.getLine() && end.getColumn() > start.getColumn()) {
            for (int i = 1; i < start.getLine() - end.getLine(); i++) {
                if (board[start.getLine() - i][start.getColumn() + i] != nullptr) {
                    return false;
                }
            }

            if (
                endPiece == nullptr ||
                endPiece->getColor() != queen->getColor()
            ) {
                return true;
            }

            return false;
        }

        // queen is moving down-left
        if (end.getLine() < start.getLine() && end.getColumn() < start.getColumn()) {
            for (int i = 1; i < start.getLine() - end.getLine(); i++) {
                if (board[start.getLine() - i][start.getColumn() - i] != nullptr) {
                    return false;
                }
            }

            if (
                endPiece == nullptr ||
                endPiece->getColor() != queen->getColor()
            ) {
                return true;
            }

            return false;
        }
    }

    return false;
}

bool Board::checkKingMove(Piece* king, Piece* endPiece, Square start, Square end) {
    // king is moving vertically
    if (abs(end.getLine() - start.getLine()) == 1 && abs(end.getColumn() - start.getColumn()) == 0) {
        if (
            endPiece == nullptr ||
            endPiece->getColor() != king->getColor()
        ) {
            return true;
        }

        return false;
    }

    // king is moving horizontally
    if (abs(end.getColumn() - start.getColumn()) == 1 && abs(end.getLine() - start.getLine()) == 0) {
        if (
            endPiece == nullptr ||
            endPiece->getColor() != king->getColor()
        ) {
            return true;
        }

        return false;
    }

    // king is moving diagonally
    if (abs(end.getLine() - start.getLine()) == 1 && abs(end.getColumn() - start.getColumn()) == 1) {
        if (
            endPiece == nullptr ||
            endPiece->getColor() != king->getColor()
        ) {
            return true;
        }

        return false;
    }

    // king is castling kingside -> TODO
    if (end.getColumn() - start.getColumn() == 2) {
        return false;
    }

    // king is castling queenside -> TODO
    if (start.getColumn() - end.getColumn() == 2) {
        return false;
    }

    return false;
}

bool Board::checkPieceMove(Piece* piece, Square start, Square end) {
    Piece* endPiece = board[end.getLine()][end.getColumn()];

    // ----- PAWN LOGIC -----
    if (piece->getPsymb() == 'P')
        return checkPawnMove(piece, endPiece, start, end);

    // ----- ROOK LOGIC -----
    if (piece->getPsymb() == 'R')
        return checkRookMove(piece, endPiece, start, end);

    // ----- KNIGHT LOGIC -----
    if (piece->getPsymb() == 'N')
        return checkKnightMove(piece, endPiece, start, end);

    // ----- BISHOP LOGIC -----
    if (piece->getPsymb() == 'B')
        return checkBishopMove(piece, endPiece, start, end);

    // ----- QUEEN LOGIC -----
    if (piece->getPsymb() == 'Q')
        return checkQueenMove(piece, endPiece, start, end);

    // ----- KING LOGIC -----
    if (piece->getPsymb() == 'K')
        return checkKingMove(piece, endPiece, start, end);

    return false;
}

// ------------------------------------------------
//               CHECK & CHECKMATE
// ------------------------------------------------

string Board::findKingPosition(bool isWhitePlaying) {
    string kingPosition = "";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != nullptr && board[i][j]->getPsymb() == 'K' && board[i][j]->getColor() == (isWhitePlaying ? Color::WHITE : Color::BLACK)) {
                kingPosition = board[i][j]->getPosition();
            }
        }
    }

    return kingPosition;
}

bool Board::isCheck(bool isWhitePlaying) {
    // Récupérer la position du roi
    string kingPosition = findKingPosition(isWhitePlaying);
    
    // Créer un objet Square pour la position du roi
    Square kingSquare(&kingPosition[0]);

    // Parcourir le tableau pour trouver les pièces adverses
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (
                board[i][j] != nullptr &&
                board[i][j]->getColor() != (isWhitePlaying ? Color::WHITE : Color::BLACK)
            ) {
                // Créer un objet Square pour la position de la pièce adverse
                Square opponentPiece(&board[i][j]->getPosition()[0]);

                // Vérifier si la pièce adverse peut capturer le roi
                if (checkPieceMove(board[i][j], opponentPiece, kingSquare)) {
                    // cout << board[i][j]->getPsymb() << " en " << board[i][j]->getPosition() << " peut capturer le roi " << (isWhitePlaying ? "blanc" : "noir") << " en " << kingPosition << endl;
                    return true;
                }
            }
        }
    }

    return false;
}

bool Board::isCheckmate(bool isWhitePlaying) {
    // get the king position
    string kingPosition = findKingPosition(isWhitePlaying);

    // get the king square
    Square kingSquare(&kingPosition[0]);
    Piece* king = board[kingSquare.getLine()][kingSquare.getColumn()];

    // check if the king can move around it's position
    // and see if it's still in check
    // taking in consideration the limits of the board
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (
                (i != 0 || j != 0) &&
                kingSquare.getLine() + i >= 0 && kingSquare.getLine() + i < 8 &&
                kingSquare.getColumn() + j >= 0 && kingSquare.getColumn() + j < 8 &&
                (board[kingSquare.getLine() + i][kingSquare.getColumn() + j] == nullptr ||
                board[kingSquare.getLine() + i][kingSquare.getColumn() + j]->getColor() != king->getColor())
            ) {
                // try to move the king
                Piece* endPiece = board[kingSquare.getLine() + i][kingSquare.getColumn() + j];

                board[kingSquare.getLine() + i][kingSquare.getColumn() + j] = king;
                string endPosition = string(1, 'a' + kingSquare.getColumn() + j) + to_string(kingSquare.getLine() + i + 1);
                board[kingSquare.getLine() + i][kingSquare.getColumn() + j]->setPosition(endPosition);
                board[kingSquare.getLine()][kingSquare.getColumn()] = nullptr;

                if (!isCheck(isWhitePlaying)) {
                    board[kingSquare.getLine()][kingSquare.getColumn()] = king;
                    board[kingSquare.getLine() + i][kingSquare.getColumn() + j] = endPiece;
                    board[kingSquare.getLine()][kingSquare.getColumn()]->setPosition(kingPosition);
                    if (endPiece != nullptr) {
                        board[kingSquare.getLine() + i][kingSquare.getColumn() + j]->setPosition(endPiece->getPosition());
                    }
                    return false;
                }

                board[kingSquare.getLine()][kingSquare.getColumn()] = king;
                board[kingSquare.getLine() + i][kingSquare.getColumn() + j] = endPiece;
                board[kingSquare.getLine()][kingSquare.getColumn()]->setPosition(kingPosition);
                if (endPiece != nullptr) {
                    board[kingSquare.getLine() + i][kingSquare.getColumn() + j]->setPosition(endPiece->getPosition());
                }
            }
        }
    }

    // check if any piece can move to protect the king
    // and see if the king is still in check
    bool saveEnPassant = possibleEnPassant;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // find a piece of the same color
            if (
                board[i][j] != nullptr &&
                board[i][j]->getColor() == (isWhitePlaying ? Color::WHITE : Color::BLACK) &&
                board[i][j]->getPsymb() != 'K'
            ) {
                // verify if a possible move exists
                for (int k = 0; k < 8; k++) {
                    for (int l = 0; l < 8; l++) {
                        string startPosition = string(1, 'a' + j) + to_string(i + 1);
                        string endPosition = string(1, 'a' + l) + to_string(k + 1);
                        if (checkPieceMove(board[i][j], Square(&startPosition[0]), Square(&endPosition[0]))) {
                            // try to move the piece
                            Piece* endPiece = board[k][l];

                            board[k][l] = board[i][j];
                            board[k][l]->setPosition(endPosition);
                            board[i][j] = nullptr;

                            if (!isCheck(isWhitePlaying)) {
                                board[i][j] = board[k][l];
                                board[k][l] = endPiece;
                                board[i][j]->setPosition(startPosition);
                                if (endPiece != nullptr) {
                                    board[k][l]->setPosition(endPiece->getPosition());
                                }
                                possibleEnPassant = saveEnPassant;
                                return false;
                            }

                            board[i][j] = board[k][l];
                            board[k][l] = endPiece;
                            board[i][j]->setPosition(startPosition);
                            if (endPiece != nullptr) {
                                board[k][l]->setPosition(endPiece->getPosition());
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}

bool Board::isStalemate(bool isWhitePlaying) {

    // check if this is a triple repetition of the position
    // for the 2 players
    bool whiteFlagRepeat = 
        lastMovesWhite[0] != "" &&
        lastMovesWhite[0] == lastMovesWhite[2] &&
        lastMovesWhite[2] == lastMovesWhite[4] &&
        lastMovesWhite[1] == lastMovesWhite[3]
    ;

    bool blackFlagRepeat =
        lastMovesBlack[0] != "" &&
        lastMovesBlack[0] == lastMovesBlack[2] &&
        lastMovesBlack[2] == lastMovesBlack[4] &&
        lastMovesBlack[1] == lastMovesBlack[3]
    ;

    return
        ((!isCheck(isWhitePlaying) && isCheckmate(isWhitePlaying)) &&
        nbMovesWithoutTaking < 50) ||
        (whiteFlagRepeat && blackFlagRepeat)
    ;
}

// ------------------------------------------------
//             GAME INTERACTIONS
// ------------------------------------------------

void Board::initGame() {
    // ----- position setup for the pieces -----
    board[0][0] = new Rook(Color::WHITE, 1, "a1");
    board[0][1] = new Knight(Color::WHITE, 2, "b1");
    board[0][2] = new Bishop(Color::WHITE, 3, "c1");
    board[0][3] = new Queen(Color::WHITE, 4, "d1");
    board[0][4] = new King(Color::WHITE, 5, "e1");
    board[0][5] = new Bishop(Color::WHITE, 6, "f1");
    board[0][6] = new Knight(Color::WHITE, 7, "g1");
    board[0][7] = new Rook(Color::WHITE, 8, "h1");

    board[7][0] = new Rook(Color::BLACK, 9, "a8");
    board[7][1] = new Knight(Color::BLACK, 10, "b8");
    board[7][2] = new Bishop(Color::BLACK, 11, "c8");
    board[7][3] = new Queen(Color::BLACK, 12, "d8");
    board[7][4] = new King(Color::BLACK, 13, "e8");
    board[7][5] = new Bishop(Color::BLACK, 14, "f8");
    board[7][6] = new Knight(Color::BLACK, 15, "g8");
    board[7][7] = new Rook(Color::BLACK, 16, "h8");

    for (int i = 0; i < 8; i++) {
        char column = 'a' + i; // Convertir l'indice en caractère ASCII ('a' + i)
        board[1][i] = new Pawn(Color::WHITE, i + 17, string(1, column) + "2");
        board[6][i] = new Pawn(Color::BLACK, i + 25, string(1, column) + "7");
    }

    for (int i = 2; i < 6; i++)
        for (int j = 0; j < 8; j++)
            board[i][j] = nullptr;

    // ----- Begin the game logic -----
    game();
}

void Board::showBoard() {
    cout << endl;
    cout << white << bold;
    cout << "\t     a   b   c   d   e   f   g   h  \n";
    cout << "\t   ┌───┬───┬───┬───┬───┬───┬───┬───┐\n";
    for (int i = 0; i < 7; i++) {
        cout << "\t" << 8 - i << "  │";
        for (int j = 0; j < 7; j++) {
            cout << " ";
            if (board[7 - i][j] == nullptr) {
                cout << "  │";
            } else {
                cout << board[7 - i][j]->getIcon() << " │";
            }
            
        }
        
        cout << " ";
        if (board[7 - i][7] == nullptr) {
            cout << "  │";
        } else {
            cout << board[7 - i][7]->getIcon() << " │";
        }
        cout << endl;
        cout << "\t   ├───┼───┼───┼───┼───┼───┼───┼───┤\n";
    }
    cout << "\t1  │";
    for (int i = 0; i < 7; i++) {
        cout << " ";
        if (board[0][i] == nullptr) {
            cout << "  │";
        } else {
            cout << board[0][i]->getIcon() << " │";
        }
    }
    cout << " ";
    if (board[0][7] == nullptr) {
        cout << "  │";
    } else {
        cout << board[0][7]->getIcon() << " │";
    }
    cout << endl;
    cout << "\t   └───┴───┴───┴───┴───┴───┴───┴───┘\n";
    cout << "\t     a   b   c   d   e   f   g   h  \n";
    cout << endl;
    
}

string Board::canonical_position() const {
    string output = "";
    for (size_t row(0); row <= 7; row++){
        for (char col('a'); col <= 'h'; col++) {
            if (board[row][col - 'a'] != nullptr) {
                output += (board[row][col - 'a']->getColor() == Color::WHITE ? "w" : "b");
                output += board[row][col - 'a']->getPsymb();
            }
            output += ",";
        }
    }

    if (whiteWin) {
        output += " 1-0";
    } else if (blackWin) {
        output += " 0-1";
    } else if (!isPlaying) {
        output += " 1/2-1/2";
    } else {
        output += " ?-?";
    }

    return output;
}

string Board::getInput(bool isWhitePlaying) {
    string input;
    cout << endl;
    cout << blue << bold;
    if (isWhitePlaying) {
        cout << "Aux blancs de jouer." << endl;
    } else {
        cout << "Aux noirs de jouer." << endl;
    }
    cout << white << bold;
    cout << "🕹️  Entrez votre coup: ";
    cout << orange;
    cin >> input;
    cout << reset << endl;

    return input;
}

bool Board::validMove(string input, bool isWhitePlaying) {
    Square start(&input[0]);
    Square end(&input[2]);

    // get the piece at the initial position
    Piece* piece = board[start.getLine()][start.getColumn()];

    // check if there is a piece at the initial position
    if (piece == nullptr) {
        invelidMoveReason = "Il n'y a pas de pièce à cet endroit.";
        return false;
    }

    // check if the piece is the right color
    if ((isWhitePlaying && piece->getColor() == Color::BLACK) || (!isWhitePlaying && piece->getColor() == Color::WHITE)) {
        invelidMoveReason = "Vous ne pouvez pas jouer cette pièce.";
        return false;
    }

    // check if the end is the start
    if (start.toString() == end.toString()) {
        invelidMoveReason = "Vous devez déplacer la pièce.";
        return false;
    }

    // check if the Piece can move to the end position
    if (!checkPieceMove(piece, start, end)) {
        invelidMoveReason = "Ce mouvement n'est pas valide.";
        return false;
    }

    // check if the move doesn't put the king in check
    // we save the current state of squares, try the move, check if the king is in check, and then revert the move
    Piece* startPiece = board[start.getLine()][start.getColumn()];
    Piece* endPiece = board[end.getLine()][end.getColumn()];

    board[end.getLine()][end.getColumn()] = board[start.getLine()][start.getColumn()];
    board[end.getLine()][end.getColumn()]->setPosition(end.toString());
    board[start.getLine()][start.getColumn()] = nullptr;

    if (isCheck(isWhitePlaying)) {
        invelidMoveReason = "Le roi ";
        invelidMoveReason += isWhitePlaying ? "blanc" : "noir";
        invelidMoveReason += " est en échec.";
        board[start.getLine()][start.getColumn()] = startPiece;
        board[end.getLine()][end.getColumn()] = endPiece;
        board[start.getLine()][start.getColumn()]->setPosition(start.toString());
        return false;
    }

    board[start.getLine()][start.getColumn()] = startPiece;
    board[end.getLine()][end.getColumn()] = endPiece;
    
    return true;
}

bool Board::validKingSideCastling(bool isWhitePlaying) {
    // verify if the king and the rook are in position
    if (
        board[isWhitePlaying ? 0 : 7][4] == nullptr ||
        board[isWhitePlaying ? 0 : 7][7] == nullptr ||
        board[isWhitePlaying ? 0 : 7][4]->getPsymb() != 'K' ||
        board[isWhitePlaying ? 0 : 7][7]->getPsymb() != 'R'
    ) {
        cout << red << bold;
        cout << "🚫 Le roi ou la tour n'est pas en position." << endl;
        cout << reset;
        return false;
    }

    // find the king and the rook positions
    Square kingSquare(&board[isWhitePlaying ? 0 : 7][4]->getPosition()[0]);
    Square rookSquare(&board[isWhitePlaying ? 0 : 7][7]->getPosition()[0]);

    // get the king and the rook
    Piece* king = board[kingSquare.getLine()][kingSquare.getColumn()];
    Piece* rook = board[rookSquare.getLine()][rookSquare.getColumn()];

    // check if the king and the rook haven't moved
    if (king->getHasMoved() || rook->getHasMoved()) {
        cout << red << bold;
        cout << "🚫 Le roi ou la tour a déjà bougé." << endl;
        cout << reset;
        return false;
    }

    // check if the squares between the king and the rook are empty
    if (
        board[rookSquare.getLine()][rookSquare.getColumn() - 1] != nullptr ||
        board[rookSquare.getLine()][rookSquare.getColumn() - 2] != nullptr
    ) {
        cout << red << bold;
        cout << "🚫 Les cases entre le roi et la tour ne sont pas vides." << endl;
        cout << reset;
        return false;
    }

    // check if the king is not in check
    if (isCheck(isWhitePlaying)) {
        cout << red << bold;
        cout << "🚫 Le roi " << (isWhitePlaying ? "blanc" : "noir") << " est en échec." << endl;
        cout << reset;
        return false;
    }

    // check if the king doesn't pass through a square that is attacked by an opponent piece
    // we do it by trying to move the king to the squares between the king and the rook
    // if the king is in check after the move, the castling is not valid

    // move the king to the first square
    board[kingSquare.getLine()][kingSquare.getColumn() + 1] = king;
    board[kingSquare.getLine()][kingSquare.getColumn()] = nullptr;
    board[kingSquare.getLine()][kingSquare.getColumn() + 1]->setPosition((isWhitePlaying? "f1" : "f8"));

    if (isCheck(isWhitePlaying)) {
        cout << red << bold;
        cout << "🚫 Une des cases du roc est attaquée" << endl;
        cout << reset;
        board[kingSquare.getLine()][kingSquare.getColumn() + 1] = nullptr;
        board[kingSquare.getLine()][kingSquare.getColumn()] = king;
        board[kingSquare.getLine()][kingSquare.getColumn()]->setPosition((isWhitePlaying? "e1" : "e8"));
        return false;
    }

    // move the king to the second square
    board[kingSquare.getLine()][kingSquare.getColumn() + 2] = king;
    board[kingSquare.getLine()][kingSquare.getColumn() + 1] = nullptr;
    board[kingSquare.getLine()][kingSquare.getColumn() + 2]->setPosition((isWhitePlaying? "g1" : "g8"));

    if (isCheck(isWhitePlaying)) {
        cout << red << bold;
        cout << "🚫 Une des cases du roc est attaquée" << endl;
        cout << reset;
        board[kingSquare.getLine()][kingSquare.getColumn() + 2] = nullptr;
        board[kingSquare.getLine()][kingSquare.getColumn()] = king;
        board[kingSquare.getLine()][kingSquare.getColumn()]->setPosition((isWhitePlaying? "e1" : "e8"));
        return false;
    }

    // move the king back to the initial position
    board[kingSquare.getLine()][kingSquare.getColumn()] = king;
    board[kingSquare.getLine()][kingSquare.getColumn() + 2] = nullptr;
    board[kingSquare.getLine()][kingSquare.getColumn()]->setPosition((isWhitePlaying? "e1" : "e8"));

    return true;
}

bool Board::validQueenSideCastling(bool isWhitePlaying) {
    // find the king and the rook positions
    Square kingSquare(&board[isWhitePlaying ? 0 : 7][4]->getPosition()[0]);
    Square rookSquare(&board[isWhitePlaying ? 0 : 7][0]->getPosition()[0]);

    // get the king and the rook
    Piece* king = board[kingSquare.getLine()][kingSquare.getColumn()];
    Piece* rook = board[rookSquare.getLine()][rookSquare.getColumn()];

    if (rook == nullptr) {
        cout << red << bold;
        cout << "🚫 La tour n'est pas en position." << endl;
        cout << reset;
        return false;
    }

    // check if the king and the rook haven't moved
    if (king->getHasMoved() || rook->getHasMoved()) {
        cout << red << bold;
        cout << "🚫 Le roi ou la tour a déjà bougé." << endl;
        cout << reset;
        return false;
    }

    // check if the squares between the king and the rook are empty
    if (
        board[rookSquare.getLine()][rookSquare.getColumn() + 1] != nullptr ||
        board[rookSquare.getLine()][rookSquare.getColumn() + 2] != nullptr ||
        board[rookSquare.getLine()][rookSquare.getColumn() + 3] != nullptr
    ) {
        cout << red << bold;
        cout << "🚫 Les cases entre le roi et la tour ne sont pas vides." << endl;
        cout << reset;
        return false;
    }

    // check if the king is not in check
    if (isCheck(isWhitePlaying)) {
        cout << red << bold;
        cout << "🚫 Le roi " << (isWhitePlaying ? "blanc" : "noir") << " est en échec." << endl;
        cout << reset;
        return false;
    }

    // check if the king doesn't pass through a square that is attacked by an opponent piece
    // we do it by trying to move the king to the squares between the king and the rook
    // if the king is in check after the move, the castling is not valid

    // move the king to the first square
    board[kingSquare.getLine()][kingSquare.getColumn() - 1] = king;
    board[kingSquare.getLine()][kingSquare.getColumn()] = nullptr;
    board[kingSquare.getLine()][kingSquare.getColumn() - 1]->setPosition((isWhitePlaying? "d1" : "d8"));

    if (isCheck(isWhitePlaying)) {
        cout << red << bold;
        cout << "🚫 Une des cases du roc est attaquée" << endl;
        cout << reset;
        board[kingSquare.getLine()][kingSquare.getColumn() - 1] = nullptr;
        board[kingSquare.getLine()][kingSquare.getColumn()] = king;
        board[kingSquare.getLine()][kingSquare.getColumn()]->setPosition((isWhitePlaying? "e1" : "e8"));
        return false;
    }

    // move the king to the second square
    board[kingSquare.getLine()][kingSquare.getColumn() - 2] = king;
    board[kingSquare.getLine()][kingSquare.getColumn() - 1] = nullptr;
    board[kingSquare.getLine()][kingSquare.getColumn() - 2]->setPosition((isWhitePlaying? "c1" : "c8"));

    if (isCheck(isWhitePlaying)) {
        cout << red << bold;
        cout << "🚫 Une des cases du roc est attaquée" << endl;
        cout << reset;
        board[kingSquare.getLine()][kingSquare.getColumn() - 2] = nullptr;
        board[kingSquare.getLine()][kingSquare.getColumn()] = king;
        board[kingSquare.getLine()][kingSquare.getColumn()]->setPosition((isWhitePlaying? "e1" : "e8"));
        return false;
    }

    // move the king back to the initial position
    board[kingSquare.getLine()][kingSquare.getColumn()] = king;
    board[rookSquare.getLine()][rookSquare.getColumn() + 3] = nullptr;
    board[kingSquare.getLine()][kingSquare.getColumn()]->setPosition((isWhitePlaying? "e1" : "e8"));

    return true;
}

void Board::resignGame() {
    cout << endl;
    cout << blue;
    cout << "Abandon de la partie par les ";
    cout << bold << (isWhitePlaying ? "blancs" : "noirs") << ".";
    cout << endl;

    isPlaying = false;
    if (isWhitePlaying) {
        blackWin = true;
    } else {
        whiteWin = true;
    }
}

void Board::drawGame() {
    isPlaying = false;
}

void Board::endGame() {
    cout << endl;
    cout << white << bold;
    cout << "🏁 Fin de la partie." << endl;
    cout << endl;

    if (whiteWin) {
        cout << "🎉 Les blancs ont gagné." << endl;
    } else if (blackWin) {
        cout << "🎉 Les noirs ont gagné." << endl;
    } else {
        cout << "🤝 Match nul." << endl;
    }

    cout << endl;

}

void Board::changePlayer() {
    isWhitePlaying = !isWhitePlaying;
}

bool Board::processNormalMove(string input) {
    // save the possible en passant before valid move modifies it
    bool savePossibleEnPassant = possibleEnPassant;
    invelidMoveReason = "";

    // verify if the move is valid
    if (!validMove(input, isWhitePlaying)) {
        cout << red << bold;
        cout << "🚫 " << invelidMoveReason << endl;
        cout << reset;
        return false;
    }
    
    // move the piece
    Square start(&input[0]);
    Square end(&input[2]);

    if (board[end.getLine()][end.getColumn()] != nullptr) {
        nbMovesWithoutTaking = 0;
    } else {
        nbMovesWithoutTaking += 1;
    }

    board[end.getLine()][end.getColumn()] = board[start.getLine()][start.getColumn()];
    board[start.getLine()][start.getColumn()] = nullptr;
    board[end.getLine()][end.getColumn()]->setPosition(end.toString());
    board[end.getLine()][end.getColumn()]->setHasMoved();

    // Promotion
    if (board[end.getLine()][end.getColumn()]->getPsymb() == 'P' && end.getLine() == (isWhitePlaying ? 7 : 0)) {
        cout << "♟️ Promotion de pion: ";
        cout << "Choisissez la pièce de promotion (Queen(Q), Rook(R), Bishop(B), Knight(N)): ";
        string promotion;
        cin >> promotion;
        while (promotion != "Q" && promotion != "R" && promotion != "B" && promotion != "N") {
            cout << "🚫 Choix invalide, veuillez réessayer: ";
            cin >> promotion;
        }

        if (promotion == "Q") {
            board[end.getLine()][end.getColumn()] = new Queen(isWhitePlaying ? Color::WHITE : Color::BLACK, 0, end.toString());
        } else if (promotion == "R") {
            board[end.getLine()][end.getColumn()] = new Rook(isWhitePlaying ? Color::WHITE : Color::BLACK, 0, end.toString());
        } else if (promotion == "B") {
            board[end.getLine()][end.getColumn()] = new Bishop(isWhitePlaying ? Color::WHITE : Color::BLACK, 0, end.toString());
        } else if (promotion == "N") {
            board[end.getLine()][end.getColumn()] = new Knight(isWhitePlaying ? Color::WHITE : Color::BLACK, 0, end.toString());
        }
    }

    // handle en passant
    if (savePossibleEnPassant) {
        if (
            board[end.getLine()][end.getColumn()]->getPsymb() == 'P' &&
            abs(end.getLine() - start.getLine()) == 1 &&
            abs(end.getColumn() - start.getColumn()) == 1
        ) {
            board[start.getLine()][end.getColumn()] = nullptr;
        }

        possibleEnPassant = false;
    }

    return true;
}

bool Board::processKingsideCastlingMove() {
    if (!validKingSideCastling(isWhitePlaying))
        return false;
        
    // find the king and the rook positions
    Square kingSquare(&board[isWhitePlaying ? 0 : 7][4]->getPosition()[0]);
    Square rookSquare(&board[isWhitePlaying ? 0 : 7][7]->getPosition()[0]);

    // get the king and the rook
    Piece* king = board[kingSquare.getLine()][kingSquare.getColumn()];
    Piece* rook = board[rookSquare.getLine()][rookSquare.getColumn()];

    // move the king and the rook
    board[rookSquare.getLine()][rookSquare.getColumn() - 1] = king;
    board[rookSquare.getLine()][rookSquare.getColumn() - 2] = rook;
    board[kingSquare.getLine()][kingSquare.getColumn()] = nullptr;
    board[rookSquare.getLine()][rookSquare.getColumn()] = nullptr;

    // update the positions
    board[rookSquare.getLine()][rookSquare.getColumn() - 1]->setPosition((isWhitePlaying? "g1" : "g8"));
    board[rookSquare.getLine()][rookSquare.getColumn() - 2]->setPosition((isWhitePlaying? "f1" : "f8"));
    board[rookSquare.getLine()][rookSquare.getColumn() - 1]->setHasMoved();
    board[rookSquare.getLine()][rookSquare.getColumn() - 2]->setHasMoved();

    nbMovesWithoutTaking += 1;

    return true;
}

bool Board::processQueensideCastlingMove() {
    if (!validQueenSideCastling(isWhitePlaying))
        return false;

    // find the king and the rook positions
    Square kingSquare(&board[isWhitePlaying ? 0 : 7][4]->getPosition()[0]);
    Square rookSquare(&board[isWhitePlaying ? 0 : 7][0]->getPosition()[0]);

    // get the king and the rook
    Piece* king = board[kingSquare.getLine()][kingSquare.getColumn()];
    Piece* rook = board[rookSquare.getLine()][rookSquare.getColumn()];

    // move the king and the rook
    board[kingSquare.getLine()][kingSquare.getColumn() - 2] = king;
    board[kingSquare.getLine()][kingSquare.getColumn() - 1] = rook;
    board[kingSquare.getLine()][kingSquare.getColumn()] = nullptr;
    board[rookSquare.getLine()][rookSquare.getColumn()] = nullptr;

    // update the positions
    board[kingSquare.getLine()][kingSquare.getColumn() - 2]->setPosition((isWhitePlaying? "c1" : "c8"));
    board[kingSquare.getLine()][kingSquare.getColumn() - 1]->setPosition((isWhitePlaying? "d1" : "d8"));
    board[kingSquare.getLine()][kingSquare.getColumn() - 2]->setHasMoved();
    board[kingSquare.getLine()][kingSquare.getColumn() - 1]->setHasMoved();

    nbMovesWithoutTaking += 1;

    return true;
}

bool Board::processMove(string input) {
    if (correctMovementPattern(input)) {
        if (!processNormalMove(input)){
            // invalid move
            return false;
        }
    } else if (correctKingsideCastlingPattern(input)) {
        if (!processKingsideCastlingMove()) {
            // invalid move
            return false;
        }
    } else if (correctQueensideCastlingPattern(input)) {
        if (!processQueensideCastlingMove()) {
            // invalid move
            return false;
        }
    }
    else
    {
        cout << red << bold;
        cout << "🚫 Commande invalide, veuillez réessayer (tapez "; 
        cout << orange << "/help" << red;
        cout << " pour voir les coups valides)." << endl;
        cout << reset;
        return false;
    }

    // IF THE MOVE IS DONE 

    cout << "✅ Mouvement " << input << " effectué." << endl;
    cout << reset;

    // check if the other player is in check
    if (isCheck(!isWhitePlaying)) {
        if (isCheckmate(!isWhitePlaying)) {
            cout << red << bold;
            cout << "👑 Échec et mat pour les " << (!isWhitePlaying ? "blancs" : "noirs")<< endl;
            cout << reset;

            isPlaying = false;
            if (isWhitePlaying) {
                whiteWin = true;
            } else {
                blackWin = true;
            }

            return false;

        } else {
            cout << red << bold;
            cout << "⚔️ Ce mouvement met le roi " << (!isWhitePlaying ? "blanc" : "noir") << " en échec." << endl;
            cout << reset;
        }
    }

    // check if the other player is in stalemate
    if (isStalemate(!isWhitePlaying)) {
        cout << blue << bold;
        cout << "💤 Pat." << endl;
        cout << reset;

        isPlaying = false;
    }

    // save the last inputs in the table of the 5 last moves
    // in order to determine if this is a Stalemate by repetition
    if (isWhitePlaying) {
        for (int i = 4; i > 0; i--) {
            lastMovesWhite[i] = lastMovesWhite[i - 1];
        }
        lastMovesWhite[0] = input;
    } else {
        for (int i = 4; i > 0; i--) {
            lastMovesBlack[i] = lastMovesBlack[i - 1];
        }
        lastMovesBlack[0] = input;
    }

    return true;
}

void Board::game() {
    // ----- Game loop -----
    while (isPlaying) {
        showBoard();
        string input = getInput(isWhitePlaying);

        if (input == "/quit") {
            return;
        } else if (input == "/help") {
            printHelp();
        }  else if (input == "/resign") {
            resignGame();
        }  else if (input == "/draw") {
            drawGame();
        } else {
            if (!processMove(input))
                continue;
            changePlayer();
        }
    }

    endGame();
}