#include <stdlib.h>

int main(void)
{
    int x = 0;
    const int y = 0;
    int *p = (int *)&y;

    x = 42;  // OK: x is not const
    y = 42;  // ERROR: y is const
    *p = 42; // Undefined behavior

    int *a = malloc(sizeof(int));
    const int *b = malloc(sizeof(int));
    int *const c = malloc(sizeof(int));
    const int *const d = malloc(sizeof(int));

    *a = 42; // OK: a is not const
    *b = 42; // ERROR: *b is const
    b = a;   // OK: b is not const
    *c = 42; // OK: *c is not const
    c = b;   // ERROR: c is const
    *d = 42; // ERROR: *d is const
    d = a;   // ERROR: d is const
}
