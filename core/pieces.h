#include <string>
using namespace std;

enum class Color {
    WHITE,
    BLACK
};

class Square {
private:
    int column;
    int line;
public:
    Square(char* move) :
        column(move[0] - 'a'),
        line(move[1] - '1')
    {}

    int getLine() const;

    int getColumn() const;

    string toString() const;
};

// ------------------------------------------------
//              PARENT CLASS PIECE
// ------------------------------------------------

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

    string getIcon() const;

    char getPsymb() const;

    Color getColor() const;

    string getPosition() const;

    bool getHasMoved() const;

    void setPosition(string position);

    void setHasMoved();
};

// ------------------------------------------------
//                PIECE CLASSES
// ------------------------------------------------

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