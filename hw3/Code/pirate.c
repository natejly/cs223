/**
 * Implementation file for pirate for HookBook B in CPSC 223 SP2024.
 *
 * Author: Nate Ly
 */
#include "pirate.h"
#include "libhookbook.h"
#include <stdlib.h>
#include <string.h>
#include "skills_list.h"
pirate *pirate_create(char *name)
{
    pirate *new_pirate = malloc(sizeof(pirate));
    new_pirate->name = name;
    new_pirate->has_rank = false;
    new_pirate->has_port = false;
    new_pirate->has_vessel = false;
    new_pirate->has_treasure = false;
    return new_pirate;
}

pirate *pirate_read(FILE *restrict input)
{
    char *currentLine = malloc(sizeof(char) * MAX_LINE_LENGTH);
    pirate *new_pirate;

    while(freadln(currentLine, MAX_LINE_LENGTH, input) && *currentLine != '\0'){
    
        if(currentLine[1] != ':' && currentLine[0] != '\0'){
            char *nameHolder = malloc(sizeof(char) * MAX_LINE_LENGTH);
            strcpy(nameHolder, currentLine);
            new_pirate = pirate_create(nameHolder);
        }
        else if (currentLine[0] == 'r'){
            char *rankHolder = malloc(sizeof(char) * MAX_LINE_LENGTH);
            strcpy(rankHolder, currentLine);
            new_pirate->rank = &rankHolder[2];
            new_pirate->has_rank = true;
        }
        else if (currentLine[0] == 'v'){
            char *vesselHolder = malloc(sizeof(char) * MAX_LINE_LENGTH);
            strcpy(vesselHolder, currentLine);
            new_pirate->vessel = &vesselHolder[2];
            new_pirate->has_vessel = true;
        }
        else if (currentLine[0] == 'p'){
            char *portHolder = malloc(sizeof(char) * MAX_LINE_LENGTH);
            strcpy(portHolder, currentLine);
            new_pirate->port = &portHolder[2];
            new_pirate->has_port = true;
        }
        else if (currentLine[0] == 't'){
            char *treasureHolder = malloc(sizeof(char) * MAX_LINE_LENGTH);
            strcpy(treasureHolder, currentLine);
            new_pirate->treasure = atoi(&treasureHolder[2]);
            new_pirate->has_treasure = true;
        }
        else if (currentLine[0] == 's'){
            char *skillHolder = malloc(sizeof(char) * MAX_LINE_LENGTH);
            strcpy(skillHolder, &currentLine[2]);
            //appendNode(new_pirate->skills, skillHolder);
        }
    
    }
    if (freadln(currentLine, MAX_LINE_LENGTH, input) == NULL){
        return NULL;
    }
    return new_pirate;
}

void pirate_print(const pirate *p, FILE *restrict output)
{
    printf("%s\n", p->name);

    if(p->has_rank){
        fprintf(output, "%s\n", p->rank);
    }
    if(p->has_vessel){
        fprintf(output,"%s\n", p->vessel);
    }
    if(p->has_port){
        fprintf(output,"%s\n", p->port);
    }
    if(p->has_treasure){
        fprintf(output,"%d\n", p->treasure);
    }


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
