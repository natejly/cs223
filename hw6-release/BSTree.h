/*
 * Filename: BSTree.h
 * Contains: Interface of Naive Binary Search Trees for CPSC 223
 * Part of: Homework assignment "Trees" for CPSC 223
 * Author: Alan Weide
 */

#pragma once

#include <iostream>
#include "BSTNode.h"

class BSTree
{
private:
    /**
     * The root of this tree.
     */
    BSTNode *root;

public:
    /**
     * Default constructor. Creates an empty tree.
     */
    BSTree();

    /**
     * Copy constructor. Creates a new tree as a deep copy of source
     */
    BSTree(const BSTree &source);

    /**
     * Destructor. Frees all memory owned by this.
     */
    ~BSTree();

    /**
     * Assignment overload. Assigns rhs to this by deep copy.
     */
    BSTree &operator=(const BSTree &rhs);

    /**
     * Reports whether this is a valid Binary Search Tree
     *
     * @param this the tree
     * @return true if this is a valid Binary Search Tree, false otherwise
     */
    bool is_valid() const;

    /**
     * @param this the tree
     * @return the minimum value in this
     * @result Searches this for its minimum value, and returns it
     * @assumes this is not empty
     */
    int minimum_value() const;

    /**
     * @param this the tree
     * @return the minimum value in this
     * @result Searches this for its maximum value, and returns it
     * @assumes this is not empty
     */
    int maximum_value() const;

    /**
     * @param this the tree
     * @param value the value to search for
     * @return the number of occurences of value in this, or 0 if value is not
     *  in this
     */
    int count_of(int value) const;

    /**
     * @param this the tree
     * @param value the value to insert
     * @result Inserts value into this, either by creating a new node or, if
     *  value is already in this, by incrementing that node's multiplicity
     */
    void insert(int value);

    /**
     * @param this the tree
     * @param value the value to remove
     * @result Removes value from the tree. If a node's multiplicity is greater than
     *  1, the multiplicity is decremented and the node is not removed. Nodes with a
     *  multiplicity of 1 are removed according to the algorithm discussed in class.
     *  Does nothing if value is not in the tree.
     */
    void remove(int value);

    /**
     * @param this the tree
     * @return the height of this (an empty tree has height -1)
     */
    int tree_height() const;

    /**
     * @param this the tree
     * @return The number of nodes in this tree
     */
    int node_count() const;

    /**
     * @param this the tree
     * @return the total of all node counts, including duplicates.
     */
    int count_total() const;

    /**
     * @param this the tree
     * @result Pretty-prints the tree
     */
    void print_tree() const;

    friend std::ostream &operator<<(std::ostream &os, const BSTree &tree);
};
