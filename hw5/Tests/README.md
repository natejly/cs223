# Testing Script for Pset 5 (Treasure Hunter)
### Modified for CPSC 223 by Alan Weide &copy;2024

## Purpose

This folder contains various scripts and files needed to run a variety of test cases on a student's submission for Pset 5 (Treasure Hunter).

## Usage

The most important file in the folder is `tests.sh`, which should be executed to perform all public tests.
It can be executed as follows:

```
$ ./tests.sh [source_directory]
```

For example, if you'd like to use the directory `~/cs223/hw5` as the source directory, run the following command:

```
$ ./tests.sh ~/cs223/hw5
```

If `./tests.sh` results in a permission error, run the following command:

```
$ chmod u+x tests.sh
```

This adds the executable permission for the current user (you!) to the file `tests.sh`.

### The Script

When invoked without the `-h`/`-H` option, the `tests.sh` script performs the following steps:
1. Executes `make treasure-hunter` and reports and warnings or errors (testing is aborted if there any errors)
2. Runs an input/output test case, checking its correctness with `diff`
3. Executes `valgrind ./treasure-hunter` and asserts there are no memory leaks (this step is skipped if Valgrind is not available on your system)
4. Executes `make unittest` (if no changes to `Makefile` have been made, this will not produce any errors)
5. Runs several unit tests and reports their results. See `unittest.cpp` for details of these tests.
6. Cleans up this directory by running `make clean`

Most of the output is redirected to files in the `output` directory:
* Output from `make treasure-hunter` is redirected to `output/student.compile`.
* Output from `./treasure-hunter` is redirected to `output/student.out`, and the generated files are also in the `output` directory.
* Output from `diff` is redirected to `output/*.diff`.
* Output from `valgrind` is redirected to `output/student.valgrind`.
* Output from `make unittest` is redirected to `output/unittest.compile`.

### The Source Directory

The `source_directory` option is the directory in which your solution lives.
For this pset, `make` looks for the following files in the source directory:
* `LinkedList.cpp`
* `Isalnd.cpp`

The `source_directory` option is not required (but is recommended).
You could *copy* your solution's files into this directory, and invoke `tests.sh` without any arguments.
Doing so will tell `make` to search in the current directory for those two source files.
If you opt for this approach, to receive reliable results you must **not** copy the following files:
* `Makefile`
* `treasure-hunter.cpp`
* `caribbean.txt`, if you modified it

### Delegation to `make`

Compilation of the `treasure-hunter` executable takes place by calling `make treasure-hunter` **in the current directory**, which is probably the same directory as `tests.sh`.
This recipe in this directory's `Makefile` is essentially the same as the one in the `Makefile` you were provided with the started code for this Pset, with some necessary modifications to account for the multi-directory structure of this testing harness.

If you have modified your starter `Makefile`, it's possible that this script will not compile your program correctly.
You are free to modify this `Makefile` as necessary to enable successful compilation, but note that it uses features of `make` that have not been covered in class and that you are therefore not expected to be familiar with.
If you'd like assistance fixing up this `Makefile` for your purposes, don't hesitate to reach out to one of the instructors or ULAs.

#### Header Files

The `treasure-hunter.cpp` and `unittest.cpp` files include header files that it searches for in the current directory: `LinkedList.h` and `Island.h` (and, indirectly, `NodeType.h`).
These files are identical to the header files in the starter code.
You may have to reconcile any modifications you've made to those files before this script will compile your program.
As with the `Makefile`, reach out to one of the instructors or ULAs for help if you need it.

## Example Invocation
Suppose your project looks like the following, and the current directory (`Tests`) is marked by `*`:

```
~/cs223 /
    ...
    hw5 /
        caribbean.txt
        LinkedList.cpp
        LinkedList.h
        Makefile
        NodeType.h
        README.md
        Island.cpp
        Island.h
        treasure-hunter.cpp
        ...
        Tests /                     * (current directory)
            input /
                caribbean.txt
            LinkedList.h
            Makefile
            NodeType.h
            README.md
            ref /
                all_islands.txt
                output.out
                remove_some.txt
            Island.h
            tests.sh
            treasure-hunter.cpp
            unittest.cpp
```

Now, assume you've already finished the assignment and your solution is perfect!
Here is the command you should run and the expected output (on a system with valgrind installed, such as the Zoo):

```
$ ./tests.sh ~/cs223/hw5
~~compiling treasure-hunter~~
No errors or warnings!

~~running difftest~~
all_islands passed!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
remove_some passed!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
output passed!
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

~~running valgrind~~
==1838790== Command: ./treasure-hunter input/caribbean.txt output/all_islands.txt output/remove_some.txt 10 1
==1838790== 
I just read and inserted 30 islands
Removed 10 islands and printed to file
Done!
==1838790== 
==1838790== HEAP SUMMARY:
==1838790==     in use at exit: 0 bytes in 0 blocks
==1838790==   total heap usage: ??? allocs, ??? frees, ??? bytes allocated
==1838790== 
==1838790== All heap blocks were freed -- no leaks are possible
==1838790== 
==1838790== For lists of detected and suppressed errors, rerun with: -s
==1838790== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

~~running unittest~~
test1 passed!
test2 passed!
test3 passed!
test4 passed!
test5 passed!
test6 passed!
test7 passed!
test8 passed!
test9 passed!
test10 passed!

~~cleaning up~~
rm -f unittest treasure-hunter
rm -f unittest.o treasure-hunter.o Island.o LinkedList.o
rm -f core* *~
```

As always, if there are any questions you should not hesitate to ask on Ed or in Office Hours!
