// Nate Ly, CS223 Pset #4 (Blotto), 3/10/2024
//header file for helper functions in blottohelpers.c
#include "gmap.h"
/**
 * checks if inputs are valid
 * @param argc
 * @returns 1 if invalid input, nothing if valid
*/
int validInput(argc);
/**
 * used as function pointer for for each
 * @param m gmap to free 
 * @param value value to free for function pointer
 * @param thing nothing
 * @returns 1 if invalid input, nothing if valid
*/
void free_pointerfunction(gmap *m, void *value, void *thing);
/**
 * reads the matchups from standard in and then calculates
 * and prints out scores according to the ReadMe
 * @param map gmap to read from
 * @param MAX_ID max line length
 * @param battlefields array of battlefields
 * @param num_battles the number of battles
*/
int read_matchups_print(gmap *map, size_t MAX_ID, int* battlefields, int num_battles);
