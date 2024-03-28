// Nate Ly, CS223 Pset #4 (Blotto), 3/10/2024
// driver file for blotto
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entry.h"
#include "gmap.h"
#include "blottohelpers.h"
#include "string_key.h"
#define MAX_ID 31

int main(int argc, char *argv[])
{
    // check if inputs are valid
    if (validInput(argc) == 1)
    {
        return 1;
    }
    int num_battles = argc - 1;
    // create gmap
    gmap *map = gmap_create(duplicate, compare_keys, hash29, free);
    entry current_entry = entry_read(stdin, MAX_ID, num_battles);
    // Check if we have an input
    if (!current_entry.id)
    {
        fprintf(stderr, "nothing to read");
        gmap_for_each(map, &free_pointerfunction, NULL);
        gmap_destroy(map);
        return 1;
    }
    // reading in the entries to the hashmap
    while (current_entry.id[0] != '\0')
    {
        gmap_put(map, current_entry.id, current_entry.distribution);
        free(current_entry.id);
        current_entry = entry_read(stdin, MAX_ID, num_battles);
    }
    // reading in the battlefields
    int *battlefields = malloc(num_battles * sizeof(int));
    for (int i = 0; i < num_battles; i++)
    {
        battlefields[i] = atoi(argv[i + 1]);
    }
    // process hashmap and print scores
    if (read_matchups_print(map, MAX_ID, battlefields, num_battles) == 1)
    {
        fprintf(stderr, "no matchups found");
        free(battlefields);
        entry_destroy(&current_entry);
        gmap_for_each(map, &free_pointerfunction, NULL);
        gmap_destroy(map);
        return 1;
    }
    entry_destroy(&current_entry);
    gmap_for_each(map, &free_pointerfunction, NULL);
    gmap_destroy(map);
    return 0;
}
