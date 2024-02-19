
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

    pirate *new_pirate = malloc(sizeof(pirate));

    (*new_pirate).name = name;
    
    return new_pirate;
}

pirate *pirate_read(FILE *restrict input) {
    char *name = malloc(sizeof(char) * MAX_LINE_LENGTH);


    if (freadln(name, MAX_LINE_LENGTH, input) == NULL) {
        free(name);
        return NULL; // Indicates failure to read a line
    }
    int c;
    while ((c = fgetc(input)) != EOF && c != '\n');
    pirate *new_pirate = pirate_create(name);
    if (new_pirate == NULL) {
        free(name);
        return NULL; // Indicates failure to create a pirate
    }
    return new_pirate;
}


void pirate_print(const pirate *p, FILE *restrict output)
{
    fprintf(output, "%s\n", (*p).name);

}

int pirate_compare_name(const pirate *a, const pirate *b)
{
    if (a->name == NULL && b->name == NULL)
        return 0;
    else if (a->name == NULL)
        return 1;
    else if (b->name == NULL)
        return -1;
    return (strcmp(a->name, b->name));
}


void pirate_destroy(pirate *p)
{
    free((*p).name);
    free(p);
}