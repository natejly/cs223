/**
 * unittest.cpp
 * CPSC 223 Pset 5
 *
 * TO STUDENT: Do not modify this file!
 *
 * Author: Alan Weide
 */

#include <iostream>
#include <vector>
#include <string>
#include "LinkedList.h"
using namespace std;

/* TESTS:

values = using LinkedList::getNextIsland to check list
length = using LinkedList::getLength to check list
currpos = ensuring correct NULL behavior

test1 - parameterized constructor
test2 - Island::isEqual
test3 - LinkedList::insertIsland ------------- values
test4 - LinkedList::insertIsland ------------- length
test5 - LinkedList::removeIsland ------------- length
test6 - LinkedList::removeIsland from front -- values
test7 - LinkedList::removeIsland from middle - values
test8 - LinkedList::removeIsland from back --- values
test9 - LinkedList::removeIsland curr -------- currpos
test10 - LinkedList::empty -------------------- currpos
*/

int test1_num_failed(bool print);
int test2_num_failed(bool print);
int test3_num_failed(bool print);
int test4_num_failed(bool print);
int test5_num_failed(bool print);
int test6_num_failed(bool print);
int test7_num_failed(bool print);
int test8_num_failed(bool print);
int test9_num_failed(bool print);
int test10_num_failed(bool print);
bool check_e(int test, char part, int input, int expected, bool print);
bool check_a(int test, char part, bool assertion, bool print);
void printPass(int test);
void printFail(int test, int failed, int expected);

int main()
{
	streambuf *orig_buf = cout.rdbuf();
	cout.rdbuf(NULL);

	// test1
	if (test1_num_failed(true) == 0)
		printPass(1);
	else
		printFail(1, test1_num_failed(false), 4);

	// test2
	if (test2_num_failed(true) == 0)
		printPass(2);
	else
		printFail(2, test2_num_failed(false), 5);

	// test3
	if (test3_num_failed(true) == 0)
		printPass(3);
	else
		printFail(3, test3_num_failed(false), 5);

	// test4
	if (test4_num_failed(true) == 0)
		printPass(4);
	else
		printFail(4, test4_num_failed(false), 5);

	// test5
	if (test5_num_failed(true) == 0)
		printPass(5);
	else
		printFail(5, test5_num_failed(false), 6);

	// test6
	if (test6_num_failed(true) == 0)
		printPass(6);
	else
		printFail(6, test6_num_failed(false), 4);

	// test7
	if (test7_num_failed(true) == 0)
		printPass(7);
	else
		printFail(7, test7_num_failed(false), 4);

	// test8
	if (test8_num_failed(true) == 0)
		printPass(8);
	else
		printFail(8, test8_num_failed(false), 4);

	// test9
	if (test9_num_failed(true) == 0)
		printPass(9);
	else
		printFail(9, test9_num_failed(false), 2);

	// test10
	if (test10_num_failed(true) == 0)
		printPass(10);
	else
		printFail(10, test10_num_failed(false), 2);

	cout.rdbuf(orig_buf);
}

int test1_num_failed(bool print)
{
	int failed = 0;
	int test = 1;
	char part = 'a';

	LinkedList list;
	Island s1("island1", true);
	Island s2("island2", false);

	if (check_a(test, part++, s1.getName() == "island1", print)) // check list
		failed++;

	if (check_a(test, part++, s2.getName() == "island2", print)) // check list
		failed++;

	if (check_a(test, part++, s1.hasBerth() == true, print)) // check list
		failed++;

	if (check_a(test, part++, s2.hasBerth() == false, print)) // check list
		failed++;

	return failed;
}

int test2_num_failed(bool print)
{
	int failed = 0;
	int test = 2;
	char part = 'a';

	LinkedList list;
	Island s1("island1", true);
	Island s2("island1", true);

	Island s3("island3", true);
	Island s4("island4", true);

	Island s5("island5", true);
	Island s6("island5", false);

	if (check_a(test, part++, s1.isEqual(s2), print)) // check list
		failed++;

	if (check_a(test, part++, s2.isEqual(s1), print)) // check list
		failed++;

	if (check_a(test, part++, !s3.isEqual(s4), print)) // check list
		failed++;

	if (check_a(test, part++, !s4.isEqual(s3), print)) // check list
		failed++;

	if (check_a(test, part++, !s5.isEqual(s6), print)) // check list
		failed++;

	return failed;
}

