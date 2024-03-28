// Nate Ly, CS223 Pset #4 (Blotto), 3/10/2024
// file containing unit tests implementation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gmap.h"
#include "gmap_test_functions.h"
#include "string_key.h"

/**
 * Non-exhaustive unit test script for gmap.
 * Author: James Glenn
 * Modified by: Alan Weide
 * Modified on: October 2023
 * Changelog:
 *  - Added comments with test numbers
 *  - Added print statements to print the test numbers when none is provided
 *
 * Test numbers:
 * 1: test_initial_size(0, on);
 * 2: test_uses_hash(SMALL_TEST_SIZE);
 * 3: test_get();
 * 4: test_size(SMALL_TEST_SIZE);
 * 5: test_contains(SMALL_TEST_SIZE);
 * 6: test_put_copies_key();
 * 7: test_put_does_not_copy_value();
 * 8: test_put_multiple_times();
 * 9: test_remove();
 * 10: test_remove_not_present();
 * 11: test_remove_collision();
 * 12: test_large_map(LARGE_TEST_SIZE, java_hash_string);
 * 13: test_for_each(SMALL_TEST_SIZE);
 * 14: test_keys_survive_embiggen(SMALL_TEST_SIZE, SMALL_TEST_SIZE);
 * 15: test_keys_survive_embiggen(SMALL_TEST_SIZE, MEDIUM_TEST_SIZE);
 * 16: test_other_types();
 * 17: test_put_time(n, on, java_hash_string);
 * 18: test_get_time(n, on, java_hash_string);
 * 19: test_for_each_time(n, on, java_hash_string);
 * 20: test_large_map(MEDIUM_TEST_SIZE, hash_string_first);
 * 21: test_put_time(n, on, hash_string_first);
 * 22: test_get_time(n, on, hash_string_first);
 *
 * TO STUDENT: Do not modify anything in this file. You may add to it, but you
 *  must not modify anything that is already here. If you do, enter your name
 *  and date below along with a description of the changes that you made.
 * Modified by: Nate Ly
 * Modified on: 03/03/2024
 * Changelog: added voids to avoid implicit declaration of function errors
 *  also changed the declaration of return_keys to avoid another error
 */

void test_initial_size(size_t size, int on);
void test_get(void);
void test_get_time(size_t n, int on, size_t (*hash)(const void *));
void test_size(size_t n);
void test_contains(size_t n);
void test_put_copies_key(void);
void test_put_does_not_copy_value(void);
void test_put_multiple_times(void);
void test_remove(void);
void test_remove_not_present(void);
void test_remove_collision(void);
void test_remove_destroy(void);
void test_large_map(size_t n, size_t (*hash)(const void *));
void test_for_each(size_t n);
void test_put_time(size_t n, int on, size_t (*hash)(const void *));
void test_for_each_time(size_t n, int on, size_t (*hash)(const void *));
void test_uses_hash(size_t n);
void test_keys_survive_embiggen(size_t n1, size_t n2);
void test_other_types(void);

size_t printing_hash_string(const void *s);
int compare_key_pointers(const void *k1, const void *k2);

gmap *make_map(const char *prefix, size_t n, int value);
void add_keys(gmap *m, char *const *keys, size_t n, int value);
void add_keys_with_values(gmap *m, char *const *keys, size_t n, int *values);

void gmap_unit_free_value(const void *key, void *value, void *arg);

#define SMALL_TEST_SIZE 4
#define MEDIUM_TEST_SIZE 1000
#define LARGE_TEST_SIZE 100000
#define VERY_LARGE_TEST_SIZE 1000000

