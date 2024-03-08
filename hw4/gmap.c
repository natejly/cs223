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
    if (temp == NULL) {
        return NULL; 
    }
    temp->key = key;
    temp->value = value;
    temp->next = NULL;
    return temp;
}
// might want to use load factor



void gmap_embiggen(gmap *m)
{
    if (m->size >= m->capacity / 2)
    {
        size_t newcap = m->capacity * 2;
        gmap *temp = gmap_create(m->copy, m->compare, m->hash, m->free);
        free(temp->table);
        temp->table = malloc(newcap * sizeof(linked_list *));
        for(size_t i = 0; i < newcap; i++){
            temp->table[i]= NULL;
        }
        temp->capacity = newcap;

        //readd all elements to new list with new hash
        for(size_t i = 0; i < m->capacity; i++){
            linked_list *list = m->table[i];
            if(list){
            node *current = list->head;
            node* prev = NULL;
            while(current){
                //do I have to copy the key
                gmap_put(temp, current->key, current->value);
                prev = current;
                current = current->next;

            }
            }
            }

        //    gmap swap = *m;
            *m = *temp;
            // *temp = swap;
            // gmap_destroy(temp);

        }
}
void gmap_emsmallen(gmap *m)
{
    if (m->size > GMAP_INITIAL_CAPACITY && m->size <= m->capacity / 4)
    {
        size_t newcap = m->capacity/2;
        gmap *temp = gmap_create(m->copy, m->compare, m->hash, m->free);
        temp->table = malloc(newcap * sizeof(linked_list *));
        temp->capacity = newcap;
        //readd all elements to new list with new hash
        for(size_t i = 0; i < m->capacity; i++){
            linked_list *list = m->table[i];
            if(list){
            node *current = list->head;
            while(current){
                gmap_put(temp, current->key, current->value);
                current = current->next;
            }
            }
            }
            
        m->table = temp->table;
        m->capacity = temp->capacity;
        m->size = temp->size;
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
        m->capacity = GMAP_INITIAL_CAPACITY;
        m->size = 0;
        for (size_t i = 0; i <  m->capacity; i++)
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
{
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
    //copy returns a poitner to a deep copy 
    node *new = newNode(m->copy(key), value);
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
        void *value = current->value;
        free(current->key);
        free(current);
        return value;
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
        linked_list *list = m->table[i];
        if (list == NULL)
        {
            continue; 
        }
        node *current = list->head;
        while (current)
        {
            f(current->key, current->value, arg);
            current = current->next;
        }
    }
}

const void **gmap_keys(gmap *m)
{
    //do we need to resize the array? no we don't you're an idiot
    const void **keys = malloc(m->size * sizeof(void *));
    size_t keysindex = 0;
    //traverse table
    for (size_t i = 0; i < m->capacity; i++)
    {
        //traverse linked list
        linked_list *list = m->table[i];
        if (list){
        node *current = list->head;
        while (current)
        {
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
    for (size_t i = 0; i < m->capacity; i++)
    {
    linked_list *list = m->table[i];
        if (list)
        {
         node *current = list->head;
        node *next = NULL;
        while (current)
    {
        //walk and destroy
        next = current->next;
        //freeing key here doen'st make s
        m->free(current->key);
        free(current);
        current = next;
    }

    free(list);
        }
    }
    free(m->table);
    free(m);
}

void gmap_print(gmap *m) {
    if (m == NULL) {
        printf("Map is NULL.\n");
        return;
    }

    printf("Map contents:\n");

    for (size_t i = 0; i < 5; i++) {
        linked_list *bucket = m->table[i];
        if (bucket != NULL) {
            node *current = bucket->head;
            while (current != NULL) {
                printf("Key: %s, Value: %d\n", (char*) current->key, (int*) current->value);
                current = current->next;
            }
        }
    }
}
