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
#include "pirate_list.h"
pirate *pirate_create(char *name)
{
    // initialize a new pirate and set all the flags to false
    pirate *new_pirate = malloc(sizeof(pirate));
    new_pirate->name = name;
    new_pirate->has_rank = false;
    new_pirate->has_port = false;
    new_pirate->has_vessel = false;
    new_pirate->has_treasure = false;
    new_pirate->has_skills = false;
    new_pirate->has_captain = false;
    new_pirate->skills = createSkillsList();
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
    pirate *new_pirate = pirate_create(name);
    if (new_pirate == NULL)
    {
        // free the name if the pirate is null
        free(name);
        return NULL;
    }
    char *currentLine = malloc(sizeof(char) * MAX_LINE_LENGTH);
    char *freadvalue = freadln(currentLine, MAX_LINE_LENGTH, input);
    // read through the file and set the pirate's attributes
    while (freadvalue != NULL && currentLine[0] != '\0')
    {
        if (currentLine[1] == ':')
        {
            if (currentLine[0] == 'r')
            {
                char *rankHolder = malloc(sizeof(char) * MAX_LINE_LENGTH);
                // the & [2] increments pointer by 2 to skip the first two characters
                strcpy(rankHolder, &currentLine[2]);
                new_pirate->rank = rankHolder;
                // making sure to set flags to true
                new_pirate->has_rank = true;
            }
            else if (currentLine[0] == 'v')
            {
                char *vesselHolder = malloc(sizeof(char) * MAX_LINE_LENGTH);
                strcpy(vesselHolder, &currentLine[2]);
                new_pirate->vessel = vesselHolder;
                new_pirate->has_vessel = true;
            }
            else if (currentLine[0] == 'p')
            {
                char *portHolder = malloc(sizeof(char) * MAX_LINE_LENGTH);
                strcpy(portHolder, &currentLine[2]);
                new_pirate->port = portHolder;
                new_pirate->has_port = true;
            }
            else if (currentLine[0] == 't')
            {
                new_pirate->treasure = atoi(&currentLine[2]);
                new_pirate->has_treasure = true;
            }
            else if (currentLine[0] == 's')
            {
                char *skillHolder = malloc(sizeof(char) * MAX_LINE_LENGTH);
                strcpy(skillHolder, &currentLine[2]);
                addSkill(new_pirate->skills, skillHolder);
                new_pirate->has_skills = true;
            }
            freadvalue = freadln(currentLine, MAX_LINE_LENGTH, input);
        }
    }
    free(currentLine);
    return new_pirate;
}

void pirate_print(const pirate *p, FILE *restrict output)
{
    fprintf(output, "%s\n", p->name);
    if (p->has_captain)
    {
        if(p->captain->has_vessel){
            fprintf(output, "    Captain: %s (%s)\n", p->captain->name, p->captain->vessel);

        }else{
            fprintf(output, "    Captain: %s\n", p->captain->name);
        }

    }
    if (p->has_rank)
    {
        fprintf(output, "    Rank: %s\n", p->rank);
    }
    if (p->has_vessel)
    {
        fprintf(output, "    Vessel: %s\n", p->vessel);
    }
    if (p->has_port)
    {
        fprintf(output, "    Port: %s\n", p->port);
    }
    if (p->has_treasure)
    {
        fprintf(output, "    Treasure: %d\n", p->treasure);
    }
    if (p->has_skills)
    {
        printSkillsList(p->skills, output);
    }
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

int pirate_compare_vessel(const pirate *a, const pirate *b)
{
    if (!a->has_vessel && !b->has_vessel)
        // if equal use name to compare
        return pirate_compare_name(a, b);
    else if (!a->has_vessel)
        return 1;
    else if (!b->has_vessel)
        return -1;
    if (strcmp(a->vessel, b->vessel) == 0)
    {
        return pirate_compare_name(a, b);
    }
    return (strcmp(a->vessel, b->vessel));
}

int pirate_compare_treasure(const pirate *a, const pirate *b)
{
    if (!a->has_treasure && !b->has_treasure)
        // if equal use name to compare
        return pirate_compare_name(a, b);
    else if (!a->has_treasure)
        return 1;
    else if (!b->has_treasure)
        return -1;
    if (a->treasure == b->treasure)
    {
        return pirate_compare_name(a, b);
    }
    return b->treasure - a->treasure;
}

void pirate_destroy(pirate *p)
{
    if (!p->name)
    {
        free(p->name);
    }
    if (p->has_rank)
    {
        free(p->rank);
    }
    if (p->has_vessel)
    {
        free(p->vessel);
    }
    if (p->has_port)
    {
        free(p->port);
    }
    destroySkillsList(p->skills);
    free(p);
}