int main(int argc, char **argv)
{

    int test = 0;
    size_t n = 0;
    int on = 0;

    if (argc > 1)
    {
        test = atoi(argv[1]);
    }
    if (argc > 2)
    {
        // test size and on/off
        if (atoi(argv[2]) < 0)
        {
            fprintf(stderr, "%s: test size must be positive\n", argv[0]);
            return 1;
        }
        n = atoi(argv[2]);
        on = atoi(argv[3]) == 1;
    }

    switch (test)
    {
    case 1:
        test_initial_size(0, on);
        break;

    case 2:
        test_uses_hash(SMALL_TEST_SIZE);
        break;

    case 3:
        test_get();
        break;

    case 4:
        test_size(SMALL_TEST_SIZE);
        break;

    case 5:
        test_contains(SMALL_TEST_SIZE);
        break;

    case 6:
        test_put_copies_key();
        break;

    case 7:
        test_put_does_not_copy_value();
        break;

    case 8:
        test_put_multiple_times();
        break;

    case 9:
        test_remove();
        break;

    case 10:
        test_remove_not_present();
        break;

    case 11:
        test_remove_collision();
        break;

    case 12:
        test_large_map(LARGE_TEST_SIZE, java_hash_string);
        break;

    case 13:
        test_for_each(SMALL_TEST_SIZE);
        break;

    case 14:
        // calling with 0 additional keys tests keys w/o embiggen
        test_keys_survive_embiggen(SMALL_TEST_SIZE, SMALL_TEST_SIZE);
        break;

    case 15:
        // NOW we add enough additional keys to trigger an embiggen
        test_keys_survive_embiggen(SMALL_TEST_SIZE, MEDIUM_TEST_SIZE);
        break;

    case 16:
        test_other_types();
        break;

    case 17:
        test_put_time(n, on, java_hash_string);
        break;

    case 18:
        test_get_time(n, on, java_hash_string);
        break;

    case 19:
        test_for_each_time(n, on, java_hash_string);
        break;

    case 20:
        test_large_map(MEDIUM_TEST_SIZE, hash_string_first);
        break;

    case 21:
        test_put_time(n, on, hash_string_first);
        break;

    case 22:
        test_get_time(n, on, hash_string_first);
        break;

    default:
        fprintf(stderr, "USAGE: %s test-number\n", argv[0]);
        fprintf(stderr, "Test numbers:\n");
        fprintf(stderr, "\t 1: test_initial_size(0, on);\n");
        fprintf(stderr, "\t 2: test_uses_hash(SMALL_TEST_SIZE);\n");
        fprintf(stderr, "\t 3: test_get();\n");
        fprintf(stderr, "\t 4: test_size(SMALL_TEST_SIZE);\n");
        fprintf(stderr, "\t 5: test_contains(SMALL_TEST_SIZE);\n");
        fprintf(stderr, "\t 6: test_put_copies_key();\n");
        fprintf(stderr, "\t 7: test_put_does_not_copy_value();\n");
        fprintf(stderr, "\t 8: test_put_multiple_times();\n");
        fprintf(stderr, "\t 9: test_remove();\n");
        fprintf(stderr, "\t10: test_remove_not_present();\n");
        fprintf(stderr, "\t11: test_remove_collision();\n");
        fprintf(stderr, "\t12: test_large_map(LARGE_TEST_SIZE, java_hash_string);\n");
        fprintf(stderr, "\t13: test_for_each(SMALL_TEST_SIZE);\n");
        fprintf(stderr, "\t14: test_keys_survive_embiggen(SMALL_TEST_SIZE, SMALL_TEST_SIZE);\n");
        fprintf(stderr, "\t15: test_keys_survive_embiggen(SMALL_TEST_SIZE, MEDIUM_TEST_SIZE);\n");
        fprintf(stderr, "\t16: test_other_types();\n");
        fprintf(stderr, "\t17: test_put_time(n, on, java_hash_string);\n");
        fprintf(stderr, "\t18: test_get_time(n, on, java_hash_string);\n");
        fprintf(stderr, "\t19: test_for_each_time(n, on, java_hash_string);\n");
        fprintf(stderr, "\t20: test_large_map(MEDIUM_TEST_SIZE, hash_string_first);\n");
        fprintf(stderr, "\t21: test_put_time(n, on, hash_string_first);\n");
        fprintf(stderr, "\t22: test_get_time(n, on, hash_string_first);\n");
    }
}

