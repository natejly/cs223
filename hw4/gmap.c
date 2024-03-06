#include <stdio.h>

#include <stdlib.h>
#include <stdbool.h>
#include "gmap.h"
#include "entry.h"
#define GMAP_INITIAL_CAPACITY 100
/**
 * Resizes the array holding the elements in the given map.
 *
 * @param m a pointer to a map, non-NULL
 */
void gmap_embiggen(gmap *m);
/**
 * Resizes the array holding the elements in the given map.
 *
 * @param m a pointer to a map, non-NULL
 */
void gmap_emsmallen(gmap *m);
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
//might want to use load factor 
void gmap_embiggen(gmap *m){
    if(m->size >= m->capacity){
        size_t newcap = m->capacity * 2;
        m->table = realloc(m->table, newcap * sizeof(entry *));
        m->capacity = newcap;
    }
}
void gmap_emsmallen(gmap *m){
    if (m->size > GMAP_INITIAL_CAPACITY && m->size * 2 <= m->capacity/2)
    {
        size_t newcap = m->capacity/2;
        if (newcap < GMAP_INITIAL_CAPACITY)
        {
            newcap = GMAP_INITIAL_CAPACITY;
        }
        m->table = realloc(m->table, newcap * sizeof(entry *));
        m->capacity = newcap;
    }
}

gmap *gmap_create(void *(*cp)(const void *), int (*comp)(const void *, const void *), size_t (*h)(const void *), void (*f)(void *))
{
    if (h == NULL || cp == NULL || comp == NULL || f == NULL)
    {
        // one of the required functions was missing
        return NULL;
    }
    gmap *m = malloc(sizeof(gmap));
    if (m != NULL)
    {
        // remember the functions used to manipulate the keys
        m->copy = cp;
        m->compare = comp;
        m->hash = h;
        m->free = f;

        // initialize the table
        m->table = malloc(sizeof(entry) * GMAP_INITIAL_CAPACITY);
        m->capacity = (m->table != NULL ? GMAP_INITIAL_CAPACITY : 0);
        m->size = 0;
    }
    return m;
}

size_t gmap_size(const gmap *m){
        if (m == NULL)
    {
        return 0;
    }

    return m->size;
}

void *gmap_put(gmap *m, const void *key, void *value){
    size_t index = m->hash(key) % m->capacity;
    entry *bucket = &m->table[index];
    //bucket is empty
    if(bucket->id == NULL){
        bucket->id = m->copy(key);
        bucket->distribution = value;
        bucket->next = NULL;
        m->size++;
        gmap_embiggen(m);
        return NULL;
    }
    //else go through linked list and check for duplicates
    entry *current = bucket;
    while(current){
        if(m->compare(current->id, key) == 0){
            void *to_remove = current->distribution;
            current->distribution = value;
            return to_remove;
        }
        current = current->next;
    }
    //no duplicates found so add to end of list 
    current->next = malloc(sizeof(entry));
    current->next->id = m->copy(key);
    current->next->distribution = value;
    current->next->next = NULL;
    m->size++;
    gmap_embiggen(m);
    return NULL;
}

void *gmap_remove(gmap *m, const void *key)
{
size_t index = m->hash(key) % m->capacity;
entry *current = &m->table[index];
entry *prev = NULL;
// Traverse the linked list and look for the node to remove
while (current != NULL) {
    if (m->compare(current->id, key) == 0) {
            printf("index is %d\n", index);
            printf("key is %d\n", *current->id);
            printf("value is %d\n", *current->distribution);
        // remove first node
        if (prev == NULL) {
                m->table[index] = current->next;
                
            } 
        }   
    }

    prev = current;
    current = current->next;
}


bool gmap_contains_key(const gmap *m, const void *key){
    size_t index = m->hash(key) % m->capacity;
    entry *bucket = &m->table[index];
    while(bucket->id && m->compare(bucket->id, key) != 0){
        bucket = bucket->next;
    }
    return bucket->distribution != NULL;

}

void *gmap_get(gmap *m, const void *key){
    size_t index = m->hash(key) % m->capacity;
    entry *bucket = &m->table[index];
    while(bucket->id && m->compare(bucket->id, key) != 0){
        bucket = bucket->next;
    }
    if(bucket->id == NULL){
        return NULL;
    } else {
        return bucket->distribution;
    }
}

void gmap_for_each(gmap *m, void (*f)(const void *, void *, void *), void *arg){
    for (size_t i = 0; i < m->capacity; i++)
    {
        entry *bucket = &m->table[i];
        while(bucket->id){
            f(bucket->id, bucket->distribution, arg);
            bucket = bucket->next;
        }
    }
    
}


const void **gmap_keys(gmap *m){
    size_t keys_index = 0;
    const void **keys = malloc(sizeof(void *) * m->size);
    for(size_t i = 0; i < m->capacity; i++){
        if(m->table[i].id){
            keys[keys_index] = m->table[i].id;
            keys_index++;
        }
    }
    return keys;
}

void gmap_destroy(gmap *m){
    // for(size_t i = 0; i < m->capacity; i++){
    //     if(m->table[i].id){
    //         m->free(m->table[i].id);
    //         m->free(m->table[i].distribution);
    //     }
    // }
    // // free(m->table);
    // // free(m->capacity);
    // // free(m->hash);
    // // free(m->compare);
    // // free(m->copy);
    // // m->free(m);
}

void gmap_print(gmap *m){
    for (size_t index = 0; index < m->capacity; index++) {
        if(m->table[index].id != NULL){
        printf("Contents of linked list at index %zu:\n", index);
        entry *bucket = &m->table[index];
        while (bucket != NULL) {
            printf("%d ", bucket->distribution[0]);
            bucket = bucket->next;
        }
        printf("\n");
    }
    }
}