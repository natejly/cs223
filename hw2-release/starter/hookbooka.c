#include <stdio.h>
#include <string.h>

#include "pirate.h"
#include "pirate_list.h"
#include "libhookbook.h"

int main(int argc, char *argv[])
{
    //checking for one or more argument input
    if (argc < 2)
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
    pirate *next_pirate = pirate_read(file);;

    while (next_pirate != NULL)
    {
        list_insert(pirates, next_pirate, list_length(pirates));
        next_pirate = pirate_read(file);

    }
    
    list_sort(pirates);
    for (size_t i = 0; i < list_length(pirates); i++)
    {
        pirate_print(list_access(pirates, i), stdout);
    }
    // list_destroy(pirates);
    fclose(file);
    return 0;

}
