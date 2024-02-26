/**
 * Implementation file for libhookbook.h
 *
 * For Hookbook B in CPSC 223 SP2024.
 *
 * Author: Nate Ly
 */

#include "libhookbook.h"

char *freadln(char *restrict str, int count, FILE *restrict stream)
{
    // set index to 0
    size_t i = 0;
    // get the next character from the stream
    int c = fgetc(stream);
    // if the stream is at EOF, return NULL
    if (c == EOF)
    {
        return NULL;
    }
    // while the character is not a newline or EOF and the index is less than the max
    while (c != '\n' && c != EOF && i < count)
    {
        // store the character in the string and increment the index
        str[i] = c;
        i++;
        c = fgetc(stream);
    }
    // add a null terminator to the end of the string
    str[i] = '\0';
    return str;
}
