/**
 * @file pieces.h
 * @brief Header file for the game pieces
 */

#include <string>
using namespace std;


/**
 * @enum Color
 * @brief Enumerates the colors of the pieces
*/
enum class Color {
    WHITE,
    BLACK
};

/**
 * @class Square
 * @brief Class representing a square on the board
*/
class Square {
private:
    int column;
    int line;
public:
    Square(char* move) :
        column(move[0] - 'a'),
        line(move[1] - '1')
    {}
    
    /**
     * @brief Get the line of the square
     * @return The line of the square
    */
    int getLine() const;

    /**
     * @brief Get the column of the square
     * @return The column of the square
    */
    int getColumn() const;

    /**
     * @brief Convert the square to a string
     * @return The string representation of the square
    */
    string toString() const;
};

// ------------------------------------------------
//              PARENT CLASS PIECE
// ------------------------------------------------

/**
 * @class Piece
 * @brief Class representing a piece on the board
*/
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

    // ------------------------------------------------
    //                 GETTERS & SETTERS
    // ------------------------------------------------

    /**
     * @brief Get the icon of the piece
     * @return The icon of the piece
    */
    string getIcon() const;

    /**
     * @brief Get the piece symbol
     * @return The piece symbol (Pawn: P, Rook: R, Knight: N, Bishop: B, Queen: Q, King: K)
    */
    char getPsymb() const;

    /**
     * @brief Get the color of the piece
     * @return The color of the piece
    */
    Color getColor() const;

    /**
     * @brief Get the position of the piece
     * @return The position of the piece
    */
    string getPosition() const;

    /**
     * @brief Get if the piece has moved
     * @return True if the piece has moved, false otherwise
    */
    bool getHasMoved() const;

    /**
     * @brief Set the position of the piece
     * @param position The new position of the piece
    */
    void setPosition(string position);

    /**
     * @brief Set the piece as moved, used for castling and pawn double move
    */
    void setHasMoved();
};

// ------------------------------------------------
//                PIECE CLASSES
// ------------------------------------------------

/**
 * @class Pawn
 * @brief Class representing a pawn piece
*/
class Pawn : public Piece {
public:
    Pawn(Color color, int id, string position) :
        Piece((color == Color::WHITE ? "♙" : "♟"), color, 'P', id, position) {}
};

/**
 * @class Rook
 * @brief Class representing a rook piece
*/
class Rook : public Piece {
public:
    Rook(Color color, int id, string position) :
        Piece((color == Color::WHITE ? "♖" : "♜"), color, 'R', id, position) {}
};

/**
 * @class Knight
 * @brief Class representing a knight piece
*/
class Knight : public Piece {
public:
    Knight(Color color, int id, string position) :
        Piece((color == Color::WHITE ? "♘" : "♞"), color, 'N', id, position) {}
};

/**
 * @class Bishop
 * @brief Class representing a bishop piece
*/
class Bishop : public Piece {
public:
    Bishop(Color color, int id, string position) :
        Piece((color == Color::WHITE ? "♗" : "♝"), color, 'B', id, position) {}
};

/**
 * @class Queen
 * @brief Class representing a queen piece
*/
class Queen : public Piece {
public:
    Queen(Color color, int id, string position) :
        Piece((color == Color::WHITE ? "♕" : "♛"), color, 'Q', id, position) {}
};

/**
 * @class King
 * @brief Class representing a king piece
*/
class King : public Piece {
public:
    King(Color color, int id, string position) :
        Piece((color == Color::WHITE ? "♔" : "♚"), color, 'K', id, position) {}
};