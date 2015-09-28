//
//  main.cpp
//  Playlist-LinkedList
//  Array-based List Class for Playlists
//

#include <string>
#include <iostream>
#include <stdexcept>

#include "ListInterface.h"
#include "LinkedList.h"
#include "Node.h"
using namespace std;

/*
// This is the array-based implementation of the ADT List. 
 
template<class ItemType>
class List
{
private:
    static const int CHUNK_SIZE=5;
    ItemType *list;
    int numItems;
    int maxItems;
public:
    // default constructor and destructor
    List() {
        numItems = 0;
        maxItems = CHUNK_SIZE;
        list = new ItemType[CHUNK_SIZE];
    }
    ~List() {
        delete [] list;
    }
    
    // list member functions
    bool isEmpty() {
        return numItems==0;
    }
    int getLength() {
        return numItems;
    }
    int getMaxItems() {
        return maxItems;
    }
    bool insert(int pos, const ItemType& item);
    bool remove(int pos);
    void reverse();
    
    // clear can simply set numItems to zero.  The array list may still contain
    // items already inserted into the list, but since numItems is zero, there
    // isn't any way to get at them using getEntry() or setEntry()
    void clear() {
        numItems = 0;
    }
    
    // throw invalid_argument if pos<1 or pos>getLength()
    ItemType getEntry(int pos) const throw(invalid_argument);
    
    // throw invalid_argument if pos<1 or pos>getLength()
    void setEntry(int pos, const ItemType& item) throw(invalid_argument);
};

template<class ItemType>
bool List<ItemType>::insert(int pos, const ItemType& item)
{
    bool canAdd;
    
    canAdd = ((pos > 0) && (pos <= numItems + 1) && (numItems < maxItems));
    
    if (canAdd)
    {
        // first, we have to move everything after our insertion point over one
        // position to make room for our new item.  start at the back of the list.
        // don't forget arrays start at postion zero and our list ADT starts at
        // position 1.
        for(int i=numItems; i>=pos; i--)
            list[i] = list[i-1];
        
        // now put our item at position pos-1
        list[pos-1] = item;
        
        numItems++;
    }
    
    else {
        cout << "Not enough memory! Allocating more..." << endl;
        // make a new tempList to hold list items
        ItemType *tempList= new ItemType[maxItems + CHUNK_SIZE];
        
        // move all the items from list onto tempList
        for (int i = 0; i<maxItems; i++){
            tempList[i] = list[i];
        }
        
        // update maxItems
        maxItems = maxItems + CHUNK_SIZE;
        
        // create new array in memory for list
        list = new ItemType[maxItems];
        
        // move all the items back to list
        for (int i = 0; i<maxItems; i++){
            list[i] = tempList[i];
        }
        
        delete [] tempList;
        
        // now that the memory is bigger, call the function again to insert the item
        this->insert(pos, item);
    }
    
    return canAdd;
} // end insert

template<class ItemType>
ItemType List<ItemType>::getEntry(int pos) const throw(invalid_argument)
{
    if(pos<1 || pos>numItems) {
        throw invalid_argument("ERROR: getEntry() using invalid position");
    }
    return list[pos-1];
} // end getEntry

template<class ItemType>
void List<ItemType>::setEntry(int pos, const ItemType& item) throw(invalid_argument){
    if(pos<1 || pos>numItems) {
        throw invalid_argument("ERROR: setEntry() using invalid position");
    }
    list[pos-1] = item;
} // end setEntry

template<class ItemType>
bool List<ItemType>::remove(int pos){
    bool canRemove;
    canRemove = ((pos > 0) && (pos <= numItems + 1) && (numItems < maxItems));
    
    if (canRemove) {
        for(; pos<numItems; pos++){
            this->setEntry(pos, this->getEntry(pos+1));
        }
    }
    
    // adjust numItems to reflect new size of list
    numItems--;
    
    return canRemove;
} */

// Utility function to input a track number with some input checking
// to make sure it's a number
int getTrack()
{
    bool inputCheck;
    int trackNumber;
    
    do
    {
        inputCheck = true;
        cout << "Please enter the track number you'd like to view: ";
        if (!(cin >> trackNumber))
        {
            cout << "Please enter numbers only.\n";
            cin.clear();
            cin.ignore(10000,'\n');
            inputCheck = false;
        }
    } while (!inputCheck);
    return trackNumber;
}

