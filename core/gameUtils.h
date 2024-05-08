#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include "interface.h"

using namespace std;

enum class Color {
    WHITE,
    BLACK
};

// -------------------------------------
//              PIECES
// -------------------------------------

class Square {
private:
    int column;
    int line;
public:
    Square(char* move) :
        column(move[0] - 'a'),
        line(move[1] - '1')
    {}

    int getLine() const {
        return line;
    }

    int getColumn() const {
        return column;
    }

    string toString() const {
        string str = "";
        str += column + 'a';
        str += line + '1';
        return str;
    }
};

class Piece {
private:
    string name;
    Color color;
    char psymb;
    int id;
    string position;
    bool hasMoved = false;
public:
    Piece(string name, Color color, char psymb, int id, string position) :
        name(name),
        color(color),
        psymb(psymb),
        id(id),
        position(position)
    {}

    string getIcon() const {
        return name;
    }

    char getPsymb() const {
        return psymb;
    }

    Color getColor() const {
        return color;
    }

    string getPosition() const {
        return position;
    }

    void setPosition(string position) {
        this->position = position;
    }

    bool getHasMoved() const {
        return hasMoved;
    }

    void setHasMoved() {
        this->hasMoved = true;
    }
};

class Pawn : public Piece {
public:
    Pawn(Color color, int id, string position) :
        Piece((color == Color::WHITE ? "♙" : "♟"), color, 'P', id, position) {}
};

class Rook : public Piece {
public:
    Rook(Color color, int id, string position) :
        Piece((color == Color::WHITE ? "♖" : "♜"), color, 'R', id, position) {}
};

class Knight : public Piece {
public:
    Knight(Color color, int id, string position) :
        Piece((color == Color::WHITE ? "♘" : "♞"), color, 'N', id, position) {}
};

class Bishop : public Piece {
public:
    Bishop(Color color, int id, string position) :
        Piece((color == Color::WHITE ? "♗" : "♝"), color, 'B', id, position) {}
};

class Queen : public Piece {
public:
    Queen(Color color, int id, string position) :
        Piece((color == Color::WHITE ? "♕" : "♛"), color, 'Q', id, position) {}
};

class King : public Piece {
public:
    King(Color color, int id, string position) :
        Piece((color == Color::WHITE ? "♔" : "♚"), color, 'K', id, position) {}
};

// -------------------------------------
//              UTILS
// -------------------------------------

bool correctMovementPattern(string const & cmd) {
    regex mouvementPattern("[a-h][1-8][a-h][1-8]");
    return regex_match(cmd, mouvementPattern);
}

bool correctKingsideCastlingPattern(string const & cmd) {
    regex kingsideCastlingPattern("(O|o|0)-(O|o|0)");
    return regex_match(cmd, kingsideCastlingPattern);
}

bool correctQueensideCastlingPattern(string const & cmd) {
    regex queensideCastlingPattern("(O|o|0)-(O|o|0)");
    return regex_match(cmd, queensideCastlingPattern);
}

class Board {
private:
    vector< vector<Piece*> > board;
    bool isWhitePlaying = true;
    bool isPlaying = true;
    bool isCheck = false;
    bool isCheckmate = false;
    bool whiteWin = false;
    bool blackWin = false;
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

    // check if the move is valid for a specific piece
    bool checkMove(Piece* piece, Square start, Square end);

    // check if the king is in check
    bool checkCheck(bool isWhitePlaying);

    // Start the game
    void startGame();

