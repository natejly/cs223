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
    /*
     * TODO: Accept two command-line arguments, which will appear in the
     * following order:
     * time_steps:
     *      a positive integer describing how many "generations" the simulation
     *      will run for.
     * init:
     *      a string consisting of the characters '0' and '1', of length ROWS * COLS,
     *      representing the initial state for this run of Game of Life.
     */

    int time_steps = atoi(argv[1]);

    printf("Time Steps: %d\n", time_steps);
    printf("Init String: %s\n", argv[2]);
    /*
     * TODO: Create a new statically-allocated array of size ROWS x COLS
     */
    char board [ROWS][COLS];
    int init_index = 0;
    for (size_t i = 0; i < ROWS; i++)
    {
        for (size_t j = 0; j < COLS; j++)
        {
            board[i][j] = argv[2][init_index];

            init_index++;
        }
    }
    /*
     * TODO: Print the initial values held in the field
     */
    // for (int i = 0; i < ROWS; i++)
    // {
    //     for (int j = 0; j < COLS; j++)
    //     {
    //         printf("%c\t", board[i][j]);
    //     }
    //     printf("\n");
    // }
    print_initial(board);
    /*
     * TODO: Run the game time_steps times, printing the field at the end of
     * each step
     */
    for(size_t i = 0; i < time_steps; i++){
        print_generation(board, i);
    }
    /*
     * Print "Done." then exit.
     */
    printf("Done.\n");
    return 0;
}
