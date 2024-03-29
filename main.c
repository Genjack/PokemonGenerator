/* Name: Tim J. Dempsey
   Student ID: 19390664
   Unit and Time: UCP, Tuesdays @ 4pm
   Tutors: Rayden and Elliot

   UCP ASSIGNMENT - MAIN.C
   Contents: This file is designed to control the overall functionality of the
   TurtleGraphics program. It contains the following methods:    

    > main( int, char* );
    > printDashes();

   Note: Tracker struct is declared in 'main.h';
         All function descriptions are located in header files, including for
         main(). 
*/

#include "main.h"

int main( int argc, char* argv[] )
{
    /* argv[0] - Program Executable ("turtleGraphics");
       argv[1] - Name of file to read from, i.e. charizard.txt. */
    
    FILE* flPtr; /*logPtr; Pointer to file being read from */
    LinkedList* list;
    Tracker* currState; /* pointer to Tracker struct for current state */    
    int valid;
    if( argc != 2 )
    {
        printf( "Error: Filename required as extra command-line parameter.\n" );
    }
    else
    {
        flPtr = fopen( argv[1], "r" );
        
        if( flPtr == NULL )
        {   
            perror( "Error: Could not open file.\n" );
        }
        else
        {
            /* Create new empty linked list. 
            Function declaration/description: linked_list.h */
            list = createList();

            /* Read file into linked list.
            Function dec/desc: file.h */
            valid = checkWordValidity( flPtr );
            if( valid == VALID )
            {
                rewind( flPtr ); /* Reset the file Pointer */
                
                /* Print dashes to denote beginning of log file instance */            
                printDashes();

                if( readInFile( flPtr, list ) != 0) /* 0 == FAIL */
                {
                    /* Create a Tracker struct, to keep track of position 
                    Function dec/desc: utility.h */
                    currState = createTracker();

                    /* Read the linked list node-by-node and initiate commands.
                    Function dec/desc: utility.h */
                    readList( list, currState );
                    free( currState );
                }
                else
                {
                    printf( "Error: invalid file. Exiting.\n" );
                }
            }
            else
            {
                printf( "Error: invalid file. Exiting.\n" );
            }
            fclose( flPtr );
            free( list );
        }
    }
    return 0;
}

void printDashes()
{
    FILE* logPtr = fopen( "graphics.log", "a" );
    
    fprintf( logPtr, "---\n" );
    fclose( logPtr );
}
