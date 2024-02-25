# Hookbook B Public Diff Test Script

## Author: Kenny Li

Hello! This is a really simple script that I wrote up to help you guys to diff test your program without having to submit to the autograder. Note that this ONLY tests the visible diff tests (comparing your program's output with the expected correct output), and does not include potential private test cases. Moreover, this also does not include the autograder's unit test cases (the test cases directly testing your functions and not the program as a whole), but if I get some extra time before the deadline, I'll try to include functionality for that as well. 

## HOW TO UPLOAD/INSTALL:
WARNING: THIS HAS ONLY BEEN TESTED ON THE ZOO, AND MAY NOT RUN LOCALLY, ESPECIALLY IF YOU ARE UNABLE TO RUN VALGRIND LOCALLY.

Upload the `btests.zip` file on to the zoo and extract it into your project directory that contains all of your code:

```
unzip btests.zip
```
 
When done properly, you should now have a `btests` sub-directory in your main project directory. If you use the `ls` command, you should see something like this (with some variation given your own directory structure):

```console
[kl858@gator hw3]$ ls
btests           libhookbook.c    pirate.c         pirate_list.h
Hookbook         libhookbook.h    pirate.h         skills_list.c
hookbookb.c      libhookbook.o    pirate.o         skills_list.h
hookbookb.o      makefile         pirate_list.c    skills_list.o
```

## UNDERSTANDING THE CONTENT OF THE TESTS FOLDER
`btests` contains the script: `run_tests.sh` and a series of even more sub-directories named `t001` to `t020`. The content of `btests`:

```console
[kl858@gator btests]$ ls
README.md     t001  t003  t005  t007  t009  t011  t013  t015  t017  t019
run_tests.sh  t002  t004  t006  t008  t010  t012  t014  t016  t018  t020
```
The smaller folders `t001` to `t020` represent each of the public diff test cases, and each contains these specific files:

```console
[kl858@gator t001]$ ls
args.txt  captains.txt  doc.txt  profiles.txt  ref_error.txt  ref.txt
```

`args.txt` contains the command line arguments for the given test. `captains.txt` and `profiles.txt` are the respective files you'll be reading in. `doc.txt` contains some documentation that aligns with the autograder, and a very brief explanation of the test case. 

Importantly, `ref.txt` contains the CORRECT EXPECTED OUTPUT. `ref_error.txt` contains the CORRECT EXPECTED ERROR MESSAGES (i.e your printing to stderr when expanding). These will be used to compare against the output that your program produces.

WARNING: DO NOT ALTER OR CHANGE ANY OF THESE FILES. THE TEST SCRIPT WILL USE THESE TO DIFF TEST WITH YOUR PROGRAM, AND ANY CHANGES MAY LEAD TO UNEXPECTED RESULTS. FEEL FREE TO EXAMINE THEM TO HAVE A BETTER IDEA OF WHAT TEST CASE YOU'RE FAILING, BUT DO NOT EDIT THESE FILES.

## UNDERSTANDING THE TEST SCRIPT CODE

The provided test script is a Bash script designed to automate the testing of your project by comparing your program's output against predefined expected outputs. You are encouraged to examine the script to understand how it works. This knowledge can help you debug your project and write your own test scripts in the future.

### Script Overview

- The script starts with defining a `usage` function that displays the available options and their descriptions. This function is called when the `-h` option is used or when an invalid option is provided.
- It then initializes variables to store the headers for different sections of the test results and calculates padding for output formatting based on the terminal's width.
- The script processes command-line options using a while loop and the `getopts` command. It supports three options: `-h` for help, `-d` to run only diff tests, and `-v` to run only Valgrind tests.
- If no specific test cases are mentioned, it defaults to running all tests found in the `btests` directory. Specific test cases can be run by providing their names as arguments.
- The script compiles your project using `make` and checks for compilation errors before proceeding with the tests.
- For diff tests, it iterates over the specified test directories, runs your program with arguments read from a file, redirects the output to `output.txt`, and compares it against a reference output using `diff`.
- For Valgrind tests, it re-runs the tests with Valgrind to check for memory leaks and errors, redirecting Valgrind's output for further inspection if necessary.

### Important Notes

- **Temporary Files**: After running a test case, the script cleans up by removing the `output.txt`, `error.txt`, and `valgrind_output.txt` files. This is to ensure that subsequent test runs start clean. However, if you wish to inspect the output directly after a test run, you can comment out the lines responsible for removing these files. Just look for lines containing `rm $test_dir/output.txt` and similar for `error.txt` and `valgrind_output.txt`, and comment them out by prefixing them with `#`.

Feel free to modify the script to suit your needs or to add more tests, but be careful that you maintain the consistent structure of the rest of the tests.

## HOW TO USE THE TEST SCRIPT
To run the script, ensure you are in your main project directory. THIS SCRIPT IS DESIGNED TO BE RUN FROM THERE, NOT WITHIN THE `btests` DIRECTORY ITSELF. If this is your first time using the script, navigate into the `btests` directory and change the permissions for the script:

```
cd btests
chmod +x run_tests.sh
```
Then return back to your main project directory. To run all of the tests, you can simply use the following command:

```
btests/run_tests.sh
```

This script will compile your code using the `makefile` and then run through each of the test cases in the `btests` directory, comparing your program's output to the expected output provided in the test case directories.


### Script Flags/Arguments

The script supports several flags/arguments to customize its behavior:

- `-h`: Display this help message. Use this flag if you need a reminder of the script's options or how to use it.
- `-d`: Only run diff tests. This option is useful if you want to specifically test the output of your program against the expected outputs provided in the test cases.
- `-v`: Only run Valgrind tests. Opt for this flag to check your program for memory leaks and other memory-related errors.
- If no test cases are specified by name, the script defaults to running all available tests in the `btests` directory. \

### Running Specific Test Cases

You can also specify one or more test cases by name after any flags. This allows you to focus on particular areas of interest or retest specific cases where your program previously failed. For example, to run only the first and second test cases, you would use:

```
btests/run_tests.sh t001 t002
```

or 

```
btests/run_tests.sh tests/t001 tests/t002
```

### Interpreting Results

After running the script, it will output the results for each test case. A successful test will indicate that your program's output matches the expected output. If a test fails, the script will provide a diff, showing the difference between your output and the expected output. If all you see is PASSED, then you're in good shape :D

## REMINDER
Remember that this does not contain the complete suite of autograder tests, but rather ONLY the visible/public diff tests. Passing all of these test cases does not guarantee that you will pass all of the public autograder tests, and will definitely not guarantee that you pass all of the private test cases. This test script is only designed to help you debug quickly, so passing the script does not correspond to passing ALL test cases. However! If you're passing all of the diff and memory tests here, then you're probably in good shape :D.

## BUGS
To be quite honest, I wrote this pretty quickly so I'm like only okay-ishly confident about it. If there are any discrepancies between this script and the autograder output, ALWAYS DEFAULT TO THE AUTOGRADER. Moreover, if you identify any bugs at all please let me (you can email me at kenny.li@yale.edu) or any of the other course staff know, and I'll try to fix it ASAP (though AHHHHHHHHHHHH MIDTERMS AHHHHHHHHHHHHHH). Let me know if you have any questions! :D

