/**
 * Implementation file for skills_list for HookBook B in CPSC 223 SP2024.
 *
 * Author: [your name here]
 */
#include <stdlib.h>
#include "skills_list.h"
#include <stdio.h>
struct node
{
    char *payload;
    struct node *nextNode;
};

struct skills_list
{
    struct Node *head;
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
void appendNode(struct skills_list *list, char *payload)
{
    struct node *temp = newNode(payload);
    if (!list->head)
    {
        // NULL is false
        // head is null set head to temp (initializing)
        list->head = temp;
    }
    else
    {
        struct node *last = list->head;
        while (last->nextNode)
        {
            // traversing
            last = last->nextNode;
        }
        last->nextNode = temp;
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
void printSkillsList(struct skills_list *list){
    struct node *temp = list->head;
    while(temp){
        fprintf(stdout, "%s", temp->payload);
        temp = temp->nextNode;
    }
    printf("Null /n");
}