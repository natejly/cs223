/*
 * Island.cpp
 * CPSC 223 Pset 5
 *
 * Implementation of the Island class
 *
 * Author: Nate Ly 
 * Modified on 3/31/24
 */

#include "Island.h"
#include <string>
//basic island constructor
Island::Island()
{
    this->name = "NoName";
    this->access = false;
}
//island constructor with parameters
Island::Island(string name, bool access)
{
    this->name = name;
    this->access = access;
}
//checks if two islands are equal
bool Island::isEqual(Island other)
{
    return (this->name.compare(other.getName()) == 0) && (this->access == other.hasBerth());
}
//prints island
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
