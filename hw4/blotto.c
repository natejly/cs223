# include <stdio.h>
# include <stdlib.h>
# include "entry.h"
# include "gmap.h"
# include "string_key.h"
#define MAX_ID 31
int main(int argc, char *argv[])
{
    if (argc < 2){
        fprintf(stderr, "not enough args");
        return 1;
    }
    int num_battles = argc - 1;
    int *battlefields = malloc(num_battles * sizeof(int));
    for (int i = 0; i < num_battles; i++){
        battlefields[i] = atoi(argv[i+1]);
    }

}
