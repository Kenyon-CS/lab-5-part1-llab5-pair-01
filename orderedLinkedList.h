#ifndef H_orderedListType
#define H_orderedListType

//***********************************************************
// Author: D.S. Malik
//
// This class specifies the members to implement the basic
// properties of an ordered doubly linked list.
//***********************************************************

#include "linkedList.h"

using namespace std;

template <class Type>
//class orderedLinkedList: public linkedListType<Type> //It was like this originally but our compiler had trouble with it
class orderedLinkedList: public linkedListType<Type>
{
public:
    bool search(const Type& searchItem) const;
      //Function to determine whether searchItem is in the list.
      //Postcondition: Returns true if searchItem is in the list,
      //    otherwise the value false is returned.

    void insert(const Type& newItem);
      //Function to insert newItem in the list.
      //Postcondition: first points to the new list, newItem
      //    is inserted at the proper place in the list, and
      //    count is incremented by 1.

    void insertFirst(const Type& newItem);
      //Function to insert newItem at the beginning of the list.
      //Postcondition: first points to the new list, newItem is
      //    inserted at the beginning of the list, last points to the
      //    last node in the list, and count is incremented by 1.

    void insertLast(const Type& newItem);
      //Function to insert newItem at the end of the list.
      //Postcondition: first points to the new list, newItem is
      //    inserted at the end of the list, last points to the
      //    last node in the list, and count is incremented by 1.

    void deleteNode(const Type& deleteItem);
      //Function to delete deleteItem from the list.
      //Postcondition: If found, the node containing deleteItem is
      //    deleted from the list; first points to the first node
      //    of the new list, and count is decremented by 1. If
      //    deleteItem is not in the list, an appropriate message
      //    is printed.

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

      void mergeLists(orderedLinkedList<Type> &list1, orderedLinkedList<Type> &list2);
    // Merges two other merged linked lists into this one and clears them as it progresses
};

template <class Type>
bool orderedLinkedList<Type>::search(const Type& searchItem) const
{
    bool found = false;
    nodeType<Type> *current; //pointer to traverse the list

    current = this->first;  //start the search at the first node

    while (current != NULL && !found)
        if (current->info >= searchItem) //what exactly is going on here?
            found = true;
        else
            current = current->link;

    if (found)
       found = (current->info == searchItem); //test for equality

    return found;
}//end search


template <class Type>
void orderedLinkedList<Type>::insert(const Type& newItem)
{
    nodeType<Type> *current; //pointer to traverse the list
    nodeType<Type> *trailCurrent; //pointer just before current
    nodeType<Type> *newNode;  //pointer to create a node

    bool  found;

    newNode = new nodeType<Type>; //create the node
    newNode->info = newItem;   //store newItem in the node
    newNode->link = NULL;      //set the link field of the node
                               //to NULL

    if (this->first == NULL)  //Case 1: insert into an empty list
    {
        this->first = newNode;
        this->last = newNode;
        this->count++;
    }
    else  //insert into a non-empty list
    {
        current = this->first;
        found = false;

        while (current != NULL && !found) //search the list
           if (current->info >= newItem)
               found = true;
           else
           {
               trailCurrent = current;
               current = current->link;
           }

        if (current == this->first)      //Case 2: the new item is smallest
        {
            newNode->link = this->first;
            this->first = newNode;
            this->count++;
        }
        else                       //Case 3: the new item is not smallest
        {
            trailCurrent->link = newNode;
            newNode->link = current;

            if (current == NULL)
                this->last = newNode;

            this->count++;
        }
    }//end else
}//end insert

template<class Type>
void orderedLinkedList<Type>::insertFirst(const Type& newItem)
{
    insert(newItem);
}//end insertFirst

template<class Type>
void orderedLinkedList<Type>::insertLast(const Type& newItem)
{
    insert(newItem);
}//end insertLast

template<class Type>
void orderedLinkedList<Type>::deleteNode(const Type& deleteItem)
{
    nodeType<Type> *current; //pointer to traverse the list
    nodeType<Type> *trailCurrent; //pointer just before current
    bool found;

    if (this->first == NULL) //Case 1
        cout << "Cannot delete from an empty list." << endl;
    else
    {
        current = this->first;
        found = false;

        while (current != NULL && !found)  //search the list
            if (current->info >= deleteItem)
                found = true;
            else
            {
                trailCurrent = current;
                current = current->link;
            }

        if (current == NULL)   //Case 4
            cout << "The item to be deleted is not in the "
                 << "list." << endl;
        else
            if (current->info == deleteItem) //the item to be
                                   //deleted is in the list
            {
                if (this->first == current)       //Case 2
                {
                    this->first = this->first->link;

                    if (this->first == NULL)
                        this->last = NULL;

                    delete current;
                }
                else                         //Case 3
                {
                    trailCurrent->link = current->link;

                    if (current == this->last)
                        this->last = trailCurrent;

                    delete current;
                }
                this->count--;
            }
            else                            //Case 4
                cout << "The item to be deleted is not in the "
                     << "list." << endl;
    }
}//end deleteNode

template <class Type>
void orderedLinkedList<Type>::mergeLists(orderedLinkedList<Type> &list1, orderedLinkedList<Type> &list2) {
    nodeType<Type>* firstCur = list1.first;
    nodeType<Type>* secondCur = list2.first;

    // we're overwriting any data saved in this tree
    this->first = nullptr;
    this->last = nullptr;
    this->count = 0;

    while(firstCur && secondCur) {
        if(firstCur->info <= secondCur->info) {
            // then list1's current element is what we need to add to our own tree now and then advance its pointer
            // keeping list2's where it is at
            // nodeType<Type>* tmp = firstCur;
            this->insert(firstCur->info);
            firstCur = firstCur->link;
        } else {
            // then list2's current element is what we need to add to our own tree now and then advance its pointer
            // keeping list1's where it is at
            // nodeType<Type>* tmp = secondCur;
            this->insert(secondCur->info);
            secondCur = secondCur->link;
        }
    }

    while(firstCur) {
        this->insert(firstCur->info);
        firstCur = firstCur->link;
    }

    while(secondCur) {
        this->insert(secondCur->info);
        secondCur = secondCur ->link;
    }

    // clear both other lists
    // list1->first = nullptr;
    // list1->last = nullptr;
    // list1->count = 0;

    // list2->first = nullptr;
    // list2->last = nullptr;
    // list1->count = 0;
} // end mergeLists

template <class Type>
void orderedLinkedList<Type>::deleteSmallest()
{
    return;
}//end deleteSmallest


template <class Type>
void orderedLinkedList<Type>::deleteAll(const Type& item)
{
    return;
}//end deleteAll


template <class Type>
Type orderedLinkedList<Type>::getKthElement(int k) const
{
    return this->first->info;
}//end getKthElement


template <class Type>
void orderedLinkedList<Type>::deleteKthElement(int k)
{
    return;
}//end deleteKthElement


template <class Type>
void orderedLinkedList<Type>::rotate()
{
    return;
}//end rotate

#endif
