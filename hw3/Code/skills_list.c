/**
 * Implementation file for skills_list for HookBook B in CPSC 223 SP2024.
 *
 * Author: Nate Ly
 */
#include <stdlib.h>
#include "skills_list.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
struct node
{
    char *payload;
    struct node *nextNode;
};

struct skills_list
{
    struct node *head;
    size_t size;
};

struct skills_list *createSkillsList()
{
    struct skills_list *list = malloc(sizeof(struct skills_list));
    list->size = 0;
    list->head = NULL;
    return list;
}

struct node *newNode(char *payload)
{
    struct node *temp = malloc(sizeof(struct node));
    temp->payload = payload;
    temp->nextNode = NULL;
    return temp;
}
void addSkill(struct skills_list *list, char *payload)
{
    struct node *temp = newNode(payload);
    struct node *curr = list->head;
    struct node *prev = NULL;
    //find place to insert
    while(curr != NULL && strcmp(curr->payload, payload) < 0){
        prev = curr;
        curr = curr->nextNode;
    }   
   if (prev == NULL)
    {
        //go at the front if prev is null
        temp->nextNode = list->head;
        list->head = temp;
    }
    else
    {
        //go between prev and curr
        temp->nextNode = prev->nextNode;
        prev->nextNode = temp;
    }
    list->size++;
}
void destroySkillsList(struct skills_list *list)
{
    struct node *current = list->head;
    struct node *next;
    while (current)
    {
        next = current->nextNode;
        free(current->payload);
        free(current);
        current = next;
    }
    free(list);
}

void printSkillsList(struct skills_list *list)
{
    printf("    Skills: ");
    struct node *temp = list->head;
    bool first = true;
    while (temp)
    {
        char *curr = temp->payload;
        int count = 0;
        struct node *currnode = list->head;
        while (currnode)
        {
            if (strcmp(currnode->payload, curr) == 0)
            {
                count++;
            }
            currnode = currnode->nextNode;
        }
        if(first)
        {
            fprintf(stdout, "%s ", curr);

        }else{
            fprintf(stdout, "            %s ", curr);
        }

            for (size_t i = 0; i < count-1; i++)
        {
            printf("*");
        }
        first = false;
        printf("\n");
        while (temp->nextNode && strcmp(temp->nextNode->payload, curr) == 0)
        {
            temp = temp->nextNode;
        }
                temp = temp->nextNode;

    }
}