int test3_num_failed(bool print)
{
	int failed = 0;
	int test = 3;
	char part = 'a';

	LinkedList list;
	Island s1("island1", true);
	Island s2("island2", false);
	Island s3("island3", true);
	Island s4("island4", false);
	Island s5("island5", true);

	list.insertIsland(s1);
	if (check_e(test, part++, list.getLength(), 1, print))
		failed++;

	list.insertIsland(s2);
	if (check_e(test, part++, list.getLength(), 2, print))
		failed++;

	list.insertIsland(s3);
	if (check_e(test, part++, list.getLength(), 3, print))
		failed++;

	list.insertIsland(s4);
	if (check_e(test, part++, list.getLength(), 4, print))
		failed++;

	list.insertIsland(s5);
	if (check_e(test, part++, list.getLength(), 5, print))
		failed++;

	return failed;
}

int test4_num_failed(bool print)
{
	int failed = 0;
	int test = 4;
	char part = 'a';

	LinkedList list;
	Island s1("island1", true);
	Island s2("island2", false);
	Island s3("island3", true);
	Island s4("island4", false);
	Island s5("island5", true);

	list.insertIsland(s1);
	list.insertIsland(s2);
	list.insertIsland(s3);
	list.insertIsland(s4);
	list.insertIsland(s5);

	Island temp;

	temp = list.getNextIsland();
	if (check_a(test, part++, temp.getName() == s5.getName() && temp.hasBerth() == s5.hasBerth(), print)) // check list
		failed++;

	temp = list.getNextIsland();
	if (check_a(test, part++, temp.getName() == s4.getName() && temp.hasBerth() == s4.hasBerth(), print)) // check list
		failed++;

	temp = list.getNextIsland();
	if (check_a(test, part++, temp.getName() == s3.getName() && temp.hasBerth() == s3.hasBerth(), print)) // check list
		failed++;

	temp = list.getNextIsland();
	if (check_a(test, part++, temp.getName() == s2.getName() && temp.hasBerth() == s2.hasBerth(), print)) // check list
		failed++;

	temp = list.getNextIsland();
	if (check_a(test, part++, temp.getName() == s1.getName() && temp.hasBerth() == s1.hasBerth(), print)) // check list
		failed++;

	return failed;
}

int test5_num_failed(bool print)
{
	int failed = 0;
	int test = 5;
	char part = 'a';

	LinkedList list;
	Island s1("island1", true);
	Island s2("island2", false);
	Island s3("island3", true);
	Island s4("island4", false);
	Island s5("island5", true);

	list.insertIsland(s1);
	list.insertIsland(s2);
	list.insertIsland(s3);
	list.insertIsland(s4);
	list.insertIsland(s5);
	if (check_e(test, part++, list.getLength(), 5, print))
		failed++;

	list.removeIsland(s1);
	if (check_e(test, part++, list.getLength(), 4, print))
		failed++;

	list.removeIsland(s2);
	if (check_e(test, part++, list.getLength(), 3, print))
		failed++;

	list.removeIsland(s3);
	if (check_e(test, part++, list.getLength(), 2, print))
		failed++;

	list.removeIsland(s4);
	if (check_e(test, part++, list.getLength(), 1, print))
		failed++;

	list.removeIsland(s5);
	if (check_e(test, part++, list.getLength(), 0, print))
		failed++;

	return failed;
}

// front remove + getNextIsland
int test6_num_failed(bool print)
{
	int failed = 0;
	int test = 6;
	char part = 'a';

	LinkedList list;
	Island s1("island1", true);
	Island s2("island2", false);
	Island s3("island3", true);
	Island s4("island4", false);
	Island s5("island5", true);

	list.insertIsland(s1);
	list.insertIsland(s2);
	list.insertIsland(s3);
	list.insertIsland(s4);
	list.insertIsland(s5);

	list.removeIsland(s5);

	Island temp;

	temp = list.getNextIsland();
	if (check_a(test, part++, temp.getName() == s4.getName() && temp.hasBerth() == s4.hasBerth(), print)) // check list
		failed++;

	temp = list.getNextIsland();
	if (check_a(test, part++, temp.getName() == s3.getName() && temp.hasBerth() == s3.hasBerth(), print)) // check list
		failed++;

	temp = list.getNextIsland();
	if (check_a(test, part++, temp.getName() == s2.getName() && temp.hasBerth() == s2.hasBerth(), print)) // check list
		failed++;

	temp = list.getNextIsland();
	if (check_a(test, part++, temp.getName() == s1.getName() && temp.hasBerth() == s1.hasBerth(), print)) // check list
		failed++;

	return failed;
}

