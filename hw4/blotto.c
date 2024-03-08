#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entry.h"
#include "gmap.h"
#include "string_key.h"
#define MAX_ID 31
int main(int argc, char *argv[])
{

    if (argc < 2){
        fprintf(stderr, "not enough args");
        return 1;
    }
    int num_battles = argc - 1;
    int *battlefields = malloc(num_battles * sizeof(int));
    gmap *map = gmap_create(duplicate, compare_keys, hash29, free);
    entry current_entry = entry_read(stdin, MAX_ID, num_battles);
    while(current_entry.id[0] != '\0'){
    gmap_put(map, current_entry.id, current_entry.distribution);

    current_entry = entry_read(stdin, MAX_ID, num_battles);
    }
    //reading in the battlefields
    for(int i = 0; i < num_battles; i++){
        battlefields[i] = atoi(argv[i+1]);
    }
    char *line = malloc(MAX_ID * sizeof(char));
    char *currentplayer;

    //reading in the matchups
    char *player1;
    char *player2;
    while(freadln(line, MAX_ID, stdin) != NULL){

        player1 = strtok(line, " ");
        player2 = strtok(NULL, "");
        int *player1_distribution = gmap_get(map, player1);
        int *player2_distribution = gmap_get(map, player2);
        for(int i = 0; i < num_battles; i++){
        }
        for(int i = 0; i < num_battles; i++){
        }
        double player1_score = 0;
        double player2_score = 0;
        for(size_t i = 0; i < num_battles; i++){
            if(player1_distribution[i] > player2_distribution[i]){
                player1_score += battlefields[i];
            }
            else if(player1_distribution[i] < player2_distribution[i]){
                player2_score += battlefields[i];
            } else{
                player1_score += battlefields[i]/ 2.0;
                player2_score += battlefields[i]/ 2.0;
            
            }
        }
        if(player1_score > player2_score){
        fprintf(stdout, "%s %.1f - %s %.1f\n", player1, player1_score, player2, player2_score);
        }else{
        fprintf(stdout, "%s %.1f - %s %.1f\n", player2, player2_score, player1, player1_score);
        
        }
     }
    return 0;
    //whoever wins gets the point
    //if it's a tie we split the point
}