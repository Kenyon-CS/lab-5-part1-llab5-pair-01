#ifndef H_LinkedListType
#define H_LinkedListType

#include <iostream>
#include <cassert>

using namespace std;

// Definition of the node
//======================================================
template <class Type>
struct nodeType
{
    Type info;
    nodeType<Type> *link;
};

//***********************************************************
// Author: D.S. Malik
//
// Iterator class for linked list
//***********************************************************
template <class Type>
class linkedListIterator
{
public:
    linkedListIterator();
      //Default constructor
      //Postcondition: current = NULL;

    linkedListIterator(nodeType<Type> *ptr);
      //Constructor with a parameter.
      //Postcondition: current = ptr;

    Type operator*();
      //Function to overload the dereferencing operator *.
      //Postcondition: Returns the info contained in the node.

    linkedListIterator<Type> operator++();
      //Overload the preincrement operator.
      //Postcondition: The iterator is advanced to the next node.

    bool operator==(const linkedListIterator<Type>& right) const;
      //Overload the equality operator.
      //Postcondition: Returns true if this iterator is equal to
      //    the iterator specified by right, otherwise returns false.

    bool operator!=(const linkedListIterator<Type>& right) const;
      //Overload the not equal to operator.
      //Postcondition: Returns true if this iterator is not equal to
      //    the iterator specified by right, otherwise returns false.

private:
    nodeType<Type> *current; //pointer to point to the current node
};

// ===== Iterator definitions =====
template <class Type>
linkedListIterator<Type>::linkedListIterator()
{
    current = NULL;
}

template <class Type>
linkedListIterator<Type>::linkedListIterator(nodeType<Type> *ptr)
{
    current = ptr;
}

template <class Type>
Type linkedListIterator<Type>::operator*()
{
    return current->info;
}

template <class Type>
linkedListIterator<Type> linkedListIterator<Type>::operator++()
{
    current = current->link;
    return *this;
}

template <class Type>
bool linkedListIterator<Type>::operator==(const linkedListIterator<Type>& right) const
{
    return (current == right.current);
}

template <class Type>
bool linkedListIterator<Type>::operator!=(const linkedListIterator<Type>& right) const
{
    return (current != right.current);
}

//***********************************************************
// Author: D.S. Malik
//
// Abstract base class linkedListType
//***********************************************************
template <class Type>
class linkedListType
{
public:
    const linkedListType<Type>& operator=(const linkedListType<Type>&);
      //Overload the assignment operator.

    void initializeList();
      //Initialize the list to an empty state.
      //Postcondition: first = NULL, last = NULL, count = 0;

    bool isEmptyList() const;
      //Function to determine whether the list is empty.
      //Postcondition: Returns true if the list is empty.

    void print() const;
      //Function to output the data contained in each node.

    int length() const;
      //Function to return the number of nodes in the list.
      //Postcondition: The value of count is returned.

    void destroyList();
      //Function to delete all the nodes from the list.
      //Postcondition: first = NULL, last = NULL, count = 0;

    Type front() const;
      //Function to return the first element of the list.
      //Precondition: The list must not be empty.
      //Postcondition: Returns info in first node.

    Type back() const;
      //Function to return the last element of the list.
      //Precondition: The list must not be empty.
      //Postcondition: Returns info in last node.

    virtual bool search(const Type& searchItem) const = 0;
    virtual void insertFirst(const Type& newItem) = 0;
    virtual void insertLast(const Type& newItem) = 0;
    virtual void deleteNode(const Type& deleteItem) = 0;

    // ==== Lab 5 abstract functions ====
    virtual void deleteSmallest() = 0;
      //Deletes the smallest element in the list.

    virtual void deleteAll(const Type& item) = 0;
      //Deletes all occurrences of item in the list.

    virtual Type getKthElement(int k) const = 0;
      //Returns the info in the kth node (1-indexed).

    virtual void deleteKthElement(int k) = 0;
      //Deletes the kth node in the list.

    virtual void rotate() = 0;
      //Moves the first node to the end of the list.
    // ==================================

    linkedListIterator<Type> begin();
      //Returns an iterator pointing to the first node.

    linkedListIterator<Type> end();
      //Returns an iterator pointing past the last node.

    linkedListType();
      //Default constructor.
      //Postcondition: first = NULL, last = NULL, count = 0;

    linkedListType(const linkedListType<Type>& otherList);
      //Copy constructor.

    ~linkedListType();
      //Destructor.
      //Deletes all nodes in the list.

protected:
    int count;               //variable to store number of elements
    nodeType<Type> *first;   //pointer to the first node
    nodeType<Type> *last;    //pointer to the last node

private:
    void copyList(const linkedListType<Type>& otherList);
      //Makes a copy of otherList.
};

// ===== linkedListType member definitions =====
template <class Type>
bool linkedListType<Type>::isEmptyList() const
{
    return (first == NULL);
}

template <class Type>
linkedListType<Type>::linkedListType()
{
    first = NULL;
    last = NULL;
    count = 0;
}

template <class Type>
void linkedListType<Type>::destroyList()
{
    nodeType<Type> *temp;
    while (first != NULL)
    {
        temp = first;
        first = first->link;
        delete temp;
    }
    last = NULL;
    count = 0;
}

template <class Type>
void linkedListType<Type>::initializeList()
{
    destroyList();
}

template <class Type>
void linkedListType<Type>::print() const
{
    nodeType<Type> *current = first;
    while (current != NULL)
    {
        cout << current->info << " ";
        current = current->link;
    }
}

template <class Type>
int linkedListType<Type>::length() const
{
    return count;
}

template <class Type>
Type linkedListType<Type>::front() const
{
    assert(first != NULL);
    return first->info;
}

template <class Type>
Type linkedListType<Type>::back() const
{
    assert(last != NULL);
    return last->info;
}

template <class Type>
linkedListIterator<Type> linkedListType<Type>::begin()
{
    linkedListIterator<Type> temp(first);
    return temp;
}

template <class Type>
linkedListIterator<Type> linkedListType<Type>::end()
{
    linkedListIterator<Type> temp(NULL);
    return temp;
}

template <class Type>
void linkedListType<Type>::copyList(const linkedListType<Type>& otherList)
{
    nodeType<Type> *newNode;
    nodeType<Type> *current;

    if (first != NULL)
        destroyList();

    if (otherList.first == NULL)
    {
        first = NULL;
        last = NULL;
        count = 0;
    }
    else
    {
        current = otherList.first;
        count = otherList.count;

        first = new nodeType<Type>;
        first->info = current->info;
        first->link = NULL;
        last = first;
        current = current->link;

        while (current != NULL)
        {
            newNode = new nodeType<Type>;
            newNode->info = current->info;
            newNode->link = NULL;
            last->link = newNode;
            last = newNode;
            current = current->link;
        }
    }
}

template <class Type>
linkedListType<Type>::~linkedListType()
{
    destroyList();
}

template <class Type>
linkedListType<Type>::linkedListType(const linkedListType<Type>& otherList)
{
    first = NULL;
    copyList(otherList);
}

template <class Type>
const linkedListType<Type>& linkedListType<Type>::operator=
(const linkedListType<Type>& otherList)
{
    if (this != &otherList)
        copyList(otherList);

    return *this;
}

#endif
