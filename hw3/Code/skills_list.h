#pragma once
#include <stdio.h>
/**
 * Header file for skills_list for HookBook B in CPSC 223 SP2024.
 *
 * TO STUDENT: You may add to this file, but do not change anything that is
 *     already here!
 * Author: Nate Ly
 * Modified by: Nate Ly 2/25/2024
 */

/**
 * Type of a list of skills, as an opaque struct.
 */
typedef struct skills_list_instance_t skills_list;
/**
 * Type of a node in a skills list, as an opaque struct.
 */
typedef struct node node;
/**
 * Creates memory for a skills_list struct and returns a pointer to it
 *
 * @return a pointer skills list
 */
struct skills_list *createSkillsList(void);
/**
 * Creates space for a node struct and returns a pointer to it
 *
 * @param payload the skill to store in the node
 * @return a pointer to a newly created node
 */
struct node *newNode(char *payload);
/**
 * Traverses the list and adds a new node with the skill to the list in the correct order
 *
 * @param list the list to add the skill to
 * @param payload the skill to add
 * @return void
 */
void addSkill(struct skills_list *list, char *payload);
/**
 * Walks the list and frees the memory for each node and finally the list itself
 *
 * @param list the list to free
 * @return void
 */
void destroySkillsList(struct skills_list *list);
/**
 * Walks the list and prints the skills to the output file per the readme requirements
 *
 * @param list the list to print
 * @param output the stream to print to
 * @return void
 */
void printSkillsList(struct skills_list *list, FILE *restrict output);
