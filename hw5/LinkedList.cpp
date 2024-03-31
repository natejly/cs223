/*
 * LinkedList.cpp
 * CPSC 223 Pset 5
 *
 * Implementation for Linked List of Islands
 *
 * Author: Nate Ly
 */

#include "LinkedList.h"
#include "NodeType.h"
using namespace std;

// Default constructor
LinkedList::LinkedList()
{
    this->head = NULL;
    this->currPos = NULL;
    this->length = 0;
}

// Destructor
LinkedList::~LinkedList()
{
    NodeType *curr = this->head;
    NodeType *next = NULL;
    // walk and destroy
    while (curr != NULL)
    {
        next = curr->next;
        delete curr;
        curr = next;
    }
    // resetting members
    this->head = NULL;
    this->currPos = NULL;
    this->length = 0;
}
// Assignment operator overload.
LinkedList &LinkedList::operator=(const LinkedList &rhs)
{
    if(this == &rhs){
        return *this;
    }
    if(rhs.head == NULL){
        return *this;
    }
    makeEmpty();
    // initialize pointers starting at head to walk lists
    NodeType *currNode = NULL;
    NodeType *rhsNode = rhs.head;
    // copy rhs head to this head
    head = new NodeType();
    head->info = rhsNode->info;
    head->next = NULL;
    currNode = head;
    // step to next node in RHS and walk and copy
    rhsNode = rhsNode->next;
    while(rhsNode != NULL){
        currNode->next = new NodeType();
        currNode = currNode->next;
        currNode->info = rhsNode->info;
        rhsNode = rhsNode->next;
        currNode->next = NULL;
    }
    this->length = rhs.length;
    return *this;
}
// Copy constructor
LinkedList::LinkedList(const LinkedList &other)
{
    if (other.head == nullptr){
        return;
    }
    // initialize pointers starting at heads 
    NodeType *currNode = NULL;
    NodeType *tempNode = other.head;
    // initilaize this head and copy other head
    head = new NodeType();
    head->info = tempNode->info;
    head->next = NULL;
    currNode = head;
    //step to next node in other and copy into this
    tempNode = tempNode->next;
    // repeat untill we reach end of list
    while (tempNode != NULL)
    {
        currNode->next = new NodeType();
        currNode = currNode->next;
        currNode->info = tempNode->info;
        tempNode = tempNode->next;
        currNode->next = NULL;
    }
    length = other.length;


}

int LinkedList::getLength() const
{
    return this->length;
}

bool LinkedList::isCurrPosNull() const
{
    return this->currPos == NULL;
}

void LinkedList::insertIsland(Island is)
{
    NodeType *newNode = new NodeType();
    newNode->info = is;
    newNode->next = this->head;
    this->head = newNode;
    this->length++;
    this->currPos = newNode;
}
void LinkedList::removeIsland(Island is)
{
    NodeType *curr = this->head;
    NodeType *prev = NULL; // Keep track of the previous node

    while (curr != NULL) {
        if (curr->info.isEqual(is)) {
            // If the node to be removed is the head
            if (prev == NULL) {
                this->head = curr->next;

            } else {
                prev->next = curr->next;
            }
            if (this->currPos == curr) {
                    resetCurrPos();
                }
            delete curr;
            this->length--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}




Island LinkedList::getNextIsland()
{   
    //if we not indexed set to head
    if(this->currPos == NULL){
        this->currPos = this->head;
    }
    //make temp node to return
    NodeType *temp = this->currPos;
    this->currPos = this->currPos->next;
    return temp->info;
}

void LinkedList::resetCurrPos()
{
    this->currPos = NULL;
}

void LinkedList::makeEmpty()
{
    NodeType *curr = this->head;
    NodeType *next = NULL;
    while (curr != NULL)
    {
        next = curr->next;
        delete curr;
        curr = next;
    }
    this->head = NULL;
    this->currPos = NULL;
    this->length = 0;
    resetCurrPos();
}

void LinkedList::print(ostream &out)
{
    NodeType *curr = this->head;
    int stops = this->length - 1;
    while(curr != NULL)
    {
        curr->info.print(out);
        out << " ";
        out << stops;
        stops--;
        if(stops >= 0){
        out << " ~~ ";
        }
        curr = curr->next;
    }
    out << endl;
}

