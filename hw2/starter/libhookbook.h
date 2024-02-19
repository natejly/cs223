#pragma once

/**
 * Use this file to encapsulate useful functionality that doesn't belong in
 * either pirate.h or pirate_list.h.
 *
 * For Hookbook A in CPSC 223 SP2024.
 *
 * Author: Alan Weide
 *
 * TO STUDENT: You may add to this file, but do not change anything that is
 *     already here!
 * Modified by: [your name here] on [date of modification]
 * Changelog: [what you added to this file]
 */

#define MAX_LINE_LENGTH 127

#include <stdio.h>

/**
 * Reads the next line of input from stream, discarding the trailing newline
 *  character if there is one, and stores the line in the array pointed to by
 *  str. If the next line of input is longer than count characters, this reads
 *  and stores the next count characters from stream. In either case, str ends
 *  with '\0'.
 *
 * If stream is at EOF when the function begins, returns NULL and leaves str
 *  unchanged.
 *
 * @param str the array in which to store the characters
 * @param count the maximum number of meaningful characters to store in str
 * @param stream the file from which to read
 * @does read the next line of input from stream, discarding the trailing
 *  newline character if there is one, and store those characters in str.
 * @return str, or NULL if stream is at EOF when the function begins
 * @assumes str points to enough memory to hold count+1 chars
 * @assumes stream is open and readable
 */
char *freadln(char *restrict str, int count, FILE *restrict stream);
