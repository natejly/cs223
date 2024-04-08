/*
 * Filename: RBTree.cpp
 * Contains: Implementation of Red-Black Trees for CPSC 223
 * Part of: Homework assignment "Trees" for CPSC 223
 */

#include "RBTree.h"

#include <iostream>
#include <cassert>

#include "BSTNodePrinter.h"
#include "BSTNodeChecker.h"

/*
 * The RBTree constructors use intializer lists. They are complete and you
 *  should not modify them.
 *
 * More info here: https://en.cppreference.com/w/cpp/language/constructor
 */
RBTree::RBTree() : root(new BSTNode()) {}

RBTree::RBTree(const RBTree &source)
    : root(new BSTNode(*source.root)) {}

RBTree::~RBTree()
{
    delete this->root;
}

RBTree &RBTree::operator=(const RBTree &source)
{
#pragma message "TODO: Students write code here"
    // Check for self-assignment

    // Delete existing tree, if it exists

    // Copy root from source.root, if it exists

    // Don't forget to return *this
    return *this;
}

bool RBTree::is_valid() const
{
    BSTNodeChecker checker;
    return checker.is_rbt(this->root);
}

int RBTree::minimum_value() const
{
    return this->root->minimum_value()->data();
}

int RBTree::maximum_value() const
{
    return this->root->maximum_value()->data();
}

int RBTree::count_of(int value) const
{
    return this->root->search(value)->count();
}

void RBTree::insert(int value)
{
    this->root = this->root->rbt_insert(value);
}

void RBTree::remove(int value)
{
    this->root = this->root->rbt_remove(value);
}

int RBTree::tree_height() const
{
    return this->root->height();
}

int RBTree::node_count() const
{
    return this->root->node_count();
}

int RBTree::count_total() const
{
    return this->root->count_total();
}

void RBTree::print_tree() const
{
    BSTNodePrinter printer(std::cout);
    printer.print_pretty(this->root, 1, 0);
}

std::ostream &operator<<(std::ostream &out, const RBTree &tree)
{
    BSTNodePrinter printer(out);
    printer.print_pretty(tree.root, 1, 0);
    return out;
}
