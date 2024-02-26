#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pirate.h"
#include "pirate_list.h"
#include "libhookbook.h"
#include "main_helpers.h"

int main(int argc, char *argv[])
{
    // Declare variables
    char *profileFile;
    char *captainFile;
    // Default sort flag
    char *sortFlag = "-n";    
    // give files and sort flag to the variables
    assignInputs(argc, argv, &profileFile, &captainFile, &sortFlag);

    // Open the files
    FILE *profile = fopen(profileFile, "r");
    FILE *captain = fopen(captainFile, "r");

    // Check if the files are openable and readable
    if (profile == NULL)
    {
        fprintf(stderr, "Error: Profile file not found or cannot be opened\n");
        return 1;
    }
    if (captain == NULL)
    {
        fprintf(stderr, "Error: Captain file not found or cannot be opened\n");
        return 1;
    }
    // initialize the compare function
    compare_fn cmp = getCompareFN(sortFlag);
    // create list of pirates
    pirate_list *pirates = list_create_with_cmp(cmp);
    pirate *next_pirate = pirate_read(profile);
    // create pirate to be removed if can't be inserted
    pirate *toremove;
    while (next_pirate != NULL)
    {
        // insert pirates into the list
        toremove = list_insert(pirates, next_pirate, list_length(pirates));
        if (toremove != NULL)
        {
            // free pirate if not inserted
            pirate_destroy(toremove);
        }
        next_pirate = pirate_read(profile);
    }
    free(next_pirate);
    list_sort(pirates);
    // assign captains to pirates
    assignCaptains(pirates, captain);
    for (size_t i = 0; i < list_length(pirates); i++)
    {
        pirate_print(list_access(pirates, i), stdout);
    }
    list_destroy(pirates);
    fclose(profile);
    fclose(captain);
    return 0;
}
