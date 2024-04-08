/*
 * Filename: AVLTree.cpp
 * Contains: Implementation of AVL Trees for CPSC 223
 * Part of: Homework assignment "Trees" for CPSC 223
 */

#include "AVLTree.h"

#include <iostream>
#include <cassert>

#include "BSTNodePrinter.h"
#include "BSTNodeChecker.h"

/*
 * The AVLTree constructors use intializer lists. They are complete and you
 *  should not modify them.
 *
 * More info here: https://en.cppreference.com/w/cpp/language/constructor
 */
AVLTree::AVLTree() : root(new BSTNode()) {}

AVLTree::AVLTree(const AVLTree &source)
    : root(new BSTNode(*source.root)) {}

AVLTree::~AVLTree()
{
    delete this->root;
}

AVLTree &AVLTree::operator=(const AVLTree &source)
{
#pragma message "TODO: Students write code here"
    // Check for self-assignment

    // Delete existing tree, if it exists

    // Copy root from source.root, if it exists

    // Don't forget to return *this
    return *this;
}

bool AVLTree::is_valid() const
{
    BSTNodeChecker checker;
    return checker.is_avlt(this->root);
}

int AVLTree::minimum_value() const
{
    return this->root->minimum_value()->data();
}

int AVLTree::maximum_value() const
{
    return this->root->maximum_value()->data();
}

int AVLTree::count_of(int value) const
{
    return this->root->search(value)->count();
}

void AVLTree::insert(int value)
{
    this->root = this->root->avl_insert(value);
}

void AVLTree::remove(int value)
{
    this->root = this->root->avl_remove(value);
}

int AVLTree::tree_height() const
{
    return this->root->height();
}

int AVLTree::node_count() const
{
    return this->root->node_count();
}

int AVLTree::count_total() const
{
    return this->root->count_total();
}

void AVLTree::print_tree() const
{
    BSTNodePrinter printer(std::cout);
    printer.print_pretty(this->root, 1, 0);
}

std::ostream &operator<<(std::ostream &os, const AVLTree &tree)
{
    BSTNodePrinter printer(os);
    printer.print_pretty(tree.root, 1, 0);
    return os;
}
