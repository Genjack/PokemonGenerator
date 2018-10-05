/* Name: Tim J. Dempsey
   Student ID: 19390664
   Unit and Time: UCP, Tuesdays @ 4pm
   Tutors: Rayden and Elliot

   UCP ASSIGNMENT - FILE.C
   Contents: This file contains the functions needed for file I/O:

    > int readInFile( FILE*, LinkedList* );
    > void toUpperCase( char* );
    > int validateInt( char* );
    > int validateReal( char* );
    > int validateChar( char* );
    > printToLog( double, double, Tracker*, char* );
*/

#include "file.h"
#include "effects.h" /* For setFgColour(int) and setBgColour(int) */
#include "utility.h" /* For moveCursor */

/**
* FUNCTION: readInFile
* PURPOSE: 
*    This is a key method that reads in the file and makes the necessary
*    calls to storage and other methods so that the draw and move operations
*    can be initiated.
* HOW IT WORKS: 
*    Returns an integer representing a success code - if -1, it's failed, if 0
*    it's all good.
**/   
int readInFile( FILE* flPtr, LinkedList* list, int lineCount )
{
    /* fscanf - check string - then fscanf with format based on string */
    char cmd[CMD_STR_LEN]; /* Malloced array of chars for the command */
    char val[VAL_STR_LEN]; /* Smaller array for the values */
    int nRead, ii;
    int valid = VALID; /* 1 is !FALSE */
    /*char fup;*/
    CmdStruct* instruction; /* Struct to store in each linked list node */
    
    for( ii = 0; ii < lineCount; ii++ )
    {
        /* malloc new CmdStruct - declared in main.h */
        instruction = (CmdStruct*)malloc(sizeof(CmdStruct));
        /* command (FP) and char[4] value */ 

        /* Read the first line, expecting two valid strings. */
        nRead = fscanf( flPtr, "%s %s", cmd, val );
        /*fgetc() check if '\n'.*/
        /*fup = fgetc(flPtr);*/
        if( ( nRead != 2 )/* || ( fup != '\n' )*/ )
        {
            valid = NOT_VALID; /* EOF - get outta town */
        }
        else
        {
            toUpperCase( cmd ); /* Ensure in upper case */
            if( strcmp( cmd, "FG" ) == 0 ) /* FOREGROUND CHANGE */
            {
                /* Ensure that it is an integer, and it's within range */
                if( validateColour( val, 0, 15 ) != valid )
                {
                    valid = NOT_VALID; 
                }
                else
                {
                    /* set command to address of setFG(), defined utility.c */
                    instruction->command = &setFG;
                }
            }
            else if( strcmp( cmd, "BG" ) == 0 ) /* BACKGROUND CHANGE */
            {
                if( validateColour( val, 0, 7 ) != valid )
                {
                    valid = NOT_VALID;
                }
                else
                {
                    instruction->command = &setBG;
                }
            }
            else if( strcmp( cmd, "MOVE" ) == 0 ) /* MOVE COMMAND */
            {
                if( validateReal( val ) != valid )
                {
                    valid = NOT_VALID;
                }
                else
                {
                    instruction->command = &moveCursor;
                }
            }
            else if( strcmp( cmd, "PATTERN" ) == 0 ) /* PATTERN CHANGE */
            {
                if( validateChar( val ) != valid )
                {
                    valid = NOT_VALID;
                }
                else
                {
                    instruction->command = &setPattern;
                }
            }
            else if( strcmp( cmd, "DRAW" ) == 0 ) /* DRAW COMMAND */ 
            {
                if( validateReal( val ) != valid )
                {
                    valid = NOT_VALID;
                }
                else
                {
                    /* Call landing function to prepare calling of line
                       Located in utility.c */
                    instruction->command = &drawLine;
                }
            }
            else if( strcmp( cmd, "ROTATE" ) == 0 ) /* ROTATE ANGLE */
            {
                if(validateReal(val) != valid )
                {
                    valid = NOT_VALID;
                }
                else
                {
                    instruction->command = &changeAngle;
                }
            }
            /* If not finished, assign char* to the struct field
               completing the struct, and add to the back of the list. */
            if( !feof(flPtr) )
            /* if( !feof(flPtr) ) */
            {    
                /* Populate struct and insert into list */
                strncpy( instruction->value, val, VAL_STR_LEN );
                /* Store the line in new LinkedListNode and add to list*/
                insertLast( list, instruction ); 
            } 
        }
    /* Terminate loop if file is invalid or end of file is reached. */
    }  /* END FOR LOOP */
    return valid;
}

int getNumLines( FILE* flPtr )
{
    int lineCount = 0;
    char newLineSearch;
    int done = FALSE;

    do
    {
        newLineSearch = fgetc( flPtr );
        if( newLineSearch == EOF )
        {
            done = TRUE;
        }
        else if( newLineSearch == '\n' )
        {
            lineCount++;
        }
    } while( !done );
    return lineCount;
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
            str[ii] -= ('a' - 'A');
        }
        ii++;
    }
}

/**
*  FUNCTION: validateColour
*  PURPOSE: 
*   To check that the imported char* can be successfully converted to an int.
*  HOW IT WORKS:
*   TO DO
*  HOW IT RELATES:
*   TO DO
**/
int validateColour( char* val, int min, int max )
{
    int valCheck; /* int to store the line value in (not used yet) */
    int success = 1; /* returns -1 if invalid, 1 if valid */
    char* endPtr;
    valCheck = strtol( val, &endPtr, 10 );
    if( ( valCheck < min ) || ( valCheck > max ) )
    {
        success = -1;
    }
    if( *endPtr != '\0' )
    {
        success = -1;
    }
    return success;
}

int validateReal( char* val )
{
    int success = 1;
    char* endPtr;
    
    strtod( val, &endPtr );
    if( *endPtr != '\0' )
    {
        success = -1;
    }
    return success;
} 

int validateChar( char* val )
{
    int success = 1;

    if( strlen( val ) != 1 )
    {
        success = -1;
    }
    return success;
}  
