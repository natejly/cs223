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
    char c;
    //skips whitespaces
    while ((c = fgetc(stream)) != EOF && c == '\n')
    {
    }
    if (c == EOF)
    {
        return NULL;
    }
    while(c != '\n' && c != EOF)
    {
        if (i < count - 1)
        {
            str[i] = c;
            i++;
        }
        c = fgetc(stream);
    }
    str[i] = '\0';
    return str;
}
