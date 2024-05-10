/**
 * @file pieces.cpp
 * @brief Implementation file for the game pieces
*/

#include "pieces.h"

// ------------------------------------------------
//                 GETTERS & SETTERS
// ------------------------------------------------

int Square::getLine() const {
    return line;
}

int Square::getColumn() const {
    return column;
}

string Square::toString() const {
    string str = "";
    str += column + 'a';
    str += line + '1';
    return str;
}

string Piece::getIcon() const {
    return name;
}

char Piece::getPsymb() const {
    return psymb;
}

Color Piece::getColor() const {
    return color;
}

string Piece::getPosition() const {
    return position;
}

bool Piece::getHasMoved() const {
    return hasMoved;
}

void Piece::setPosition(string position) {
    this->position = position;
}

void Piece::setHasMoved() {
    this->hasMoved = true;
}