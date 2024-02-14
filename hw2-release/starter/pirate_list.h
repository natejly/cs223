#pragma once

/**
 * Header file for pirate_list for HookBook A in CPSC 223 SP2024.
 *
 * Author: Alan Weide
 *
 * TO STUDENT: You may add to this file, but do not change anything that is
 *     already here!
 * Modified by: [your name here] on [date of modification]
 * Changelog: [what you added to this file]
 */

#include <stdlib.h>

#include "pirate.h"

/**
 * Type of a list of pirates, as an opaque struct.
 */
typedef struct pirate_list_instance_t pirate_list;

/**
 * Allocate memory for a new pirate_list and return a pointer to it.
 *
 * @return a pointer to a newly-created pirate list
 */
pirate_list *list_create();

/**
 * Return the index in pirates of the pirate with the name, or a value greater
 *  than or equal to the length of the list if the there is no such pirate.
 *
 * @param pirates the list to search
 * @param name the name to search for
 * @return the index of the pirate with name, or a value greater than or equal
 *  to the length of the list if the there is no such pirate.
 * @assumes neither pirates nor p are NULL
 */
size_t list_index_of(const pirate_list *pirates, const char *name);

/**
 * Only if there is no pirate in the list with the same name as p, insert
 *  pirate p into the list at index idx by copying the pointer, shifting the
 *  latter part of the list one "slot" to the right.
 *
 * If idx >= [length of pirates], then this function appends p to the end of
 *  the list.
 *
 * If there is a pirate in the list with the same name as p, do nothing, and
 *  return p (the pirate that was not inserted).
 *
 * If the pirate was inserted into the list, return NULL.
 *
 * If p is added to the list, the list claims ownership of the pirate pointed
 *  to by p; otherwise ownership remains with p.
 *
 * @param pirates the list in which to insert p
 * @param p the pirate to insert
 * @param idx the index at which to insert p
 * @return NULL or p, depending on whether p was successfully inserted
 * @assumes neither pirates nor p are NULL, and that p has a name
 */
pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx);

/**
 * Remove the pirate from the list with name, and return a pointer to it.
 *
 * If name is NULL or there is no pirate in the list with name, return NULL.
 *
 * If this function does not return NULL, then the caller owns the returned
 *  pirate.
 *
 * @param pirates the list from which to remove a pirate
 * @param name the name of the pirate to remove
 * @return the removed pirate, or NULL if there is no matching pirate in the
 *  list
 * @assumes pirates is not NULL
 * @assumes every pirate in pirates has a name that is unique in the list
 */
pirate *list_remove(pirate_list *pirates, const char *name);

/**
 * Return a pointer to the pirate pointed to by index idx in the list, or NULL
 *  if idx is not a valid index (i.e., it is >= the length of the list).
 *
 * Ownership of the returned pirate remains with the list.
 *
 * @param pirates the list to access
 * @param idx the index to access of the list
 * @return a pointer to the pirate at index idx of pirates, or NULL
 * @assumes pirates is not NULL
 */
const pirate *list_access(const pirate_list *pirates, size_t idx);

/**
 * Sort the list of pirates in lexicographical order by name.
 *
 * @param pirates the list to sort
 * @does sorts the list of pirates in lexicographical order by name
 * @assumes pirates is not NULL and every pirate in the list has a name that is
 *  unique in the list
 */
void list_sort(pirate_list *pirates);

/**
 * Return the number of pirates in the list.
 *
 * @param pirates the list
 * @return the number of pirates in pirates
 * @assumes pirates is not NULL
 */
size_t list_length(const pirate_list *pirates);

/**
 * Free all memory owned by the list, including the pirates in the list.
 *
 * @param pirates the list to destroy
 */
void list_destroy(pirate_list *pirates);
