# CPSC 223 SPRING 2024 PSET 1: Game of Life

## Due Friday, Feb 2, 2024 at 11:59 PM NHT (New Haven Time)

## Submission Checklist 

Your final submission must have (exactly) the following files:

* `constants.h`
* `helpers.c`
* `helpers.h`
* `life.c`
* `life.h`
* `main.c`
* `makefile`

When you submit these files, submit them indvidually to Gradescope.

## Background

Read this entire document carefully before you begin writing any code!

In this assignment, you will design and write a C program to simulate [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).
The basic idea of the Game of Life is that cells in a grid are used to simulate biological cells.
Each cell is either `ALIVE` or `DEAD`.
At each step of the simulation, each cell’s current status and its number of living neighbors are used to determine the status of the cell for the next step of the simulation.

The Game of Life is set up as a two-dimensional $N \times M$ grid with cells indexed `[0][0]` through `[N-1][M-1]`.
Your grid will be stored in a **statically-allocated array**.
Each cell `[i][j]` is adjacent to cells `[i-1][j-1]`, `[i-1][j]`, `[i-1][j+1]`, `[i][j-1]`, `[i][j+1]`, `[i+1][j-1]`, `[i+1][j]`, and `[i+1][j+1]`.
Cells at the edge of the grid do not wrap around!
For example, cells in the corners have only 3 neighbors (for `[0][0]`, the adjacent cells are `[0][1]`, `[1][0]`, and `[1][1]`).
At each step of the simulation, the cell values at that step determine what changes will occur at the next timestep as follows:

1. Any alive cell with fewer than two live neighbors dies
2. Any alive cell with two or three live neighbors stays alive
3. Any alive cell with more than three live neighbors dies
4. Any dead cell with exactly three live neighbors becomes alive

We'll use the following labels for cells in our grid(s):

```
 [0][0]   [0][1]   [0][2]       [0][M-1]
 [1][0]   [1][1]   [1][2]  ...  [1][M-1]
 [2][0]   [2][1]   [2][2]       [2][M-1]
  ...      ...      ...    ...    ...
[N-1][0] [N-1][1] [N-1][2]     [N-1][M-1]
```

Consider the state with $4 \times 4$ cells (for simplicity's sake, we'll let `0` represent a `DEAD` cell and `1` represent an `ALIVE` cell):

```
0 0 1 0
0 1 1 1
1 0 1 0
0 0 0 0
```

* Cell `[0][0]` is dead; it has one alive neighbor (`[1][1]`) so it **stays dead**. 
* Cell `[0][1]` is dead; it has three alive neightbors, so it **becomes alive** in the next time step
* Cell `[2][2]` is alive; it has three alive neighbors, so it **stays alive** in the next time step
* Cell `[0][3]` is dead; it has three alive neighbors so it **becomes alive** in the next time step
* Cell `[1][0]` is dead; it has two alive neighbors so it **stays dead** in the next time step
* Cell `[1][1]` is alive; it has four alive neighbors so it **dies** in the next time step
* Cell `[1][2]` is alive; it has four alive neighbors so it **dies** in the next time step
* Cell `[1][3]` is alive; it has three alive neighbors so it **stays alive** in the next time step
* Cell `[2][0]` is alive; it has one alive neighbor so it **dies** in the next time step
* Cell `[2][1]` is dead; it has four alive neighbors so it **stays dead** in the next time step
* Cell `[2][2]` is alive; it has three alive neighbors so it **stays alive** in the next time step
* Cell `[2][3]` is dead; it has three alive neighbors so it **becomes alive** in the next time step
* Cells `[3][0]` through `[3][3]` are all dead and have no more than two alive neighbors; they all **remain dead** in the next time step

So at the next step of the simulation, the state would be:

```
0 1 1 1
0 0 0 1
0 0 1 1
0 0 0 0
```

After another simulation step, then the state would be:

```
0 0 1 1
0 1 0 0
0 0 1 1
0 0 0 0
```

Work through this example by hand to make sure you understand the rules for cell modification.
 
## The Assignment 

