/*
Implementations of helper functions for Game of Life assignment for CPSC 223 Spring 2024.

Author: Alan Weide
Modified by: STUDENT NAME HERE
Changelog:
*/
#include "helpers.h"

#include <stdio.h>

#include "life.h"

#define ALIVE_CH '#'
#define DEAD_CH ' '

void print_initial(int field[ROWS][COLS])
{
    printf("Initial Values\n");
    for (size_t i = 0; i < ROWS; i++)
    {
        printf("    ");
        for (size_t j = 0; j < COLS; j++)
        {
            printf("%c ", is_alive(field, i, j) ? ALIVE_CH : DEAD_CH);
        }
        printf("\n");
    }
}

void print_generation(int field[ROWS][COLS], unsigned int gen)
{
    printf("Step %d\n", gen);
    for (size_t i = 0; i < ROWS; i++)
    {
        printf("    ");
        for (size_t j = 0; j < COLS; j++)
        {
            printf("%c ", is_alive(field, i, j) ? ALIVE_CH : DEAD_CH);
        }
        printf("\n");
    }
}
