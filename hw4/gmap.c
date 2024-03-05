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
    if(m == NULL){
        return NULL;
    }
    m->table = malloc(sizeof(entry) * GMAP_INITIAL_CAPACITY);
    m->capacity = GMAP_INITIAL_CAPACITY;
    m->size = 0;
    m->hash = h;
    m->compare = comp;
    m->copy = cp;
    m->free = f;
    return m;
}

size_t gmap_size(const gmap *m){
    return m->size;
}

void *gmap_put(gmap *m, const void *key, void *value){
    size_t index = m->hash(key) % m->capacity;
    entry *bucket = &m->table[index];
    //if key is already in the map
    if(bucket->id && m->compare(bucket->id, key) == 0){
        void *old_value = bucket->distribution;
        bucket->distribution = value;
        return old_value;
    }
     //if key is not in the map then we add
    gmap_embiggen(m);
    m->table[index].id = m->copy(key);
    m->table[index].distribution = value;
    m->size++;
    return NULL;
}

void *gmap_remove(gmap *m, const void *key){
    size_t index = m->hash(key) % m->capacity;
    entry *bucket = &m->table[index];
    if(bucket->id && m->compare(bucket->id, key) == 0){
        void *toremove = bucket->distribution;
        bucket->id = NULL;
        bucket->distribution = NULL;
        m->size--;
        gmap_emsmallen(m);
        return toremove;
    }
}

bool gmap_contains_key(const gmap *m, const void *key){
    size_t index = m->hash(key) % m->capacity;
    entry *bucket = &m->table[index];
    if(m->compare(bucket->id, key) == 0){
        return true;
    }

}

void *gmap_get(gmap *m, const void *key){
    size_t index = m->hash(key) % m->capacity;
    entry *bucket = &m->table[index];
    if(m->compare(bucket->id, key) == 0){
        return bucket->distribution;
    }
}

void gmap_for_each(gmap *m, void (*f)(const void *, void *, void *), void *arg){
    for(size_t i = 0; i < m->capacity; i++){
        if(m->table[i].id){
            f(m->table[i].id, m->table[i].distribution, arg);
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
}

void gmap_destroy(gmap *m){
    for(size_t i = 0; i < m->capacity; i++){
        if(m->table[i].id){
            m->free(m->table[i].id);
            m->free(m->table[i].distribution);
        }
    }
    free(m->table);
    free(m->capacity);
    free(m->hash);
    free(m->compare);
    free(m->copy);
    free(m);
}
