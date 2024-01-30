#pragma once
/*
Interface for core functions for Game of Life assignment in CPSC 223 fall 2024

Author: Alan Weide
Modified by: STUDENT NAME HERE
Changelog:
 */
#include <stdbool.h>
#include <stdlib.h>

#include "constants.h"

#define ALIVE 1
#define DEAD 0

/**
 * Reports whether field[i][j] is alive.
 *
 * @param field the 2D array representing the state of the game
 * @param i the row-index to check
 * @param j the column-index to check
 * @returns true iff field[i][j] == ALIVE
 * @assumes field[i][j] exists
 */
bool is_alive(int field[ROWS][COLS], size_t i, size_t j);

/**
 * Reports the number of alive neighbors of cell field[i][j].
 *
 * @param field the 2D array representing the state of the game
 * @param i the row-index to check
 * @param j the column-index to check
 * @returns the number of cells adjacent to field[i][j] that are ALIVE. Neighbor cells that do not exist do not count as alive.
 * @assumes field[i][j] exists
 */
unsigned int num_living_neighbors(int field[ROWS][COLS], size_t i, size_t j);

/**
 * Reports the state of field[i][j] in the next time step according to the rules of the Game of Life.
 *
 * @param field the 2D array representing the state of the game
 * @param i the row-index
 * @param j the column-index
 * @returns ALIVE or DEAD as the rules for Game of Life determine wither field[i][j] should be ALIVE or DEAD in the next time step of the game.
 * @assumes field[i][j] exists and that every cell in field is either ALIVE or DEAD
 */
int get_next_state(int field[ROWS][COLS], size_t i, size_t j);

/**
 * Computes the state at the next time step given the state described by cur_field, storing the next state in next_field.
 *
 * @param cur_field the 2D array representing the current state
 * @param next_field the 2D array in which to store the representation of the next state
 * @does computes the next state of the game of life given the state described by cur_field. The new state is stored in next_field.
 * @assumes all cells in cur_field are either ALIVE or DEAD.
 */
void compute_next_gen(int cur_field[ROWS][COLS], int next_field[ROWS][COLS]);
