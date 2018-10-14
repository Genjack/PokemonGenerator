/* Name: Tim J. Dempsey
   Student ID: 19390664
   Unit and Time: UCP, Tuesdays @ 4pm
   Tutors: Rayden and Elliot

   UCP ASSIGNMENT - UTILITY.C
   Contents: This file contains any methods needed to facilitate the drawing of
      the object that I have written myself (so excluding effects.c methods):
    > createTracker();
    > readList( LinkedList*, Tracker* );
    > moveCursor( char*, Tracker* );
    > drawLine( char*, Tracker* );
    > plotPoint( void* );
    > changeAngle( char*, Tracker* );
    > setFG( char*, Tracker* );
    > setBG( char*, Tracker* );
    > roundReal( double );
    > calcMovement( char*, Tracker* );
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

    clearScreen();
    #ifdef SIMPLE
    setFgColour( 0 );
    setBgColour( 7 );
    #endif
    while( list->count > 0 )
    {
        /* Call the function contained within each node:
        list node -> void* data (CmdStruct) -> command/value fields */
        cmd = (CmdStruct*)(removeFirst( list ));
        (*cmd->command)(cmd->value, currState);
        free( cmd );
    }
    penDown();
}

void moveCursor( char* inDistance, Tracker* currState )
{
    double x1, y1;
    /* Usage of atof VALIDATED because I have already VALIDATED (file.c) */

    x1 = currState->currX;
    y1 = currState->currY;

    calcMovement( inDistance, currState );

    printLog( x1, y1, currState, "MOVE" );
}

void drawLine( char* inDistance, Tracker* currState )
{
    double x1, y1, x2, y2; /* cast to ints when calling line() */

    x1 = currState->currX;
    y1 = currState->currY; /* original position is set to x/y1. */

    calcMovement( inDistance, currState );

    x1 = roundReal( x1 );
    y1 = roundReal( y1 );
    x2 = roundReal( currState->currX );
    y2 = roundReal( currState->currY );
    /* ... calls to line() to be preceded by relevant log file entries..."*/
    #ifdef DEBUG
    printLog( x1, y1, currState, "DRAW" ); 
    #endif

    line( (int)x1, (int)y1, (int)x2-1, (int)y2, &plotPoint, (void*)currState );

    #ifndef DEBUG    
    printLog( x1, y1, currState, "DRAW" ); 
    #endif
}

void plotPoint( void* currState )
{
    Tracker* current;
    current = (Tracker*)currState;
    printf( "%c", current->currPattern );
}

void changeAngle( char* angleChange, Tracker* currState )
{ 
    double rotation, temp;
    rotation = atof( angleChange ); 
    
    temp = rotation + currState->currAngle;
    while( temp > 360.0 )
    {
        temp -= 360.0;
    }
    if( temp < 0.0 )
    {
        while( temp < 0.0 )
        {
            temp += 360.0;
        }
    }
    currState->currAngle = temp;
}

void setFG( char* inColour, Tracker* currState )
{
    /* Validation completed in file.c */
    currState->currFG = atoi( inColour ); /* Struct colour updated */
    /* Call function in effects.h to actually effect the change */
    #ifndef SIMPLE
    setFgColour( currState->currFG );
    #endif
}

void setBG( char* inColour, Tracker* currState )
{
    /* Validation completed in file.c */
    currState->currBG = atoi( inColour ); /* Struct colour updated */
    /* Call function in effects.h to actually effect the change */
    #ifndef SIMPLE
    setBgColour( currState->currBG );
    #endif
}
    
void setPattern( char* inPattern, Tracker* currState )
{
    /* Validation already completed */
    currState->currPattern = inPattern[0];
}

double roundReal( double num )
{
    double rounded;
    
    if( num >= 0.0 ) /* Unlikely to be exactly 0 without tolerance, but wahey */
    {
        rounded = num + 0.5;
        rounded = floor( rounded );
    }
    else /* num < 0; should round up basically */
    {
        rounded = num - 0.5;
        rounded = ceil( rounded );
    }
    return rounded;
}

void calcMovement( char* inDistance, Tracker* currState )
{
    double angleInRadians, distance;

    distance = atof( inDistance );
    
    angleInRadians = ( currState->currAngle * PI ) / 180.0;
     
    currState->currX += distance * cos( angleInRadians );
    currState->currY -= distance * sin( angleInRadians );
}
