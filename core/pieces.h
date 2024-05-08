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