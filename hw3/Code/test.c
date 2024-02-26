#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "pirate_list.h"
#include "pirate.h"

int compare_pirates_by_name(const pirate *a, const pirate *b) {
    return strcmp(a->name, b->name);
}

void test_pirate_sort() {
    pirate_list *plist = list_create_with_cmp(pirate_compare_name);
    assert(plist != NULL);

    pirate *p1 = pirate_create("b");
    pirate *p2 = pirate_create("a");
    pirate *p3 = pirate_create("c");

    list_insert(plist, p1, list_length(plist));
    list_insert(plist, p2, list_length(plist));
    list_insert(plist, p3, list_length(plist));

    list_sort(plist);

    assert(list_access(plist, 0) == p2);
    assert(list_access(plist, 1) == p1);
    assert(list_access(plist, 2) == p3);



    list_destroy(plist);

    printf("test_pirate_sort passed\n");
}

int main() {
    test_pirate_sort();
    return 0;
}
//gcc -o test test.c pirate.c pirate_list.c skills_list.c libhookbook.c -Wall -std=c99