gmap *make_map(const char *prefix, size_t n, int value)
{
    gmap *m = gmap_create(duplicate, compare_keys, java_hash_string, free);

    char **keys = make_words(prefix, n);
    add_keys(m, keys, n, value);
    free_words(keys, n);

    return m;
}

void add_keys(gmap *m, char *const *keys, size_t n, int value)
{
    for (size_t i = 0; i < n; i++)
    {
        int *temp = malloc(sizeof(int));
        *temp = value;
        gmap_put(m, keys[i], temp);
    }
}

void add_keys_with_values(gmap *m, char *const *keys, size_t n, int *values)
{
    for (size_t i = 0; i < n; i++)
    {
        gmap_put(m, keys[i], values + i);
    }
}

void test_get(void)
{
    gmap *m = gmap_create(duplicate, compare_keys, java_hash_string, free);

    int twenty = 20;
    gmap_put(m, "Twenty", &twenty);

    if (*((int *)gmap_get(m, "Twenty")) == 20)
    {
        PRINT_PASSED;
    }
    else
    {
        PRINT_FAILED;
    }

    gmap_destroy(m);
}

void test_get_time(size_t n, int on, size_t (*hash)(const void *))
{
    gmap *m = gmap_create(duplicate, compare_keys, hash, free);
    char **keys = make_random_words(10, n);
    add_keys(m, keys, n, 1);

    if (on == 1)
    {
        for (int i = 0; i < n; i++)
        {
            if (*((int *)gmap_get(m, keys[i])) != 1)
            {
                printf("FAILED -- retrieved value is incorrect\n");

                free_values(m, keys, n);
                gmap_destroy(m);
                free_words(keys, n);
                return;
            }
        }
    }

    free_values(m, keys, n);
    gmap_destroy(m);
    free_words(keys, n);
}

void test_initial_size(size_t n, int on)
{
    int *dummy = malloc(sizeof(int));
    free(dummy);

    if (on)
    {
        gmap *m = gmap_create(duplicate, compare_keys, java_hash_string, free);
        gmap_destroy(m);
    }
}

void test_size(size_t n)
{
    gmap *m = gmap_create(duplicate, compare_keys, java_hash_string, free);

    if (gmap_size(m) != 0)
    {
        PRINT_FAILED;
        return;
    }

    char **keys = make_words("word", n);
    add_keys(m, keys, n, 0);

    if (gmap_size(m) != n)
    {
        printf("FAILED -- size is %lu after %lu puts\n", gmap_size(m), n);

        free_values(m, keys, n);
        gmap_destroy(m);
        free_words(keys, n);
        return;
    }

    gmap_put(m, "word0", gmap_get(m, "word0"));

    if (gmap_size(m) != n)
    {
        printf("FAILED -- size changed when putting duplicate key\n");

        free_values(m, keys, n);
        gmap_destroy(m);
        free_words(keys, n);
        return;
    }

    free_values(m, keys, n);
    gmap_destroy(m);
    free_words(keys, n);

    PRINT_PASSED;
}

void test_contains(size_t n)
{
    gmap *m = gmap_create(duplicate, compare_keys, java_hash_string, free);
    char **keys = make_words("word", n);
    char **not_keys = make_words("worte", n);

    add_keys(m, keys, n, 0);
    for (int i = 0; i < n; i++)
    {
        if (!gmap_contains_key(m, keys[i]))
        {
            printf("FAILED -- does not contain key %s\n", keys[i]);

            free_values(m, keys, n);
            gmap_destroy(m);
            free_words(keys, n);
            free_words(not_keys, n);
            return;
        }
        if (gmap_contains_key(m, not_keys[i]))
        {
            printf("FAILED -- contains non-key %s\n", not_keys[i]);

            free_values(m, keys, n);
            gmap_destroy(m);
            free_words(keys, n);
            free_words(not_keys, n);
            return;
        }
    }

    free_values(m, keys, n);
    gmap_destroy(m);
    free_words(keys, n);
    free_words(not_keys, n);

    PRINT_PASSED;
}

