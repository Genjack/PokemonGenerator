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

#include "linked_list.h"
#include "main.h"

#define CMD_STR_LEN 8 /* PATTERN = 7 + 1('\0') = longest valid string */

#define FALSE 0
#define TRUE !FALSE

#define VALID TRUE
#define NOT_VALID FALSE

/* FUNCTION DECLARATIONS */
int getNumLines( FILE* );
int readInFile( FILE*, LinkedList*, int );
void toUpperCase( char* );
int validateColour( char*, int, int );
int validateReal( char* );
int validateChar( char* );
void printLog( double, double, Tracker*, char* );

#endif
