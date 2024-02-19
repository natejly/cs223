# Pset 2: Ahoy Matey!

## AKA Hookbook A

### OPTIONAL ASSIGNMENT

Ahoy, matey!
This exercise will get you started programming Hookbook.
In this assignment, you will be practicing **file I/O operations**, **structs**, **dynamic memory allocation**, **array lists**, **sorting**, and **software engineering** in C.

## The Assignment
Hookbook is a hot new social media platform built for pirates, by pirates (bulldogs are kind of piratey, right?).
To create Hookbook, you'll load a bunch of pirates from a file and add them to a list that you've created.
For this assignment, the only information about each pirate that you will be given is their name. 

However, your swashbuckling clientele is in the process of creating profiles for themselves that they will give you in a separate document.
This means that your Hookbook program must easily transform to accept a list of pirates that includes all kinds of additional information about them, including:
* Their current vessel of employ
* Their current captain (who is another pirate!)
* The number of treasures they've found
* Their favorite port of call
* All of the pirating skills they possess

After the list of pirates is loaded by your program, your job will be to display each pirate's profile in sorted order.

### Parallel Assignment: Hookbook B

This assignment has a companion, Hookbook B.
Hookbook B has been assigned concurrently with Hookbook A, but it is not optional and is due on Friday, Feb 23.
The Hookbook B assignment is somewhat more sophisticated than Hookbook A, and the functionality of Hookbook B is a superset of the required functionality of Hookbook A.
That means you have two options for completing these assignments:

1. Implement Hookbook A, and then implement Hookbook B
2. Implement Hookbook B, and then modify your driver to handle Hookbook A's requirements

Historically, when completed sequentially and separately, Hookbook A and Hookbook B take a similar amount of time on average.
You might find it easier to jump straight to the more complicated Hookbook B and then "backtrack" from that solution to accommodate the reduced Hookbook A functionality.
Or, you might want to tackle the assignments sequentially, given you know exactly where you need to go from your solution to Hookbook A to complete Hookbook B.

> **Note**: Hookbook A is an **optional** assignment.
> We strongly encourage you to complete it because it is a great place to start your solution to Hookbook B, which is a required assignment.
> There will be test cases made available on Gradescope for *both* Hookbook A and Hookbook B, and due to its optional nature, a more complete public test suite will be available for Hookbook A.

### To summarize

For Hookbook A, your program must:
1. Load a list of pirate names from a file whose name is given to you as a command-line argument
1. Add those pirates into a list, and sort that list in lexicographical order
1. Display the profiles of the pirates, sorted lexicographically
2. All of the above steps must be taken with the fact in mind that separate requirements increase the information you will hold about each pirate.

The companion assignment, Hookbook B, is designed to be completed either in parallel with Hookbook A or sequentially following it.

### Background: The `const` Type Qualifier

