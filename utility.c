/* Name: Tim J. Dempsey
   Student ID: 19390664
   Unit and Time: UCP, Tuesdays @ 4pm
   Tutors: Rayden and Elliot

   UCP ASSIGNMENT - UTILITY.C
   Contents: This file contains any methods needed to facilitate the drawing of
      the object that I have written myself (so excluding effects.c methods):
    > setDefault( Tracker* currState );
*/

#include "utility.h"
#include "effects.h" /* For the setFg and setBg methods */
#include "file.h" /* for toUpperCase method */

void setDefault( Tracker* currState )
{
    currState->currX = 0.0; /* x-axis position begins at 0 */ 
    currState->currY = 0.0; /* y-axis position begins at 0 */ 
    currState->currAngle = 0.0; /* Initial angle is 0 - facing right */
    
    currState->currFG = 7;
    setFgColour( currState->currFG );
    
    currState->currBG = 0;
    setBgColour( currState->currBG );

    currState->currPattern = '+';
}

void readList( LinkedList* list, Tracker* currState )
{
    /* strcmp; */
    LinkedListNode* currNode;
    char cmd[8]; /* array to hold command for each node */
    char trash[8]; /* junk array to take the command time fscanf goes. */
    double distance, angleChange;
    int lineNum;
    

    /* Set the current node to the start of the list. */
    currNode = list->head;
    lineNum = list->count;

    while( currNode != NULL )
    {
        /* Check the command */
        sscanf( (char*)currNode->data, "%s", cmd );
        toUpperCase( cmd ); /* Ensure in upper case */

        if( strcmp( cmd, "FG" ) == 0 ) /* FOREGROUND CHANGE */
        {
            sscanf( (char*)currNode->data, "%s %d", trash, 
                &currState->currFG );
        }
        else if( strcmp( cmd, "BG" ) == 0 ) /* BACKGROUND CHANGE */
        {
            sscanf( (char*)currNode->data, "%s %d", trash, 
                &currState->currBG );
    printf( "BG Colour: %d\n", currState->currBG );
        }
        else if( strcmp( cmd, "MOVE" ) == 0 ) /* MOVE COMMAND */
        {
            sscanf( (char*)currNode->data, "%s %lf", trash, &distance );
    printf( "distance: %f\n", distance );
            /* Do something with the distance and moving etc */
            moveCursor( distance, currState );
            printf( "cursor position: %f, %f\n", currState->currX,
                currState->currY );
        }
        else if( strcmp( cmd, "PATTERN" ) == 0 ) /* PATTERN CHANGE */
        {
            sscanf( (char*)currNode->data, "%s %c", trash, 
                &currState->currPattern );
        }
        else if( strcmp( cmd, "DRAW" ) == 0 ) /* DRAW COMMAND */
        {
            sscanf( (char*)currNode->data, "%s %lf", trash, &distance );
            /* Do something with drawing */
        }
        else if( strcmp( cmd, "ROTATE" ) == 0 ) /* ROTATE CURSOR */
        {
            sscanf( (char*)currNode->data, "%s %lf", trash, &angleChange );
            /* Calculate new angle and store it in currState->currAngle */
        }
        else /* INVALID LINE */
        {
            printf( "Error: line %d is invalid.\n", lineNum );
        }
        lineNum++;
        currNode = currNode->next;
    }
}

void moveCursor( double distance, Tracker* currState )
{
    double angleInRadians;
    angleInRadians = currState->currAngle / (PI/180);

    currState->currX += distance * cos( angleInRadians ); 
    currState->currY += distance * sin( angleInRadians );
}

    
