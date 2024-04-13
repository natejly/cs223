#   Aidan Gibson
#   run_tests.sh for trees
#   Simple Testing Script For Yale's CPSC 223 

echo "Testing testing..."
# Creates necessary directories if they don't exist
if ! test -d testing/bst; then
    mkdir testing/bst
    mkdir testing/avlt
    mkdir testing/rbt
    chmod 777 the_*
    fi

# Tests make file
make clean > testing/clean.out
make > testing/make.out 2> testing/make.out.err

# Checks make file for warnings
if grep -q "warning" "testing/make.out.err"; then
    echo "FAIL: Warnings detected. Check make.out.err for warnings."
    fi
rm testing/make.out

echo "Testing bst..."
# Compares the_bst output against bst output
./the_bst > testing/bst/bst_test.out 2> testing/bst/bst_test.err.out
valgrind --leak-check=full --log-file="testing/bst/bst_valgrind.out.student" ./bst > testing/bst/bst_test.out.student 2> testing/bst/bst_test.err.out.student
diff testing/bst/bst_test.out.student testing/bst/bst_test.out
# Check to ensure no STDERR
if [ -s testing/bst/bst_test.err.out.student ]; then
        echo "ERROR: STDERR of BST not empty, see testing/bst/bst_test.err.out.student"
    fi
# Checks for BST memory errors
if ! grep -q "All heap blocks were freed -- no leaks are possible" "testing/bst/bst_valgrind.out.student" && ! grep -q "ERROR SUMMARY: 0 errors from 0 contexts" "testing/bst/bst_valgrind.out.student"; then
            echo "FAIL: Memory leak detected. Check testing/bst/bst_vagrind.out.student for more details."
        fi


echo "Testing avlt..."
# Compares the_avlt output againt avlt output
./the_avlt > testing/avlt/avlt_test.out 2> testing/avlt/avlt_test.err.out
valgrind --leak-check=full --log-file="testing/avlt/avlt_valgrind.out.student" ./avlt > testing/avlt/avlt_test.out.student 2> testing/avlt/avlt_test.err.out.student
diff testing/avlt/avlt_test.out testing/avlt/avlt_test.out.student
# Check to ensure no STDERR
if [ -s testing/avlt/avlt_test.err.out.student ]; then
        echo "ERROR: STDERR of AVLT not empty, see testing/avlt/avlt_test.err.out.student"
    fi
# Checks for AVLT memory errors
if ! grep -q "All heap blocks were freed -- no leaks are possible" "testing/avlt/avlt_valgrind.out.student" && ! grep -q "ERROR SUMMARY: 0 errors from 0 contexts" "testing/avlt/avlt_valgrind.out.student"; then
            echo "FAIL: Memory leak detected. Check testing/avlt/avlt_vagrind.out.student for more details."
        fi

echo "Testing rbt..."
# Compares the_rbt output againt rbt output
valgrind --leak-check=full --log-file="testing/rbt/rbt_valgrind.out" ./the_rbt > testing/rbt/rbt_test.out 2> testing/rbt/rbt_test.err.out
valgrind --leak-check=full --log-file="testing/rbt/rbt_valgrind.out.student" ./rbt > testing/rbt/rbt_test.out.student 2> testing/rbt/rbt_test.err.out.student
diff testing/rbt/rbt_test.out testing/rbt/rbt_test.out.student 
# Check to ensure no STDERR
if [ -s testing/rbt/rbt_test.err.out.student ]; then
        echo "ERROR: STDERR of RBT not empty, see testing/rbt/rbt_test.err.out.student"
    fi
# Checks for RBT memory errors
if ! grep -q "All heap blocks were freed -- no leaks are possible" "testing/rbt/rbt_valgrind.out.student" && ! grep -q "ERROR SUMMARY: 0 errors from 0 contexts" "testing/rbt/rbt_valgrind.out.student"; then
            echo "FAIL: Memory leak detected. Check testing/rbt/rbt_vagrind.out.student for more details."
        fi

echo "If there was diff output, check files for details.  Otherwise, nice job! :)"

# Cleanup
rm -rf testing/bst/bst_valgrind.out.student.core*
rm -rf testing/avlt/avlt_valgrind.out.student.core*
rm -rf testing/rbt/rbt_valgrind.out.student.core*