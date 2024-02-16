/**
 * Implementation file for pirate_list for HookBook A in CPSC 223 SP2024.
 *
 * Author: [your name here]
 */

#include "pirate_list.h"
#include <stdio.h>
#include <string.h>
struct pirate_list_instance_t
{
    pirate *pirates; 
    size_t size;    
    size_t capacity; 
};
#define INITIAL_CAPACITY 25
#define RESIZE_FACTOR 2
/***********************
 * "Private" Functions *
 ***********************/

/**
 * Check if the actual number of pirates in the array is "too large"; if it is,
 *  increase the capacity of the array by a factor of RESIZE_FACTOR.
 *
 * Given N actual pirates in the array of capacity C, we say N is "too large"
 *  whenever N >= C
 *
 * If the array capacity was changed, print to stderr the string "Expand to ",
 *  followed by the new capacity of the list and a newline. Here is a possible
 *  print statement:
 *
 *     fprintf(stderr, "Expand to %zu\n", new_capacity);
 *
 * If the capacity was not changed, print nothing.
 *
 * @param pirates the pirate list to expand, if necessary
 * @does increases the capacity of the array if there are too many pirates in
 *  it
 * @assumes the pirate list is in the process of having a pirate added to it.
 */
void list_expand_if_necessary(pirate_list *pirates);

/**
 * Check if the actual number of pirates in the array is "too small"; if it is,
 *  decrease the capacity of the array by a factor of RESIZE_FACTOR.
 *
 * Given N actual pirates in the array of capacity C, we say N is "too small"
 *  whenever C > INITIAL_CAPACITY and N * RESIZE_FACTOR <= C / RESIZE_FACTOR
 *
 * If the array capacity was changed, print to stderr the string "Contract to "
 *  followed by the new capacity of the list. Here is a possible print
 *  statement:
 *
 *     fprintf(stderr, Contract to %zu\n, new_capacity);
 *
 * If the capacity was not changed, print nothing.
 *
 * The capacity of the array must never fall below INITIAL_CAPACITY!
 *
 * @param pirates the pirate list to contract, if necessary
 * @does decreases the capacity of the array if there are too few pirates in
 *  it.
 * @assumes the pirate list is in the process of having a pirate removed from it.
 */
void list_contract_if_necessary(pirate_list *pirates);

/*******************
 * Function bodies *
 *******************/

pirate_list *list_create()
{
    pirate_list *list = (pirate_list *)malloc(sizeof(pirate_list));
    if (list == NULL) {
        // Memory allocation failed
        fprintf(stderr, "list not created\n");
        return NULL;
    }
    (*list).capacity = INITIAL_CAPACITY;
    (*list).size = 0;
    return list;
}

size_t list_index_of(const pirate_list *pirates, const char *name)
{
    for(size_t i = 0; i < (*pirates).size; i++){
        if (strcmp(pirates->pirates[i].name, name) == 0) {
            return i;
        }

    }
    return (*pirates).size +1;
}

pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx)
{
    // TODO: Implement this function.
    // This line is here only so starter code compiles.
    return NULL;
}

pirate *list_remove(pirate_list *pirates, const char *name)
{
    // TODO: Implement this function.
    // This line is here only so starter code compiles.
    return NULL;
}

const pirate *list_access(const pirate_list *pirates, size_t idx)
{
    // TODO: Implement this function.
    // This line is here only so starter code compiles.
    return NULL;
}

void list_sort(pirate_list *pirates)
{
    // TODO: Implement this function.
}

size_t list_length(const pirate_list *pirates)
{
    // TODO: Implement this function.
    // This line is here only so starter code compiles.
    return 0;
}

void list_destroy(pirate_list *pirates)
{
    // TODO: Implement this function.
}

void list_expand_if_necessary(pirate_list *pirates)
{
    // TODO: Implement this function.
}

void list_contract_if_necessary(pirate_list *pirates)
{
    // TODO: Implement this function.
}
