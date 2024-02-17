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
        fprintf(stderr, "invalid argument count\n");
        return 1;
    }
    //init vars
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "can't open file %s\n", argv[1]);
        return 1;
    }    
    pirate_list *pirates = list_create();
    list_insert(pirates, pirate_create("test"), 0);
    pirate_print(list_access(pirates, 0),stdout);

    list_insert(pirates, pirate_create("test1"), 121);

    pirate_print(list_access(pirates, 1),stdout);
    list_remove(pirates, "test");
    pirate_print(list_access(pirates, 0),stdout);




    // pirate *next_pirate = pirate_read(file);
    // while (next_pirate != NULL)
    // {
    //     pirate *p = list_insert(pirates, next_pirate, list_length(pirates));
    //     pirate_destroy(p);
    // }
    // list_insert(pirates, pirate_read(file), 1);
    // pirate_print(list_access(pirates, 1),stdout);
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
