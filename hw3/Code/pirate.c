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
    new_pirate->has_skills = false;
    skills_list *skills = createSkillsList();
    new_pirate->skills = skills;
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
        free(name);
        return NULL;
    }
    char *currentLine = malloc(sizeof(char) * MAX_LINE_LENGTH);
    char *freadvalue = freadln(currentLine, MAX_LINE_LENGTH, input);
    while (freadvalue != NULL && currentLine[0] != '\0')
    {
        if (currentLine[1] == ':')
        {
            if (currentLine[0] == 'r')
            {
                char *rankHolder = malloc(sizeof(char) * MAX_LINE_LENGTH);
                strcpy(rankHolder, currentLine);
                new_pirate->rank = &rankHolder[2];
                new_pirate->has_rank = true;
            }
            else if (currentLine[0] == 'v')
            {
                char *vesselHolder = malloc(sizeof(char) * MAX_LINE_LENGTH);
                strcpy(vesselHolder, currentLine);
                new_pirate->vessel = &vesselHolder[2];
                new_pirate->has_vessel = true;
            }
            else if (currentLine[0] == 'p')
            {
                char *portHolder = malloc(sizeof(char) * MAX_LINE_LENGTH);
                strcpy(portHolder, currentLine);
                new_pirate->port = &portHolder[2];
                new_pirate->has_port = true;
            }
            else if (currentLine[0] == 't')
            {
                char *treasureHolder = malloc(sizeof(char) * MAX_LINE_LENGTH);
                strcpy(treasureHolder, currentLine);
                new_pirate->treasure = atoi(&treasureHolder[2]);
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
    return new_pirate;
}

void pirate_print(const pirate *p, FILE *restrict output)
{
    printf("%s\n", p->name);

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
        printSkillsList(p->skills);
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
        return 0;
    else if (!a->has_vessel)
        return 1;
    else if (!b->has_vessel)
        return -1;
    return (strcmp(a->vessel, b->vessel));
}

int pirate_compare_treasure(const pirate *a, const pirate *b)
{

    if (!a->has_treasure && !b->has_treasure)
        return 0;
    else if (!a->has_treasure)
        return 1;
    else if (!b->has_treasure)
        return -1;
    return b->treasure - a->treasure;
}

void pirate_destroy(pirate *p)
{
    destroySkillsList(p->skills);
    free(p->name);
    free(p->rank);
    free(p->vessel);
    free(p->port);
    free(p);
    
}
