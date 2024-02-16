#include "pirate.h"

/**
 * Implementation file for pirate for HookBook A in CPSC 223 SP2024.
 *
 * Author: [Your name here]]
 */

pirate *pirate_create(char *name)
{
    pirate *new_pirate = (pirate *)malloc(sizeof(pirate));
    //if allocation fails 
    if (new_pirate == NULL){
        return NULL;
    }
    (*new_pirate).name = strdup(name);
    if ((*new_pirate).name == NULL) {
        // free if allocation fails
        free(new_pirate);
        return NULL;
    }
}

pirate *pirate_read(FILE *restrict input)
{
    // TODO: Implement this function.
    // This line is here only so starter code compiles.
    return NULL;
}

void pirate_print(const pirate *p, FILE *restrict output)
{
    // TODO: Implement this function.
}

int pirate_compare_name(const pirate *a, const pirate *b)
{
    // TODO: Implement this function.
    // This line is here only so starter code compiles.
    return 0;
}

void pirate_destroy(pirate *p)
{
    // TODO: Implement this function.
}
