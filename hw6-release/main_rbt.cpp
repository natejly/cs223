/*
 * main_rbt.cpp
 *
 *  Main driver for testing the RBTree class
 */

#include <iostream>
#include "RBTree.h"

using namespace std;

void print_tree_details(RBTree &t)
{
        t.print_tree();
        cout << "\n";
        cout << "min: " << t.minimum_value() << "\n";
        cout << "max: " << t.maximum_value() << "\n";
        cout << "nodes: " << t.node_count() << "\n";
        cout << "count total: " << t.count_total() << "\n";
        cout << "tree height: " << t.tree_height() << "\n";
        cout << "\n";
}

int main()
{
        RBTree t;
        int values[] = {4, 2, 11, 15, 9, 1, -6, 5, 3, 15, 2, 5, 13, 14};
        int num_values = sizeof(values) / sizeof(int);

        for (int i = 0; i < num_values; i++)
        {
                t.insert(values[i]);
                // t.print_tree();
        }
        cout << "Original tree "
             << "(asterisk or capital 'R' denote a multiplicity of more than 1;\n"
             << "\t'r' or 'R' denote RED node):\n";
        print_tree_details(t);

        // make a copy with copy constructor
        RBTree t_copy_constructor = t;
        // cout << "\nPrinting copied tree (by constructor):" << endl;
        // t_copy_constructor.print_tree();

        // make a copy with assignment overload
        RBTree t_copy_1;
        t_copy_1 = t;
        // cout << "\nPrinting copied tree (by assignment):" << endl;
        // t_copy_1.print_tree();

        // remove a node with one children
        cout << "Removing 9 from original tree:\n";
        t.remove(9);
        print_tree_details(t);

        t = t_copy_1;

        // remove a node with one child
        cout << "Removing 1 from original tree:\n";
        t.remove(1);
        print_tree_details(t);

        t = t_copy_1;

        // remove a node with one child
        cout << "Removing 11 from original tree:\n";
        t.remove(11);
        print_tree_details(t);

        t = t_copy_1;

        // remove a node with one child (but the multiplicity is 2)
        cout << "Removing 5 from original tree "
             << "(should still have one 5):\n";
        t.remove(5);
        print_tree_details(t);

        t = t_copy_1;

        // remove a red node with no children
        cout << "Removing 3 from original tree:\n";
        t.remove(3);
        print_tree_details(t);

        t = t_copy_1;

        // remove a black node with no children
        cout << "Removing -6 from original tree:\n";
        t.remove(-6);
        print_tree_details(t);

        t = t_copy_1;

        // check if the tree contains values
        for (int i = -10; i < 20; i++)
        {
                cout << "Original Tree "
                     << (t.count_of(i) > 0 ? "contains " : "does not contain ")
                     << "the value " << i << "\n";
        }
        cout << "\nFinished!\n";
        return 0;
}
