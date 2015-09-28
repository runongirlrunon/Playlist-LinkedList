//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** Implementation file for the class LinkedList.
 @file LinkedList.cpp */

#include "LinkedList.h"  // Header file
#include <cassert>
#include <string>
#include <cstdlib>
#include <iostream>

template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), tailPtr(nullptr), itemCount(0)
{
    headPtr = nullptr;
    tailPtr = nullptr;
    itemCount = 0;
}  // end default constructor


template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList) : itemCount(aList.itemCount)
{
    Node<ItemType>* origChainPtr = aList.headPtr;  // Points to nodes in original chain

    if (origChainPtr == nullptr)
    {
        headPtr = nullptr;  // Original list is empty
        tailPtr = nullptr;
    }
    else
    {
        // Copy first node
        headPtr = new Node<ItemType>();
        headPtr->setItem(origChainPtr->getItem());
      
        // Copy remaining nodes
        Node<ItemType>* newChainPtr = headPtr;      // Points to last node in new chain
        origChainPtr = origChainPtr->getNext();     // Advance original-chain pointer
        while (origChainPtr != nullptr)
        {
            // Get next item from original chain
            ItemType nextItem = origChainPtr->getItem();
         
            // Create a new node containing the next item
            Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
         
            // Link new node to end of new chain
            newChainPtr->setNext(newNodePtr);
         
            // Advance pointer to new last node
            newChainPtr = newChainPtr->getNext();
         
            // Advance original-chain pointer
            origChainPtr = origChainPtr->getNext();
        }  // end while
      
        newChainPtr->setNext(nullptr);              // Flag end of chain
    }  // end if
}  // end copy constructor


template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
    clear();
}  // end destructor


template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
    return itemCount == 0;
}  // end isEmpty


template<class ItemType>
int LinkedList<ItemType>::getLength() const
{
    return itemCount;
}  // end getLength


template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
    bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
    if (ableToInsert)
    {
        // Create a new node containing the new entry
        Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
        
        if ((newPosition == 1) && (getLength() == 0)) {
            // case for first item on empty list
            headPtr = newNodePtr;
            newNodePtr->setNext(nullptr);
            newNodePtr->setPrev(nullptr);
            tailPtr = newNodePtr;
        }
        else if ((newPosition == 1) && (getLength() > 0))
        {
            // case for first item on non-empty list
            Node<ItemType>* nextPtr = getNodeAt(newPosition);
            newNodePtr->setNext(headPtr);
            newNodePtr->setPrev(nullptr);
            nextPtr->setPrev(newNodePtr);
            headPtr = newNodePtr;
        }
        else if ((newPosition > 1) && (newPosition < itemCount))
        {
            // case for item on non-empty list, not in last place
            // Create node pointers to hold our place in the chain
            Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);
            Node<ItemType>* nextPtr = getNodeAt(newPosition);
        
            // Attach the new node between prevPtr and nextPtr
            newNodePtr->setNext(prevPtr->getNext());
            newNodePtr->setPrev(nextPtr->getPrev());
        
            // Re-point the pointers for prevPtr and nextPtr to the new node
            prevPtr->setNext(newNodePtr);
            nextPtr->setPrev(newNodePtr);
        }
        else if (newPosition == itemCount + 1){
            // special case for last item on non-empty list
            Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);
            newNodePtr->setPrev(tailPtr);
            newNodePtr->setNext(nullptr);
            prevPtr->setNext(newNodePtr);
            tailPtr = newNodePtr;
        }
        itemCount++;  // Increase count of entries
    }  // end if
   
    return ableToInsert;
}  //end insert


template<class ItemType>
bool LinkedList<ItemType>::remove(int position)
{
    bool ableToRemove = (position >= 1) && (position <= itemCount);
    if (ableToRemove)
    {
        // point at the node to be removed
        Node<ItemType>* curPtr = getNodeAt(position);
        
        // case 1: to remove the only node on a list of length 1
        if ((position == 1) && (itemCount == 1)) {
            headPtr = nullptr;
            tailPtr = nullptr;
        }
        
        // case 2: to remove the first node in list of length > 1
        else if ((position == 1) && (itemCount > 1))
        {
            Node<ItemType>* nextPtr = getNodeAt(position + 1);
            nextPtr->setPrev(nullptr);
            headPtr = nextPtr;
            nextPtr = nullptr;
        }
        
        // case 3: to remove the last node in list of length > 1
        else if ((position == itemCount) && (itemCount > 1))
        {
            Node<ItemType>* prevPtr = getNodeAt(position - 1);
            prevPtr->setNext(nullptr);
            tailPtr = prevPtr;
            prevPtr = nullptr;
        }
        
        // case 4: to remove a node in the middle of list of length > 1
        else if ((1 < position) && (position < itemCount) && (1 < itemCount) )
        {
            // Create node pointers to hold our place in the chain
            Node<ItemType>* prevPtr = getNodeAt(position - 1);
            Node<ItemType>* nextPtr = getNodeAt(position + 1);
         
            // Disconnect indicated node from chain by connecting the
            // previous node with the next node
            prevPtr->setNext(nextPtr);
            nextPtr->setPrev(prevPtr);
        }  // end if
        
        // Return node to system
        curPtr->setNext(nullptr);
        curPtr->setPrev(nullptr);
        delete curPtr;
        curPtr = nullptr;
      
        itemCount--;  // Decrease count of entries
    }  // end if
   
    return ableToRemove;
}  // end remove


template<class ItemType>
void LinkedList<ItemType>::reverse()
{
    // create two dummy pointers to keep our place on the chain
    Node<ItemType>* cur = headPtr;
    Node<ItemType>* temp = nullptr;

    while (cur != NULL) {
        // trade all the pointers up to tailPtr using tempPtr
        temp = cur->getNext();
        cur->setNext(cur->getPrev());
        cur->setPrev(temp);
        cur = cur->getPrev();
    }
    
    // now swap each end pointer
    std::swap(headPtr, tailPtr);
    
}  // end reverse


template<class ItemType>
void LinkedList<ItemType>::clear()
{
    while (!isEmpty())
        remove(1);
}  // end clear


template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcep)
{
    // Enforce precondition
    bool ableToGet = (position >= 1) && (position <= itemCount);
    if (ableToGet)
    {
        Node<ItemType>* nodePtr = getNodeAt(position);
        return nodePtr->getItem();
    }
    else
    {
        string message = "getEntry() called with an empty list or ";
        message  = message + "invalid position.";
        throw(PrecondViolatedExcep(message));
    }  // end if
}  // end getEntry


template<class ItemType>
void LinkedList<ItemType>::setEntry(int position, const ItemType& newEntry) throw(PrecondViolatedExcep)
{
    // Enforce precondition
    bool ableToSet = (position >= 1) && (position <= itemCount);
    if (ableToSet)
    {
        Node<ItemType>* nodePtr = getNodeAt(position);
        nodePtr->setItem(newEntry);
    }
    else
    {
        string message = "setEntry() called with an invalid position.";
        throw(PrecondViolatedExcep(message));
    }  // end if
}  // end setEntry


template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const
{
    // Debugging check of precondition
    assert( (position >= 1) && (position <= itemCount) );
   
    // Count from the beginning of the chain
    Node<ItemType>* curPtr = headPtr;
    for (int skip = 1; skip < position; skip++)
        curPtr = curPtr->getNext();
      
    return curPtr;
}  // end getNodeAt


// End of implementation file.  To get this to compile on hills,
// add definitions of template types we will use (int or string now,
// add more types if necessary)
template class LinkedList<int>;
template class LinkedList<std::string>;
