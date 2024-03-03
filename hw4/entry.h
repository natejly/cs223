#ifndef __ENTRY_H__
#define __ENTRY_H__

#include <stdio.h>

typedef struct entry
{
  char *id;
  int *distribution;
} entry;

/**
 * Reads a Blotto entry from the given source.  The entry should
 * be in the format
 *
 * id,x0,x1,x2,...,xn
 *
 * where id is a string of no more that max_id characters not
 * containing newlines or command, each xi is a non-negative decimal
 * integer, and n = battlefields - 1.  Both the id and distribution
 * returned in the entry struct are dynamically allocated and it is
 * the caller's responsibility to destroy them by passing the entry to
 * entry_destroy.  End-of-input (a blank line or EOF) is signalled by
 * returning {"", undefined} and other errors are signalled by
 * returning {NULL, NULL}.
 *
 * @param in a file, non-NULL
 * @param max_id, a positive integer
 * @param battlefields a positive integer
 */
entry entry_read(FILE *in, int max_id, int battlefields);

/**
 * Frees the id and distribution in the given entry.
 *
 * @param e a pointer to an entry, non-NULL
 */
void entry_destroy(entry *e);

#endif
