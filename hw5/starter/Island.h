#pragma once
/*
 * Island.h
 * CPSC 223 Pset 5
 *
 * Interface for Island class
 *
 */

#include <fstream>
#include <string>
using namespace std;

/**
 * Type representing an Island. The state of a Island consists of:
 *  name
 *      the name of this island, a string
 *  access
 *      a boolean that is true if this island is accessible by ship; false
 *      otherwise
 */
class Island
{
public:
    /**
     * Default constructor.
     * Creats a Island with name "NoName" and accessibility "false".
     */
    Island();

    /**
     * Parameterized constructor.
     * Creates a island with name `name` and accessibility `access`.
     *
     * @param name the name of the new Island
     * @param access the accessibility of the new Island
     */
    Island(string name, bool access);

    /**
     * Prints this Island's name and accessibility level to `out`.
     * Format of output is `this.name` followed by a single space, followed by
     *  the accessibility level of `this`, which is either 'A' (if this is
     *  accessible) or 'U' (if this is not accessible).
     *
     * @param out the stream to which to print this Island's information
     */
    void print(ostream &out);

    /**
     * Reports whether `this` Island is equal to `other`.
     * Two islands are equal if their name and accessibility levels are both
     *  equal.
     *
     * @param other the Island to which to compare `this`
     * @return (this = other)
     */
    bool isEqual(Island other);

    /**
     * Getter for `this` Island's accessiblity; implemented for you.
     *
     * @return this.access
     */
    bool hasBerth()
    {
        return access;
    };

    /**
     * Getter for `this` Island's name; implemented for you.
     *
     * @return this.name
     */
    string getName()
    {
        return name;
    }

private:
    string name;
    bool access;
};
