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
    CmdStruct* cmd;
    while( list->count > 0 )
    {
        /* Call the function contained within each node:
        list node -> void* data (CmdStruct) -> command/value fields */
        cmd = (CmdStruct*)(removeFirst( list ));
        (*cmd->command)(cmd->value, currState);
        free( cmd );
    }
}

void moveCursor( char* inDistance, Tracker* currState )
{
    double angleInRadians, distance;
    /* Usage of atof VALIDATED because I have already VALIDATED (file.c) */
    distance = atof( inDistance );

    angleInRadians = currState->currAngle / (PI/180.0);

    currState->currX += distance * cos( angleInRadians ); 
    currState->currY += distance * sin( angleInRadians );
}

void changeAngle( char* angleChange, Tracker* currState )
{ 
    
