#ifndef H_UnorderedLinkedList
#define H_UnorderedLinkedList

//***********************************************************
// Author: D.S. Malik
//
// This class specifies the members to implement the basic
// properties of an unordered linked list. This class is
// derived from the class linkedListType.
//***********************************************************

#include "linkedList.h"

using namespace std;

template <class Type>
class unorderedLinkedList : public linkedListType<Type>
{
public:
    bool search(const Type& searchItem) const;
      //Function to determine whether searchItem is in the list.
      //Postcondition: Returns true if searchItem is in the list,
      //    otherwise the value false is returned.

    void insertFirst(const Type& newItem);
      //Function to insert newItem at the beginning of the list.
      //Postcondition: first points to the new list, newItem is
      //    inserted at the beginning of the list, last points to
      //    the last node, and count is incremented by 1.

    void insertLast(const Type& newItem);
      //Function to insert newItem at the end of the list.
      //Postcondition: first points to the new list, newItem is
      //    inserted at the end of the list, last points to the
      //    last node, and count is incremented by 1.

    void deleteNode(const Type& deleteItem);
      //Function to delete deleteItem from the list.
      //Postcondition: If found, the node containing deleteItem
      //    is deleted from the list. first points to the first
      //    node, last points to the last node of the updated
      //    list, and count is decremented by 1.

    // ==== Lab 5 functions ====
    void deleteSmallest() override;
      //Deletes the smallest element (first occurrence).

    void deleteAll(const Type& item) override;
      //Deletes all occurrences of item in the list.

    Type getKthElement(int k) const override;
      //Returns the info in the kth node (1-indexed).
      //Terminates program if k is invalid.

    void deleteKthElement(int k) override;
      //Deletes the kth node in the list.
      //Prints message if invalid.

    void rotate() override;
      //Moves the first node to the end of the list.
    // =========================
};


//***********************************************************
// Author: D.S. Malik
//
// Member function definitions
//***********************************************************

template <class Type>
bool unorderedLinkedList<Type>::search(const Type& searchItem) const
{
    nodeType<Type>* current; //pointer to traverse the list
    bool found = false;

    current = this->first; //set current to point to the first node

    while (current != NULL && !found) //search the list
        if (current->info == searchItem) //searchItem is found
            found = true;
        else
            current = current->link; //advance current

    return found;
}//end search


template <class Type>
void unorderedLinkedList<Type>::insertFirst(const Type& newItem)
{
    nodeType<Type>* newNode; //pointer to create the new node

    newNode = new nodeType<Type>; //create the new node
    newNode->info = newItem;      //store the new item in the node
    newNode->link = this->first;  //insert newNode before first
    this->first = newNode;        //make first point to new node
    this->count++;                //increment count

    if (this->last == NULL)       //if the list was empty,
        this->last = newNode;     //newNode is also the last node
}//end insertFirst


template <class Type>
void unorderedLinkedList<Type>::insertLast(const Type& newItem)
{
    nodeType<Type>* newNode; //pointer to create the new node

    newNode = new nodeType<Type>; //create the new node
    newNode->info = newItem;      //store the new item
    newNode->link = NULL;         //set link field to NULL

    if (this->first == NULL)      //if the list is empty
    {
        this->first = newNode;
        this->last = newNode;
        this->count++;            //increment count
    }
    else                          //the list is not empty
    {
        this->last->link = newNode; //insert after last
        this->last = newNode;       //update last
        this->count++;
    }
}//end insertLast


