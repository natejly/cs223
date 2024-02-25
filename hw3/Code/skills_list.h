#pragma once

/**
 * Header file for skills_list for HookBook B in CPSC 223 SP2024.
 *
 * TO STUDENT: You may add to this file, but do not change anything that is
 *     already here!
 * Author: [your name here]
 */

/**
 * Type of a list of skills, as an opaque struct.
 */
typedef struct skills_list_instance_t skills_list;
typedef struct node node;

struct skills_list *createSkillsList();
struct node *newNode(char *payload);

void appendNode(struct skills_list *list, char *payload);
void destroySkillsList(struct skills_list *list);
void printSkillsList(struct skills_list *list);
// TODO: Define and implement an interface for skills_list
