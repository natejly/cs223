/*
Implementations for core functions for Game of Life assignment in CPSC 223 fall 2024

Author: Alan Weide
Modified by: Nate
Changelog:
 */

#include "life.h"

#include <stdio.h>

bool is_alive(int field[ROWS][COLS], size_t i, size_t j)
{
    return field[i][j] == 1;
}

unsigned int num_living_neighbors(int field[ROWS][COLS], size_t i, size_t j)
{
    int count = 0;
    int mrows = ROWS - 1;
    int mcols = COLS - 1;
    for (int row = i - 1; row <= i + 1; row++)
    {
        for (int col = j - 1; col <= j + 1; col++)
        {
            if (0 <= row && row <= mrows && 0 <= col && col <= mcols)
            {
                if (field[row][col] == 1)
                {
                    count++;
                }
            }
        }
    }
    return count;
}

int get_next_state(int field[ROWS][COLS], size_t i, size_t j)
{
    int alive_neighbors = num_living_neighbors(field, i, j);
    bool alive = is_alive(field, i, j);
    if (alive)
    {
        if (alive_neighbors == 2 || alive_neighbors == 3)
        {
            return 1;
        }
        return 0;
    }
    else
    {
        if (alive_neighbors == 3)
        {
            return 1;
        }
        return 0;
    }
}

void compute_next_gen(int cur_field[ROWS][COLS], int next_field[ROWS][COLS])
{
    for (size_t i = 0; i < ROWS; i++)
    {
        for (size_t j = 0; j < COLS; j++)
        {
            next_field[i][j] = get_next_state(cur_field, i, j);
        }
    }
}
