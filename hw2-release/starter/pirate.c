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
    pirate *new_pirate = (pirate *)malloc(sizeof(pirate));
    //if allocation fails 

    (*new_pirate).name = strdup(name);
    
    return new_pirate;
}

pirate *pirate_read(FILE *restrict input)
{
    char name[127];
    if (input == NULL)
    {
        printf("Error: File not found\n");
    }
    if(freadln(name, sizeof(name), input) != NULL)
    {     
        pirate *p = pirate_create(name);
    return p;
    }
    return NULL;


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

int pirate_compare_name(const pirate *a, const pirate *b)
{   
    if ((*a).name == (*b).name){   
        return 0;
    }
    else if ((*a).name[0] == '\0'){
        return 1;
    }else if ((*b).name[0] == '\0'){
        return -1;
    } else {
    return strcmp((*a).name, (*b).name);
    }
}

void pirate_destroy(pirate *p)
{
    free((*p).name);
    free(p);
}
