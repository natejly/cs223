/**
 * Implementation file for skills_list for HookBook B in CPSC 223 SP2024.
 *
 * Author: [your name here]
 */
#include <stdlib.h>
#include "skills_list.h"
struct Skill{
    char *skillname;
    int level;
};
struct Node {
    struct Node* next;
};


struct skills_list_instance_t
{   
    size_t size;
    struct Node* head;
};

struct skills_list_instance_t* skills_list_create(){
    struct skills_list_instance_t* new_skills_list = malloc(sizeof(struct skills_list_instance_t));
    new_skills_list->size = 0;
    new_skills_list->head = NULL;
    return new_skills_list;
}


