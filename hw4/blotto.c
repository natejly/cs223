#include <stdio.h>
#include <stdlib.h>
#include "entry.h"
#include "gmap.h"
#include "string_key.h"
#define MAX_ID 31
int main(int argc, char *argv[])
{
        char line[MAX_ID];

    if (argc < 2){
        fprintf(stderr, "not enough args");
        return 1;
    }
    int num_battles = argc - 1;
    int *battlefields = malloc(num_battles * sizeof(int));

    entry current_entry = entry_read(stdin, MAX_ID, num_battles);
    //print currenty entry attributes

    return 0;

}
