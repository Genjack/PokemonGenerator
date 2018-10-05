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

Tracker* createTracker()
{
    /* Initialise and malloc new Tracker struct pointer */
    Tracker* currState;
    currState = (Tracker*)malloc(sizeof(Tracker));
    
    /* Set everything to default */
    currState->currX = 0.0; /* x-axis position begins at 0 */ 
    currState->currY = 0.0; /* y-axis position begins at 0 */ 
    currState->currAngle = 0.0; /* Initial angle is 0 - facing right */
    
    currState->currFG = 7;
    setFgColour( currState->currFG );
    
    currState->currBG = 0;
    setBgColour( currState->currBG );

    currState->currPattern = '+';
    return currState;
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

void drawLine( char* inDistance, Tracker* currState )
{
    double x1, double y1; /* cast to ints when calling line() */
    x1 = currState->currX;
    y1 = currState->currY;

    moveCursor( inDistance, currState ); /* cursor is now at x2, y2 */

    x1 += 0.5;
    x1 = floor( x1 ); /* becomes int-friendly */
    y1 += 0.5;
    y1 = floor( y1 );
    x2 = currState->currX + 0.5;
    x2 = floor( x2 );
    y2 = currState->currY + 0.5;
    y2 = floor( y2 );

    line( x1, y1, x2, y2, &plotPoint, currState );
}

void plotPoint( Tracker* currState )
{
    printf( "%c", currState->currPattern );
}

void changeAngle( char* angleChange, Tracker* currState )
{ 
    double rotation, temp;
    rotatation = atof( angleChange ); 
    
    temp = rotation + currState->currAngle;
    while( temp > 360 )
    {
        temp -= 360;
    }
    if( temp < 0 )
    {
        while( temp < 0 )
        {
            temp += 180;
        }
    }
    currState->currAngle = temp;
}

void setFG( char* inColour, Tracker* currState )
{
    /* Validation completed in file.c */
    currState->currFG = atoi( inColour ); /* Struct colour updated */
    /* Call function in effects.h to actually effect the change */
    setFgColour( currState->currFG );
}

void setBG( char* inColour, Tracker* currState )
{
    /* Validation completed in file.c */
    currState->currBG = atoi( inColour ); /* Struct colour updated */
    /* Call function in effects.h to actually effect the change */
    setBgColour( currState->currBG );
}
    
void setPattern( char* inPattern, Tracker* currState )
{
    /* Validation already completed */
    currState->currPattern = inPattern[0];
}


