/*
Driver for Game of Life assignment in CPSC 223 Fall 2023

Author: Nate Ly
*/

#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "life.h"
#include "helpers.h"
void printArray(int array[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%d\t", array[i][j]);
        }
        printf("\n");
    }
}
int main(int argc, char *argv[])
{

    int time_steps = atoi(argv[1]);

    int board[ROWS][COLS];
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

    for (size_t i = 0; i < time_steps; i++)
    {
        compute_next_gen(board, board);
        print_generation(board, i + 1);
        }

    printf("Done.\n");
    return 0;
}
