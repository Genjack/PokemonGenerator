/* Name: Tim J. Dempsey
   Student ID: 19390664
   Unit and Time: UCP, Tuesdays @ 4pm
   Tutors: Rayden and Elliot

   UCP ASSIGNMENT - FILE.C
   Contents: This file contains the functions needed for file I/O:

    > readInEntries( FILE*, LinkedList* );
    > toUpperCase( char* );
*/

#include "file.h"

/**
* FUNCTION: readInEntries
* PURPOSE: 
*    This is a key method that reads in the file and makes the necessary
*    calls to storage and other methods so that the draw and move operations
*    can be initiated.
* HOW IT WORKS: 
* 
**/   
void readInFile( FILE* flPtr, LinkedList* list )
{
    /* fscanf - check string - then fscanf with format based on string */
    char* cmd;
    int done = FALSE; /* defined in file.h */

    do
    {
        cmd = (char*)malloc(CMD_STR_LEN * sizeof(char));

        if( fgets( cmd, CMD_STR_LEN, flPtr ) == NULL )
        {
            done = TRUE;
        }
        else
        {
            /* Store the line in a new LinkedListNode and add to list */
            insertLast( list, (void*)(cmd) ); 
        }
    } while( !done );
}

/** 
* FUNCTION: toUpperCase
* PURPOSE:
*   Ensure that all valid commands from file are formatted in upper case to 
*   avoid errors and promote usability.
* HOW IT WORKS:
*   Takes a char pointer, which points at an array of chars; iterates over each
*   character, and if the ASCII value of the character falls within the lower
*   case range, it subtracts 32 from the value, which converts the character to
*   upper case.
* HOW IT RELATES:
*   Struggles; upper case characters can be pretty stuck up. Also, it fits in by
*   ensuring that any case-insensitivity in the file is not an issue. Will be 
*   called by the main.c file to sanitise the data after file read.
**/
void toUpperCase( char* str )
{
    int ii = 0;

    while( str[ii] != '\0' )
    {
        if( ( str[ii] >= 'a' ) && ( str[ii] <= 'z' ) )
        {
            /* The upper-case version is 32 values behind its counterpart */
            str[ii] -= 32;
        }
        ii++;
    }
}