void test_put_copies_key(void)
{
    gmap *m = gmap_create(duplicate, compare_keys, java_hash_string, free);
    char *key = malloc(sizeof(char) * (strlen("Twenty") + 1));
    strcpy(key, "Twenty");

    int twenty = 20;
    gmap_put(m, key, &twenty);
    strcpy(key, "Plenty");

    if (!gmap_contains_key(m, "Twenty"))
    {
        printf("FAILED -- key in map lost\n");

        gmap_destroy(m);
        free(key);
        return;
    }
    else if (gmap_contains_key(m, "Plenty"))
    {
        printf("FAILED -- key in map changed\n");

        gmap_destroy(m);
        free(key);
        return;
    }
    else if (*((int *)gmap_get(m, "Twenty")) != 20)
    {
        printf("FAILED -- incorrect value for key\n");

        gmap_destroy(m);
        free(key);
        return;
    }

    gmap_destroy(m);
    free(key);
    PRINT_PASSED;
}

void test_put_does_not_copy_value(void)
{
    gmap *m = gmap_create(duplicate, compare_keys, java_hash_string, free);

    int twenty = 20;
    gmap_put(m, "Twenty", &twenty);
    twenty++;

    if (*((int *)gmap_get(m, "Twenty")) != 21)
    {
        printf("FAILED -- value did not change\n");

        gmap_destroy(m);
        return;
    }

    gmap_destroy(m);
    PRINT_PASSED;
}

void test_put_multiple_times(void)
{
    gmap *m = gmap_create(duplicate, compare_keys, java_hash_string, free);

    int *values = malloc(sizeof(int) * 20);
    for (int i = 0; i < 20; i++)
    {
        values[i] = i + 1;
        int *old_value = gmap_put(m, "Twenty", values + i);
        if (i == 0 && old_value != NULL)
        {
            printf("FAILED -- first put did not return NULL\n");
            goto destroy_map; // goto for freeing after error lessens repetition
        }
        else if (i > 0 && *old_value != i)
        {
            printf("FAILED -- put reported old value of %d when new value was %d\n", *old_value, i + 1);
            goto destroy_map;
        }
    }

    if (*((int *)gmap_get(m, "Twenty")) != 20)
    {
        printf("FAILED -- value did not update after multiple puts\n");
        goto destroy_map;
    }

    gmap_destroy(m);
    free(values);

    PRINT_PASSED;
    return;

destroy_map:
    gmap_destroy(m);
    free(values);
}

void test_large_map(size_t n, size_t (*hash)(const void *))
{
    gmap *m = gmap_create(duplicate, compare_keys, hash, free);
    char **keys = make_words("word", n);
    char **not_keys = make_words("wort", n);
    for (int i = 0; i < n; i++)
    {
        int *value = malloc(sizeof(int));
        *value = n - i;

        gmap_put(m, keys[i], value);
    }
    if (gmap_size(m) != n)
    {
        printf("FAILED -- size is %lu; should be %lu\n", gmap_size(m), n);

        free_values(m, keys, n);
        gmap_destroy(m);
        free_words(keys, n);
        free_words(not_keys, n);
        return;
    }

    for (size_t i = 0; i < n; i++)
    {
        if (!gmap_contains_key(m, keys[i]))
        {
            printf("FAILED -- map missing key %s\n", keys[i]);

            free_values(m, keys, n);
            gmap_destroy(m);
            free_words(keys, n);
            free_words(not_keys, n);
            return;
        }
        else if (*((int *)gmap_get(m, keys[i])) != n - i)
        {
            printf("FAILED -- value for key %s is not %lu\n", keys[i], n - i);

            free_values(m, keys, n);
            gmap_destroy(m);
            free_words(keys, n);
            free_words(not_keys, n);
            return;
        }
        else if (gmap_contains_key(m, not_keys[i]))
        {
            printf("FAILED -- map contains non-key %s\n", not_keys[i]);

            free_values(m, keys, n);
            gmap_destroy(m);
            free_words(keys, n);
            free_words(not_keys, n);
            return;
        }
    }

    free_values(m, keys, n);
    gmap_destroy(m);
    free_words(keys, n);
    free_words(not_keys, n);

    PRINT_PASSED;
}

