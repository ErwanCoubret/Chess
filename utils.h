#include <iostream>
#include <vector>
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
        line(move[1] - '0')
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
        str += line + '0';
        return str;
    }
};

class Piece {
private:
    string name;
    Color color;
    int id;
    string position;
public:
    Piece(string name, Color color, int id, string position) :
        name(name),
        color(color),
        id(id),
        position(position)
    {}

    string affiche() const {
        return name;
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

};

class Pawn : public Piece {
public:
    Pawn(Color color, int id, string position) :
        Piece((color == Color::WHITE ? "♟" : "♙"), color, id, position) {}
};

class Rook : public Piece {
public:
    Rook(Color color, int id, string position) :
        Piece((color == Color::WHITE ? "♜" : "♖"), color, id, position) {}
};

class Knight : public Piece {
public:
    Knight(Color color, int id, string position) :
        Piece((color == Color::WHITE ? "♞" : "♘"), color, id, position) {}
};

class Bishop : public Piece {
public:
    Bishop(Color color, int id, string position) :
        Piece((color == Color::WHITE ? "♝" : "♗"), color, id, position) {}
};

class Queen : public Piece {
public:
    Queen(Color color, int id, string position) :
        Piece((color == Color::WHITE ? "♛" : "♕"), color, id, position) {}
};

class King : public Piece {
public:
    King(Color color, int id, string position) :
        Piece((color == Color::WHITE ? "♚" : "♔"), color, id, position) {}
};

class Board {
private:
    vector< vector<Piece*> > board;
public:
    Board() :
        board(8, vector<Piece*>(8))
    {}

    void init() {
        board[0][0] = new Rook(Color::BLACK, 1, "a1");
        board[0][1] = new Knight(Color::BLACK, 2, "b1");
        board[0][2] = new Bishop(Color::BLACK, 3, "c1");
        board[0][3] = new Queen(Color::BLACK, 4, "d1");
        board[0][4] = new King(Color::BLACK, 5, "e1");
        board[0][5] = new Bishop(Color::BLACK, 6, "f1");
        board[0][6] = new Knight(Color::BLACK, 7, "g1");
        board[0][7] = new Rook(Color::BLACK, 8, "h1");

        board[7][0] = new Rook(Color::WHITE, 9, "a8");
        board[7][1] = new Knight(Color::WHITE, 10, "b8");
        board[7][2] = new Bishop(Color::WHITE, 11, "c8");
        board[7][3] = new Queen(Color::WHITE, 12, "d8");
        board[7][4] = new King(Color::WHITE, 13, "e8");
        board[7][5] = new Bishop(Color::WHITE, 14, "f8");
        board[7][6] = new Knight(Color::WHITE, 15, "g8");
        board[7][7] = new Rook(Color::WHITE, 16, "h8");

        for (int i = 0; i < 8; i++) {
            board[1][i] = new Pawn(Color::BLACK, i + 17, "a" + to_string(i + 2));
            board[6][i] = new Pawn(Color::WHITE, i + 25, "a" + to_string(i + 7));
        }

        for (int i = 2; i < 6; i++) {
            for (int j = 0; j < 8; j++) {
                board[i][j] = nullptr;
            }
        }
    }

    void show() {
        cout << endl;
        cout << "\t     a   b   c   d   e   f   g   h  \n";
        cout << "\t   ┌───┬───┬───┬───┬───┬───┬───┬───┐\n";
        for (int i = 0; i < 7; i++) {
            cout << "\t" << 8 - i << "  │";
            for (int j = 0; j < 7; j++) {
                cout << " ";
                if (board[i][j] == nullptr) {
                    cout << "  │";
                } else {
                    cout << board[i][j]->affiche() << " │";
                }
                
            }
            
            cout << " ";
            if (board[i][7] == nullptr) {
                cout << "  │";
            } else {
                cout << board[i][7]->affiche() << " │";
            }
            cout << endl;
            cout << "\t   ├───┼───┼───┼───┼───┼───┼───┼───┤\n";
        }
        cout << "\t1  │";
        for (int i = 0; i < 7; i++) {
            cout << " ";
            if (board[7][i] == nullptr) {
                cout << "  │";
            } else {
                cout << board[7][i]->affiche() << " │";
            }
        }
        cout << " ";
        if (board[7][7] == nullptr) {
            cout << "  │";
        } else {
            cout << board[7][7]->affiche() << " │";
        }
        cout << endl;
        cout << "\t   └───┴───┴───┴───┴───┴───┴───┴───┘\n";
        cout << "\t     a   b   c   d   e   f   g   h  \n";
        cout << endl;
        
    }
};