#include <string.h>
#include <stdio.h>
#include "pirate_list.h"
int isSortFlag(char *flag)
{
    if (strcmp(flag, "-n") == 0 || strcmp(flag, "-v") == 0 || strcmp(flag, "-t") == 0) // compare to valid flags
    {
        return 1; // Valid sort flag
    }
    else if (flag[0] == '-')
    {
        return 2; // Invalid sort flag
    }
    return 0; // Not a sort flag
}
int assignInputs(int argc, char *argv[], char **profileFile, char **captainFile, char **sortFlag)
{if (argc < 3)
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
        else if (isSortFlag(argv[i]) == 2) // if invalid sort flag, print error message and return 1
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
    // If there are no flags, the first two arguments are file names
    if (flagCount == 0 && argc == 3)
    {
        *profileFile = argv[1];
        *captainFile = argv[2];
    }
    // Default sort flag
    *sortFlag = "-n";

    // Determine sort flag position and assign file names accordingly
    if (argc == 4)
    {
        // First argument is a sort flag
        if (isSortFlag(argv[1]) == 1)
        {
            *sortFlag = argv[1];
            *profileFile = argv[2];
            *captainFile = argv[3];
        }
        // Second argument is a sort flag
        else if (isSortFlag(argv[2]) == 1)
        {
            *sortFlag = argv[2];
            *profileFile = argv[1];
            *captainFile = argv[3];
        }
        // Third argument is a sort flag
        else
        {
            *sortFlag = argv[3];
            *profileFile = argv[1];
            *captainFile = argv[2];
        }
    }
    
    return 0;
}
compare_fn getCompareFN(char *sortFlag)
{
    if (strcmp(sortFlag, "-v") == 0)
    {
        return pirate_compare_vessel;
    }
    else if (strcmp(sortFlag, "-t") == 0)
    {
        return pirate_compare_treasure;
    }
    else
    {
        return pirate_compare_name;
    }
}