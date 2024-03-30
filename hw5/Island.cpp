/*
 * Island.cpp
 * CPSC 223 Pset 5
 *
 * Implementation of the Island class
 *
 * Author: Nate Ly
 */

#include "Island.h"
#include <string>

// Default Constructor (Implemented for you)
Island::Island()
{
    this->name = "NoName";
    this->access = false;
}

Island::Island(string name, bool access)
{
    this->name = name;
    this->access = access;
}

bool Island::isEqual(Island other)
{
    return (this->name.compare(other.name) == 0) && (this->access == other.access);
}

void Island::print(ostream &outfile)
{   
    char accessChar = this->access ? 'A' : 'U';
    outfile << this->name << " " << accessChar << endl;
}
