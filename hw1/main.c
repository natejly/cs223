/*
Driver for Game of Life assignment in CPSC 223 Fall 2023

Author: Nate Ly
*/

#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "life.h"
#include "helpers.h"
int main(int argc, char *argv[])
{
    // initialize steps and creeate space for arrays
    int time_steps = atoi(argv[1]);
    int board[ROWS][COLS];
    int next[ROWS][COLS];
    // copy the init string into a 2d array
    int init_index = 0;
    for (size_t i = 0; i < ROWS; i++)
    {
        for (size_t j = 0; j < COLS; j++)
        {
            board[i][j] = argv[2][init_index] - '0';
            init_index++;
        }
    }
    print_initial(board);
    // keep doing next steps untill we reach the number specified
    for (size_t i = 0; i < time_steps; i++)
    {
        compute_next_gen(board, next);
        print_generation(next, i + 1);
        // update board
        for (size_t i = 0; i < ROWS; i++)
        {
            for (size_t j = 0; j < COLS; j++)
            {
                board[i][j] = next[i][j];
            }
        }
    }
    printf("Done.\n");
    return 0;
}