template <class Type>
void unorderedLinkedList<Type>::deleteNode(const Type& deleteItem)
{
    nodeType<Type>* current;       //pointer to traverse the list
    nodeType<Type>* trailCurrent;  //pointer just before current
    bool found;

    if (this->first == NULL) //Case 1: the list is empty
        cout << "Cannot delete from an empty list." << endl;
    else
    {
        if (this->first->info == deleteItem) //Case 2: delete first node
        {
            current = this->first;
            this->first = this->first->link;
            this->count--;

            if (this->first == NULL) //if the list had only one node
                this->last = NULL;

            delete current;
        }
        else //Case 3: search the rest of the list
        {
            found = false;
            trailCurrent = this->first;
            current = this->first->link;

            while (current != NULL && !found)
            {
                if (current->info != deleteItem)
                {
                    trailCurrent = current;
                    current = current->link;
                }
                else
                    found = true;
            }//end while

            if (found) //node found
            {
                trailCurrent->link = current->link;
                this->count--;

                if (this->last == current) //deleted node was last
                    this->last = trailCurrent;

                delete current;
            }
            else
                cout << "The item to be deleted is not in the list."
                     << endl;
        }//end else
    }//end else
}//end deleteNode


//***********************************************************
//                LAB 5 IMPLEMENTATIONS
//***********************************************************

template <class Type>
void unorderedLinkedList<Type>::deleteSmallest()
{
    if (this->first == NULL)
        return; //empty list

    nodeType<Type>* prev = NULL;
    nodeType<Type>* curr = this->first;
    nodeType<Type>* minPrev = NULL;
    nodeType<Type>* minNode = this->first;

    while (curr != NULL)
    {
        if (curr->info < minNode->info)
        {
            minNode = curr;
            minPrev = prev;
        }
        prev = curr;
        curr = curr->link;
    }

    if (minPrev == NULL) //smallest is first node
    {
        this->first = this->first->link;
        if (this->last == minNode)
            this->last = this->first;
    }
    else
    {
        minPrev->link = minNode->link;
        if (this->last == minNode)
            this->last = minPrev;
    }

    delete minNode;
    this->count--;
}//end deleteSmallest


template <class Type>
void unorderedLinkedList<Type>::deleteAll(const Type& item)
{
    nodeType<Type>* curr = this->first;
    nodeType<Type>* prev = NULL;

    while (curr != NULL)
    {
        if (curr->info == item)
        {
            nodeType<Type>* doomed = curr;
            if (prev == NULL)
            {
                this->first = curr->link;
                curr = this->first;
            }
            else
            {
                prev->link = curr->link;
                curr = prev->link;
            }

            if (doomed == this->last)
                this->last = prev;

            delete doomed;
            this->count--;
        }
        else
        {
            prev = curr;
            curr = curr->link;
        }
    }
}//end deleteAll


template <class Type>
Type unorderedLinkedList<Type>::getKthElement(int k) const
{
    if (k < 1 || k > this->count)
    {
        cerr << "No such element exists (k=" << k << ")." << endl;
        exit(1);
    }

    nodeType<Type>* curr = this->first;
    for (int i = 1; i < k; ++i)
        curr = curr->link;

    return curr->info;
}//end getKthElement


template <class Type>
void unorderedLinkedList<Type>::deleteKthElement(int k)
{
    if (k < 1 || k > this->count)
    {
        cout << "No such element exists." << endl;
        return;
    }

    if (k == 1)
    {
        nodeType<Type>* doomed = this->first;
        this->first = this->first->link;
        if (this->last == doomed)
            this->last = this->first;
        delete doomed;
        this->count--;
        return;
    }

    nodeType<Type>* prev = this->first;
    for (int i = 1; i < k - 1; ++i)
        prev = prev->link;

    nodeType<Type>* doomed = prev->link;
    prev->link = doomed->link;

    if (doomed == this->last)
        this->last = prev;

    delete doomed;
    this->count--;
}//end deleteKthElement


template <class Type>
void unorderedLinkedList<Type>::rotate()
{
    if (this->first == NULL || this->first->link == NULL)
        return; //empty or single-node list

    nodeType<Type>* oldFirst = this->first;
    this->first = this->first->link;
    this->last->link = oldFirst;
    this->last = oldFirst;
    this->last->link = NULL;
}//end rotate

#endif
