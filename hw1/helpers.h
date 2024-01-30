#pragma once
/*
Interface for helper functions for Game of Life assignment for CPSC 223 Spring 2024.

Author: Alan Weide
Modified by: STUDENT NAME HERE
Changelog:
*/

#include <stdlib.h>

#include "constants.h"

/**
 * Prints the field formatted for the initial state as described in the README.
 *
 * @param field the 2D array to print
 * @does prints the string "Initial Values" on its own line followed by ROWS lines each containing a row of the field, in a space-separated list beginning at column 4
 */
void print_initial(int field[ROWS][COLS]);

/**
 * Prints the field formatted for the gen-th generation as described in the README.
 *
 * @param field the 2D array to print
 * @does prints the string "Step {gen}" on its own line followed by ROWS lines each containing a row of the field, in a space-separated list beginning at column 4
 */
void print_generation(int field[ROWS][COLS], unsigned int gen);
