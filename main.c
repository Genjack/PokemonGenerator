/* Name: Tim J. Dempsey
   Student ID: 19390664
   Unit and Time: UCP, Tuesdays @ 4pm
   Tutors: Rayden and Elliot

   UCP ASSIGNMENT - MAIN.C
   Contents: This file is designed to control the overall functionality of the
   TurtleGraphics program. It contains the following methods:    

    > main( int, char* );

   stdio.h, stdlib.h, string.h and other required declarations are here.
   Note: Tracker struct is declared in 'main.h';
         All function descriptions are located in header files. */

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
        flPtr = fopen( argv[1], "r" );
        
        if( flPtr == NULL )
        {
            perror( "Error: Could not open file.\n" );
        }
        else
        {
            /* Create new empty linked list. 
            Function LOCATION: linked_list.c; DECLARED: linked_list.h*/
            list = createList();

            /* Read file into linked list.
            Function LOCATION: file.c; DECLARED: file.h */
            if( readInFile( flPtr, list ) == 0)
            {
                
            }
            
            /* Malloc a Tracker struct, to begin keeping track of position */
            currState = (Tracker*)malloc(sizeof(Tracker));

            /* Set the state to default values
               Function LOCATION: utility.c; DECLARED: utility.h */
            setDefault( currState );

            /* Read the linked list node-by-node and initiate commands.
               Function LOCATION: utility.c; DECLARED: utility.h */
            readList( list, currState );
        

            fclose( flPtr );
        }
    }
    return 0;
}

