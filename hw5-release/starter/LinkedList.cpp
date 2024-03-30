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
    while (curr != nullptr)
    {
        next = curr->next;
        delete curr;
        curr = next;
    }
    this->head = nullptr;
    this->currPos = nullptr;
    this->length = 0;
}

// Assignment operator overload.
LinkedList &LinkedList::operator=(const LinkedList &rhs)
{
    if(this == &rhs)
    {
        return *this;
    }
    *this = LinkedList(rhs);
    *this->head = *rhs.head;
    *this->currPos = *rhs.currPos;
    this->length = rhs.length;
    //copying the linked nodes 
    NodeType *rhsCurr = rhs.head;
    NodeType *copyCurr = nullptr;
    while(rhsCurr != nullptr){
        //making new node and copying the attributes
        NodeType *nodeCopy = new NodeType();
        nodeCopy->info = rhsCurr->info;
        nodeCopy->next = nullptr;
        //if head null set new node to head
        if(this->head == nullptr){
            this->head = nodeCopy;
        }
        //append to end of linked list
        else{
            copyCurr->next = nodeCopy;
        }
        //go next node
        copyCurr = nodeCopy;
        rhsCurr = rhsCurr->next;

    }
    
    return *this;

    
}

// Copy constructor
LinkedList::LinkedList(const LinkedList &other)
{
    this->head = nullptr;
    this->currPos = nullptr;
    this->length = 0;
    NodeType *otherCurr = other.head;
    NodeType *copyCurr = nullptr;
    while(otherCurr != nullptr){
        //making new node and copying the attributes
        NodeType *nodeCopy = new NodeType();
        nodeCopy->info = otherCurr->info;
        nodeCopy->next = nullptr;
        //if head null set new node to head
        if(this->head == nullptr){
            this->head = nodeCopy;
        }
        //append to end of linked list
        else{
            copyCurr->next = nodeCopy;
        }
        //go next node
        copyCurr = nodeCopy;
        otherCurr = otherCurr->next;

    }
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
    //traverse to end
    NodeType *curr = this->head;
    while(curr->next != nullptr){
        curr = curr->next;
    }
    //make new node
    NodeType *newNode = new NodeType();
    newNode->info = is;
    newNode->next = nullptr;
    //if head null set new node to head
    if(this->head == nullptr){
        this->head = newNode;
    }
    //append to end of linked list
    else{
        curr->next = newNode;
    }
    this->length++;
    this->currPos = newNode;
}

void LinkedList::removeIsland(Island is)
{
    NodeType *curr = this->head;
    while(curr->next != nullptr){
        //if found island
        if(curr->next->info.isEqual(is)){
            //if node is head
            if(curr == this->head){
                NodeType *temp = this->head;
                this->head = this->head->next;
                delete temp;
                this->length--;
                return;
            }
            NodeType *temp = curr->next;
            //skip node to be deleted
            curr->next = curr->next->next;
            delete temp;
            this->length--;
            return;
        }
        curr = curr->next;
    }
}

Island LinkedList::getNextIsland()
{
    this->currPos = currPos->next;
    return this->currPos->info;
}

void LinkedList::resetCurrPos()
{
        this->currPos = nullptr;
}

void LinkedList::makeEmpty()
{
    delete this;
}

void LinkedList::print(ostream &out)
{
    NodeType *curr = this->head;
    while(curr != nullptr){
        curr->info.print(out);
        out << " " << this->length;
        if(curr->next != nullptr){
            out << " ~~ ";
        }
        else{
            out << endl;
        }
        curr = curr->next;
    }
    if(this->head == nullptr){
        out << endl;
    }
}