// middle remove + getNextIsland
int test7_num_failed(bool print)
{
	int failed = 0;
	int test = 7;
	char part = 'a';

	LinkedList list;
	Island s1("island1", true);
	Island s2("island2", false);
	Island s3("island3", true);
	Island s4("island4", false);
	Island s5("island5", true);

	list.insertIsland(s1);
	list.insertIsland(s2);
	list.insertIsland(s3);
	list.insertIsland(s4);
	list.insertIsland(s5);

	list.removeIsland(s3);

	Island temp;

	temp = list.getNextIsland();
	if (check_a(test, part++, temp.getName() == s5.getName() && temp.hasBerth() == s5.hasBerth(), print)) // check list
		failed++;

	temp = list.getNextIsland();
	if (check_a(test, part++, temp.getName() == s4.getName() && temp.hasBerth() == s4.hasBerth(), print)) // check list
		failed++;

	temp = list.getNextIsland();
	if (check_a(test, part++, temp.getName() == s2.getName() && temp.hasBerth() == s2.hasBerth(), print)) // check list
		failed++;

	temp = list.getNextIsland();
	if (check_a(test, part++, temp.getName() == s1.getName() && temp.hasBerth() == s1.hasBerth(), print)) // check list
		failed++;

	return failed;
}

// last remove + getNextIsland
int test8_num_failed(bool print)
{
	int failed = 0;
	int test = 8;
	char part = 'a';

	LinkedList list;
	Island s1("island1", true);
	Island s2("island2", false);
	Island s3("island3", true);
	Island s4("island4", false);
	Island s5("island5", true);

	list.insertIsland(s1);
	list.insertIsland(s2);
	list.insertIsland(s3);
	list.insertIsland(s4);
	list.insertIsland(s5);

	list.removeIsland(s1);

	Island temp;

	temp = list.getNextIsland();
	if (check_a(test, part++, temp.getName() == s5.getName() && temp.hasBerth() == s5.hasBerth(), print)) // check list
		failed++;

	temp = list.getNextIsland();
	if (check_a(test, part++, temp.getName() == s4.getName() && temp.hasBerth() == s4.hasBerth(), print)) // check list
		failed++;

	temp = list.getNextIsland();
	if (check_a(test, part++, temp.getName() == s3.getName() && temp.hasBerth() == s3.hasBerth(), print)) // check list
		failed++;

	temp = list.getNextIsland();
	if (check_a(test, part++, temp.getName() == s2.getName() && temp.hasBerth() == s2.hasBerth(), print)) // check list
		failed++;

	return failed;
}

// removing + check currpos = NULL
int test9_num_failed(bool print)
{
	int failed = 0;
	int test = 9;
	char part = 'a';

	LinkedList list;
	Island s1("island1", true);
	Island s2("island2", false);

	list.insertIsland(s1);
	list.insertIsland(s2);

	Island temp = list.getNextIsland();
	if (check_a(test, part++, temp.getName() == s2.getName() && temp.hasBerth() == s2.hasBerth(), print))
		failed++;

	list.removeIsland(s1);

	if (check_a(test, part++, list.isCurrPosNull(), print)) // check list
		failed++;

	return failed;
}

// make empty + check currpos = NULL
int test10_num_failed(bool print)
{
	int failed = 0;
	int test = 10;
	char part = 'a';

	LinkedList list;
	Island s1("island1", true);
	Island s2("island2", false);
	Island s3("island3", true);
	Island s4("island4", false);
	Island s5("island5", true);

	list.insertIsland(s1);
	list.insertIsland(s2);
	list.insertIsland(s3);
	list.insertIsland(s4);
	list.insertIsland(s5);

	list.makeEmpty();

	if (check_e(test, part++, list.getLength(), 0, print))
		failed++;

	if (check_a(test, part++, list.isCurrPosNull(), print)) // check list
		failed++;

	return failed;
}

// UTILITIES //

void printPass(int test)
{
	cerr << "test" << test << " passed!" << endl;
}

void printFail(int test, int failed, int expected)
{
	cerr << "test" << test << " failed " << failed << " / " << expected << " parts." << endl;
}

bool check_e(int test, char part, int input, int expected, bool print)
{
	if (input != expected)
	{
		if (print)
			cerr << "test" << test << " part " << part << " failed. Expected "
				 << expected << " but got " << input << "." << endl;
		return true;
	}
	return false;
}

bool check_a(int test, char part, bool assertion, bool print)
{
	if (!assertion)
	{
		if (print)
		{
			cerr << "test" << test << " part " << part << " failed. Expected "
				 << "true"
				 << " but got "
				 << "false"
				 << "." << endl;
		}
		return true;
	}
	return false;
}