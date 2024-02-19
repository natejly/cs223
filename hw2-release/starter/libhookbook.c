/**
 * Implementation file for libhookbook.h
 *
 * For Hookbook A in CPSC 223 SP2024.
 *
 * Author: [your name here]
 */

#include "libhookbook.h"

char *freadln(char *str, int count, FILE *stream)
{
    size_t i = 0;
    char c = fgetc(stream);
    // skips whitespaces

    if (c == EOF)   
    {
        return NULL;
    }
    while (c != '\n' && c != EOF && i < count)
    {
        str[i] = c;
        i++;
        c = fgetc(stream);
    }
    str[i] = '\0';
    return str;
}
