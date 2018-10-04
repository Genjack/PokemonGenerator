/* Name: Tim J. Dempsey
   Student ID: 19390664
   Unit and Time: UCP, Tuesdays @ 4pm
   Contents: linked_list.c - Program for printing out journal entries from file.
*/

/**
* Notes: Create capability to:
* > Create empty linked list;
* > Insert an element at the start;
* > Remove an element from the start;
* > Retrieve ith element from the list;
* > Print out contents of the list;
* > Free the list.
**/

#include <stdio.h>
#include "linked_list.h"

LinkedList* createList() /* DOUBLE-DOUBLE */
{
    LinkedList* list;
    list = (LinkedList*)malloc(sizeof(LinkedList)); /* Declaration of empty list */
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    return list;
}

/*FUNCTION: Insert a node at the start of the linked list.*/
void insertFirst( LinkedList* list, void* contents ) /* DOUBLE-DOUBLE */
{
    LinkedListNode* newNode;

    /* Create the new node */
    newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    
    /* Assign the imported data to the newly created node */
    newNode->data = contents;
    /* Set the new node's prev to NULL (it's first) */
    newNode->prev = NULL;
    
    if( list->head == NULL )
    {
        list->head = newNode;
        list->tail = newNode; /*First element; is both front and back.*/
        newNode->next = NULL;
    }
    else    
    {
        list->head->prev = newNode; /* Former first node prev field set to new*/
        /* Point the newNode 'next' field at the first node */
        newNode->next = list->head; 

        /* Point the head at the new node */
        list->head = newNode;

    }
    list->count += 1; /* Update count to reflect node addition */
}

/*FUNCTION: Insert a node last in the list; DOUBLE-ENDED DOUBLE-LINKED */
void insertLast( LinkedList* list, void* contents )
{
    LinkedListNode* newNode, *currNode;
    
    newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));

    newNode->data = contents;
    newNode->next = NULL; /*It's the last node - no next*/

    if( list->head == NULL ) /* first node */
    {
        list->head = newNode;
        list->tail = newNode;
        newNode->prev = NULL;
    }
    else /* there are others */
    {
        currNode = list->tail; /* Easy way to grab the soon-to-be 2nd last node */
        currNode->next = newNode;
        newNode->prev = currNode;
        list->tail = newNode;
    }
    list->count += 1;
    
}

/*DOUBLE-LINK DOUBLE-END*/
/*FUNCTION: Remove the node, if it exists, from the start of the linked list.*/
void* removeFirst( LinkedList* listPtr ) /*Returns a void pointer.*/
{
    LinkedListNode* currNode;
    void* rescuedData = NULL;
    
    if( listPtr->head != NULL )
    {
        if( listPtr->head->next != NULL ) /* More than one node */
        {
            currNode = listPtr->head;
            listPtr->head = listPtr->head->next; /*set head to 2nd node */
            listPtr->head->prev = NULL; /*New first node prev set to null */
            rescuedData = currNode->data;
            free( currNode );
        }
        else /* Removing the only node in the list */
        {
            rescuedData = listPtr->head->data;
            listPtr->head = NULL;
            listPtr->tail = NULL;
        }
        listPtr->count -= 1;
    }
    return rescuedData;
}

/*REMOVE LAST */
void* removeLast( LinkedList* listPtr ) /* DOUBLE-DOUBLE */
{
    void* rescuedData = NULL;

    if( listPtr->tail != NULL )
    {
        if( listPtr->tail->prev == NULL ) /* Only one node */
        {
            rescuedData = listPtr->head->data;
            listPtr->head = NULL;
            listPtr->tail = NULL;
        }
        else /* Multiple nodes */
        {
            rescuedData = listPtr->tail->data;
            listPtr->tail = listPtr->tail->prev;
            listPtr->tail->next = NULL;
        }
        listPtr->count -= 1;
    }
    return rescuedData;
}

/*FUNCTION: Retrieve the ith element of the list without modifying.*/
void* returnElement( LinkedList* listPtr, int index )
{
    int ii = 0;
    LinkedListNode* currNode;
    void* rescuedData;

    if( ( index > listPtr->count) || ( index < 0 ) )
    {
        rescuedData = NULL;
    }
    else
    {
        currNode = listPtr->head;
        while( ii < index ) 
        {
            currNode = currNode->next;
        }
        rescuedData = currNode->data;
    }
    return rescuedData;
}

void printList( LinkedList* listPtr, void(*funcPtr)(void*) )
{
    LinkedListNode* currNode = listPtr->head;
     
    while(currNode != NULL)
    {
        (*funcPtr)(currNode->data);
        currNode = currNode->next;
    }
}

/* FUNCTION: Free the list. Works similarly to printList, in that we need a 
   function pointer to determine what the datatype is and free it */
void freeList( LinkedList* listPtr, void(*funcPtr)(void*) )
{
    LinkedListNode* currNode, *nextNode;
    
    currNode = listPtr->head;

    while( currNode != NULL )
    {
        nextNode = currNode->next;
        (*funcPtr)(currNode->data);
        free( currNode );
        currNode = nextNode;
    }
    free( listPtr );
}    
