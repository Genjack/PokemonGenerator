/* Name: Tim J. Dempsey
   Student ID: 19390664
   Unit and Time: UCP, Tuesdays @ 4pm
   Contents: Stripped version of my Linked List, for the assignment.

* Notes: Contains following functions:
* > createList()
* > insertLast()
* > removeFirst()
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
            currNode = NULL;
        }
        else /* Removing the only node in the list */
        {
            rescuedData = listPtr->head->data;
            free( listPtr->head );
            listPtr->head = NULL;
            listPtr->tail = NULL;
        }
        listPtr->count -= 1;
    }
    return rescuedData;
}
