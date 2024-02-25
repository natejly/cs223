#include "pirate.h"
#include "pirate_list.h"
#include "libhookbook.h"
#include "skills_list.h"
#include "main_helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    // Declare variables
    char *profileFile;
    char *captainFile;
    // Default sort flag
    char *sortFlag = "-n";

    // Check if there are enough arguments
    if (argc < 3)
    {
        fprintf(stderr, "Error: Not enough arguments\n");
        return 1;
    }
    // Check if there are too many arguments
    if (argc > 4)
    {
        fprintf(stderr, "Error: Too many arguments\n");
        return 1;
    }

    // Make sure 0 or 1 flags are used
    int flagCount = 0;
    // go through the arguments and check if they are sort flags and count them
    for (size_t i = 1; i < argc; i++)
    {
        if (isSortFlag(argv[i]) == 1)
        {
            flagCount++;
        }
        else if (isSortFlag(argv[i]) == 2) // if we see an invalid sort flag, print an error message and return 1
        {
            fprintf(stderr, "Error: Invalid sort flag %s\n", argv[i]);
            return 1;
        }
    }
    // too many flags
    if (flagCount > 1)
    {
        fprintf(stderr, "Error: Too many flags\n");
        return 1;
    }
    // no flags and more than 2 file names
    if (flagCount == 0 && argc == 4)
    {
        fprintf(stderr, "Error: Too many filenames\n");
        return 1;
    }
    // Determine sort flag position and assign file names accordingly
    // If there are no flags, the first two arguments are file names
    if (flagCount == 0 && argc == 3)
    {
        profileFile = argv[1];
        captainFile = argv[2];
    }
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
    // testing

    compare_fn cmp;
    if(strcmp(sortFlag, "-v")==0){
        cmp = pirate_compare_vessel;
    } else if (strcmp(sortFlag, "-t")==0){
        cmp = pirate_compare_treasure;
    } else {
        cmp = pirate_compare_name;
    }
    
    pirate_list *pirates = list_create_with_cmp(cmp);
    pirate *next_pirate = pirate_read(profile);
    while (next_pirate != NULL)
    {
        list_insert(pirates, next_pirate, list_length(pirates));
        next_pirate = pirate_read(profile);
    }

    free(next_pirate);
    list_sort(pirates);
    assignCaptains(pirates, captain);

    for (size_t i = 0; i < list_length(pirates); i++)
    {
        pirate_print(list_access(pirates, i), stdout);
    }
    // list_destroy(pirates);
    // fclose(profile);

    /**
     * Your main function must:
     *  1. Take three command-line arguments: the path to a file containing the
     *      pirates' profiles, the path to a file containing pirate/captain
     *      pairs, and the sort order.
     *  2. Open the profiles file and read from it the list of pirate profiles,
     *      appearing as specified in the README, and store them in a
     *      pirate_list*
     *  3. Open the captains file and read from it the list of pirate/captain
     *      pairs, appearing as specified in the README
     *  4. Sort the list in the order defined by the sort-flag command-line
     *      argument
     *  5. Print the sorted list to stdout, conforming to the format described
     *      in the README
     *  6. Release all resources (files, memory, etc.)
     */

}
// returns true if the flag is a valid sort flag
// returns false if the flag is not a valid sort flag
// prints an error message if the flag is not a valid sort flag
