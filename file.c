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
   
int readInFile( FILE* flPtr, LinkedList* list )
{
    /* fscanf - check string - then fscanf with format based on string */
    char cmd[CMD_STR_LEN]; /* Array of chars for the command */
    char* val; /* Smaller array for the values */
    int nRead, checkChar; 
    int valid = VALID; /* 1 is !FALSE */
    CmdStruct* instruction; /* Struct to store in each linked list node */
    
    while( valid && !(feof( flPtr )) )
    {
        /* Malloc new char* for the command value */
        val = (char*)malloc(10 * sizeof(char));
        /* Read the first line, expecting two valid strings. */
        nRead = fscanf( flPtr, "%7s %9s", cmd, val );
        if( ( nRead != 2 ) ) 
        {
            valid = NOT_VALID; /* EOF - get outta town */
            free( val );
        }
        else
        {
            /* Initial check: Ensure that the number read in is not all there is
               to it by seeking the newline character.
               checkChar is an int, but it uses the ASCII values to be a char.*/
            checkChar = fgetc(flPtr);
            while( checkChar != '\n' && checkChar != EOF )
            {
                /* Reallocate var char* with 1 extra space for each while loop
                   iteration, accounting for the null terminator, hence +2 */
                val = (char*)realloc( val, strlen(val)+2 );
                val[strlen(val)] = checkChar;
                checkChar = fgetc(flPtr);
            }
            fscanf(flPtr, "\n");
            toUpperCase( cmd ); /* Ensure in upper case */
            if( strcmp( cmd, "FG" ) == 0 ) /* FOREGROUND CHANGE */
            {
                /* Ensure that it is an integer, and it's within range */
                if( validateColour( val, 0, 15 ) != valid )
                {
                    valid = NOT_VALID; 
                    printf( "Colour change out of bounds;\n" );
                    free( val );
                }
                else
                {
                    /* malloc new CmdStruct - declared in main.h */
                    instruction = (CmdStruct*)malloc(sizeof(CmdStruct));
                    /* Struct contents: command (FP) and char[4] value */ 

                    /* set command to address of setFG() */
                    instruction->command = &setFG;
                }
            }
            else if( strcmp( cmd, "BG" ) == 0 ) /* BACKGROUND CHANGE */
            {
                if( validateColour( val, 0, 7 ) != valid )
                {
                    valid = NOT_VALID;
                    printf( "Colour change out of bounds;\n" );
                    free( val );
                    /*fflush(stdout);*/
                }
                else
                {
                    /* malloc new CmdStruct - declared in main.h */
                    instruction = (CmdStruct*)malloc(sizeof(CmdStruct));
                    /* Struct contents: command (FP) and char[4] value */ 

                    instruction->command = &setBG;
                }
            }
            else if( strcmp( cmd, "MOVE" ) == 0 ) /* MOVE COMMAND */
            {
                if( validateReal( val ) != valid )
                {
                    valid = NOT_VALID;
                    printf( "Invalid real number parsed;\n" );
                    free( val );
                }
                else
                {
                    /* malloc new CmdStruct - declared in main.h */
                    instruction = (CmdStruct*)malloc(sizeof(CmdStruct));
                    /* Struct contents: command (FP) and char[4] value */ 

                    instruction->command = &moveCursor;
                }
            }
            else if( strcmp( cmd, "PATTERN" ) == 0 ) /* PATTERN CHANGE */
            {
                if( validateChar( val ) != valid )
                {
                    valid = NOT_VALID;
                    printf( "pattern value invalid;" );
                    free( val );
                }
                else
                {
                    /* malloc new CmdStruct - declared in main.h */
                    instruction = (CmdStruct*)malloc(sizeof(CmdStruct));
                    /* Struct contents: command (FP) and char[4] value */ 

                    instruction->command = &setPattern;
                }
            }
            else if( strcmp( cmd, "DRAW" ) == 0 ) /* DRAW COMMAND */ 
            {
                if( validateReal( val ) != valid )
                {
                    valid = NOT_VALID;
                    printf( "Invalid real number parsed;\n" );
                    free( val );
                }
                else
                {
                    /* malloc new CmdStruct - declared in main.h */
                    instruction = (CmdStruct*)malloc(sizeof(CmdStruct));
                    /* Struct contents: command (FP) and char[4] value */ 

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
                    printf( "Invalid real number parsed;\n" );
                    free( val );
                }
                else
                {
                    /* malloc new CmdStruct - declared in main.h */
                    instruction = (CmdStruct*)malloc(sizeof(CmdStruct));
                    /* Struct contents: command (FP) and char[4] value */ 

                    instruction->command = &changeAngle;
                }
            }
            /* If not finished, assign char* to the struct field
               completing the struct, and add to the back of the list. */
            if( valid )
            {
                /* Populate struct and insert into list */
                instruction->value = val;
                /* Store the line in new LinkedListNode and add to list*/
                insertLast( list, instruction ); 
            } 
        }

        /* Terminate loop if file is invalid or end of file is reached. */
    }
    return valid; /* Send validation integer back to main */
} /*Finish readFile()*/

int checkWordValidity( FILE* flPtr )
{
    int valid = VALID;
    int lineCount = 0;
    int wordCount = 0;
    int newLineSearch;
    int done = FALSE;
    int inWord = FALSE;
    int len = 0;

    do
    {
        newLineSearch = fgetc( flPtr );
        if( newLineSearch == EOF )
        {
            done = TRUE;
        }
        else if( newLineSearch != ' ' && newLineSearch != '\n' )
        {
            if( !inWord )
            {
                inWord = TRUE;
                wordCount++;
            }
            if( wordCount == 1 )
            {
                len++;
            }
        }
        else if( newLineSearch == ' ' && inWord )
        {
            if( wordCount == 1 && len > 7 )
            {
                valid = NOT_VALID;
                printf( "Line %d invalid;\n", lineCount );
            }
            len = 0;
            inWord = FALSE;
        }
        else if( newLineSearch == '\n' ) /*empty line causes dump*/
        {
            if( wordCount != 2 )
            {
                valid = NOT_VALID;
            }
            lineCount++;
            wordCount = 0;
            inWord = FALSE;
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
