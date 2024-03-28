#!/bin/bash

if [[ $1 =~ ^--?[hH](elp)? ]]; then
	less README.md
	exit 0
elif [[ $# -eq 1 ]]; then
	export SRCDIR=$1
elif [[ $# -gt 1 ]]; then
	echo "usage: $0 [source_directory]"
	exit 1
fi

# Creating symbolic links to submitted header files.
ln -s $SRCDIR/LinkedList.h -f
ln -s $SRCDIR/Island.h -f
ln -s $SRCDIR/NodeType.h -f

rm -rf output
mkdir -p output

exe="treasure-hunter"

echo "~~compiling ${exe}~~"
make -B -e $exe &>output/student.compile

## check compilation
if [ -f ./${exe} ]; then
	warnings=$(grep -i "\(warning\|warnings\) generated" output/student.compile)
	if [ -z "$warnings" ]; then
		echo "No errors or warnings!"
	else
		echo "Warnings! Check output/student.compile!"
	fi
else
	echo "Errors! Check output/student.compile!"
	echo "Stopping tests."
	exit 1
fi

GLXFILE=caribbean.txt
ALLSTATIONSFILE=all_islands.txt
REMOVESOMEFILE=remove_some.txt
NUMREMOVE=10
PATTERN=(1)

ALLSTATIONSDIFF=$(basename $ALLSTATIONSFILE '.txt').diff
REMOVESOMEDIFF=$(basename $REMOVESOMEFILE '.txt').diff

echo ""
cmd="./$exe input/$GLXFILE output/$ALLSTATIONSFILE output/$REMOVESOMEFILE $NUMREMOVE ${PATTERN[@]}"
# echo $cmd
$cmd >./output/student.out

echo "~~running difftest~~"
diff ./ref/$ALLSTATIONSFILE ./output/$ALLSTATIONSFILE >./output/$ALLSTATIONSDIFF 2>&1
if [ -s ./output/$ALLSTATIONSDIFF ]; then
	echo "all_islands failed!"
	echo "all_isalnds (first 5 lines):"
	head -n 5 ./output/$ALLSTATIONSFILE
	echo ""
	echo "Expected output  (first 5 lines):"
	head -n 5 ./ref/$ALLSTATIONSFILE
	echo ""
	echo "diff (first 5 lines)"
	head -n 5 ./output/$ALLSTATIONSDIFF
	echo ""
else
	echo "all_islands passed!"
fi

echo '~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'

diff ./ref/$REMOVESOMEFILE ./output/$REMOVESOMEFILE >./output/$REMOVESOMEDIFF 2>&1
if [ -s ./output/$REMOVESOMEDIFF ]; then
	echo "remove_some failed!"
	echo "remove_some (first 5 lines):"
	head -n 5 ./output/$REMOVESOMEFILE
	echo ""
	echo "Expected output  (first 5 lines):"
	head -n 5 ./ref/$REMOVESOMEFILE
	echo ""
	echo "diff (first 5 lines)"
	head -n 5 ./output/$REMOVESOMEDIFF
	echo ""
else
	echo "remove_some passed!"
fi

echo '~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'

diff ./ref/output.out ./output/student.out >./output/output.diff 2>&1
if [ -s ./output/output.diff ]; then
	echo "output failed!"
	echo "output (first 5 lines):"
	head -n 5 ./output/student.out
	echo ""
	echo "Expected output  (first 5 lines):"
	head -n 5 ./ref/output.out
	echo ""
	echo "diff (first 5 lines)"
	head -n 5 ./output/output.diff
	echo ""
else
	echo "output passed!"
fi
echo '~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~'
echo ""

if ! command -v valgrind &>/dev/null; then
	echo "~~valgrind not found on this system...skipping valgrind~~"
else
	echo "~~running valgrind~~"
	timeout 600s valgrind $cmd &>output/student.valgrind
	tail -n 14 output/student.valgrind
fi
echo ""

echo "~~running unittest~~"
make -B -e unittest &>output/unittest.compile
# checking compilation
if [ -f ./unittest ]; then
	warnings=$(grep -i "\(warning\|warnings\) generated" output/unittest.compile)
	if [ ! -z "$warnings" ]; then
		echo "Warnings! Check output/unittest.compile!"
	fi
else
	echo "Errors! Check output/unittest.compile!"
	echo "Stopping tests."
	exit 1
fi

timeout 30s ./unittest

echo ""
echo "~~cleaning up~~"
echo "Unlinking header files...."
rm *.h
make clean
