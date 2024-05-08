#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

#define white "\x1B[37m"
#define bold "\x1b[1m"
#define reset "\x1b[0m"
#define orange "\x1B[33m"
#define blue "\x1B[34m"
#define red "\x1B[31m"

enum class Color {
    WHITE,
    BLACK
};

void printBegin() {
    cout << endl;
    cout << bold << white;
    cout << endl;
    cout << "\t\t┌────────────────┐" << endl;
    cout << "\t\t│ Jeu d'échec ♟♙ │" << endl;
    cout << "\t\t└────────────────┘" << endl;
    cout << endl;

    cout << "\t👋 Bienvenue dans le jeu d'échec !" << endl;
    cout << "\t👥 Il s'agit d'un jeu en local, soyez 2 pour y jouer." << endl;

    cout << reset << bold;

    cout << endl;

    cout << "\t🕹️  Pour commencer une partie, tapez" << orange << " \\play" << endl;
    cout << reset << bold;
    cout << "\t📜 Pour voir comment jouer au jeu, tapez" << orange << " \\help" << endl;
    cout << reset << bold;
    cout << "\t🚪 Pour quitter le jeu, tapez" << orange << " \\quit" << endl;

    cout << endl;
    cout << endl;
}

void printHelp() {
    cout << bold << white;
    cout << endl;
    cout << endl;
    cout << "\t\t┌──────────────────┐" << endl;
    cout << "\t\t│ 📜 Comment jouer │" << endl;
    cout << "\t\t└──────────────────┘" << endl;

    cout << endl;

    cout << reset << bold;
    cout << "\t🕹️  Pour déplacer une pièce, tapez" << orange << " <position de début><position d'arrivée>" << endl;
    cout << reset << bold;
    cout << "\tExemple : pour déplacer le pion en e2 à e4, tapez" << orange << " e2e4" << endl;
    cout << reset;

    cout << endl;

    string skip;
    cout << "Appuyez sur ";
    cout << white << bold << "Entrée" << reset;
    cout << " pour continuer...";
    cin.ignore();
    getline(cin, skip);

    cout << endl;
    cout << endl;
}


void printQuit() {
    cout << bold << white;
    cout << endl;
    cout << endl;
    cout << "\t\t┌───────────────────┐" << endl;
    cout << "\t\t│ 🚪 Quitter le jeu │" << endl;
    cout << "\t\t└───────────────────┘" << endl;

    cout << endl;

    cout << reset << bold;
    cout << "\t👋 Merci d'avoir joué, à bientôt !" << endl;
    cout << endl;
}

int getInputStart() {
    string input;

    while (true)
    {
        cout << white << bold;
        cout << "🔧 Entrez votre commande: ";
        cout << orange;
        cin >> input;

        if (input == "\\quit") {
            return 0;
        } else if (input == "\\play") {
            return 1;
        } else if (input == "\\help") {
            printHelp();
        } else {
            cout << red;
            cout << "🚫 Commande invalide, veuillez réessayer." << endl;
            cout << reset;
            cout << endl;
        }
    }
}

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

bool saisie_correcte(string const & cmd) {
    regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
        return regex_match(cmd,mouvmtpattern);
}

bool saisie_correcte_petitroque(string const & cmd) {
    regex mouvmtpattern("(O|o|0)-(O|o|0)");
        return regex_match(cmd,mouvmtpattern);
}

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
        cout << white << bold;
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

    string getInput(bool isWhitePlaying) {
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
        cout << reset;

        return input;
    }

    void begin() {
        
        bool isWhitePlaying = true;
        bool isPlaying = true;
        bool isCheck = false;
        bool isCheckmate = false;
        bool whiteWin = false;
        bool blackWin = false;

        while (isPlaying) {
            show();

            string input = getInput(isWhitePlaying);
            
            if (input == "\\quit") {
                isPlaying = false;
                return;
            } else if (input == "\\help") {
                printHelp();
            } else if (input == "\\resign") {
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
            } else if (input == "\\draw") {
                cout << endl;
                cout << "Proposition de match nul par les ";
                cout << white << bold << (isWhitePlaying ? "blancs" : "noirs") << ".";
                cout << endl;
                cout << reset;
                cout << "🤝 Acceptez-vous la proposition de match nul ? (y/n): ";
                string response;
                cin >> response;


                if (response == "y") {
                    cout << endl;
                    isPlaying = false;
                } else {
                    cout << endl;
                    cout << red << bold;
                    cout << "⛔ Proposition de match nul refusée." << endl;
                    cout << reset;
                }
            
            } else {
                if (saisie_correcte(input)) {
                    cout << "Déplacement de " << input << endl;
                    isWhitePlaying = !isWhitePlaying;
                } else if (saisie_correcte_petitroque(input)) {
                    cout << "Petit roque" << endl;
                } else {
                    cout << red << bold;
                    cout << "🚫 Commande invalide, veuillez réessayer (tapez "; 
                    cout << orange << "\\help" << red;
                    cout << " pour voir les coups valides)." << endl;
                    cout << reset;
                }
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
};