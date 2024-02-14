#pragma once

#include <stdio.h>

/**
 * Header file for pirate for HookBook A in CPSC 223 SP2024.
 *
 * Author: Alan Weide
 *
 * TO STUDENT: You may add to this file, but do not change anything that is
 *     already here!
 * Modified by: [your name here] on [date of modification]
 * Changelog: [what you added to this file]
 */

/**
 * Type of a pirate, as a (non-opaque) struct
 */
typedef struct pirate_t pirate;
struct pirate_t
{
    char *name;
    // TODO: Extend this struct (optional for Hookbook A)
};

/**
 * Allocates enough memory for a pirate, and sets the pirate's name to name.
 * Ownership of the name pointer is transferred to the pirate. Returns a
 *  pointer to the newly-allocated pirate.
 *
 * @return a pointer to a new pirate with given name
 */
pirate *pirate_create(char *name);

/**
 * Reads a pirate profile from input. Assumes that the input cursor is at the
 *  beginning of a pirate profile (otherwise, the behavior is undefined).
 *
 * Returns a pointer to a pirate created from the profile in input.
 *
 * This function consumes the blank line after the end of the current profile
 *  before returning (that is, the first newline character and the second, if
 *  there is one, or the EOF marker if not), meaning that after this function
 *  is done, the input cursor is either at the end of the input file or at the
 *  beginning of the next pirate profile.
 *
 * @param input the stream from which to read a pirate profile
 * @returns a new pirate based on the contents of input
 * @assumes input is an open and readable stream
 * @assumes the next character in input is the first character of a pirate's
 *  profile, and that input is well-formed according to the input specification
 *  in the README.
 */
pirate *pirate_read(FILE *restrict input);

/**
 * Prints a pirate's profile to output in conformance with the output
 *  specification in the README.
 *
 * @param p the pirate to print
 * @param output the stream to which the pirate's profile should be printed
 * @does prints p's profile to output
 * @assumes p is not NULL
 * @assumes output is an open, writable stream
 */
void pirate_print(const pirate *p, FILE *restrict output);

/**
 * Compares two pirates, returning a negative number, zero, or a positive
 *  number as pirate a "comes before", is equal to, or "comes after" pirate b.
 * For this function, we say a "comes before" b if the name of pirate a is
 *  lexicographically less than the name of pirate b, and that they are equal
 *  if they have the same name.
 *
 * A pirate with no name always comes after a pirate with a name. No order is
 *  defined between two pirates with no name.
 *
 * @param a the first pirate
 * @param b the second pirate
 * @return a negative number, zero, or a positive number as a "comes before",
 *  is equal to, or "comes after" b according to their names
 * @assumes neither a nor b are NULL
 */
int pirate_compare_name(const pirate *a, const pirate *b);

/**
 * Frees all memory owned by p. This function claims ownership of p.
 *
 * @param p the pirate to destroy
 * @does frees all memory owned by p
 * @assumes p is not NULL
 */
void pirate_destroy(pirate *p);
