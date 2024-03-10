// Nate Ly, CS223 Pset #4 (Blotto), 3/10/2024
//implementation for main helpers in blottohelpers.h
#include "blottohelpers.h"
#include "gmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entry.h"
int validInput(argc)
{
    if (argc < 2) // more than 1 arg 
    {
        fprintf(stderr, "not enough args");
        return 1;
    }
    if (feof(stdin)) // make sure stdin has stuff
    {
        fprintf(stderr, "stdin is empty\n");
        return 1;
    }
}
void free_pointerfunction(gmap *m, void *value, void *thing)
//used as function poitner in gmap_foreach to free distributions
{
    free(value);
}
int read_matchups_print(gmap *map, size_t MAX_ID, int *battlefields, int num_battles)
{
    char *line = malloc(MAX_ID * sizeof(char));
    // reading in the matchups
    char *player1;
    char *player2;
    while (freadln(line, MAX_ID, stdin) != NULL)
    {
        player1 = strtok(line, " ");
        player2 = strtok(NULL, "");
        if (player1 == NULL || player2 == NULL)
        {
            free(line);
            return 1;
        }
        //get points distributions
        int *player1_distribution = gmap_get(map, player1);
        int *player2_distribution = gmap_get(map, player2);
        if (!player1_distribution || !player2_distribution)
        {
            free(line);
            return 1;
        }
        double player1_score = 0;
        double player2_score = 0;
        //calculate scores
        for (size_t i = 0; i < num_battles; i++)
        {
            if (player1_distribution[i] > player2_distribution[i])
            {
                player1_score += battlefields[i];
            }
            else if (player1_distribution[i] < player2_distribution[i])
            {
                player2_score += battlefields[i];
            }
            else
            {
                player1_score += battlefields[i] / 2.0;
                player2_score += battlefields[i] / 2.0;
            }
        }
        //print scores
        if (player1_score >= player2_score)
        {
            fprintf(stdout, "%s %.1f - %s %.1f\n", player1, player1_score, player2, player2_score);
        }
        else
        {
            fprintf(stdout, "%s %.1f - %s %.1f\n", player2, player2_score, player1, player1_score);
        }
    }
    free(line);
}
