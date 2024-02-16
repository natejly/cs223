#include <stdio.h>
#include <string.h>

#include "pirate.h"
#include "pirate_list.h"
#include "libhookbook.h"

int main(int argc, char *argv[])
{
    //checking for one argument input
    if (argc != 2)
    {
        printf("Error: invalid argument count\n");
        return 1;
    }
    //init vars
    FILE *file;
    // pirate_list *list = list_create();
    char name[127];
    //open file given in command line
    file = fopen(argv[1], "r");
    //if can't be opened then error
    if (file == NULL)
    {
        printf("Error: File not found\n");
        return 1;
    }
    //reads each pirate name and stores in name and stores in name
    while (fscanf(file, "%s", name) != EOF)
    {
        pirate *p = pirate_create(name);
    }
    /**
     * Your main function must:
     *   1. Take as the only command-line argument the path to a file
     *      containing the pirates' names to be placed into your Hookbook.
     *   2. Open that file and read from it the list of pirate names, formatted
     *      as specified in the README, and store them in a pirate_list*
     *   3. Sort the list in lexicographic order by pirate name
     *   4. Print the sorted list to stdout, conforming to the format described
     *      in the README
     *   5. Release all resources (files, memory, etc.)
     */
}
