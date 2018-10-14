/* Name: Tim J. Dempsey
   Student ID: 19390664
   Unit and Time: UCP, Tuesdays @ 4pm
   Tutors: Rayden and Elliot

   UCP ASSIGNMENT - FILE.C
   Contents: This file contains the functions needed for file I/O.

    > int readInFile( FILE*, LinkedList* );
    > void toUpperCase( char* );
    > int validateInt( char* );
    > int validateReal( char* );
    > int validateChar( char* );
    > printToLog( double, double, Tracker*, char* );

*/

#include "file.h"
/********************* ADDED WHILE LOOP - CAN REMOVE *********************/
   
int readInFile( FILE* flPtr, LinkedList* list, int lineCount )
{
    /* fscanf - check string - then fscanf with format based on string */
    char cmd[CMD_STR_LEN]; /* Array of chars for the command */
    char val[VAL_STR_LEN]; /* Smaller array for the values */
    int nRead = 0; 
    int ii;
    int valid = VALID; /* 1 is !FALSE */
    CmdStruct* instruction; /* Struct to store in each linked list node */
    
    for( ii = 0; ii < lineCount; ii++ )
    {
        /* Struct contents: command (FP) and char[4] value */ 
        /* malloc new CmdStruct - declared in main.h */
        instruction = (CmdStruct*)malloc(sizeof(CmdStruct));

        /* Read the first line, expecting two valid strings. */
        nRead = fscanf( flPtr, "%s %s", cmd, val );
        if( ( nRead != 2 ) ) 
        {
            valid = NOT_VALID; /* EOF - get outta town */
            free( instruction );
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

int checkWordValidity( FILE* flPtr )
{
    int valid = VALID;
    int wordCount = 0;
    char newLineSearch;
    int done = FALSE;
    int inWord = FALSE;

    do
    {
        newLineSearch = fgetc( flPtr );
        if( newLineSearch == EOF )
        {
            done = TRUE;
        }
        else if( newLineSearch != ' ' && newLineSearch != '\n' )
        {
            inWord = TRUE;
        }
        else if( newLineSearch == ' ' )
        {
            inWord = FALSE;
            wordCount++;
        }
        else if( newLineSearch == '\n' ) /*empty line causes dump*/
        {
            lineCount++;
            if( wordCount != 2 )
            {
                valid = NOT_VALID;
                wordCount = 0;
            }
        }
    } while( !done && valid );
    return valid;
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


int validateColour( char* val, int min, int max )
{
    int valCheck; /* int to store the line value in (not used yet) */
    int success = 1; /* returns -1 if invalid, 1 if valid */
    char* endPtr;
    /* strol's second parameter is an endPtr which points to the character 
       immediately following the string.
       strtol's third parameter is a 'base' parameter - in this case, we are
       working with base 10, so we put 10 */
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

void printLog( double x1, double y1, Tracker* currState, char* cmd )
{
    FILE* logPtr;
    #ifdef DEBUG
    FILE* termPtr; /* additional optional file pointer for standard in */
    termPtr = stderr;
    fprintf( termPtr, "%s ( %6.3f, %6.3f ) - ( %6.3f, %6.3f )\n", cmd, x1, y1,
        (double)currState->currX, (double)currState->currY );
/*    fclose( termPtr ); */
    #endif

    logPtr = fopen( "graphics.log", "a" );

    fprintf( logPtr, "%s ( %6.3f, %6.3f ) - ( %6.3f, %6.3f )\n", cmd, x1, y1,
        (double)currState->currX, (double)currState->currY );
    fclose( logPtr );
}
