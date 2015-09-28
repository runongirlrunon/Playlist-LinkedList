//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file Node.cpp 
    Listing 4-2 */
#include "Node.h"
#include <cstddef>
#include <string>

template<class ItemType>
Node<ItemType>::Node() : next(nullptr), prev(nullptr)
{
} // end default constructor


template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr), prev(nullptr)
{
} // end constructor


template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr, Node<ItemType>* prevNodePtr) :
                item(anItem), next(nextNodePtr), prev(prevNodePtr)
{
} // end constructor


template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem)
{
   item = anItem;
} // end setItem


template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr)
{
    next = nextNodePtr;
} // end setNext


template<class ItemType>
void Node<ItemType>::setPrev(Node<ItemType>* prevNodePtr)
{
    prev = prevNodePtr;
} // end setPrev


template<class ItemType>
ItemType Node<ItemType>::getItem() const
{
   return item;
} // end getItem


template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const
{
   return next;
} // end getNext


template<class ItemType>
Node<ItemType>* Node<ItemType>::getPrev() const
{
    return prev;
} // end getPrev


//  End of implementation file.  Add definitions of template types we will use (int or string):
template class Node<int>;
template class Node<std::string>;
