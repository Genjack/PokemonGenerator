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

void setDefault( Tracker* currState )
{
    currState->currX = 0.0; /* x-axis position begins at 0 */ 
    currState->currY = 0.0; /* y-axis position begins at 0 */ 
    currState->currAngle = 0.0; /* Initial angle is 0 - facing right */
    
    currState->currFG = 7;
    setFgColor( currState->currFG );
    
    currState->currBG = 0;
    setBgColor( currState->currBG );

    currState->currPattern = '+';
}
    