int main()
{
    LinkedList<string> songs;
    char goAgain = 'y';
    int trackNumber;
    string trackName;
    
    // Insert some songs into our list
    songs.insert(1, "One More Saturday Night");
    songs.insert(1, "Friday I'm in Love");
    songs.insert(3, "Sunday Morning Coming Down");
    songs.insert(1, "California Love");
    
    cout << "Welcome!  There are " << songs.getLength() << " tracks.\n";
    while (goAgain!='n')
    {
        trackNumber = getTrack();
        try
        {
            trackName = songs.getEntry(trackNumber);
        }
        catch (invalid_argument arg)
        {
            cout << arg.what() << endl;
            trackName = "No Track";
        }
        cout << "Your track name is " << trackName << endl;
        cout << "Go again? (y/n) ";
        cin >> goAgain;
    }
    
    // DEBUG SECTION 1: Testing setEntry function
    
    cout << endl << "**Debugging** Now using setEntry to change song #1 to Boiled Frogs." << endl;
    songs.setEntry(1, "Boiled Frogs");
    cout << "Playlist now has " << songs.getLength() << " tracks in this order: " << endl;
    for (int i = 0; i<songs.getLength(); i++) {
        cout << "Track #" << i+1 << ": " << songs.getEntry(i+1) << endl;
    }
    cout << endl;
    
    // DEBUG SECTION 2: Testing remove function
    cout << "**Debugging** Now using remove to delete track #3." << endl;
    songs.remove(3);
    cout << "Playlist now has " << songs.getLength() << " tracks in this order: " << endl;
    for (int i = 0; i<songs.getLength(); i++) {
        cout << "Track #" << i+1 << ": " << songs.getEntry(i+1) << endl;
    }
    cout << endl;
    
    // DEBUG SECTION 3: Testing insert function with full list (CHUNK_SIZE is now 5 for testing of this function without taking up a hundred lines of code...)
    // This section is used with the array-based ADT List.
    /*
    cout << "**Debugging** Now using updated insert function to allocate more memory." << endl;
    cout << "Adding song: Phoenix in Flight" << endl;
    songs.insert(1, "Phoenix In Flight");
    cout << "Playlist can hold " << songs.getMaxItems() << " songs." << endl;
    cout << "Adding song: Waiting Room" << endl;
    songs.insert(1, "Waiting Room");
    cout << "Playlist can hold " << songs.getMaxItems() << " songs." << endl;
    cout << "Adding song: Holland, 1945" << endl;
    songs.insert(1, "Holland, 1945");
    cout << "Playlist can hold " << songs.getMaxItems() << " songs." << endl << endl;
    
    cout << "Playlist now has " << songs.getLength() << " tracks in this order: " << endl;
    for (int i = 0; i<songs.getLength(); i++) {
        cout << "Track #" << i+1 << ": " << songs.getEntry(i+1) << endl;
    }
    cout << endl;
     */
    
    // DEBUG SECTION 3.1: Testing insert function for ADT LinkedList.
    cout << "**Debugging** Now using insert function to extend list." << endl;
    cout << "Adding song: Phoenix in Flight" << endl;
    songs.insert(1, "Phoenix In Flight");
    cout << "Adding song: Waiting Room" << endl;
    songs.insert(1, "Waiting Room");
    cout << "Adding song: Holland, 1945" << endl;
    songs.insert(1, "Holland, 1945");
    
    cout << endl;
    cout << "Playlist now has " << songs.getLength() << " tracks in this order: " << endl;
    for (int i = 0; i<songs.getLength(); i++) {
        cout << "Track #" << i+1 << ": " << songs.getEntry(i+1) << endl;
    }
    cout << endl;
    
    // DEBUG SECTION 4: Testing reverse function.
    cout << "**Debugging** Now using reverse function to reverse all songs." << endl;
    songs.reverse();
    
    cout << "Playlist now has " << songs.getLength() << " tracks in this order: " << endl;
    for (int i = 0; i<songs.getLength(); i++) {
        cout << "Track #" << i+1 << ": " << songs.getEntry(i+1) << endl;
    }
    cout << endl;
    
    cout << "Rock on!\n";
    return 0;
}

