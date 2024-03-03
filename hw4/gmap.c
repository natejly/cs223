#include <stdio.h>

#include <stdlib.h>
#include <stdbool.h>
#include "gmap.h"


gmap *gmap_create(void *(*cp)(const void *), int (*comp)(const void *, const void *), size_t (*h)(const void *), void (*f)(void *));


size_t gmap_size(const gmap *m);

void *gmap_put(gmap *m, const void *key, void *value);

void *gmap_remove(gmap *m, const void *key);

bool gmap_contains_key(const gmap *m, const void *key);

void *gmap_get(gmap *m, const void *key);

void gmap_for_each(gmap *m, void (*f)(const void *, void *, void *), void *arg);

const void **gmap_keys(gmap *m);

void gmap_destroy(gmap *m);


