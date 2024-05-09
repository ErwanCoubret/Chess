#include <iostream>

using namespace std;

// -------------------------------------
//                COLORS
// -------------------------------------

#define white "\x1B[37m"
#define bold "\x1b[1m"
#define reset "\x1b[0m"
#define orange "\x1B[33m"
#define blue "\x1B[34m"
#define red "\x1B[31m"

// -------------------------------------
//              INTERFACE
// -------------------------------------

void printBegin();

void printHelp();

void printQuit();

int getInputStart();
