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
#include "effects.h" /* For setFgColour(int) and setBgColour(int) */
#include "utility.h" /* For moveCursor */

/**
* FUNCTION: readInEntries
* PURPOSE: 
*    This is a key method that reads in the file and makes the necessary
*    calls to storage and other methods so that the draw and move operations
*    can be initiated.
* HOW IT WORKS: 
*    Returns an integer representing a success code - if -1, it's failed, if 0
*    it's all good.
**/   
int readInFile( FILE* flPtr, LinkedList* list )
{
    /* fscanf - check string - then fscanf with format based on string */
    char cmd[CMD_STR_LEN]; /* Malloced array of chars for the command */
    char val[VAL_STR_LEN]; /* Smaller array for the values */
    int done = FALSE; /* defined in file.h */
    int nRead, value;
    char fup;
    CmdStruct* instruction; /* Struct to store in each linked list node */

    do
    {
        instruction = (CmdStruct*)malloc(sizeof(CmdStruct));
        /* command (FP) and char[4] value */ 

        nRead = fscanf( flPtr, "%s %s %c", cmd, val, &fup );
        /* fgetc() check if '\n'. */
        if( nRead != 2 ) /* i.e. if fup is not '\n' */
        {
            done = TRUE; /* EOF - get outta town */
        }
        else
        {
            toUpperCase( cmd ); /* Ensure in upper case */
            if( strcmp( cmd, "FG" ) == 0 ) /* FOREGROUND CHANGE */
            {
                value = validateColour( val, 0, 15 );
                if( value == -1 )
                {
                   done = TRUE;
                }
                else
                {
                    /* set command to address of setFG(), defined utility.c */
                    instruction->command = &setFG;
                }
            }
            else if( strcmp( cmd, "BG" ) == 0 ) /* BACKGROUND CHANGE */
            {
                value = validateColour( val, 0, 7 );
                if( value == -1 )
                {
                    done = TRUE;
                }
                else
                {
                    instruction->command = &setBG;
                }
            }
            else if( strcmp( cmd, "MOVE" ) == 0 ) /* MOVE COMMAND */
            {
                value = validateReal( val );
                if( value == -1 )
                {
                    done = TRUE;
                }
                else
                {
                    instruction->command = &moveCursor;
                }
            }
            else if( strcmp( cmd, "PATTERN" ) == 0 ) /* PATTERN CHANGE */
            {
                value = validateChar( val );
                if( value == -1 )
                {
                    done = TRUE;
                }
                else
                {
                    instruction->command = &setPattern;
                }
            }
            else if( strcmp( cmd, "DRAW" ) == 0 ) /* DRAW COMMAND */            
            {
                value = validateReal( val );
                if( value == -1 )
                {
                    done = TRUE;
                }
                else
                {
                    /* Call landing function to prepare calling of line
                       Located in utility.c */
                    instruction->command = &Drawline;
                }
            }
            else if( strcmp( cmd, "ROTATE" ) == 0 ) /* ROTATE ANGLE */
            {
                if(validateReal(val) == VALID)
                {
                    instruction->command = &changeAngle;
                }
                else
                {
                    valid = NOT_VALID;
                }
                /*value = validateReal( val );
                if( value == -1 )
                {
                    done = TRUE;
                }
                else
                {
                    instruction->command = &changeAngle;
                }*
            }
            /* Final check - if not finished, assign char* to the struct field,
               completing the struct, and add it to the back of the list. */
            if( !done )
            {    
                /* Populate struct and insert into list */
                strncpy( instruction->value, val, VAL_STR_LEN );
                /* Store the line in a new LinkedListNode and add to list*/
                insertLast( list, instruction ); 
           } 
        }
    } while( valid && !feof(flPtr) );
    return done;
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
*  FUNCTION: validateInt
*  PURPOSE: 
*   To check that the imported char* can be successfully converted to an int.
*  HOW IT WORKS:
*   TO DO
*  HOW IT RELATES:
*   TO DO
**/
int validateInt( char* val, int min, int max )
{
    int valCheck = 0;
    char* endPtr;
    valCheck = strtol( val, &endPtr, 10 );
    if( ( valCheck < min ) || ( valCheck > max ) )
    {
        valCheck = -1;
    }
    if( *endPtr != '\0' )
    {
        valCheck = -1;
    }
    return valCheck;
}

int validateReal( char* val )
{
    int valCheck = 0;
    char* endPtr;
    
    strtof( val, &endPtr );
    if( *endPtr != '\0' )
    {
        valCheck = -1;
    }
    return ValCheck;
} 

int validateChar( char* val )
{
    int valCheck = 0;

    if( strlen( val ) != 1 )
    {
        valCheck = -1;
    }
    return valCheck;
}        
