#include "interface.h"

// -------------------------------------
//              INTERFACE
// -------------------------------------

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
    cout << "\tExemple : pour déplacer un pion en e2 à e4, tapez" << orange << " e2e4" << endl;
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