    // Print the board state as string
    string canonical_position() const;
};

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
    startGame();
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
    for (size_t row(1); row<=8; row++){
            for (char col('a');col<='h';col++) {
                if (board[8-row][col-'a'] != nullptr) {
                    output += (board[8-row][col-'a']->getColor() == Color::WHITE ? "w" : "b");
                    output += board[8-row][col-'a']->getPsymb();
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

bool Board::checkMove(Piece* piece, Square start, Square end) {
    // cout << piece->getPsymb() << start.getLine() << start.getColumn() << " to " << end.getLine() << end.getColumn();
    Piece* endPiece = board[end.getLine()][end.getColumn()];

    // ----- WHITE PAWN LOGIC -----
    if (piece->getPsymb() == 'P' && piece->getColor() == Color::WHITE) {
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
                return true;
            }
        } else {
            // pawn is capturing a piece
            if (
                end.getLine() == start.getLine() + 1 &&
                abs(end.getColumn() - start.getColumn()) == 1 &&
                endPiece->getColor() != piece->getColor()
            ) {
                return true;
            }

            // pawn is capturing a piece using en passant move -> TODO
        }

        return false;
    }

    // ----- BLACK PAWN LOGIC -----
    if (piece->getPsymb() == 'P' && piece->getColor() == Color::BLACK) {
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
                return true;
            }
        } else {
            // pawn is capturing a piece
            if (
                end.getLine() == start.getLine() - 1 &&
                abs(end.getColumn() - start.getColumn()) == 1 &&
                endPiece->getColor() != piece->getColor()
            ) {
                return true;
            }

            // pawn is capturing a piece using en passant move -> TODO
        }

        return false;
    }

    // ----- ROOK LOGIC -----
    if (piece->getPsymb() == 'R') {
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
                    endPiece->getColor() != piece->getColor()
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
                    endPiece->getColor() != piece->getColor()
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
                    endPiece->getColor() != piece->getColor()
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
                    endPiece->getColor() != piece->getColor()
                ) {
                    return true;
                }

                return false;
            }
        }
    }

    // ----- KNIGHT LOGIC -----
    if (piece->getPsymb() == 'N') {
        if (
            (abs(end.getLine() - start.getLine()) == 2 && abs(end.getColumn() - start.getColumn()) == 1) ||
            (abs(end.getLine() - start.getLine()) == 1 && abs(end.getColumn() - start.getColumn()) == 2)
        ) {
            if (
                endPiece == nullptr ||
                endPiece->getColor() != piece->getColor()
            ) {
                return true;
            }

            return false;
        }
        return false;
    }

    // ----- BISHOP LOGIC -----
    if (piece->getPsymb() == 'B') {
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
                    endPiece->getColor() != piece->getColor()
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
                    endPiece->getColor() != piece->getColor()
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
                    endPiece->getColor() != piece->getColor()
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
                    endPiece->getColor() != piece->getColor()
                ) {
                    return true;
                }

                return false;
            }
        }
    }

    // ----- QUEEN LOGIC -----
    if (piece->getPsymb() == 'Q') {
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
                    endPiece->getColor() != piece->getColor()
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
                    endPiece->getColor() != piece->getColor()
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
                    endPiece->getColor() != piece->getColor()
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
                    endPiece->getColor() != piece->getColor()
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
                    endPiece->getColor() != piece->getColor()
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
                    endPiece->getColor() != piece->getColor()
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
                    endPiece->getColor() != piece->getColor()
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
                    endPiece->getColor() != piece->getColor()
                ) {
                    return true;
                }

                return false;
            }
        }
    }

    // ----- KING LOGIC -----
    if (piece->getPsymb() == 'K') {
        // king is moving vertically
        if (abs(end.getLine() - start.getLine()) == 1 && abs(end.getColumn() - start.getColumn()) == 0) {
            if (
                endPiece == nullptr ||
                endPiece->getColor() != piece->getColor()
            ) {
                return true;
            }

            return false;
        }

        // king is moving horizontally
        if (abs(end.getColumn() - start.getColumn()) == 1 && abs(end.getLine() - start.getLine()) == 0) {
            if (
                endPiece == nullptr ||
                endPiece->getColor() != piece->getColor()
            ) {
                return true;
            }

            return false;
        }

        // king is moving diagonally
        if (abs(end.getLine() - start.getLine()) == 1 && abs(end.getColumn() - start.getColumn()) == 1) {
            if (
                endPiece == nullptr ||
                endPiece->getColor() != piece->getColor()
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
    }

    return false;
}

bool Board::checkCheck(bool isWhitePlaying) {
    // get the king position
    string kingPosition;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != nullptr && board[i][j]->getPsymb() == 'K' && board[i][j]->getColor() == (isWhitePlaying ? Color::WHITE : Color::BLACK)) {
                kingPosition = board[i][j]->getPosition();
            }   
        }
    }

    // check if the king is in check
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != nullptr && board[i][j]->getColor() != (isWhitePlaying ? Color::WHITE : Color::BLACK)) {
                if (checkMove(board[i][j], Square(&board[i][j]->getPosition()[0]), Square(&kingPosition[0]))) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Board::validMove(string input, bool isWhitePlaying) {
    Square start(&input[0]);
    Square end(&input[2]);

    // get the piece at the initial position
    Piece* piece = board[start.getLine()][start.getColumn()];

    // check if there is a piece at the initial position
    if (piece == nullptr) {
        cout << red << bold;
        cout << "🚫 Il n'y a pas de pièce à cet endroit." << endl;
        cout << reset;
        return false;
    }

    // check if the piece is the right color
    if ((isWhitePlaying && piece->getColor() == Color::BLACK) || (!isWhitePlaying && piece->getColor() == Color::WHITE)) {
        cout << red << bold;
        cout << "🚫 Vous ne pouvez pas jouer cette pièce." << endl;
        cout << reset;
        return false;
    }

    // check if the end is the start
    if (start.toString() == end.toString()) {
        cout << red << bold;
        cout << "🚫 Vous devez déplacer la pièce." << endl;
        cout << reset;
        return false;
    }

    // check if the Piece can move to the end position
    if (!checkMove(piece, start, end)) {
        cout << red << bold;
        cout << "🚫 Ce mouvement n'est pas valide." << endl;
        cout << reset;
        return false;
    }

    // check if the move doesn't put the king in check
    // we save the current state of squares, try the move, check if the king is in check, and then revert the move
    Piece* startPiece = board[start.getLine()][start.getColumn()];
    Piece* endPiece = board[end.getLine()][end.getColumn()];
    board[end.getLine()][end.getColumn()] = board[start.getLine()][start.getColumn()];
    board[start.getLine()][start.getColumn()] = nullptr;

    if (checkCheck(isWhitePlaying)) {
        cout << red << bold;
        cout << "🚫 Le roi " << (isWhitePlaying ? "blanc" : "noir") << " est en échec." << endl;
        cout << reset;
        board[start.getLine()][start.getColumn()] = startPiece;
        board[end.getLine()][end.getColumn()] = endPiece;
        return false;
    }

    board[start.getLine()][start.getColumn()] = startPiece;
    board[end.getLine()][end.getColumn()] = endPiece;
    
    return true;
}

void Board::startGame() {
    // ----- Game loop -----
    while (isPlaying) {
        showBoard();
        string input = getInput(isWhitePlaying);

        if (input == "/quit")
        {
            return;
        } 
        else if (input == "/help")
        {
            printHelp();
        } 
        else if (input == "/resign")
        {
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
        else if (input == "/draw")
        {
            isPlaying = false;
            return;
        } else {
            if (correctMovementPattern(input)) {
                if (!validMove(input, isWhitePlaying))
                    continue;

                // move the piece
                Square start(&input[0]);
                Square end(&input[2]);
                board[end.getLine()][end.getColumn()] = board[start.getLine()][start.getColumn()];
                board[start.getLine()][start.getColumn()] = nullptr;
                board[end.getLine()][end.getColumn()]->setPosition(end.toString());
                board[end.getLine()][end.getColumn()]->setHasMoved();
            } else if (correctKingsideCastlingPattern(input)) {
                continue;
            } else if (correctQueensideCastlingPattern(input)) {
                continue;
            }
            else {
                cout << red << bold;
                cout << "🚫 Commande invalide, veuillez réessayer (tapez "; 
                cout << orange << "/help" << red;
                cout << " pour voir les coups valides)." << endl;
                cout << reset;
                continue;
            }

            cout << "✅ Mouvement " << input << " effectué." << endl;
            cout << reset;

            // check if the other player is in check
            if (checkCheck(!isWhitePlaying)) {
                cout << red << bold;
                cout << "👑 Ce mouvement met le roi " << (!isWhitePlaying ? "blanc" : "noir") << " en échec." << endl;
                cout << reset;
            }
        
            isWhitePlaying = !isWhitePlaying;
        }
    }

    if (whiteWin || blackWin) {
        cout << endl;
        cout << "🎉 ";
        cout << white << bold;
        cout << (whiteWin ? "Les blancs" : "Les noirs");
        cout << reset;
        cout << " remportent la partie !" << endl;
    } else {
        cout << endl;
        cout << "🤝 La partie se termine sur un match nul." << endl;
    }

}