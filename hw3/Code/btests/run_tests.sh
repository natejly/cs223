#!/bin/bash

usage() {
    echo "Usage: $0 [options] [test_case1 test_case2 ...]"
    echo "Options:"
    echo "  -h                Display this help message."
    echo "  -d                Only run diff tests."
    echo "  -v                Only run Valgrind tests."
    echo "If no test cases are specified, all tests will be run."
}

compilation_header="Compilation Test"
diff_header="Diff Tests"
valgrind_header="Valgrind Tests"

terminal_width=$(tput cols)
padding_length=$(( (terminal_width - ${#header}) / 4 ))

padding=""
for ((i = 0; i < padding_length; i++)); do
    padding+=" "
done

# Parse command-line options
while getopts "hdv" opt; do
    case ${opt} in
        h )
            usage
            exit 0
            ;;
        d )
            run_diff_tests=true
            ;;
        v )
            run_valgrind_tests=true
            ;;
        \? )
            usage
            exit 1
            ;;
    esac
done
shift $((OPTIND -1))

# If no options are given, run both tests
if [ -z "$run_diff_tests" ] && [ -z "$run_valgrind_tests" ]; then
    run_diff_tests=true
    run_valgrind_tests=true
fi

# Get test directories from command-line arguments or default to all
declare -a test_dirs

if [ $# -eq 0 ]; then
    test_dirs=(btests/t*)
else
    for arg in "$@"; do
        if [[ ! $arg =~ ^tests/ ]]; then
            test_dirs+=("btests/$arg")
        else
            test_dirs+=("$arg")
        fi
    done
fi

echo -e "Testing start...\n"

echo "${padding}${compilation_header}${padding}"
make Hookbook
# Check if succesfully compiled
if [ $? -ne 0 ]; then
    echo "ERROR: Compilation failed."
    echo "${padding}Compilation Test: 1 of 1 tests passed${padding}"
    exit 1
else
    echo "PASSED: Compilation succeeded."
    echo -e "${padding}Compilation Test: 1 of 1 tests passed${padding}\n\n"
fi


if [ "$run_diff_tests" = true ]; then
    total_diff_tests=0
    passed_diff_tests=0
    echo "${padding}${diff_header}${padding}"
    # Iterate over test case directories for diff tests
    for test_dir in ${test_dirs[@]}; do
        ((total_diff_tests++))
        # echo "Testing $test_dir..."

        args_formatted=""
        while IFS= read -r line || [[ -n "$line" ]]; do
            args_formatted="$args_formatted $test_dir/$line"
        done < "$test_dir/args.txt"

        # Redirect output to output.txt, error messages to error.txt
        ./Hookbook $args_formatted > "$test_dir/output.txt" 2> "$test_dir/error.txt"  

        # Compares program output with reference output
        stdout_diff=$(diff -q "$test_dir/output.txt" "$test_dir/ref.txt")
        stderr_diff=$(diff -q "$test_dir/error.txt" "$test_dir/ref_error.txt")

        # If both output and error have no differences, the test passes
        if [ -z "$stdout_diff" ] && [ -z "$stderr_diff" ]; then
            echo "PASSED: $test_dir"
            ((passed_diff_tests++))
        else
            echo "----------------------------------"
            echo "FAILED: $test_dir"

            # If there is a difference in output, print it
            if [ -n "$stdout_diff" ]; then
                echo "Output differences:"
                diff "$test_dir/output.txt" "$test_dir/ref.txt"
            fi

            # If there is a difference in error, print it
            if [ -n "$stderr_diff" ]; then
                echo "Error differences:"
                diff "$test_dir/error.txt" "$test_dir/ref_error.txt"
            fi

            echo "----------------------------------"
        fi
        # Comment the line below out if you want to store your output and error
        rm $test_dir/output.txt
        rm $test_dir/error.txt
    done
    # Report diff test results
    echo -e "${padding}${diff_header}: $passed_diff_tests out of $total_diff_tests diff tests passed.${padding}\n\n"
fi

if [ "$run_valgrind_tests" = true ]; then
    total_valgrind_tests=$total_diff_tests
    passed_valgrind_tests=0

    echo "${padding}${valgrind_header}${padding}"
    # Re-run tests with Valgrind
    for test_dir in ${test_dirs[@]}; do
        # echo "Valgrind testing $test_dir..."

        args_formatted=""
        while IFS= read -r line || [[ -n "$line" ]]; do
            args_formatted="$args_formatted $test_dir/$line"
        done < "$test_dir/args.txt"


        # Use Valgrind to check for memory leaks and errors
        valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s --error-exitcode=1 ./Hookbook $args_formatted > /dev/null 2>$test_dir/valgrind_output.txt
        valgrind_exit_code=$?

        # Check Valgrind's exit code to determine if memory issues were found
        if [ $valgrind_exit_code -eq 0 ]; then
            echo "PASSED: $test_dir"
            ((passed_valgrind_tests++))
        else
            echo "FAILED: $test_dir"
            echo "----------------------------------"
            cat $test_dir/valgrind_output.txt  # Optionally print Valgrind output
            echo "----------------------------------"
        fi
        # Comment the line below out if you want to store your valgrind output
        rm $test_dir/valgrind_output.txt
    done

    # Report Valgrind test results
    echo -e "$passed_valgrind_tests out of $total_valgrind_tests Valgrind tests passed.\n\n"
fi

echo "Testing complete."
exit 0