void sum_keys_and_values(const void *key, void *value, void *p)
{
    int *sum = p;
    *sum += atoi(key);
    *sum += *((int *)value);
}

void test_for_each(size_t n)
{
    int sum = 0;
    gmap *m = make_map("", n, 2);
    gmap_for_each(m, sum_keys_and_values, &sum);
    if (sum != n * (n - 1) / 2 + 2 * n)
    {
        printf("FAILED -- sum of keys and values is %d\n", sum);
    }

    gmap_for_each(m, gmap_unit_free_value, NULL);

    gmap_destroy(m);
    PRINT_PASSED;
}
// defined returned_keys earlier so no error
void test_keys_survive_embiggen(size_t n1, size_t n2)
{
    gmap *m = gmap_create(duplicate, compare_keys, java_hash_string, free);
    const char **returned_keys = NULL;
    char **keys = make_words("key", n2);
    add_keys(m, keys, n1, 33);

    if (gmap_size(m) != n1)
    {
        printf("FAILED -- could not add all keys to map\n");
        goto destroy_keys;
    }

    // get the current keysb2
    returned_keys = (const char **)gmap_keys(m);

    if (returned_keys == NULL)
    {
        printf("FAILED -- gmap_keys returned NULL\n");
        goto destroy_keys;
    }

    // add more keys -- enough to trigger an embiggen
    add_keys(m, keys + n1, n2 - n1, 20);

    if (gmap_size(m) != n2)
    {
        printf("FAILED -- could not add all additional keys to map\n");
        goto destroy_keys;
    }

    // search for NULL entries
    size_t i = 0;
    while (i < n1 && returned_keys[i] != NULL)
    {
        i++;
    }

    if (i < n1)
    {
        printf("FAILED -- NULL in returned array\n");
        goto destroy_keys;
    }

    // sort the keys so order of output doesn't depend on hash function
    qsort(returned_keys, n1, sizeof(*returned_keys), compare_key_pointers);

    // sort the original keys to facilitate comparison
    qsort(keys, n1, sizeof(*keys), compare_key_pointers);

    i = 0;
    while (i < n1 && strcmp(returned_keys[i], keys[i]) == 0)
    {
        i++;
    }
    if (i < n1)
    {
        printf("FAILED -- %zuth returned key is %s, not %s\n", i, returned_keys[i], keys[i]);
        goto destroy_keys;
    }

    free(returned_keys);
    free_words(keys, n2);
    gmap_for_each(m, gmap_unit_free_value, NULL);
    gmap_destroy(m);
    PRINT_PASSED;
    return;

destroy_keys:
    free(returned_keys);
    free_words(keys, n2);
    gmap_for_each(m, gmap_unit_free_value, NULL);
    gmap_destroy(m);
}

int compare_key_pointers(const void *k1, const void *k2)
{
    // k1 and k2 are really pointers to the pointers to the keys cast
    // them to what they really are, dereference to get the the pointers
    // to the keys, and compare with strcmp
    return strcmp(*(const char **)k1, *(const char **)k2);
}

void test_put_time(size_t n, int on, size_t (*hash)(const void *))
{
    gmap *m = gmap_create(duplicate, compare_keys, hash, free);
    char **keys = make_random_words(10, n);
    int *values = calloc(n, sizeof(int));

    if (on == 1)
    {
        add_keys_with_values(m, keys, n, values);
    }

    free(values);
    gmap_destroy(m);
    free_words(keys, n);
}

