/* Name: Tim J. Dempsey
   Student ID: 19390664
   Unit and Time: UCP, Tuesdays @ 4pm
   Tutors: Rayden and Elliot

   UCP ASSIGNMENT - UTILITY.H
   Contents: This is the header file for utility.c, containing the relevant 
      forward declarations.
*/
#ifndef UTILITY_H
#define UTILITY_H

#include <math.h>
#include "main.h"
#include "effects.h"

#define PI 3.14159265358979323846

/**
* FUNCTION createTracker
* IMPORTS: N/A
* PURPOSE: 
*    Initialises, mallocs and sets the Tracker pointer.
* HOW IT WORKS:
*    The Tracker struct keeps track of the values the program moves along, so
*    the pointer always has access to up to date fields. The pointer is 
*    malloced, and then all fields are set to their default.
* HOW IT RELATES:
*    The Tracker pointer is passed around the majority of the program so it 
*    can update its fields as needed.
**/
Tracker* createTracker();

/**
* FUNCTION readList
* IMPORTS: LinkedList* - The list.
*          Tracker* - current state for updating.
* PURPOSE:
*    To iterate through the list, calling each function pointer as it goes,
*    while freeing the nodes.
* HOW IT WORKS:
*    A new CmdStruct is declared, and with each while loop iteration, the list
*    assigns it its first node via removeFirst(). The struct accesses the 
*    function pointer that it contains, and calls it by passing it the value
*    of its other field (char* value) plus Tracker*. The struct is then freed.
* HOW IT RELATES:
*    While it frees the list, it manipulates the cursor, draws and updates 
*    fields in the background.
**/  
void readList( LinkedList*, Tracker* );

/**
* FUNCTION moveCursor
* IMPORTS: char* - A string representation of the distance as a real number.
*          Tracker* - Current state.
* PURPOSE:
*    To move the cursor from the old coordinates to the new.
* HOW IT WORKS:
*    Sets variables x1 and y1 to hold the current coordinates of the cursor, 
*    and then Calls calcMovement() to determine the movement details, before
*    making a call to printLog() to chart the movement to file/stdout.
* HOW IT RELATES:
*    Handles cursor movement without drawing.
**/  
void moveCursor( char*, Tracker* );

/**
* FUNCTION drawLine
* IMPORTS: char* - String representation of distance as a real number.
*          Tracker* - current state.
* PURPOSE:
*    Controls the handling of data before it's passed to the line() function, 
*    by calculating the coordinates with calcMovement() before rounding the
*    numbers and sending to line(). Charts the draw action to logfile/stdout.
* HOW IT WORKS:
*    Similar to moveCursor(), but with the additional rounding and call to 
*    line().
* HOW IT RELATES:
*    Links the effects.c file for the more complex line plotting functions.
**/  
void drawLine( char*, Tracker* );

/**
* FUNCTION plotPoint
* IMPORTS: void* - void representation of the Tracker*
* PURPOSE: 
*    Plots the current character at the current coordinates.
* HOW IT WORKS:
*    Takes in the void*, casts it to a Tracker* and prints the current pattern
*    as a char.
* HOW IT RELATES:
*    This function is really controlled by the line() function in effects.c, 
*    and serves only to print the current character.
**/  
void plotPoint( void* );

/**
* FUNCTION changeAngle
* IMPORTS: char* - String representation of the current angle.
*          Tracker* - The current state.
* PURPOSE:
*    To update the current angle.
* HOW IT WORKS:
*    Reads the char* with atof() to receive the amount by which to change the 
*    angle - this is possible due to the fact that the double has already 
*    been validated thanks to file.c. If the resulting angle is over 360, 
*    360 is subtracted from the total until it's less; and likewise, if the 
*    resulting angle is below 0, 360 is added until it is between 0 and 360.
* HOW IT RELATES:
*    The angle dictates the direction in which the cursor moves, and so this
*    function is another element in ensuring an accurate rendition of the file.
**/  
void changeAngle( char*, Tracker* );

/**
* FUNCTION setFG
* IMPORTS: char* - String representation of the current colour as an integer.
*          Tracker* - The current state.
* PURPOSE:
*    To update the current foreground (text) colour.
* HOW IT WORKS:
*    The char* is converted to integer with atoi() - prior validation has been
*    performed in file.c - and the tracker then uses this value to update the
*    currFG integer it holds.
* HOW IT RELATES:
*    Another element to drawing the input file.
**/  
void setFG( char*, Tracker* );

/**
* FUNCTION setBG
* IMPORTS: char* - String representation of the current colour as an integer.
*          Tracker* - The current state.
* PURPOSE:
*    To update the current background (terminal window) colour behind text.
* HOW IT WORKS:
*    The char* is converted to integer with atoi() - prior validation has been
*    performed in file.c - and the tracker then uses this value to update the
*    currBG integer it holds.
* HOW IT RELATES:
*    Another element to drawing the input file.
**/
void setBG( char*, Tracker* );

/** 
* FUNCTION setPattern
* IMPORTS: char* - String representation of the pattern char.
*          Tracker* - The current state.
* PURPOSE:
*    To update the current pattern character.
* HOW IT WORKS:
*    The tracker* accesses the current pattern, which is a char, and sets the
*    first index of the string to be the new pattern (it will only have a
*    string length of 1 anyway owing to prior validation in file.c ).
* HOW IT RELATES:
*    Another element to drawing the input file.
**/  
void setPattern( char*, Tracker* );

/**
* FUNCTION roundReal
* IMPORTS: double - the number to be rounded
* PURPOSE: 
*    To round the double to the nearest integer so it can be passed to line().
* HOW IT WORKS:
*    Checks if the double is positive (or 0), adds 0.5 and floors(), which
*    basically truncates it to the nearest integer. If negative, it subtracts
*    0.5 and ceils().
* HOW IT RELATES:
*    Necessary function for passing to line(), which was not written by us.
**/
double roundReal( double );

/**
* FUNCTION calcMovement
* IMPORTS: char* - String representation of the distance.
*          Tracker* - The current state.
* PURPOSE: 
*    To calculate the new coordinates of x and y based on the angle and 
*    distance.
* HOW IT WORKS:
*    The distance is parsed using atof(), again doable because of prior
*    validation in file.c, and the angle in Radians is calculated by 
*    converting the current angle to radians with the help of PI, which I
*    defined at the top of this header file. From there, the calculations 
*    given to us in the spec are applied to the current state, which updates
*    the cursor position accordingly.
* HOW IT RELATES:
*    This function is called by both moveCursor() and drawLine(), providing
*    the math required to accurately render the input file.
**/
void calcMovement( char*, Tracker* );

#endif
