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
    return (this->name.compare(other.getName()) == 0) && (this->access == other.hasBerth());
}

void Island::print(ostream &outfile)
{   
    char access;
    if(this->access){
        access = 'A';
    } else
    {
        access = 'U';
    }
    outfile << this->name << " " << access;
}
