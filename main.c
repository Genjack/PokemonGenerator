/* Name: Tim J. Dempsey
   Student ID: 19390664
   Unit and Time: UCP, Tuesdays @ 4pm
   Tutors: Rayden and Elliot

   UCP ASSIGNMENT - MAIN.C
   Contents: This file is designed to control the overall functionality of the
   TurtleGraphics program. It contains the following methods:    

    > main( int, char* );

   stdio.h, stdlib.h, string.h and other required declarations are here.
   Note: Tracker struct is declared in 'main.h'. */

#include "main.h"

int main( int argc, char* argv[] )
{
    /* argv[0] - Program Executable ("turtleGraphics");
       argv[1] - Name of file to read from. */
    
    FILE* flPtr;
    LinkedList* list;
    Tracker* currState; /* pointer to Tracker struct for current state */

    if( argc != 2 )
    {
        printf( "Error: Filename required as extra command-line parameter.\n" );
    }
    else
    {
        /* Create new empty linked list. 
           Function LOCATION: linked_list.c; DECLARED: linked_list.h*/
        list = createList();
        flPtr = fopen( argv[1], "r" );
        
        if( flPtr == NULL )
        {
            perror( "Error: Could not open file.\n" );
        }
        else
        {
            /* Read file into linked list.
               Function LOCATION: file.c; DECLARED: file.h */
            readInFile( flPtr, list );
            /* Nodes are full - each node data void* contains a char* string. */

            /* Malloc a Tracker struct, to begin keeping track of position */
            currState = (Tracker*)malloc(sizeof(Tracker));

            /* Set the state to default values
               Function LOCATION: utility.c; DECLARED: utility.h */
            setDefault( currState );
            printf( "%f\n", currState->currX );
        }
        fclose( flPtr );
    }
    return 0;
}