void count_keys(const void *key, void *value, void *p)
{
    (*((int *)p))++;
}

void test_for_each_time(size_t n, int on, size_t (*hash)(const void *))
{
    gmap *m = gmap_create(duplicate, compare_keys, hash, free);
    char **keys = make_random_words(10, n);
    int *values = calloc(n, sizeof(int));
    add_keys_with_values(m, keys, n, values);

    int sum = 0;

    if (on == 1)
    {
        gmap_for_each(m, count_keys, &sum);
        if (sum != n)
        {
            printf("FAILED -- iterated over %d keys\n", sum);

            free(values);
            free_words(keys, n);
            gmap_destroy(m);
            return;
        }
    }

    free(values);
    free_words(keys, n);
    gmap_destroy(m);
}

void gmap_unit_free_value(const void *key, void *value, void *arg)
{
    free(value);
}

void test_uses_hash(size_t n)
{
    gmap *m = gmap_create(duplicate, compare_keys, printing_hash_string, free);

    char **keys = make_words("word", n);
    int *values = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        gmap_put(m, keys[i], values + i);
    }

    int *value = malloc(sizeof(int));
    *value = 42;
    printf("And now a message from your friendly local hash function: ");
    gmap_put(m, "magic", value);
    gmap_destroy(m);
    free_words(keys, n);
    free(values);
    free(value);
}

size_t printing_hash_string(const void *s)
{
    if (strcmp("magic", s) == 0)
    {
        printf("hello!\n");
    }

    return java_hash_string(s);
}

typedef struct _pair
{
    int x;
    int y;
} pair;

void *copy_pair(const void *ptr)
{
    const pair *p = ptr;

    pair *copy = malloc(sizeof(pair));
    *copy = *p;
    return copy;
}

int compare_pairs(const void *p1, const void *p2)
{
    const pair *pair1 = p1;
    const pair *pair2 = p2;

    if (pair1->x != pair2->x)
    {
        return pair1->x - pair2->x;
    }
    else
    {
        return pair1->y - pair2->y;
    }
}

size_t hash_pair(const void *p)
{
    const pair *pair = p;

    // this is not intended to be good
    return pair->x + pair->y;
}

void test_other_types(void)
{
    gmap *m = gmap_create(copy_pair, compare_pairs, hash_pair, free);

    pair key = {10, 23};
    pair not_key = {23, 10};
    char *value = "value";

    gmap_put(m, &key, value);

    if (!gmap_contains_key(m, &key))
    {
        printf("FAILED -- key is missing\n");
        goto destroy_map;
    }
    else if (gmap_contains_key(m, &not_key))
    {
        printf("FAILED -- map contains non-key\n");
        goto destroy_map;
    }
    else if (gmap_get(m, &key) != value)
    {
        printf("FAILED -- incorrect value\n");
        goto destroy_map;
    }

    gmap_destroy(m);
    PRINT_PASSED;
    return;

destroy_map:
    gmap_destroy(m);
}

void test_remove(void)
{
    gmap *m = gmap_create(duplicate, compare_keys, hash_string_sum, free);
    int *nbo_value = malloc(sizeof(int));
    *nbo_value = 10;
    int *cai_value = malloc(sizeof(int));
    *cai_value = 11;

    gmap_put(m, "NBO", nbo_value);
    gmap_put(m, "CAI", cai_value);
    gmap_remove(m, "NBO");

    if (gmap_contains_key(m, "NBO"))
    {
        printf("FAILED -- map contains removed key NBO\n");
        goto destroy_values;
    }

    if (!gmap_contains_key(m, "CAI"))
    {
        printf("FAILED -- map lost key CAI after removing NBO\n");
        goto destroy_values;
    }

    if (*(int *)gmap_get(m, "CAI") != 11)
    {
        printf("FAILED -- map changed value for CAI after removing NBO\n");
        goto destroy_values;
    }

    if (gmap_size(m) != 1)
    {
        printf("FAILED -- incorrect size %zu after remove\n", gmap_size(m));
        goto destroy_values;
    }

    free(cai_value);
    free(nbo_value);
    gmap_destroy(m);
    PRINT_PASSED;
    return;

destroy_values:
    free(cai_value);
    free(nbo_value);
    gmap_destroy(m);
}

