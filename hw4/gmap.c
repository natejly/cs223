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
typedef struct node
{
    void *key;
    void *value;
    struct node *next;
} node;
typedef struct linked_list
{
    node *head;
} linked_list;
struct _gmap
{
    linked_list **table;
    size_t capacity;
    size_t size;
    size_t (*hash)(const void *);
    int (*compare)(const void *, const void *);
    void *(*copy)(const void *);
    void (*free)(void *);
};
struct linked_list *linked_list_create()
{
    struct linked_list *list = malloc(sizeof(struct linked_list));
    list->head = NULL;
    return list;
}
struct node *newNode(void *key, void *value)
{
    struct node *temp = malloc(sizeof(struct node));
    temp->key = key;
    temp->value = value;
    temp->next = NULL;
    return temp;
}
// might want to use load factor
void gmap_embiggen(gmap *m)
{

    if (m->size >= m->capacity)
    {
        size_t newcap = m->capacity * 2;
        linked_list **new_list = calloc(m->table, newcap * sizeof(linked_list *));
        for(size_t i = 0; i< m->capacity; i++){
            linked_list *list = m->table[i];
            if(list){
                size_t newindex = m->hash(list->head->key) % newcap;
                new_list[newindex] = list;
                //remove ownership?
                m->table[i] = NULL;
            }
        }
        m->capacity = newcap;
        m->table = new_list;
        fprintf(stderr, "expanded to %zu",newcap);

    }
}
void gmap_emsmallen(gmap *m)
{
    if (m->size > GMAP_INITIAL_CAPACITY && m->size * 2 <= m->capacity / 2)
    {
        size_t newcap = m->capacity / 2;
        if (newcap < GMAP_INITIAL_CAPACITY)
        {
            newcap = GMAP_INITIAL_CAPACITY;
        }
        m->table = realloc(m->table, newcap * sizeof(linked_list *));
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
        m->table = malloc(sizeof(linked_list *) * GMAP_INITIAL_CAPACITY);
        m->capacity = (m->table != NULL ? GMAP_INITIAL_CAPACITY : 0);
        m->size = 0;
    }
    return m;
}

size_t gmap_size(const gmap *m)
{
    if (m == NULL)
    {
        return 0;
    }

    return m->size;
}

void *gmap_put(gmap *m, const void *key, void *value)
{
    size_t index = m->hash(key) % m->capacity;
    // if index is empty, create a new linked list
    if (m->table[index] == NULL)
    {
        m->table[index] = linked_list_create();
    }
    // if there is no head, initialize the head
    if (m->table[index]->head == NULL)
    {
        m->table[index]->head = newNode(m->copy(key), value);
        m->size++;
        gmap_embiggen(m);
        return NULL;
    }
    linked_list *list = m->table[index];
    node *current = list->head;
    // traverse list to find matching node
    while (current->next)
    {
        if (m->compare(current->key, key) == 0)
        {
            void *toremove = current->value;
            current->value = value;
            return toremove;
        }
        current = current->next;
    }
    // if the key is not present, add it to the end of the list
    current->next = newNode(m->copy(key), value);
    m->size++;
    gmap_embiggen(m);
    return NULL;
}

void *gmap_remove(gmap *m, const void *key)
{
    size_t index = m->hash(key) % m->capacity;
    node *prev = NULL;
    if (!m->table[index])
    {
        return NULL;
    }
    linked_list *list = m->table[index];
    node *current = list->head;
    if (current && m->compare(current->key, key) == 0)
    {
        // at start of list
        list->head = current->next;
        m->size--;
        gmap_emsmallen(m);
        free(current);
        return current->value;
    }
    // traverse to end or node to remove
    while (current)
    {
        if (m->compare(current->key, key) == 0)
        {
            if (!current)
            {
                return NULL;
            }
            else
            {
                prev->next = current->next;
                m->size--;
                gmap_emsmallen(m);
                free(current);
                return current->value;
            }
        }
        prev = current;
        current = current->next;
    }
}

bool gmap_contains_key(const gmap *m, const void *key)
{
    size_t index = m->hash(key) % m->capacity;
    if (m->table[index] == NULL)
    {
        return false;
    }
    node *current = m->table[index]->head;
    while (current)
    {

        if (m->compare(key, current->key) == 0)
        {
            return current->value != NULL;
        }
        current = current->next;
    }
    return false;
}

void *gmap_get(gmap *m, const void *key)
{
    size_t index = m->hash(key) % m->capacity;
    node *current = m->table[index]->head;
    while (current)
    {
        if (m->compare(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void gmap_for_each(gmap *m, void (*f)(const void *, void *, void *), void *arg)
{
    for (size_t i = 0; i < m->capacity; i++)
    {
        node *bucket = m->table[i]->head;
        while (bucket->key)
        {
            f(bucket->key, bucket->value, arg);
            bucket = bucket->next;
        }
    }
}

const void **gmap_keys(gmap *m)
{
    size_t keys_index = 0;
    const void **keys = malloc(sizeof(void *) * m->size);
    for (size_t i = 0; i < m->capacity; i++)
    {
        if (m->table[i]->head->key)
        {
            keys[keys_index] = m->table[i]->head->key;
            keys_index++;
        }
    }
    return keys;
}

void gmap_destroy(gmap *m)
{
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

void gmap_print(gmap *m)
{
    if (m == NULL)
    {
        printf("Map is NULL\n");
        return;
    }

    printf("Map contents:\n");
    for (size_t i = 0; i < m->capacity; i++)
    {
        linked_list *bucket = m->table[i];
        if (bucket == NULL || bucket->head == NULL)
        {
            continue; // Skip empty buckets
        }
        node *current = bucket->head;
        while (current != NULL)
        {
            printf("Key: %c, Value: %d\n", current->key, current->value);
            current = current->next;
        }
    }
}