You will submit `main.c` (which we'll call the "driver"), `life.h` ("interface"), `life.c` ("implementation"), `helpers.h` (interface), and `helpers.c` (implementation), and `makefile` for this assignment.

The point of this assignment is to build your understanding of statically-allocated memory, so **you may not use dynamic memory allocation anywhere in your program: that means you may not use `malloc` or `calloc`!**

### Starter Code

You are given the following files as starter code, all of which you must submit with your assignment.

* `constants.h`
* `helpers.c`
* `helpers.h`
* `life.c`
* `life.h`
* `main.c`
* `makefile`

This is a complete (though not correct) C project.
That is, it will compile without errors or warnings using the provided `Life` target in the supplied `makefile`.
Read on for details about each of the starter files.

The header files and `makefile` provided with the starter code should not be changed.
They are "ready-to-go", and the requirements sections below describe their contents.
If you change these files, you do so at your own risk as your submitted code must be compatible with the unit test program to earn full credit for this assignment.

### Requirements for `constants.h`

`constants.h` must contain constant definitions, in `#define` directives, for the following constants:

* `ROWS`, with value `4` (this corresponds to the constant $N$ above)
* `COLS`, with value `4` (this correspondes to the constant $M$ above)

Additionally, the values for `ROWS` and `COLS` must be able to be overriden at compile time.

> **Note**: The starter code contains a ready-to-go `constants.h` file, including permitting overriding of `ROWS` and `COLS`.
> You should not change this file, except perhaps to add more constants.
> Any constants that you add to `constants.h` must be *universal* constants, needed and shared by all files in the project.
> Constants that are used by only one file should be defined in that file.
> Examples of non-universal constants include `ALIVE` and `DEAD`, which are defined in `life.h`.

### Requirements for `life.h`

`life.h` must contain prototypes for at least the following two functions:

* ```C
  bool is_alive(int field[ROWS][COLS], size_t i, size_t j);
  ```
    The `is_alive` function takes as arguments a two-dimensional array of `int`s called `field` and indices `i` and `j`.
    It returns `true` if the cell at position `[i][j]` is alive, otherwise returns `false`.
    When implementing this function, you may assume that `i` and `j` are valid indices of `field`.
    > **Note**: Unlike in many languages, `bool`, `true` and `false` are not keywords in C, so you must `#include <stdbool.h>` to use them.

* ```C
  unsigned int num_living_neighbors(int field[ROWS][COLS], size_t i, size_t j);
  ```
    The `num_living_neighbors` function takes as arguments a two-dimensional array of `int`s called `field` and indices `i` and `j`.
    It returns the number of alive neighbor cells of `field[i][j]`.
    When implementing this function, you may assume that `i` and `j` are valid indices in `field`.

* ```C
  int get_next_state(int field[ROWS][COLS], size_t i, size_t j);
  ```
    The `get_next_state` function takes as arguments a two-dimensional array of `int`s called `field` and indices `i` and `j`.
    It returns the state of cell `field[i][j]` in the next time step according to the rules of the Game of Life.
    When implementing this function, you may assume that `i` and `j` are valid indices in `field` and that all cells in `field` have value either `ALIVE` or `DEAD`.
    > **Hint**: Accessing neighbors that don’t exist (*e.g.*, things at index `-1` or at an index equal to `ROWS` or `COLS`) will cause an error.
    > Check your indexes before using them! 

* ```C
  void compute_next_gen(int cur_field[ROWS][COLS], int next_field[ROWS][COLS]);
  ```
    The `compute_next_gen` function takes as arguments two 2-dimensional arrays: `cur_field` and `next_field`, each of which are of size `[ROWS][COLS]`.
    The function computes the state of the field at the next time step given the state described by `cur_field`, storing the next state in `next_field`.
    When implementing this function, you may assume that all cells in `cur_field` are either `ALIVE` or `DEAD`, and that the two fields have the same size, which is `ROWS` rows by `COLS` columns.

> **Note**: The starter code for this assignment includes a ready-to-go `life.h` header file.
> You may add to that file, but **do not change anything that is already there**.
> Our unit tests rely on these four functions being present with these precise prototypes.
> You will not receive any credit for unit tests if any function prototype is not compatible with the unit testing suite.

### Requirements for `life.c`

`life.c` must contain an implementation for each function prototype in `life.h`, and they must be correct according to the specification.

The starter code contains function stubs for the required functions in `life.c`, but you must provide correct bodies.

### Requirements for `helpers.h`

`helpers.h` must contain a prototype for at least the following functions:

* ```C
  void print_initial(int field[ROWS][COLS]);
  ```
    The `print_initial` function prints the field formatted for the initial state as described in this README document.
* ```C
  void print_generation(int field[ROWS][COLS], unsigned int gen);
  ```
    The `print_generation` function prints the field formatted for generation number `gen` according to the format described in this README document.

> **Note**: The starter code for this assingment includes a ready-to-go `helpers.h` header file.
> You may add to that file, but **do not change anything that is already there**.
> Our unit tests rely on these functions being present with these precise prototypes.
> You will not receive any credit for unit tests if any function prototype is not compatible with the unit testing suite.

### Requirements for `helpers.c`

`helpers.c` must contain an implementation for each function prototype in `helpers.h`, and they must be correct according to the specification.

> **Note**: The starter code for this assignment includes a ready-to-go `helpers.c` file.
> You should only change this file if you add function prototypes to the `helpers.h` header file, in which case you should provide bodies for those functions in `helpers.c`.

### Requirements for `main.c`

You should start with the provided `main.c` scaffolding file to ensure your macro definition and general program structure are appropriate.
You **may not** remove anything outside of the `main` function (but you may add to it).

Somewhere in your project, you must define two constants named `ROWS` and `COLS`, which must both have value `4`:

```C
#define ROWS 4
#define COLS 4
```

In the provided `constants.h` scaffolding file, these constants are already defined, and they are surrounded by a guard that permits us (and you!) to override their definition at the command line during compilation, which makes it relatively easy to test differing field sizes.
We will do this during grading with the following make command (we will vary `X` and `Y`; see the [section below](#requirements-for-makefile-or-makefile) for details):

```
$ make Life ROWS=X COLS=Y
```

For example, if `X` is `30` and `Y` is `50`, your program should accept and simulate Game of Life for a field of size $30 \times 50$.

> **Note**: **Do not change** the code surrounding the definition of `ROWS` and `COLS` in the starter code, and ensure the values of `ROWS` and `COLS` in your submission are both `4`.

`main.c` must contain a single function with the following signature:

```C
int main(int argc, char* argv[])
```

The `main` function should accept two command-line arguments, which will appear in the following order:

* `time_steps`: a positive integer describing how many "generations" the simulation will run for.

    > **Hint**: Use a low value *e.g.*, 1 or 2 as you write and test your code, and increase it after you confirm expected outputs for the lower values.
    > As part of grading your submission, we will test your program on arbitrarily large values of `time_steps` (within the range of type `int`).
* `init`: a string consisting of the characters `'0'` and `'1'`, of length `ROWS * COLS`, representing the initial state for this run of Game of Life. `init` must be interpreted by your program in row-major order; that is, the first `COLS` characters are the first row, the second `COLS` characters are the second row, and so on

Thereafter, your `main` function must create a new two-dimensional **statically-allocated array** of size `ROWS` by `COLS` (that is, you may *not* use `malloc` or `calloc`), and populate it with the values of the field described by `init`.
Using this array: 

* Print the initial values held in the array (they must match what was entered as the final command-line argument)
* Run the game `time_steps` times, printing the array at the end of each step (so it looks like the examples in the [sample runs](#sample-runs) below)

### Requirements for `makefile`

`makefile` must have a rule to generate an executable called `Life`, which when executed runs the `main` function implemented in `main.c`.
The name of the target must be "`Life`", and it must be the first target in the file.

There must also be a target named `clean` that removes all files created by the `Life` target (*i.e.*, object and executable files).
`clean` must be the last target in the file.

Your `makefile` must also accept two command-line variables named `ROWS` and `COLS` which, when given values during the make invocation, override the values of `ROWS` and `COLS` defined in `constants.h`.
Here is a possible `make` invocation that provides values for the `ROWS` and `COLS` variables, and the desired output starting from a clean project directory:
```
$ make Life ROWS=6 COLS=6
gcc -DROWS=6 -DCOLS=6 -std=c17 -Wall -pedantic -g   -c -o main.o main.c
gcc -DROWS=6 -DCOLS=6 -std=c17 -Wall -pedantic -g   -c -o life.o life.c
gcc -DROWS=6 -DCOLS=6 -std=c17 -Wall -pedantic -g   -c -o helpers.o helpers.c
gcc -DROWS=6 -DCOLS=6 -std=c17 -Wall -pedantic -g -o Life main.o life.o helpers.o
```

> **Note**: The starter code for this assignment includes a ready-to-go `makefile`, including conditionally-expanded `ROWS` and `COLS` variables.
> Study this file and read some of the GNU Make and GCC documentation to ensure you understand it.

## Output format

The first line of ouptut must begin with the string `"Initial values"`, which must be followed by the initial cell values, having each row a space-separated list of `'#'` for `ALIVE` cells and `' '` (a single space) for `DEAD` cells, beginning on column 4 of the following line.
Thereafter, each time step output must begin with the string `"Step k"` (for some value `k`, starting at $1$), which must be followed by the cell values at that timestep, having each row a space-separated list of `'#'` characters for `ALIVE` cells and `' '` (a single space) for `DEAD` cells, beginning on column 4 of the following line.

After the last step is printed, your program must print the string `"Done."` followed by a new line before exiting.

> **Note**: You may use the provided functions in `helpers.h` and `helpers.c` to aid in output formatting.
> We encourage you to study the implementations of the helper functions, because output scaffolding will decrease as the semester goes on and precise format specification adherence will remain important.

### Sample Runs 

To aid your testing, multiple sample runs are shown below.
Before you begin to write any code, it is crucial that you can replicate these by hand (given the initial values, carry out the next 2, 3, or more timesteps).

(Depending on your editor settings when you view this README document, trailing whitespace here may not match precisely what you see if you execute these commands yourself.
But the `#` characters are all in the correct place.)

#### Example A:

```
$ ./Life 2 0010011110100000
Initial Values
        #   
      # # # 
    #   #   
            
Step 1
      # # # 
          # 
        # # 
            
Step 2
        # # 
      #     
        # # 

Done.
```

#### Example B

```
$ ./Life 4 0100010001000000
Initial Values
      #     
      #     
      #     
            
Step 1
            
    # # #   
            
            
Step 2
      #     
      #     
      #     
            
Step 3
            
    # # #   
            
            
Step 4
      #     
      #     
      #     
            
Done.
```

#### Example C

```
$ ./Life 3 0000011001100000
Initial Values
            
      # #   
      # #   
            
Step 1
            
      # #   
      # #   
            
Step 2
            
      # #   
      # #   
            
Step 3
            
      # #   
      # #   
            
Done.
```

#### Example D

```
$ make clean Life ROWS=6 COLS=6
rm -f Life *.o
gcc -DROWS=6 -DCOLS=6 -std=c17 -Wall -pedantic -g   -c -o main.o main.c
gcc -DROWS=6 -DCOLS=6 -std=c17 -Wall -pedantic -g   -c -o life.o life.c
gcc -DROWS=6 -DCOLS=6 -std=c17 -Wall -pedantic -g   -c -o helpers.o helpers.c
gcc -DROWS=6 -DCOLS=6 -std=c17 -Wall -pedantic -g -o Life main.o life.o helpers.o
$ ./Life 6 000110001001100101000010101100010000
Initial Values
          # #   
        #     # 
    #     #   # 
            #   
    #   # #     
      #         
Step 1
          # #   
        #     # 
          #   # 
      # #   #   
      # # #     
      # #       
Step 2
          # #   
        #     # 
      #   #   # 
      #     #   
    #           
      #   #     
Step 3
          # #   
        #     # 
      #   #   # 
    # # #   #   
    # # #       
                
Step 4
          # #   
        #     # 
    #     #   # 
            #   
    #   # #     
      #         
Step 5
          # #   
        #     # 
          #   # 
      # #   #   
      # # #     
      # #       
Step 6
          # #   
        #     # 
      #   #   # 
      #     #   
    #           
      #   #     
Done.
```

## Assumptions You May Make

You may assume that we will test your program "in good faith".
In particular, you may assume:

* We will compile your program with values of `ROWS` and `COLS` that are positive integers
* There are exactly three command-line arguments including the name of the executable (that is, the value of `argc` is `3`)
* The first command-line argument (`argv[1]`) is convertible to an `int` using the `atoi` function from the C standard library
* The first command-line argument, when converted to an `int`, is positive
* The second command-line argument (`argv[2]`) contains exactly `ROWS * COLS` characters, each of which is either `'0'` or `'1'`
* The length of the given command (including the command-line arguments) will not exceed the maximum length of a command on the Zoo (which is ~130k characters). In other words, we won't run your executable with a field larger than about $350 \times 350$

In all runs of your program that adhere to these assumptions, your program must produce correct output, not encounter any runtime errors, and exit with status code `0`.

**We will not test your program on input that does not adhere to these assumptions.**

In future assignments we will not be so kind with our testing!
To help you prepare, consider what changes you would need to make to your solution for *this* assignment for it to behave predictably (*e.g.*, print a meaningful message and exit with status code `1`) given the removal of any or all of the above assumptions.
Ask yourself the following questions:

* What if there are not exactly 3 command-line arguments?
* What if the first command-line argument is not convertible to an `int` (*e.g.* it is a non-integer number such as `6.25`)? What if it is not a number at all? What if it is `0`?
* What if the second command-line argument does not contain the appropriate number of `'0'`s or `'1'`s? Too few? Too many?
* What if the second command-line argument contains characters other than `'0'` or `'1'`?

We encourage you to account for such cases, although you will not be graded in this assignment on handling ill-formed input.

Also consider the final assumption regarding input length.
A 350-cell square is not that big: what changes could you make to your program so that it can handle larger input sizes?
How else can input be given to your program besides command-line arguments?
Answer these questions in your weekly survey discussions.

### Assumptions for individual functions

The specification for some of the required functions have an "`@assumes`" clause.
These clauses indicate the kinds of things that you *are not required to handle* in your implementation.
For this course, we'll consider the behavior of a function under conditions that violate its `@assumes` clause to be **undefined**&mdash;that is, the function could do anything at all in that case and still be considered "correct"!
There is a lot of undefined behavior in the C language, which we'll see more of as we progress through the course.
You must *always* avoid undefined behavior in your programs, so these assumptions must be handled somewhere.
The **code that calls the function** is responsible for ensure the assumptions are satisfied.

For example, the `is_alive` function declared in `life.h` specifies that it assumes `field[i][j]` exists.
In other words, it assumes that `i` and `j` are valid indices in the array `field`.
*Before calling this function*, you must make sure that's the case!
How can you do this?
You could explicitly check that `i` and `j` are valid before every call to `is_alive`, but that is cumbersome and inefficient.
A better way to do it is to write the code surrounding `is_alive` such that `i` and `j` are *guaranteed* to be valid indices.
The following code fragment makes such a guarantee:

```C
int field[ROWS][COLS];
// Initialize values in field
for (size_t i = 0; i < ROWS; i++)
{
  for (size_t j = 0; j < COLS; j++)
  {
    bool living = is_alive(field, i, j);
    // Do something with living, and maybe field
  }
}
// Rest of program
```

## Testing and Grading

Grading for this assignment is automated.
Unless otherwise requested, we will grade the *latest* submission on Gradescope.
The autograder will perform three kinds of tests on your code:

* Compilation tests
* Diff tests
* Unit tests

We will first ensure your program compiles without errors or warnings using the `makefile` provided to you with the starter code.
We will compile several versions of your executable, each with a different grid size, running `make clean` in between each.

> *IMPORTANT:* **You will receive no credit this assignment if your program does not compile on Gradescope with your provided makefile, including for varying grid sizes and `make clean`.**
> If your program compiles on the Zoo but not Gradescope, it is your responsibility to seek out clarification as to why and to modify your submission so that it *does* compile on Gradescope.
>
> The most common cause of a discrepancy is submitting incorrect files.

Next, we will run each of the compiled `Life` executables on several test cases and check its output using the `diff` tool available on Unix systems including the Zoo and Gradescope.

Finally, we will run **unit tests** on your code.
These unit tests will exercise the required functions that you have implemented, in isolation from one another, to assess that each individual function is correct relative to its specification.
Here is a possible unit test for the `is_alive` function:

```C
void test_is_alive_corner_cell_all_dead()
{
  // Set up field
  int field[ROWS][COLS];
  for (size_t i = 0; i < ROWS; i++)
  {
    for (size_t j = 0; j < COLS; j++)
    {
      field[i][j] = 0;
    }
  }
  
  // Expected value for is_alive(field, 0, 0)
  bool expected = false;

  // Actual value for is_alive(field, 0, 0)
  bool actual = is_alive(field, 0, 0);

  // Determine whether passed or failed
  if (result == expected)
  {
    printf("test_is_alive_corner_cell (%dx%d) PASSED\n", ROWS, COLS);
  }
  else
  {
    printf("test_is_alive_corner_cell (%dx%d) FAILED\n", ROWS, COLS);
  }
}
```

> **Note**: The values of `ROWS` and `COLS` are not restricted by the assumptions in the specifications of the required functions (except that they are positive, because that is required for array dimensions and thus is checked by the compiler for you).
> This is because *they are not limited by input size in the same way as the main function*!
> Within unit tests, we will test your program on even larger fields and your functions must handle them correctly.
> For example, we may set `ROWS` and `COLS` to 1000 and run the test case above.
>
> There is actually another system-imposed limit to the size of stack-allocated arrays, which is on the order of 1MB, so 1000 x 1000 really is as large a grid as your program could possibly handle!

> *IMPORTANT:* **You will not receive any credit for this assignment if the unit testing suite does not compile, for any grid size.**
> It is possible that your provided `makefile` may successfully compile your program, but that the unit test program does not compile (or vice versa!).
> If this happens, it is your resposibility to seek out clarification as to why and to modify your submission so that the unit testing script *does* compile.
>
> The most common cause is changing the required function prototypes.
> The unit tests (by necessity) assume the prototypes for all required functions are provided unchanged from the starter code.
> **Do not modify the prototype for any of the required functions.**
> 
> This can also happen because the unit test program is written in C++, which (despite popular belief) is not actually a superset of C.
> That is, although many C programs are also valid C++ programs, *not all of them are*!
> Due to this property of the autograder, we require that your C programs use only the subset of C that is valid C++.
> (You're unlikely to stray too far during this assignment, but do be aware of the possibility.)

### Public vs. Private Test Cases

As you work on this assignment, there will be a reasonably complete suite of test cases that will run automatically on your submission when you upload it to Gradescope.
Although you will see the output from compilation for 8-9 different grid sizes, the only test case output you'll see is from running your code on a $4 \times 4$ (i.e., default) grid!
Other grid sizes are exercised in secret, and you'll see your results after the due date for the assignment.

Depending on how mean we're feeling, we may or may not release additional public test cases before the end of the submission period.
We plan to release some public diff tests during the first week of the assignment.

> Begging us for more public test cases is a good way to make us meaner ;-).

The output of passed test cases is not easy to decipher because of how we had to name our test cases in the unit testing framework we are using.
Ask a staff member if you're really curious about what a particular test case does (Alan wrote the script so if the person you ask first doesn't know, ask him).
For failed test cases, however, the output is somewhat more enlightening because it will display a message to you describing the test case along with the assertion that was violated and caused the failure.

### Numerical Scores

The unit testing suite contains 5,588 individual test cases, each of which is worth the same number of points.
The unit tests, in total, are worth 80 points for this assignment.
80 does not evenly divide by 5,588 and floating-point numbers are not terribly precise, so we end up with scores such as `15.175375805297065`.
These are rounded in the summary provided at the top of the Autograder output, but are *not* rounded in the actual computation of your grade to preserve the invariant that the sum of your scores for each grid size is as close to exactly `80` points as possible.
Don't worry about weird fractions; they'll be rounded in the gradebook.

## Weekly Survey

Each week, you will be asked to fill out a survey asking for at least the following information:

* Your full name and netID
* Your estimate of the time required to complete this assignment, selected *before* you start writing any code.
* The total time you *actually* spent on the assignment
* The names of all others (but not members of the teaching staff) with whom you discussed the assignment for more than 10 minutes
* A brief discussion (~100 words) of the major conceptual and coding difficulties that you encountered in developing and debugging the program (and there will always be some)

In total, the weekly surveys are worth 5% of your overall grade for the course.

## Comments and Coding Style 

Make sure all your code is well-commented and readable.
In particular: 

* Ensure all of your variable names are good variable names 
* Include high level comments that explain what the program is doing or what it is implementing 
* Include lower level comments that explain how particular elements of the program are implemented *if the implementation is not obvious*
* Structure your `#include` directives so that all and only those headers used directly in any particular file are included by that file. You should have no transitive dependencies.

Please look at the style guide for further style suggestions and expectations, which has been shared via Canvas.

# Hints and Advice

Before you do any coding, complete a design planning exercise by carrying out the following steps: 

1. Re-read the gameplay instructions and consult the [sample runs](#sample-runs) until you understand exactly what will change from one time step to the next
2. Determine what data is involved, based on the problem description 
3. Write out a high level program outline
4. Write more refined pseudocode within the outline, sketching out each function in pseudocode
5. Write more refined pseudocode for the main function
6. Then (and only then!) start turning your pseudocode into real code.
    Compile and test your program often, maybe as frequently as after each line of code!
7. As you test your code, unexpected things will occur! Add print statements to inspect variable values to help understand what your program is doing or&mdash;better&mdash;use [GDB](https://www.sourceware.org/gdb/) (if you're on the Zoo or another Linux machine, including WSL on Windows) or [LLDB](https://lldb.llvm.org/) (if you're on a Mac).

If you feel that adding more functions in addition to the ones you are required to implement would help, you are welcome to do so.
If these extra functions are called from `main`, they should be declared in `life.h` or `helpers.h` and implemented in the corresponding source file (either `life.c` or `helpers.c`, as appropriate).
If these extra functions were useful only in the implementations of your other `life.h` functions, they *should not* be declared in `life.h` and instead *only* exist in `life.c` (you may find it useful to separate their *declaration* from their *implementation*, even within the same file, but you are not required to do so).
Be sure to note any additional functions you have implemented in your weekly survey response, and ensure they are well-commented (*i.e.*, there must be an English-language description of their behavior adjacent to their prototype or definition; complicated functions should have comments in their body, too).

By itself, the C programming language does not provide many functions you can call.
Several useful functions for this assignment are defined in `stdlib.h`, which you should `#include` in `main.c` and maybe also in `life.h` or `.c`, or `helpers.h` or `.c`, depending on how you have structured your program.
One such function, `int atoi(const char* s)` returns the `int` that is represented by the (ASCII) string `s` interpreted as a decimal integer.
If you'd like to check the provided input for validity, `size_t strlen(const char *str)` may be a useful function.
It is defined in `string.h`.

### Submission

This assignment is due on **Friday, Feb 2, 2024 at 11:59 PM NHT (New Haven Time)**.

Per the Syllabus, late submissions with no Dean's Extension will incur a 5-point penalty for each 12-hour period after the end of the grace period.
Absent a Dean's Extension, no work will be accepted more than 72 hours (3 days) after the due date or after the end of the Reading Period, whichever comes earlier.
Every programming assignment and late period deadline except for the end of the Reading Period and the 72-hour hard limit on late submissions has an automatic 2-hour grace period.
The grace period accounts for last-minute problems like laptop batteries dying, slowdowns on the Zoo, or frogs raining from the sky.
It is strict.

To submit this assignment to Gradescope, you'll upload your source code, header files, and your makefile.
For this assignment, you should submit (only and exactly) the following files:

1. `constants.h`
2. `helpers.c`
3. `helpers.h`
4. `life.c`
5. `life.h`
6. `main.c`
7. `makefile`

Your submission **should not** contain any executable files or object files, nor should it contain this README file.

Upload your files to [this Gradescope assignment](https://www.gradescope.com/courses/694843/assignments/3918882) before the deadline.

## For Interested Students

Conway's Game of Life is more than a decades-old curiosity!
It is one of a class of systems called **cellular automata**, and the study of how these systems behave is frequently a topic of curiosity for mathematics and computer science researchers.
For example, see [this recent article in Quanta magazine](https://www.quantamagazine.org/maths-game-of-life-reveals-long-sought-repeating-patterns-20240118/).
