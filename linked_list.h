/* Name: Tim J. Dempsey
   Student ID: 19390664
   Unit and Time: UCP, Tuesdays @ 4pm
   Contents: linked_list.h - Header file for linked_list.c
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* STRUCT: LinkedListNode
* PURPOSE: The linkedlist node is designed as the struct to hold the data
*    That will be stored by the linked list, in the form of a void* that will
*    point to whatever data type is required - for this assignment, it will
*    be a CmdStruct holding a function pointer and a char pointer.
* HOW IT WORKS:
*    The node contains two LinkedListNode struct pointers which are set to
*    reference the nodes it is adjacent to, which creates a chain. This chain
*    will be accessed in this way, so that the data each node contains is
*    read sequentially.
* HOW IT RELATES:
*    It contains the information parsed from each line of a valid text file
*    that tells the program what to do with the information it's given. When
*    the node is removed and read later on, it will surrender its data to the
*    relevant drawing function and then be freed from memory.
**/
typedef struct LinkedListNode /* tag name */
{
    void* data;
    struct LinkedListNode* next;
    struct LinkedListNode* prev;
} LinkedListNode; /* typedef name */

/**
* STRUCT: LinkedList
* PURPOSE: This forms the start of a list, containing two LinkedListNodes - 
*    the head and tail. This is so that we always know where a list begins and
*    ends, and can access the start quickly if we need to iterate, and the end
*    if we need the last entry to be accessed in O(1).
* HOW IT WORKS:
*    The list is created, and the head and tail are set to NULL while the 
*    count is set to 0. When the head points to a new LinkedListNode, the 
*    count is set to 1 and the tail points at the node, before it is moved 
*    down by one each time a new node is added at the end.
* HOW IT RELATES:
*    Forms the start of the list when parsing the input file.
**/
typedef struct
{
    LinkedListNode* head;
    LinkedListNode* tail;
    int count;
} LinkedList;

/************************** FUNCTION DECLARATIONS ***************************/

/**
* FUNCTION: createList
* IMPORTS: N/A
* PURPOSE:
*    Initialises the LinkedList with a malloc() so that it can be used.
* HOW IT WORKS:
*    Pointer to the struct is declared and initialised with a malloc the size
*    of the struct, and then the head and tail are assigned NULL while the 
*    count is assigned a value of 0. This is then returned to main.c for use.
* HOW IT RELATES:
*    Forms an easy to read function for main.c to use so that a pointer to the
*    list can be passed between functions from different files - one to 
*    populate the file, and another to read and disband it.
**/
LinkedList* createList();

/**
* FUNCTION: insertLast
* IMPORTS: LinkedList* - Pointer to the list to insert into
*          void* - data for the new node to point at. 
* PURPOSE:
*    Fairly self-explanatory - this function lets imported data be passed into
*    the list at the start, so the head points to it.
* HOW IT WORKS:
*    A new LinkedListNode struct is malloced, and points to the data, while
*    the tail is adjusted to point at this node from either NULL (no prior
*    nodes) or the node it was pointing at before. If there was a prior node, 
*    then that node now points at this new one as it is the last in the chain.
* HOW IT RELATES:
*    This function is called in file.c after the line has been parsed and 
*    validated to insert the next step in the chain.
**/
void insertLast( LinkedList*, void* );

/**
* FUNCTION: removeFirst
* IMPORTS: LinkedList*
* PURPOSE:
*    This function takes the first node in the list and detaches it, saving
*    the data while freeing the node. The head now either points to NULL if 
*    that was the only node, or it points to the next node.
* HOW IT WORKS:
*    The head node is accessed, its data is retrieved, and the node is freed.
*    The node count in LinkedList is decremented by one, and the data is 
*    returned.
* HOW IT RELATES:
*    When reading the list, this function is called to retrieve the stored
*    command struct so that its two fields may be used. Eventually, the list
*    whittles away to nothing and is freed entirely.
**/
void* removeFirst( LinkedList* listPtr );

#endif