void test_remove_not_present(void)
{
    gmap *m = gmap_create(duplicate, compare_keys, hash_string_sum, free);
    int *nbo_value = malloc(sizeof(int));
    *nbo_value = 10;
    int *cai_value = malloc(sizeof(int));
    *cai_value = 11;

    gmap_put(m, "NBO", nbo_value);
    gmap_remove(m, "CAI");

    if (gmap_contains_key(m, "CAI"))
    {
        printf("FAILED -- map contains key CAI that was never added\n");
        goto destroy_values;
    }

    if (!gmap_contains_key(m, "NBO"))
    {
        printf("FAILED -- map lost key NBO after removing CAI\n");
        goto destroy_values;
    }

    if (*(int *)gmap_get(m, "NBO") != 10)
    {
        printf("FAILED -- map changed value for NBO after removing CAI\n");
        goto destroy_values;
    }

    if (gmap_size(m) != 1)
    {
        printf("FAILED -- incorrect size %zu after remove\n", gmap_size(m));
        goto destroy_values;
    }

    free(cai_value);
    free(nbo_value);
    gmap_destroy(m);
    PRINT_PASSED;
    return;

destroy_values:
    free(cai_value);
    free(nbo_value);
    gmap_destroy(m);
}

void test_remove_collision(void)
{
    gmap *m = gmap_create(duplicate, compare_keys, hash_string_first, free);
    int *bwi_value = malloc(sizeof(int));
    *bwi_value = 10;
    int *bos_value = malloc(sizeof(int));
    *bos_value = 11;
    int *btr_value = malloc(sizeof(int));
    *btr_value = 12;
    gmap_put(m, "BWI", bwi_value);
    gmap_put(m, "BOS", bos_value);
    gmap_put(m, "BTR", btr_value);

    gmap_remove(m, "BOS");

    if (gmap_contains_key(m, "BOS"))
    {
        printf("FAILED -- map contains removed key BOS\n");
        goto destroy_values;
    }

    if (!gmap_contains_key(m, "BWI"))
    {
        printf("FAILED -- map lost key BWI after removing BOS\n");
        goto destroy_values;
    }

    if (!gmap_contains_key(m, "BTR"))
    {
        printf("FAILED -- map lost key BTR after removing BOS\n");
        goto destroy_values;
    }

    if (*(int *)gmap_get(m, "BWI") != 10)
    {
        printf("FAILED -- value changed for key BWI after removing BOS\n");
        goto destroy_values;
    }

    if (*(int *)gmap_get(m, "BTR") != 12)
    {
        printf("FAILED -- value changed for key BTR after removing BOS\n");
        goto destroy_values;
    }

    gmap_remove(m, "BTR");

    if (gmap_contains_key(m, "BTR"))
    {
        printf("FAILED -- map contains removed key BTR\n");
        goto destroy_values;
    }

    if (!gmap_contains_key(m, "BWI"))
    {
        printf("FAILED -- map lost key BWI after removing BTR\n");
        goto destroy_values;
    }

    if (gmap_size(m) != 1)
    {
        printf("FAILED -- incorrect size %zu after removes\n", gmap_size(m));
        goto destroy_values;
    }

    free(bwi_value);
    free(bos_value);
    free(btr_value);
    gmap_destroy(m);
    PRINT_PASSED;
    return;

destroy_values:
    free(bwi_value);
    free(bos_value);
    free(btr_value);
    gmap_destroy(m);
}
