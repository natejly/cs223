#include "gmap.h"

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * An implementation of a generic map as an unsorted fixed-size array.
 * This implementation will not meet the requirements of Assignment #4 and
 * is not completely tested itself but should be sufficient for testing your
 * Blotto competition program.
 *
 * Author: James Glenn
 *
 * TO STUDENT: You do not need to modify this file, though you may if you wish.
 */

char *gmap_error = "error";

/**
 * A (key, value) pair stored in a map.
 */
typedef struct
{
    void *key;
    void *value;
} entry;

/**
 * Meta-data for the map.
 *
 * @member table a pointer to the array of entries in the map
 * @member capacity the max number of entries that can be stored in the array
 * @member size the number of entries in the map
 * @member hash the hash function used by the map
 * @member compare the function used to compare keys in the map
 * @member copy the function used to create new copies of keys in the map
 * @member free the function used to destroy keys in the map
 */
struct _gmap
{
    entry *table;
    size_t capacity;
    size_t size;
    size_t (*hash)(const void *);
    int (*compare)(const void *, const void *);
    void *(*copy)(const void *);
    void (*free)(void *);
};

#define GMAP_INITIAL_CAPACITY 100

/**
 * Returns the index where key is located in the given map, or the index
 * where it would go if it is not present.
 *
 * @param table a table with at least one free slot, non-NULL
 * @param key a string, non-NULL
 * @param hash the hash function used for the keys, non-NULL
 * @param compare a comparison function for keys, non-NULL
 * @param size the size of the table
 * @param capacity the capacity of the table
 * @return the index of key in table, or the index of the empty slot to put it in if it is not present
 */
size_t gmap_table_find_key(const entry *table, const void *key, size_t (*hash)(const void *), int (*compare)(const void *, const void *), size_t size, size_t capacity);

/**
 * Resizes the array holding the elements in the given map.  The current
 * implementation does nothing.
 *
 * @param m a pointer to a map, non-NULL
 */
void gmap_embiggen(gmap *m);

gmap *gmap_create(void *(*cp)(const void *), int (*comp)(const void *, const void *), size_t (*h)(const void *s), void (*f)(void *))
{
    if (h == NULL || cp == NULL || comp == NULL || f == NULL)
    {
        // one of the required functions was missing
        return NULL;
    }

    gmap *result = malloc(sizeof(gmap));
    if (result != NULL)
    {
        // remember the functions used to manipulate the keys
        result->copy = cp;
        result->compare = comp;
        result->hash = h;
        result->free = f;

        // initialize the table
        result->table = malloc(sizeof(entry) * GMAP_INITIAL_CAPACITY);
        result->capacity = (result->table != NULL ? GMAP_INITIAL_CAPACITY : 0);
        result->size = 0;
    }
    return result;
}

size_t gmap_size(const gmap *m)
{
    if (m == NULL)
    {
        return 0;
    }

    return m->size;
}

size_t gmap_table_find_key(const entry *table, const void *key, size_t (*hash)(const void *), int (*compare)(const void *, const void *), size_t size, size_t capacity)
{
    // sequential search for key
    int i = 0;
    while (i < size && compare(table[i].key, key) != 0)
    {
        i++;
    }
    return i;
}

void *gmap_put(gmap *m, const void *key, void *value)
{
    if (m == NULL || key == NULL)
    {
        return NULL;
    }

    if (m->size == m->capacity)
    {
        // table is full (would that be the right condition for a hash table?); try to expand
        gmap_embiggen(m); // does nothing in this implementation
    }

    // find key
    int index = gmap_table_find_key(m->table, key, m->hash, m->compare, m->size, m->capacity);
    if (index < m->size)
    {
        // key already present; replace old value and return the old one
        void *old_value = m->table[index].value;
        m->table[index].value = value;
        return old_value;
    }
    else
    {
        // new key; check whether there is room for the new entry
        if (m->size == m->capacity)
        {
            // still no room :(
            return gmap_error;
        }

        // make a copy of the new key
        void *copy = m->copy(key);

        if (copy != NULL)
        {
            m->table[index].key = copy;
            m->table[index].value = value;
            m->size++;
            return NULL;
        }
        else
        {
            return NULL;
        }
    }
}

void *gmap_remove(gmap *m, const void *key)
{
    // TO-DO: write and test remove
    return NULL;
}

void gmap_embiggen(gmap *m)
{
    // TO-DO: write and test embiggen
}

bool gmap_contains_key(const gmap *m, const void *key)
{
    return gmap_table_find_key(m->table, key, m->hash, m->compare, m->size, m->capacity) < m->size;
}

void *gmap_get(gmap *m, const void *key)
{
    if (m == NULL || key == NULL)
    {
        return NULL;
    }

    size_t index = gmap_table_find_key(m->table, key, m->hash, m->compare, m->size, m->capacity);
    if (index < m->size)
    {
        // found -- get and return value from table
        return m->table[index].value;
    }
    else
    {
        // not found
        return NULL;
    }
}

/**
 * A location in an array where a key can be stored.  The location is
 * represented by a (array, index) pair.
 */
typedef struct _gmap_store_location
{
    const void **arr;
    size_t index;
} gmap_store_location;

/**
 * Stores the given key in the given location and increments the location
 * by one element.
 *
 * @param key a pointer to a key, non-NULL
 * @param value ignored
 * @param arg a pointer to a gmap_store_location
 */
void gmap_store_key_in_array(const void *key, void *value, void *arg)
{
    gmap_store_location *where = arg;
    where->arr[where->index] = key;
    where->index++;
}

const void **gmap_keys(gmap *m)
{
    const void **keys = malloc(sizeof(*keys) * m->size);

    if (keys != NULL)
    {
        gmap_store_location loc = {keys, 0};
        gmap_for_each(m, gmap_store_key_in_array, &loc);
    }

    return keys;
}

void gmap_for_each(gmap *m, void (*f)(const void *, void *, void *), void *arg)
{
    if (m == NULL || f == NULL)
    {
        return;
    }

    for (int i = 0; i < m->size; i++)
    {
        f(m->table[i].key, m->table[i].value, arg);
    }
}

void gmap_destroy(gmap *m)
{
    if (m == NULL)
    {
        return;
    }

    // free all the copies of the keys we made
    for (int i = 0; i < m->size; i++)
    {
        m->free(m->table[i].key);
    }

    // free the table
    free(m->table);

    // free the gmap struct
    free(m);
}
