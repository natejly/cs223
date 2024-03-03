#ifndef __GMAP_H__
#define __GMAP_H__

#include <stdlib.h>
#include <stdbool.h>

/**
 * Interface for generic map for HW4 in CPSC 223.
 * Author: James Glenn
 *
 * TO STUDENT: You may not modify this file.
 */

struct _gmap;
typedef struct _gmap gmap;

/**
 * Used for gmap_put to report an allocation error through its return value.
 */
extern char *gmap_error;

/**
 * Creates an empty map that uses the given hash function.
 *
 * @param cp a pointer to a function that takes a pointer to a key and returns a pointer to a deep
 * copy of that key
 * @param comp a pointer to a function that takes two keys and returns the result of comparing them,
 * with return value as for strcmp
 * @param h a pointer to a function that takes a pointer to a key and returns its hash code
 * @param f a pointer to a function that takes a pointer to a copy of a key make by cp and frees it
 * @return a pointer to the new map or NULL if it could not be created;
 * it is the caller's responsibility to destroy the map
 */
gmap *gmap_create(void *(*cp)(const void *), int (*comp)(const void *, const void *), size_t (*h)(const void *), void (*f)(void *));

/**
 * Returns the number of (key, value) pairs in the given map. Behavior
 * is undefined if m is NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @return the size of the map pointed to by m
 */
size_t gmap_size(const gmap *m);

/**
 * Adds a copy of the given key with value to this map.  If the key is
 * already present then the old value is replaced and returned.  The
 * map copies the key, so the caller retains ownership of the original
 * key and may modify it or destroy it without affecting the map.  The
 * map copies the pointer to the value, but the caller retains
 * ownership of the value. Behavior is undefined if either m or key is
 * NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @param key a pointer to a key, non-NULL
 * @param value a pointer to a value
 * @return a pointer to the old value, or NULL, or a pointer to gmap_error
 */
void *gmap_put(gmap *m, const void *key, void *value);

/**
 * Removes the given key and its associated value from the given map if
 * the key is present.  The return value is NULL and there is no effect
 * on the map if the key is not present.  The copy of the key held by
 * the map is destroyed.  It is the caller's responsibility to free the
 * returned value if necessary. Behavior is undefined if either m or key
 * is NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @param key a key, non-NULL
 * @return the value associated with the removed key, or NULL
 */
void *gmap_remove(gmap *m, const void *key);

/**
 * Determines if the given key is present in this map. Behavior is undefined
 * if either m or key is NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @param key a pointer to a key, non-NULL
 * @return true if a key equal to the one pointed to is present in this map,
 * false otherwise
 */
bool gmap_contains_key(const gmap *m, const void *key);

/**
 * Returns the value associated with the given key in this map.
 * If the key is not present in this map then the returned value is
 * NULL.  The pointer returned is the original pointer passed to gmap_put,
 * and it remains the responsibility of whatever called gmap_put to
 * release the value it points to (no ownership transfer results from
 * gmap_get). Behavior is undefined is either m or key is NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @param key a pointer to a key, non-NULL
 * @return a pointer to the assocated value, or NULL if they key is not present
 */
void *gmap_get(gmap *m, const void *key);

/**
 * Calls the given function for each (key, value) pair in this map, passing
 * the extra argument (arg) as well. Behavior is undefined if either m or f
 * is NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @param f a pointer to a function that takes a key, a value, and an
 * extra piece of information, and does not add or remove keys from the
 * map, non-NULL
 * @param arg a pointer
 */
void gmap_for_each(gmap *m, void (*f)(const void *, void *, void *), void *arg);

/**
 * Returns an array containing pointers to all of the keys in the
 * given map.  The return value is NULL if there was an error
 * allocating the array.  The map retains ownership of the keys, and
 * the pointers to them are only valid as long until they are removed
 * from the map, or until the map is destroyed, whichever comes first.
 * It is the caller's responsibility to destroy the returned array if
 * it is non-NULL. Behavior is undefined is m is NULL.
 *
 * @param m a pointer to a map, non-NULL
 * @return a pointer to an array of pointers to the keys, or NULL
 */
const void **gmap_keys(gmap *m);

/**
 * Destroys the given map.  There is no effect if the given pointer is NULL.
 *
 * @param m a pointer to a map, or NULL
 */
void gmap_destroy(gmap *m);

#endif
