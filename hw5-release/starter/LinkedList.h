#pragma once

/*
 * LinkedList.h
 * CPSC 223 Pset 5
 *
 * Interface for Linked List of Islands
 *
 * TO STUDENT: You may ONLY modify this file by adding private members!
 * The only exception is the TODO on line 30, which is part of an optional
 *  additional activity.
 */

#include "NodeType.h"
#include "Island.h"
#include <fstream>

/**
 * Class for a linked list of Islands. The (abstract) state of a LinkedList is
 *  a sequence of Islands.
 * Besides this itself (which is a sequence of Islands), there are two
 *  (abstract) properties of a LinkedList:
 *      this.length
 *          the number of Islands in the list
 *      this.currPos
 *          a cursor into the list, which is NULL if it has never been used or
 *          if it has just been reset or if it has traveled past the end of the
 *          list. Otherwise it is an island that is in the list.
 *
 * TODO: The above comment describes the ABSTRACT state of a list. The CONCRETE
 *  state (i.e., the private members) may differ slightly, significantly, or
 *  not at all. Describe the "abstraction function" for this list: how does a
 *  particular set of values of the private members translate to an abstract
 *  value? Importantly: in which order do the nodes of the linked list map to
 *  the sequence in the abstract state?
 * NOTE: This is part of an optional additional activity.
 *
 * Abstraction Function: [describe abstraction function here]
 */
class LinkedList
{
public:
    /**
     * Default constructor.
     *
     * Creates a new, empty LinkedList with NULL currPos
     */
    LinkedList();

    /**
     * Destructor.
     * Frees all memory owned by `this`.
     */
    ~LinkedList();

    /**
     * Assignment operator overload. Performs a deep copy of the list referred
     *  to by `rhs` into `this`.
     *
     * @param rhs reference to the list on the right-hand side of the
     *  assignment statement
     * @return a reference to `this`, a copy of `rhs`.
     */
    LinkedList &operator=(const LinkedList &rhs);

    /**
     * Copy constructor.
     *
     * Creates a new list that is a deep copy of `other`.
     *
     * @param other reference to the list to copy to create `this`
     */
    LinkedList(const LinkedList &other);

    /**
     * Inserts an island at the front of `this`. After this function:
     *  `this` is `is` followed by the Islands that were in
     *  `this` before this function was called, and
     *  `this.currPos` is unchanged
     *
     * @param is the Island to insert.
     */
    void insertIsland(Island is);

    /**
     * Removes from `this` the first Island in `this` that is equal to `is`.
     *
     * This method removes the first Island equal to `is` from `this`, and
     *  deallocates the memory owned by the removed Island as well as any
     *  memory allocated by `this` to manage the Island.
     *
     * If the removed Island is `this.currPos`, then the method resets
     *  `this.currPos`.
     *
     * If `is` is not in `this`, then the method does nothing (including not
     *  changing any state of `this`).
     *
     * @param is the Island to remove
     */
    void removeIsland(Island is);

    /**
     * Removes all Islands from `this` and dellocates all memory owned by
     *  those Islands and all memory allocated by `this` to manage each
     *  Island.
     *
     * This method resets `this.currPos`.
     */
    void makeEmpty();

    /**
     * Resets `this.currPos`. In other words, sets `this.currPos` to NULL.
     */
    void resetCurrPos();

    /**
     * Returns the island `this.currPos` and advances `this.currPos` to the
     *  next island in the list.
     *
     * If `this.currPos` is NULL, then this function behaves as though
     *  `this.currPos` was the first island in the list.
     *
     * If there are no islands in the list, the behavior of this function is
     *  undefined.
     *
     * @return the next Island in `this`
     */
    Island getNextIsland();

    /**
     * Reports whether `this.currPos` is NULL.
     *
     * @return (this.currPos = nullptr)
     */
    bool isCurrPosNull() const;

    /**
     * Reports the number of Islands in `this`.
     */
    int getLength() const;

    /**
     * Prints `this` as a formatted list of Islands to the stream referenced
     *  by `out`.
     *
     * For each Island in `this`, proceeding sequentially, print the following
     *  for each of them:
     *  1. The name and accessibility level of the Island
     *  2. A single space
     *  3. The number of remaining stops in the list
     *  4. If there is a next island, the string " ~~ " (note the space before
     *      and after the "waves" ~~)
     *  5. If there is no next island, a single newline character
     *
     * If there are no Islands in `this`, print a single newline character.
     *
     * @param out the stream to which to print this list
     */
    void print(ostream &out);

private:
};
