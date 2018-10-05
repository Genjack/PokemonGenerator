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
* PURPOSE:
*   TO DO
* HOW IT WORKS:
*   TO DO
**/
Tracker* createTracker();

/**
* FUNCTION readList
* PURPOSE:
*   TO DO
* HOW IT WORKS:
*   TO DO
**/  
void readList( LinkedList*, Tracker* );

/**
* FUNCTION moveCursor
* PURPOSE:
*   TO DO
* HOW IT WORKS:
*   TO DO
**/  
void moveCursor( double, Tracker* );

#endif
