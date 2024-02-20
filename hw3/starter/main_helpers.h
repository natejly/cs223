#pragma once
/**
 * Header file for main_helpers for HookBook B in CPSC 223 SP2024.
 *
 * Author: Nate Ly
 *

 * Modified by: Nate Ly 
 * Changelog: 2/20/2024 created header file for main_helpers
 */
/**
 * takes in a string and checks if it is a valid sort flag according to the readme
 * @param flag the string to check
 * @returns 1 if the flag is valid, 0 if it is not a flag, 2 if it is an invalid flag
*/
int isSortFlag(char *flag);

/**
 * assigns the filenames to the correct pointers from input
 * @param argc the number of arguments
 * @param argv the arguments
 * @param profileFile the pointer to the profile file
 * @param captainFile the pointer to the captain file
 * @param sortFlag the pointer to the sort flag
 * @returns void
*/
void assignFilenames(int argc, char *argv[], char **profileFile, char **captainFile, char **sortFlag);

