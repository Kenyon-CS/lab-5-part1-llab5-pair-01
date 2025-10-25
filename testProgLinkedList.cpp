//This program tests various operation of a linked list
//34 62 21 90 66 53 88 24 10 -999

#include <iostream>                                 //Line 1
#include "unorderedLinkedList.h"                    //Line 2
#include "orderedLinkedList.h" 

using namespace std;                                //Line 3

int main()                                          //Line 4
{                                                   //Line 5
    unorderedLinkedList<int> list1, list2;          //Line 6

    int num;
                                            //Line 7
    cout << "Line 8: Enter integers ending "
         << "with -999" << endl;                    //Line 8
    cin >> num;                                     //Line 9

    while (num != -999)                             //Line 10
    {                                               //Line 11
        list1.insertLast(num);                      //Line 12
        cin >> num;                                 //Line 13
    }                                               //Line 14

    cout << endl;                                   //Line 15

    cout << "Line 16: list1: ";                     //Line 16
    list1.print();                                  //Line 17
    cout << endl;                                   //Line 18
    cout << "Line 19: Length of list1: "
         << list1.length() << endl;                 //Line 19

    list2 = list1;	   //test the assignment operator Line 20

    cout << endl;
    cout << "TESTING LIST ASSIGNMENT (list2 = list1)" << endl;
    cout << "Line 21: list2: ";                     //Line 21
    list2.print();                                  //Line 22
    cout << endl;                                   //Line 23
    cout << "Line 24: Length of list2: "
         << list2.length() << endl;                 //Line 24

    cout << endl;
    cout << "TESTING NODE DELETION ON list2" << endl;
    cout << "Line 25: Enter the number to be "
         << "deleted: ";                            //Line 25
    cin >> num;                                     //Line 26
    cout << endl;                                   //Line 27

    list2.deleteNode(num);                          //Line 28

    cout << "Line 29: After deleting " << num
         << " list2: " << endl;                     //Line 29
    list2.print();                                  //Line 30
    cout << endl;                                   //Line 31

    cout << "Line 32: Length of list2: "
         << list2.length() << endl;                 //Line 32

     cout << endl;
    cout << "TESTING VIEWING LIST USING ITERATOR (list1)" << endl;
    cout << endl << "Line 33: Output list1 "
         << "using an iterator" << endl;            //Line 33

    linkedListIterator<int> it;                     //Line 34

    for (it = list1.begin(); it != list1.end();
                             ++it)                  //Line 35
        cout << *it << " ";                         //Line 36
    cout << endl;                                   //Line 37

    //-----------------------------------------------------
    //  Lab 5: Testing new member functions
    //-----------------------------------------------------
    cout << endl << "====== LAB 5 TESTS ======" << endl;

    cout << "Original list1: ";
    list1.print();
    cout << endl;

    cout << endl;
    cout << "Deleting smallest element..." << endl;
    list1.deleteSmallest();
    cout << "After deleteSmallest(): ";
    list1.print();
    cout << endl;

    cout << endl;
    cout << "Enter a number to delete all its occurrences: ";
    cin >> num;
    list1.deleteAll(num);
    cout << "After deleteAll(" << num << "): ";
    list1.print();
    cout << endl;

    cout << endl;
    cout << "Enter a position k to display kth element: ";
    cin >> num;
    cout << "The " << num << "th element is: "
         << list1.getKthElement(num) << endl;

     cout << endl;
    cout << "Enter a position k to delete kth element: ";
    cin >> num;
    list1.deleteKthElement(num);
    cout << "After deleteKthElement(" << num << "): ";
    list1.print();
    cout << endl;

    cout << endl;
    cout << "Rotating list..." << endl;
    list1.rotate();
    cout << "After rotate(): ";
    list1.print();
    cout << endl;

    orderedLinkedList<int> ordered1, ordered2, ordered3;

    cout << endl;
    cout << "Populating ordered1 with values for mergeLists test..." << endl;
    ordered1.insert(4);
    ordered1.insert(1);
    ordered1.insert(9);
    ordered1.insert(11);
    ordered1.insert(81);
    ordered1.insert(64);
    ordered1.insert(21);
    cout << "ordered1 is now: ";
    ordered1.print(); 
    cout << endl;

    cout << endl;
    cout << "Populating ordered2 with values for mergeLists test..." << endl;
    ordered2.insert(3);
    ordered2.insert(59);
    ordered2.insert(98);
    ordered2.insert(30);
    ordered2.insert(10);
    ordered2.insert(33);
    ordered2.insert(5);
    ordered2.insert(92);
    ordered2.insert(86);
    cout << "ordered2 is now: ";
    ordered2.print(); 
    cout << endl;

     cout << endl;
     cout << "Merging ordered1 with ordered2 and saving to ordered3..." << endl;
     ordered3.mergeLists(ordered1, ordered2);
     cout << "ordered3 is: ";
     ordered3.print();
     cout << endl;
     cout << "expected:    1 3 4 5 9 10 11 21 30 33 59 64 81 86 92 98" << endl;
     cout << "mergeLists method for ordered linked lists works as expected!" << endl;
    //-----------------------------------------------------

    //system("pause");
    return 0;                                       //Line 38
}                                                   //Line 39
