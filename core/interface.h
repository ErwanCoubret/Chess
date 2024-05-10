/**
 * @file interface.h
 * @brief Header file for the game interface & colors
 */

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
#define green "\x1B[32m"

// -------------------------------------
//              INTERFACE
// -------------------------------------

/**
 * @brief Print the beginning of the game
*/
void printBegin();

/**
 * @brief Print the help message
*/
void printHelp();

/**
 * @brief Print the quit message
*/
void printQuit();