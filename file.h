/* Name: Tim J. Dempsey
   Student ID: 19390664
   Unit and Time: UCP, Tuesdays @ 4pm
   Tutors: Rayden and Elliot

   UCP ASSIGNMENT - FILE.H
   Contents: This is the header file for file.c, containing the function
   declarations for the following methods:

    > readInFile( FILE*, LinkedList* );
*/

#ifndef FILE_H
#define FILE_H

#include "main.h"
#include "linked_list.h"

#define CMD_STR_LEN 11 /* ROTATE xxx + '\0': longest valid first string */
#define FALSE 0
#define TRUE !FALSE

/* FUNCTION DECLARATIONS */
void readInFile( FILE*, LinkedList* );
void toUpperCase( char* );

#endif
