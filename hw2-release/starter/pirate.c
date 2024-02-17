#include "pirate.h"
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
    if (new_pirate == NULL){
        return NULL;
    }
    (*new_pirate).name = strdup(name);
    if ((*new_pirate).name == NULL) {
        // free if allocation fails
        free(new_pirate);
        return NULL;
    }
    return new_pirate;
}

pirate *pirate_read(FILE *restrict input)
{
    //null terminator so 128
    char name[128];
    if (input == NULL)
    {
        printf("Error: File not found\n");
    }
    while (fgets(name, sizeof(name), input) != NULL)
    {     
        //remove null terminator  
        name[strcspn(name, "\n")] = '\0';
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
        //names are equal
        printf("equal");
        return 0;
    }
    else if(strcmp((*a).name, "")==0){
        //a is empty, b comes first
        printf("in order");
        return 1;
    } else if(strcmp((*b).name, "")==0){
        //b is empty a comes first
        printf("not in order");
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
