/**
 * Implementation file for pirate_list for HookBook B in CPSC 223 SP2024.
 *
 * Author: Nate Ly
 */
#include <stdio.h>
#include <string.h>
#include "pirate_list.h"
#include "pirate.h"
typedef int (*compare_fn)(const pirate *, const pirate *);

struct pirate_list_instance_t
{
    pirate **pirates;
    size_t size;
    size_t capacity;
    compare_fn cmp;
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
    pirate_list *list = malloc(sizeof(pirate_list));
    if (list == NULL)
    {
        return NULL;
    }
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    list->pirates = malloc(list->capacity * sizeof(pirate *));
    return list;
}

pirate_list *list_create_with_cmp(compare_fn cmp)
{
    pirate_list *list = malloc(sizeof(pirate_list));
    if (list == NULL)
    {
        return NULL;
    }
    // initialize the list and structure members
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    list->pirates = malloc(list->capacity * sizeof(pirate *));
    list->cmp = cmp;
    return list;
}

size_t list_index_of(const pirate_list *pirates, const char *name)
{
    for (size_t i = 0; i < pirates->size; i++)
    {
        if (strcmp((pirates->pirates[i])->name, name) == 0)
        {
            return i;
        }
    }
    // return out of bounds index if not in list
    return pirates->size + 1;
}

pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx)
{
    if (idx > pirates->size)
    {
        idx = pirates->size;
    }
    size_t index = list_index_of(pirates, p->name);

    if (index <= pirates->size)
    {
        // return pirate pointer if already in list
        return p;
    }
    list_expand_if_necessary(pirates);
    for (size_t i = pirates->size; i > idx; i--)
    {
        // shift all elements to the right starting at end of list to idx
        pirates->pirates[i] = pirates->pirates[i - 1];
    }
    pirates->pirates[idx] = p;
    pirates->size++;
    return NULL;
}

pirate *list_remove(pirate_list *pirates, const char *name)
{
    if (name == NULL)
    {
        return NULL;
    }
    size_t index = list_index_of(pirates, name);
    if (index >= pirates->size)
    {
        return NULL;
    }
    pirate *toremove = pirates->pirates[index];

    for (size_t i = index; i < pirates->size - 1; i++)
    {
        // shift elements to the left
        pirates->pirates[i] = pirates->pirates[i + 1];
    }
    list_contract_if_necessary(pirates);
    pirates->size--;
    return toremove;
}

const pirate *list_access(const pirate_list *pirates, size_t idx)
{
    if (idx >= pirates->size)
    {
        return NULL;
    }
    return pirates->pirates[idx];
}
int partition(const pirate_list *pirates, int left, int right){
    pirate *pivot = pirates->pirates[right];
    int i = left - 1;
    for (size_t j = left; j < right; j++){
        if (pirates->cmp(pirates->pirates[j], pivot) < 0){ //<=??
            i++;
            pirate *temp = pirates->pirates[i];
            pirates->pirates[i] = pirates->pirates[j];
            pirates->pirates[j] = temp;
        }
    }
    pirate *temp = pirates->pirates[i + 1];
    pirates->pirates[i + 1] = pirates->pirates[right];
    pirates->pirates[right] = temp;
    return i + 1;
}
void myqSort(pirate_list *pirates, int left, int right)
{
    if (left < right){
        int partitionidx = partition(pirates, left, right);
        myqSort(pirates, left, partitionidx - 1);
        myqSort(pirates, partitionidx + 1, right);
    }
}

void list_sort(pirate_list *pirates)
{
    myqSort(pirates, 0, list_length(pirates) - 1);
}

size_t list_length(const pirate_list *pirates)
{
    return pirates->size;
}

void list_destroy(pirate_list *pirates)
{
    // go though the list and free all pirates
    for (size_t i = 0; i < pirates->size; i++)
    {
        pirate_destroy(pirates->pirates[i]);
    }
    free(pirates->pirates);
    free(pirates);
}

void list_expand_if_necessary(pirate_list *pirates)
{
    if (pirates->size >= pirates->capacity)
    {
        // if size too large expand the list by resize factor
        size_t newcap = pirates->capacity * RESIZE_FACTOR;
        pirates->pirates = realloc(pirates->pirates, newcap * sizeof(pirate *));
        pirates->capacity = newcap;

        fprintf(stderr, "Expand to %zu\n", newcap);
    }
}

void list_contract_if_necessary(pirate_list *pirates)
{
    // if size too small contract the list by resize factor
    if (pirates->capacity > INITIAL_CAPACITY &&
        pirates->size * RESIZE_FACTOR <= pirates->capacity / RESIZE_FACTOR)
    {
        size_t newcap = pirates->capacity / RESIZE_FACTOR;
        // making sure not to go below initail cap
        if (newcap < INITIAL_CAPACITY)
        {
            newcap = INITIAL_CAPACITY;
        }
        pirates->pirates = realloc(pirates->pirates, newcap * sizeof(pirate *));
        pirates->capacity = newcap;
        fprintf(stderr, "Contract to %zu\n", newcap);
    }
}

void assignCaptains(pirate_list *pirates, FILE *restrict input)
{
    // initialize space for current line
    char *currentLine = malloc(sizeof(char) * MAX_LINE_LENGTH);
    char *freadvalue = freadln(currentLine, MAX_LINE_LENGTH, input);
    pirate *underling;
    pirate *captain;
    while (freadvalue != NULL)
    {
        // assign captains to pirates
        underling = list_access(pirates, list_index_of(pirates, currentLine));
        freadvalue = freadln(currentLine, MAX_LINE_LENGTH, input);
        captain = list_access(pirates, list_index_of(pirates, currentLine));
        underling->captain = captain;
        underling->has_captain = true;
        freadvalue = freadln(currentLine, MAX_LINE_LENGTH, input);
    }
    free(currentLine);
}