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

#define CMD_STR_LEN 8 /* PATTERN = 7 + 1('\0') = longest valid string */
#define VAL_STR_LEN 4 /* Allows for 3 digits plus null term (i.e. 360) */

#define FALSE 0
#define TRUE !FALSE

#define VALID TRUE
#define NOT_VALID FALSE

/* FUNCTION DECLARATIONS */
int readInFile( FILE*, LinkedList* );
void toUpperCase( char* );
int validateInt( char*, int, int );
int validateReal( char* );
int validateChar( char* );


#endif
