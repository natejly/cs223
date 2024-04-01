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
    this->head = nullptr;
    this->currPos = nullptr;
    this->length = 0;
}

// Destructor
LinkedList::~LinkedList()
{
    NodeType *curr = this->head;
    NodeType *next = nullptr;
    // walk and destroy
    while (curr != nullptr)
    {
        next = curr->next;
        delete curr;
        curr = next;
    }
    // resetting members
    this->head = nullptr;
    this->currPos = nullptr;
    this->length = 0;
}
// Assignment operator overload.
LinkedList &LinkedList::operator=(const LinkedList &rhs)
{
    if(this == &rhs){
        return *this;
    }
    if(rhs.head == nullptr || rhs.length == 0){
        return *this;
    }
    //clear old list
    makeEmpty();
    // initialize pointers starting at head to walk both lists
    NodeType *currNode = nullptr;
    NodeType *rhsNode = rhs.head;
    // copy rhs head to this head
    head = new NodeType();
    head->info = rhsNode->info;
    head->next = nullptr;
    currNode = head;
    // check to update currPos
    if(rhsNode == rhs.currPos){
        this->currPos = currNode;
    }
    // step to next node in RHS and walk and copy
    rhsNode = rhsNode->next;
    while(rhsNode != nullptr){
        currNode->next = new NodeType();
        currNode = currNode->next;
        currNode->info = rhsNode->info;
        // check if we update currentPos
        if(rhsNode == rhs.currPos){
            this->currPos = currNode;
        }
        rhsNode = rhsNode->next;
        currNode->next = nullptr;
    }
    this->length = rhs.length;
    return *this;
}
// Copy constructor
LinkedList::LinkedList(const LinkedList &other)
{
    currPos = nullptr;

    if (other.head == nullptr){
        return;
    }
    // initialize pointers starting at heads 
    NodeType *currNode = nullptr;
    NodeType *tempNode = other.head;
    // initilaize this head and copy other head
    head = new NodeType();
    head->info = tempNode->info;
    head->next = nullptr;
    currNode = head;
    // check to update currPos
    if(tempNode == other.currPos){
        this->currPos = currNode;
    }
    //step to next node in other and copy into this
    tempNode = tempNode->next;
    // repeat untill we reach end of list
    while (tempNode != nullptr)
    {
        currNode->next = new NodeType();
        currNode = currNode->next;
        currNode->info = tempNode->info;
        // check to update currPos
        if(tempNode == other.currPos){
        this->currPos = currNode;
        }
        tempNode = tempNode->next;
        currNode->next = nullptr;
    }
    length = other.length;
}

int LinkedList::getLength() const
{
    return this->length;
}

bool LinkedList::isCurrPosNull() const
{
    return this->currPos == nullptr;
}

void LinkedList::insertIsland(Island is)
{
    NodeType *newNode = new NodeType();
    newNode->info = is;
    newNode->next = this->head;
    this->head = newNode;
    this->length++;
}
void LinkedList::removeIsland(Island is)
{
    NodeType *curr = this->head;
    NodeType *prev = nullptr; // Keep track of the previous node

    while (curr != nullptr) {
        if (curr->info.isEqual(is)) {
            // If the node to be removed is the head
            if (prev == nullptr) {
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
{   if(this->head == nullptr || this->length == 0){
    return Island();
}
    //if we not indexed set to head
    if(this->currPos == nullptr){
        this->currPos = this->head;
    }
    //make temp node to return
    NodeType *temp = this->currPos;
    this->currPos = this->currPos->next;
    return temp->info;
}

void LinkedList::resetCurrPos()
{
    this->currPos = nullptr;
}

void LinkedList::makeEmpty()
{
    NodeType *curr = this->head;
    NodeType *next = nullptr;
    while (curr != nullptr)
    {
        next = curr->next;
        delete curr;
        curr = next;
    }
    this->head = nullptr;
    this->currPos = nullptr;
    this->length = 0;
    resetCurrPos();
}

void LinkedList::print(ostream &out)
{
    NodeType *curr = this->head;
    int stops = this->length - 1;
    while(curr != nullptr)
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

