
#include "pirate.h"
#include "libhookbook.h"
#include <string.h>
#include <stdlib.h>
/**
 * Implementation file for pirate for HookBook A in CPSC 223 SP2024.
 *
 * Author: [Your name here]]
 */

pirate *pirate_create(char *name)
{
    if(name == NULL){
        return NULL;
    }
    pirate *new_pirate = malloc(sizeof(pirate));

    (*new_pirate).name = strdup(name);
    
    return new_pirate;
}


pirate *pirate_read(FILE *restrict input)
{
    if (input == NULL)
    {
        return NULL;
    }
    char name[127];
    if (freadln(name, sizeof(name), input) == NULL)
    {
        return NULL;
    }
    pirate *p = pirate_create(name);
    char blank[127];
    if (freadln(blank, sizeof(blank), input) != NULL)
    {

        return p;
    }
    
    return p;
}

void pirate_print(const pirate *p, FILE *restrict output)
{
    if (p == NULL){
        fprintf(stderr, "Pirate doesn't exist\n");
    }
    if (output == NULL){
        fprintf(stderr, "Output doesn't exist\n");
    }
    fprintf(output, "%s\n", (*p).name);
}

int pirate_compare_name(const pirate *a, const pirate *b) {
        if( (!a && !b)){
            return 0;
        }
            return strcmp((*a).name, (*b).name);

}

void pirate_destroy(pirate *p)
{
    free((*p).name);
    free(p);
}
