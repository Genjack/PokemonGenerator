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

/* DEFINE: Linked list node as a struct - double-linked double-ended*/
typedef struct LinkedListNode /* tag name */
{
    void* data;
    struct LinkedListNode* next;
    struct LinkedListNode* prev;
} LinkedListNode; /* typedef name */

/*DEFINE: Linked list head as a separate struct to the node */
typedef struct
{
    LinkedListNode* head;
    LinkedListNode* tail;
    int count;
} LinkedList;

/* FUNCTION DECLARATIONS */

/*Create List*/
LinkedList* createList();

/*Insert element at the start*/
void insertFirst( LinkedList*, void* );

/* Insert element at the end */
void insertLast( LinkedList*, void* );

/*Remove the first element (the start) */
void* removeFirst( LinkedList* listPtr );

/* Remove the last element */
void* removeLast( LinkedList* listPtr );

/* Return the ith element from the list */
void* returnElement( LinkedList* listPtr, int index );

/* Print out the list contents */
void printList( LinkedList*, void(*funcPtr)(void*) );

/* Free the list and all its contents */
void freeList( LinkedList*, void(*funcPtr)(void*) );

#endif

