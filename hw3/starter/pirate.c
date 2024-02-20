/**
 * Implementation file for pirate for HookBook B in CPSC 223 SP2024.
 *
 * Author: Nate Ly
 */
#include "pirate.h"
#include "libhookbook.h"
#include <stdlib.h>
#include <string.h>
pirate *pirate_create(char *name)
{
    pirate *new_pirate = malloc(sizeof(pirate));

    (*new_pirate).name = name;
    //????? 
    (*new_pirate).vessel = NULL;
    (*new_pirate).treasure = -1;
    return new_pirate;
}

pirate *pirate_read(FILE *restrict input)
{
    char *name = malloc(sizeof(char) * MAX_LINE_LENGTH);

    if (freadln(name, MAX_LINE_LENGTH, input) == NULL)
    {
        free(name);
        return NULL;
    }
    int c;
    while ((c = fgetc(input)) != EOF && c != '\n');
    pirate *new_pirate = pirate_create(name);
    if (new_pirate == NULL)
    {
        free(name);
        return NULL;
    }

    //need to be able to read in vessel and treasure
    return new_pirate;
}

void pirate_print(const pirate *p, FILE *restrict output)
{
    fprintf(output, "%s\n", (*p).name);

}

int pirate_compare_name(const pirate *a, const pirate *b)
{
    if ((*a).name == NULL && (*b).name == NULL)
        return 0;
    else if ((*a).name == NULL)
        return 1;
    else if ((*b).name == NULL)
        return -1;
    return (strcmp((*a).name, (*b).name));
}

int pirate_compare_vessel(const pirate *a, const pirate *b)
{
    if ((*a).vessel == NULL && (*b).vessel == NULL)
        return 0;
    else if ((*a).vessel == NULL)
        return 1;
    else if ((*b).vessel == NULL)
        return -1;
    return (strcmp((*a).vessel, (*b).vessel));

}

int pirate_compare_treasure(const pirate *a, const pirate *b)
{
    if ((*a).treasure == -1 && (*b).treasure == -1)
        return 0;
    else if ((*a).treasure == -1)
        return 1;
    else if ((*b).treasure == -1)
        return -1;
    else if ((*a).treasure > (*b).treasure)
        return 1;
    else if ((*a).treasure < (*b).treasure)
        return -1;
    else
        return 0;
}

void pirate_destroy(pirate *p)
{
    free((*p).name);
    free((*p).vessel);
    free((*p).treasure);
    free(p);
}
