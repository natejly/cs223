// Nate Ly, CS223 Pset #4 (Blotto), 3/10/2024
// implementing abstract hashmap desrcribed in gmap.h
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
 * puts elements in the array same as gmap_put but does not copy keys
 * @param m a pointer to a map
 * @param key the key to put in
 * @param value the value associated with the key to add
 */
void *gmap_put_nocopy(gmap *m, const void *key, void *value);
/**
 * same as the gmap_destroy function except doesn't touch the keys
 * @param m a pointer to a gmap
 */
void gmap_destroynk(gmap *m);
/**
 * initializes and creates a linked list
 */
struct linked_list *linked_list_create();
/**
 * initializes and creates a new node
 * @param m the map to put the node in
 * @param key the key to associate with the node
 * @param value the value to associate with the node
 */
struct node *newNode(gmap *m, void *key, void *value);

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

struct node *newNode(gmap *m, void *key, void *value)
{
    struct node *temp = malloc(sizeof(struct node));
    if (temp == NULL)
    {
        return NULL;
    }
    temp->key = key;
    temp->value = value;
    temp->next = NULL;
    return temp;
}

void gmap_embiggen(gmap *m)
{
    // does embiggen if we are using more than half of the table
    if (m->size >= m->capacity / 2)
    {
        size_t newcap = m->capacity * 2;
        // create a new gmap
        gmap *temp = gmap_create(m->copy, m->compare, m->hash, m->free);
        // release its table and replace with one twice the size
        free(temp->table);
        temp->table = malloc(newcap * sizeof(linked_list *));
        // initialize to none
        for (size_t i = 0; i < newcap; i++)
        {
            temp->table[i] = NULL;
        }
        temp->capacity = newcap;
        // readd all elements to new list with new hash
        for (size_t i = 0; i < m->capacity; i++)
        {
            linked_list *list = m->table[i];
            if (list)
            { // traversing linked list
                node *current = list->head;
                node *prev = NULL;
                while (current)
                {
                    // not copying keys
                    gmap_put_nocopy(temp, current->key, current->value);
                    prev = current;
                    current = current->next;
                }
            }
        }
        // swaping the temp map with the old map
        gmap swap = *m;
        *m = *temp;
        *temp = swap;
        // free the temp map
        gmap_destroynk(temp);
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
        // set datafields to given
        m->copy = cp;
        m->compare = comp;
        m->hash = h;
        m->free = f;
        m->table = malloc(sizeof(linked_list *) * GMAP_INITIAL_CAPACITY);
        m->capacity = GMAP_INITIAL_CAPACITY;
        m->size = 0;
        // initialize to null
        for (size_t i = 0; i < m->capacity; i++)
        {
            m->table[i] = NULL;
        }
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
{ // call embiggen to resize if needed
    gmap_embiggen(m);
    // get hash
    size_t index = m->hash(key) % m->capacity;
    // if list is empty, create a linked list
    if (m->table[index] == NULL)
    {
        m->table[index] = linked_list_create();
    }
    node *current = NULL;
    node *prev = NULL;
    // go to linked list at hashed table index
    linked_list *list = m->table[index];
    current = list->head;
    // traverse list to check for matching node
    while (current)
    {
        if (m->compare(current->key, key) == 0)
        {
            void *toremove = current->value;
            current->value = value;
            return toremove;
        }
        prev = current;
        current = current->next;
    }
    // copy returns a poitner to a deep copy
    void *copy = m->copy(key);
    if (copy)
    { // make new node and add to end of list
        node *new = newNode(m, copy, value);
        m->size++;
        if (prev == NULL)
        {
            m->table[index]->head = new;
        }
        else
        {
            prev->next = new;
        }
        return NULL;
    }
    return NULL;
}
void *gmap_put_nocopy(gmap *m, const void *key, void *value)
{
    // same as gmap_put but no copy function when creagin new node
    gmap_embiggen(m);
    size_t index = m->hash(key) % m->capacity;
    // if list is empty, create a linked list
    if (m->table[index] == NULL)
    {
        m->table[index] = linked_list_create();
    }
    node *current = NULL;
    node *prev = NULL;
    linked_list *list = m->table[index];
    current = list->head;
    // traverse list to check for matching node
    while (current)
    {
        if (m->compare(current->key, key) == 0)
        {
            void *toremove = current->value;
            current->value = value;
            return toremove;
        }
        prev = current;
        current = current->next;
    }
    // same as gmap_put but not copying the node this time
    node *new = newNode(m, key, value);
    m->size++;

    if (prev == NULL)
    {
        m->table[index]->head = new;
    }
    else
    {
        prev->next = new;
    }
    return NULL;
}

void *gmap_remove(gmap *m, const void *key)
{
    // hashing
    size_t index = m->hash(key) % m->capacity;
    node *prev = NULL;
    if (!m->table[index])
    {
        return NULL;
    }
    // go to linked list at hash
    linked_list *list = m->table[index];
    node *current = list->head;
    if (current && m->compare(current->key, key) == 0)
    {
        // at start of list
        list->head = current->next;
        m->size--;
        void *value = current->value;
        // free found node and return value
        free(current->key);
        free(current);
        return value;
    }
    while (current)
    {
        // traversing list to find matching node
        if (m->compare(current->key, key) == 0)
        {
            if (!current)
            {
                return NULL;
            }
            else
            {
                // removing node and changing pointers
                prev->next = current->next;
                m->size--;
                void *value = current->value;
                free(current->key);
                free(current);
                return value;
            }
        }
        prev = current;
        current = current->next;
    }
}

bool gmap_contains_key(const gmap *m, const void *key)
{
    // hashing
    size_t index = m->hash(key) % m->capacity;
    // if no table can't have key so return false
    if (m->table[index] == NULL)
    {
        return false;
    }
    // start at head
    node *current = m->table[index]->head;
    while (current)
    {
        // if we find return true
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
    // hashing
    size_t index = m->hash(key) % m->capacity;
    if (m->table[index])
    {
        // go to linked list at hash
        node *current = m->table[index]->head;
        while (current)
        { // traverse and compare
            if (m->compare(current->key, key) == 0)
            {
                return current->value;
            }
            current = current->next;
        }
    }
    return NULL;
}

void gmap_for_each(gmap *m, void (*f)(const void *, void *, void *), void *arg)
{ // traverse table indexes
    for (size_t i = 0; i < m->capacity; i++)
    { // traverse linked list
        linked_list *list = m->table[i];
        if (list == NULL)
        {
            continue;
        }
        // traverse
        node *current = list->head;
        while (current)
        {
            // apply function
            f(current->key, current->value, arg);
            current = current->next;
        }
    }
}

const void **gmap_keys(gmap *m)
{
    // create keys list
    const void **keys = malloc(m->size * sizeof(void *));
    size_t keysindex = 0;
    // traverse table
    for (size_t i = 0; i < m->capacity; i++)
    {
        // traverse linked list
        linked_list *list = m->table[i];
        if (list)
        {
            node *current = list->head;
            while (current)
            {
                // add key to keys list
                keys[keysindex] = current->key;
                keysindex++;
                current = current->next;
            }
        }
    }
    return keys;
}
void gmap_destroy(gmap *m)
{
    if (m == NULL)
    {
        return;
    }
    // Traverse the table
    for (int i = 0; i < m->capacity; i++)
    {
        // Traverse the linked list at table[i]
        linked_list *list = m->table[i];
        if (list)
        {
            node *current = list->head;
            while (current != NULL)
            {
                // freeing keys
                node *next = current->next;
                m->free(current->key);
                free(current);
                current = next;
            }
            // Move to the next linked list
            free(list);
        }
    }
    // free the table
    free(m->table);

    // free the gmap struct
    free(m);
}
void gmap_destroynk(gmap *m)
{
    if (m == NULL)
    {
        return;
    }
    // Traverse the table
    for (int i = 0; i < m->capacity; i++)
    {
        // Traverse the linked list at table[i]
        linked_list *list = m->table[i];
        if (list)
        {
            node *current = list->head;
            while (current != NULL)
            {
                // not freeing keys here
                node *next = current->next;
                free(current);
                current = next;
            }
            // Move to the next linked list
            free(list);
        }
    }
    // free the table
    free(m->table);
    // free the gmap struct
    free(m);
}
