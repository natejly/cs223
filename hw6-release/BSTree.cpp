/*
 * Filename: BSTree.cpp
 * Contains: Implementation of Naive Binary Search Trees for CPSC 223
 * Part of: Homework assignment "Trees" for CPSC 223
 */

#include "BSTree.h"

#include <iostream>
#include <cassert>

#include "BSTNodePrinter.h"
#include "BSTNodeChecker.h"

/*
 * The BSTree constructors use intializer lists. They are complete and you
 *  should not modify them.
 *
 * More info here: https://en.cppreference.com/w/cpp/language/constructor
 */
BSTree::BSTree() : root(new BSTNode()) {}

BSTree::BSTree(const BSTree &source)
    : root(new BSTNode(*source.root)) {}

BSTree::~BSTree()
{
    delete this->root;
}

BSTree &BSTree::operator=(const BSTree &source)
{
#pragma message "TODO: Students write code here"
    // Check for self-assignment

    // Delete existing tree, if it exists

    // Copy root from source.root, if it exists

    // Don't forget to return *this
    return *this;
}

bool BSTree::is_valid() const
{
    BSTNodeChecker checker;
    return checker.is_bst(this->root);
}

int BSTree::minimum_value() const
{
    return this->root->minimum_value()->data();
}

int BSTree::maximum_value() const
{
    return this->root->maximum_value()->data();
}

int BSTree::count_of(int value) const
{
    return this->root->search(value)->count();
}

void BSTree::insert(int value)
{
    this->root = this->root->bst_insert(value);
}

void BSTree::remove(int value)
{
    this->root = this->root->bst_remove(value);
}

int BSTree::tree_height() const
{
    return this->root->height();
}

int BSTree::node_count() const
{
    return this->root->node_count();
}

int BSTree::count_total() const
{
    return this->root->count_total();
}

void BSTree::print_tree() const
{
    BSTNodePrinter printer(std::cout);
    printer.print_pretty(this->root, 1, 0);
}

std::ostream &operator<<(std::ostream &os, const BSTree &tree)
{
    BSTNodePrinter printer(os);
    printer.print_pretty(tree.root, 1, 0);
    return os;
}