The [`const` type qualifier](https://en.cppreference.com/w/c/language/const) in C identifies to the compiler that the object's value may not be changed.
This has several implications, not all of which are straightforward.

For non-pointer variables, qualifying their type with `const` makes it impossible to modify their value.
Directly attempting to modify the value of a variable with `const`-qualified type results in a compiler error; *indirect* modification attempts are undefined behavior.

In C, it is possible to explicitly cast a `const`-qualified object to a non-`const` object: this is a bad idea.
Going the other way&mdash;casting a non-`const` object to `const`&mdash;is **implicit** and always safe.

For pointer types, the `const` qualifier refers to the object the pointer refers to, rather than the pointer itself.
Because of this, you should avoid allocating `const`-qualified memory.
Remember, `malloc` allocates memory but does not initialize it&mdash;as you can see below, it is an error to modify that memory if the pointer variable is `const`, thus rendering that memory essentially useless!
Further, the `free` function expects a non-`const` pointer as its argument&mdash;you cannot free `const` memory!

A pointer to `const` should instead be initialized by *assigning* it to another (already-initialized) object.
The restricts modification of the object only via access by the `const`-qualified pointer; the object can still be modified through access from the other (non-`const`) pointer.
Most commonly, this happens when functions are declared with parameters having `const`-qualified types.
Remember: in C, parameter passing to a function is nearly indistinguishable from assignment.

To declare a pointer variable *itself* as `const` (e.g., to force it always to point to the same address in memory), the `const` keyword should appear *after* the `*` pointer specifier.
This is (perhaps surprisingly) an uncommon thing to do, particularly for the kinds of programs we wil be writing in this course.

See an example of several `const` and non-`const` variables below.
Play around with it in `const_demo.c` in the starter code.
(Yes, there are memory leaks in this example program.)

```C
int main(void)
{
    int x = 0;
    const int y = 0;
    int *p = (int*)&y;

    x = 42;  // OK: x is not const
    y = 42;  // ERROR: y is const
    *p = 42; // Undefined behavior

    int *a = malloc(sizeof(int));
    const int *b = malloc(sizeof(int));
    int *const c = malloc(sizeof(int));
    const int *const d = malloc(sizeof(int));

    *a = 42; // OK: a is not const
    *b = 42; // ERROR: *b is const
    b = a;   // OK: b is not const; implicit cast of *a (non-const to const)
    *c = 42; // OK: *c is not const
    c = b;   // ERROR: c is const
    *d = 42; // ERROR: *d is const
    d = a;   // ERROR: d is const
}
```

Variables with `const`-qualified type declarations are not necessarily constants in the same sense as constants defined by preprocessor `#define` directives.
Whenever a value is required to be named as a constant in this document (and in this course, broadly speaking), you should use a `#define` directive unless specifically instructed otherwise in the document.

### Background: The `restrict` Type Qualifier

Some of the functions you implement have parameters declared with the [`restrict` type qualifier](https://en.cppreference.com/w/c/language/restrict).
This type qualifier is a hint o the compiler that for the life of this pointer, no other pointers will access the memory it is associated with.
For this assignment, **there is nothing in particular you should do** to handle `restrict`-qualified pointers.
It is needed to make the C++/C interoperability happy when we compile unit tests for your submission.

## Files you are given

Files are reproduced here for your convenience.
If there are any differences in these files and those in the starter code, defer to the version in the starter code.

* `pirate.h` (Interface), with the following (partial) type definition.
    You may optionally complete the task marked by `TODO` (it's required for Hookbook B).
    **You may not change anything else already in this file**, however you may add functions or other definitions to it if you like.
    ```C
    /**
     * Type of a pirate, as a (non-opaque) struct
     */
    typedef struct pirate_t pirate;
    struct pirate_t
    {
        char *name;
        // TODO: Expand this type definition (optional in Hookbook A)
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
    ```

    > **Note**: The `pirate_t` struct includes a declaration of a single field, `char *name`.
    > This must remain in your submission unchanged because the unit tests rely on the presence of a field with this name and type.
    > The remainder of the `pirate_t` type definition is up to you.

    > **Note**: The `pirate` interface for Hookbook A defines a strict subset of the behavior of the `pirate` interface for Hookbook B.
    > Therefore, you could implement only the Hookbook B version of the interface and use it for *both* Hookbook assignments!

* `pirate_list.h` (Interface), with the following declarations.
    **You may not change anything already in this file**, however you may add functions or other definitions to it if you like.

    ```C
    /**
    * Type of a list of pirates, as an opaque struct.
    */
    typedef struct pirate_list_instance_t pirate_list;

    /**
    * Allocate memory for a new pirate_list and return a pointer to it.
    *
    * @return a pointer to a newly-created pirate list
    */
    pirate_list *list_create();

    /**
    * Return the index in pirates of the pirate with the name, or a value greater
    *  than or equal to the length of the list if the there is no such pirate.
    *
    * @param pirates the list to search
    * @param name the name to search for
    * @return the index of the pirate with name, or a value greater than or equal
    *  to the length of the list if the there is no such pirate.
    * @assumes neither pirates nor p are NULL
    */
    size_t list_index_of(const pirate_list *pirates, const char *name);

    /**
    * Only if there is no pirate in the list with the same name as p, insert
    *  pirate p into the list at index idx by copying the pointer, shifting the
    *  latter part of the list one "slot" to the right.
    *
    * If idx >= [length of pirates], then this function appends p to the end of
    *  the list.
    *
    * If there is a pirate in the list with the same name as p, do nothing, and
    *  return p (the pirate that was not inserted).
    *
    * If the pirate was inserted into the list, return NULL.
    *
    * If p is added to the list, the list claims ownership of the pirate pointed
    *  to by p; otherwise ownership remains with p.
    *
    * @param pirates the list in which to insert p
    * @param p the pirate to insert
    * @param idx the index at which to insert p
    * @return NULL or p, depending on whether p was successfully inserted
    * @assumes neither pirates nor p are NULL, and that p has a name
    */
    const pirate *list_insert(pirate_list *pirates, const pirate *p, size_t idx);

    /**
    * Remove the pirate from the list with name, and return a pointer to it.
    *
    * If name is NULL or there is no pirate in the list with name, return NULL.
    *
    * If this function does not return NULL, then the caller owns the returned
    *  pirate.
    *
    * @param pirates the list from which to remove a pirate
    * @param name the name of the pirate to remove
    * @return the removed pirate, or NULL if there is no matching pirate in the
    *  list
    * @assumes pirates is not NULL
    * @assumes every pirate in pirates has a name that is unique in the list
    */
    pirate *list_remove(pirate_list *pirates, const char *name);

    /**
    * Return a pointer to the pirate pointed to by index idx in the list, or NULL
    *  if idx is not a valid index (i.e., it is >= the length of the list).
    *
    * Ownership of the returned pirate remains with the list.
    *
    * @param pirates the list to access
    * @param idx the index to access of the list
    * @return a pointer to the pirate at index idx of pirates, or NULL
    * @assumes pirates is not NULL
    */
    const pirate *list_access(const pirate_list *pirates, size_t idx);

    /**
    * Sort the list of pirates in lexicographical order by name.
    *
    * @param pirates the list to sort
    * @does sorts the list of pirates in lexicographical order by name
    * @assumes pirates is not NULL and every pirate in the list has a name that is
    *  unique in the list
    */
    void list_sort(pirate_list *pirates);

    /**
    * Return the number of pirates in the list.
    *
    * @param pirates the list
    * @return the number of pirates in pirates
    * @assumes pirates is not NULL
    */
    size_t list_length(const pirate_list *pirates);

    /**
    * Free all memory owned by the list, including the pirates in the list.
    *
    * @param pirates the list to destroy
    */
    void list_destroy(pirate_list *pirates);
    ```

    > **Note**: The `pirate_list` interface for Hookbook A defines a strict subset of the behavior of the `pirate_list` interface for Hookbook B.
    > Therefore, you could implement only the Hookbook B version of the interface and use it for *both* Hookbook assignments!

* `libhookbook.h` (Interface) which contains the following definitions.
    **You may not change anything already in this file**, however you may add functions or other definitions to it if you like.
    ```C
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
    char *freadln(char *str, int count, FILE *stream);
    ```
* `makefile` (Incomplete)
    * The provided makefile defines two variables, `CC` and `CFLAGS`.
        You must submit a makefile having identical values for those two variables:
        ```
        CC = gcc
        CFLAGS = -std=c17 -Wall -pedantic -g
        ```
    * The first target, `Hookbook`, is incomplete and you must complete it, however, you must not change its name, and it must generate an executable file named "`Hookbook`".
    * The last target, `clean`, is complete and you should not change it.
    * The rest of `makefile` is up to you, except that the first target in the file must remain `Hookbook` and the last target must remain `clean`.

## Files you must complete

The starter code contains stubs/skeletons for the following files.

* `hookbooka.c` (Driver)
    * This will be the file where your `main` function is going to be.
        Your `main` function must:
        1. Take as the only command-line argument the path to a file containing the pirates' names to be placed into your Hookbook.
        2. Open that file and read from it the list of pirate names, appearing one on every other line, storing them in a `pirate_list*`
        3. Sort the list in [lexicographic](https://en.wikipedia.org/wiki/Lexicographic_order) order by pirate name
        4. Print the sorted list to `stdout`, conforming to the format described below in [Output Format](#output-format)
        5. Release all resources (files, memory, _etc._)
* `pirate.c` (Implementation), containing a definition for every declaration or prototype in `pirate.h`
* `pirate_list.c` (Implementation), containing a body for every function prototype in `pirate_list.h`, and a definition for `struct pirate_list_instance_t`
    * `pirate_list` must be implemented as an **array list**, _a.k.a._ **resizing array**
    * The initial capacity of the list must be defined as a constant named `INITIAL_CAPACITY`, having value `25`
    * The capacity of the list must never fall below `INITIAL_CAPACITY`
    * When the array capacity changes, it must change by a *factor* of `2`, which must be the value of a constant named `RESIZE_FACTOR`
    * Your array list implementation must avoid the oscillation problem discussed in class
    * In addition to functions declared in `pirate_list.h`, `pirate_list.c` must contain a declaration and implementation for each of the following two "helper" functions that are not declared in the header file:
        ```C
        /**
         * Check if the actual number of pirates in the array is "too large"; if it is,
         *  increase the capacity of the array by a factor of RESIZE_FACTOR.
         *
         * Given N actual pirates in the array of capacity C, we say N is "too large"
         *  whenever N >= C
         *
         * If the array capacity was changed, print to stderr the string "Expand to ",
         *  followed by the new capacity of the list and a newline. Here is a possible
         *  print statement:
         *
         *     fprintf(stderr, "Expand to %zu\n", new_capacity);
         *
         * If the capacity was not changed, print nothing.
         *
         * @param pirates the pirate list to expand, if necessary
         * @does increases the capacity of the array if there are too many pirates in
         *  it
         * @assumes the pirate list is in the process of having a pirate added to it.
         */
        void list_expand_if_necessary(pirate_list *pirates);

        /**
         * Check if the actual number of pirates in the array is "too small"; if it is,
         *  decrease the capacity of the array by a factor of RESIZE_FACTOR.
         *
         * Given N actual pirates in the array of capacity C, we say N is "too small"
         *  whenever C > INITIAL_CAPACITY and N * RESIZE_FACTOR <= C / RESIZE_FACTOR
         *
         * If the array capacity was changed, print to stderr the string "Contract to "
         *  followed by the new capacity of the list. Here is a possible print
         *  statement:
         *
         *     fprintf(stderr, Contract to %zu\n, new_capacity);
         *
         * If the capacity was not changed, print nothing.
         *
         * The capacity of the array must never fall below INITIAL_CAPACITY!
         *
         * @param pirates the pirate list to contract, if necessary
         * @does decreases the capacity of the array if there are too few pirates in
         *  it.
         * @assumes the pirate list is in the process of having a pirate removed from
         *  it.
         */
        void list_contract_if_necessary(pirate_list *pirates);
        ```
* `libhookbook.c` (Implementation), containing a definition for every declaration or prototype in `libhookbook.h`

## Other requirements

* You may add to `pirate.h` as you wish but there _must_ remain a declaration of a type named `pirate` and definitions for `pirate_create`, `pirate_read`, `pirate_print`, `pirate_name`, `pirate_compare`, and `pirate_destroy` with the above signatures.
    This includes declaring additional functions in that file or making the `struct` an **opaque struct**.
* Each header and source file must use `#include` directives to include headers that are _directly_ used by that file&mdash;**no more, no less**. Points will be deducted for clearly extraneous `#include` directives or definitions that rely on transitive inclusions except between an implementation file and its corresponding header.
* You may not use the standard library's `qsort` function to sort anything, nor any other pre-implemented sorting function. You **must** implement every sorting algorithm that you use on your own
    * Sorting a `pirate_list` must take $O(n \log n)$ time and $O(\log n)$ additional memory

    > **Note**: Think back to the sorting algorithms we discussed in class recently&mdash;which of them conform to these requirements? Which of them do not?

* You must create _exactly one_ pirate for each name in the input file&mdash;you may not create copies of pirates (copies of _pointers_ to pirates is OK).
  * In other words, your program must use $O(n)$ memory for an input file with $n$ pirates
* It is possible that you will not use every function you implemented...but you still must implement every function identified in this README! We will run **unit tests** on your program, meaning we will test&mdash;in isolation&mdash;each of the functions identified in this document. For example, you can efficiently implement a solution to this assignment without using the `list_remove` function, although we will run test cases that call `list_remove` on contrived input values and check that your implementation of that function conforms to its specification.
* Respond to the weekly surveys, with at least the following information
  * Your full name and netID
  * Your estimate of the time required to complete this assignment, selected *before* you start writing any code.
  * The total time you *actually* spent on the assignment
  * The names of all others (but not members of the teaching staff) with whom you discussed the assignment for more than 10 minutes
  * A brief discussion (~100 words) of the major conceptual and coding difficulties that you encountered in developing and debugging the program (and there will always be some)

### Memory Management

Now that you're managing memory yourself, we will test your submission with `valgrind`, a tool to help identify memory leaks.
When run on valid input, **for full credit, your submission must produce a valgrind report with no memory leaks, no errors, and no warnings**.

> **Note**: Valgrind is not available for the most recent several generations of Apple computers, and its support on modern Windows computers is iffy.
> It is however available, stable, and configured for use on the Zoo.
> This is yet another reason it is important to run your programs on the Zoo before submitting them (an easy way to make sure you do this is to develop them entirely on the Zoo).

## Suggestions and Notes

* In class, we implemented a naive array list to which you could append and remove `int`s from just one end. Use that to jump start your implementation of `pirate_list`.
* Factor out the functionality of `main` into several well-named, easily-understood functions.
* To help manage `#include` directives, draw a "map" of your project's files, with arrows marking *direct* dependencies, and use that to write your include directives
* `NULL` is a special pointer value that means "points to nothing". Attempting to dereference `NULL` will probably result in a segmentation fault, which your program must avoid, although it is technically undefined behavior (which your program also must avoid).
* If you find yourself struggling to accomplish a task in the course of your development, break that task down into smaller steps&mdash;chances are you'll know how to do some of the smaller steps!&mdash;and keep breaking it down into smaller and smaller steps that you know how to tackle. Then, compose those smaller steps into a function that solves your original problem.
  * Do not use ChatGPT or CoPilot for help. Generative AI is not permitted as a tool in this course.

## Input Format

You will receive pirate information in the form of a regular text file organized as follows (which is the same between this assignment and the parallel one).

> **Note**: For this assignment (only), pirate profiles will not have any additional information associated with them; that is, the input for this assignment will contain only pirate names, each separated from one another by an empty line.

* The first line of the file is the name of a pirate, which may be empty
* The following consecutive non-empty lines hold pirate information, each of which is labeled with the kind of information it provides. Each line is one of the following:
  * "`r:[rank-name]`", where `[rank-name]` is the name of this pirate's rank on their vessel, such as "captain", "first mate", or "sailor"
  * "`v:[vessel-name]`", where `[vessel-name]` is the name of this pirate's current vessel of employ
  * "`p:[port-name]`", where `[port-name]` is the name of this pirate's favorite port of call
  * "`t:[treasure-amount]`", where `[treasure-amount]` is a nonnegative integer that counts the number of treasure pieces this pirate owns
  * "`s:[skill-name]`" where `[skill-name]` is a skill that a pirate might possess, such as "swashbuckling", "treasure hunting", or "navigating"
* Each pirate profile in the input is followed by *exactly* one empty line (the last profile in the file is followed by a *single* newline character; the last empty line of the file is terminated by the end of the file, not a second newline)

There are some features of the input that are important:

* The pirate's name will be on the first line of their profile, but the rest of the profile information can appear in any order, or may not be present at all
* There may be several pirates with the same name. In this case, only the *first* pirate with a given name should be persisted. Put another way, *in the generated `pirate_list`, every pirate should have a unique name*.
* There may be lines with repeated labels, even within a profile. Except in the case of repeated skills, only the *last* occurrence of a label in a profile should be persisted. Repeated skills should *all* be persisted, with duplicate skills interpreted as increased proficiency by the pirate.
* Not every pirate profile will contain a line for every piece of information; your method of storing pirate information must account for this possibility.

## Output Format

The output from your program must be a list of pirate names, sorted in increasing lexicographic order.
Each profile must begin with the pirate's name, which must be followed for a line identifying each additional piece of information you have available for this pirate.

> **Note**: To reiterate, in this assignment, you will have no additional information, so the output will just be a list of names.

Additional pieces of information must appear each on their own line, indented by **4** spaces and beginning with the kind of information displayed ("Captain", "Rank", "Vessel", *etc.*) followed by a colon and a space (`": "`).
In the case of a pirate with multiple skills, the label "Skills" should appear only once, with each *unique* skill on its own line, indented by **12** spaces (the first skill must appear on the same line as the "Skills" label).
Skills must be sorted in ascending lexicographic order of their name, and skills must be followed on their line by a number of asterisks (`'*'`) equal to that skill's "rating" for the pirate (*i.e.*, the number of times that skill appeared in the pirate's profile in the input) minus 1.

### Examples

Here are several example runs of the program showing the output both to `stdout` and to `stderr`.

1. File with three pirates
    > File: `A_list.txt`
    > ```text
    > jack sparrow
    >
    > william turner
    >     
    > elizabeth swan
    > ```

    > Command and output:
    > ```text
    > $ ./Hookbook A_list.txt
    > elizabeth swan
    > jack sparrow
    > william turner
    > ```

2. File with 30 pirates
    > File: `B_list.txt`
    > ```text
    > captain mansel alcantra
    >
    > john alexander
    >
    > algerine pirates
    >
    > ali basha
    >
    > captain alleston
    >
    > alwilda
    >
    > alexander ammand
    >
    > ibrahim ameer
    >
    > captain cornelius anderson
    >
    > captain androeas
    >
    > sultan of timor angora
    >
    > angria
    >
    > captain thomas anstis
    >
    > antonio
    >
    > john rose archer
    >
    > james austin
    >
    > captain john avery
    >
    > captain bridgeman
    >
    > captain aylett
    >
    > job baily
    >
    > captain baker
    >
    > roger ball
    >
    > john ballet
    >
    > captain baltizar
    >
    > captain bannister
    >
    > barbarosa
    >
    > redbeard
    >
    > captain nicholas barbe
    >
    > captain barnard
    >
    > captain barnes
    > ```
    

    > Command and output (note the line reading, "Expand to 50"!):
    > ```text
    > $ ./Hookbook B_list.txt
    > Expand to 50
    > alexander ammand
    > algerine pirates
    > ali basha
    > alwilda
    > angria
    > antonio
    > barbarosa
    > captain alleston
    > captain androeas
    > captain aylett
    > captain baker
    > captain baltizar
    > captain bannister
    > captain barnard
    > captain barnes
    > captain bridgeman
    > captain cornelius anderson
    > captain john avery
    > captain mansel alcantra
    > captain nicholas barbe
    > captain thomas anstis
    > ibrahim ameer
    > james austin
    > job baily
    > john alexander
    > john ballet
    > john rose archer
    > redbeard
    > roger ball
    > sultan of timor angora
    > ```

## Assumptions

You may assume the following about the command-line arguments to the program:

* **Nothing!** 
    We will run your program with no command-line arguments, many command-line arguments, and a single command-line argument that is the name of a file that does not exist.
    In all cases where the first command-line argument is *not* the name of file from which you can read, your program must exit with status code `1` and not cause any errors such as segmentation faults.
    If there are many command-line arguments provided, your program should attempt to interpret the first one as the name of the input file.

You may assume the following about the file referred to by the command-line argument, if you can open it for reading:

* It is a text file. That is, we will not try to open a binary file, _e.g._, an image
* It conforms to the [input specification](#input-format) above
* No line in the file will be longer than 127 characters
* No line in the file will contain any non-ASCII characters
* No pirate profile information will be provided in the input file besides pirate names

Assumptions for individual functions are listed in their specifications.
No unit test will violate those assumptions (the behavior of that function is&mdash;by definition&mdash;undefined if the assumption is violated).

## Testing

This is an optional assignment, so you will not receive a grade for it.
However, as mentioned above we strongly encourage you to complete this assignment anyway, particularly if you are unsure where to start on Hookbook B.

There will be an automated test suite available to you on Gradescope with which you can assess your code's correctness.
The "autograder" (it's not a *grader*, per se) will perform three kinds of tests on your code:

* Compilation tests
* Diff tests
* Unit tests
* Performance tests

We will first ensure your program compiles without errors or warnings using the `makefile` that you submit.
We will compile several versions of your executable, each with a different grid size, running `make clean` in between each.

Next, we will run the compiled `Hookbook` executables on several test cases and check its output using the `diff` tool available on Unix systems including the Zoo and Gradescope.
For each diff test, you will pass if there are **no differences** between the expected output and your program's actual output.
If there are any differences between the two for a given test case, you will not pass that test case.

We will also run **unit tests** on your code.
These unit tests will exercise the required functions that you have implemented, in isolation from one another, to assess that each individual function is correct relative to its specification.

Here is a possible unit test for `list_remove` (note: this test case *does not* test `pirate_destroy` or `list_destroy`, as the the assertions are made before those functions are called; nor does it test the functionality of `pirate_create`, `list_length`, or `list_insert`&mdash;rather, it *assumes* those functions are correctly implemented):

```C
void test_remove_1()
{
    pirate_list* p = list_create();
    pirate* r = pirate_create("Foo");
    list_insert(p, r, 0);
    pirate* r2 = list_remove(p, r);
    if (list_length(p) == 0 && r2 != NULL && strcmp(r2->name, "Foo") == 0)
    {
        printf("test_remove_1 passed!\n");
    }
    else
    {
        printf("test_remove_1 failed!\n");
    }
    pirate_destroy(r2);
    list_destroy(p);
}
```

It could be called by a `main` function that does nothing but calls a bunch of similar unit test functions.

Finally, your code will be run with `valgrind` on a variety of inputs, and you will pass those test cases if and only if valgrind reports no memory leaks and no memory errors.

### Public vs. Private Test Cases

As this is an optional assignment, the public testing suite will be quite extensive, and there will be no private test cases.

The output of passed test cases may not be easy to decipher because of how we had to name our test cases in the unit testing framework we are using.
Ask a staff member if you're really curious about what a particular test case does (Alan wrote the script so if the person you ask first doesn't know, ask him).
For failed test cases, however, the output should be somewhat more enlightening because it will display a message to you describing the test case along with the assertion that was violated and caused the failure.

## Weekly Survey

Each week, you will be asked to fill out a survey asking for at least the following information:

* Your full name and netID
* Your estimate of the time required to complete this assignment, selected *before* you start writing any code.
* The total time you *actually* spent on the assignment
* The names of all others (but not members of the teaching staff) with whom you discussed the assignment for more than 10 minutes
* A brief discussion (~100 words) of the major conceptual and coding difficulties that you encountered in developing and debugging the program (and there will always be some)

In total, the weekly surveys are worth 5% of your overall grade for the course.
(They are not optional.)

## Submission

Submit your project to Gradescope by uploading all files needed to run your program.
It is due **11:59 PM NHT on Friday, February 23, 2024**.

You must submit the following files:

* `makefile`
* `hookbook.c`
* `pirate.h`
* `pirate.c`
* `pirate_list.h`
* `pirate_list.c`
* `libhookbook.h`
* `libhookbook.c`
* Any other files needed to compile and run your program.

Although this is an optional assignment, unless you are given express permission otherwise (e.g., during a lab section with Prof. Erat) **you may not collaborate on this assignment except in the manner allowed by the Syllabus.**

Submission for the assignment will close at the end of the 72-hour late submission window after the deadline, although of course no late penalties will be applied.
