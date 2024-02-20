#include <string.h>
// takes in a string
// returns 1 if the string is a valid sort flag
// returns 2 if the string is an invalid sort flag
// returns 0 if the string is not a sort flag
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
void assignFilenames(int argc, char *argv[], char **profileFile, char **captainFile, char **sortFlag)
{
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
}