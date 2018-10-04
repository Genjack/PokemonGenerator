/* Name: Tim J. Dempsey
   Student ID: 19390664
   Unit and Time: UCP, Tuesdays @ 4pm
   Contents: Header file for main.c, UCP Assignment 2018 S2.

   This file contains header declarations for C89 functionality, including:
   > stdio, stdlib, string.h;
   > STRUCT Tracker, Command;
*/

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "linked_list.h"

/* DEFINE: my function pointer for move/draw/change angle */
typedef void (*CmdFunc)(char*, Tracker*); /*type name is 'CmdFunc' */
/* Declaration example: CmdFunc command = &function; */

/* Don't think I need these anymore - I think I can just define one function
   pointer type and then use that for everything..? */
typedef void( *pFuncPtr )( void* data ); /* Print function pointer */
typedef void( *fFuncPtr )( void* data ); /* Free function pointer */


/** 
*  STRUCT: Tracker
*  PURPOSE: To hold all of the information necessary to track the current state
*     of the program instance - pointers to doubles for coordinates, a pointer  
*     to double for the current angle, int pointers for the current colours 
*     (FG and BG) and a char pointer representing the current pattern.
*   HOW IT WORKS: main.c will pass a pointer to this struct around, and via this
*      pointer I can access and update the relevant datatypes as I go.
*   HOW IT RELATES: Other functions that require this information will have
*      access to the data via the pointer and appropriate dereferencing. 
**/
typedef struct
{
    double currX; 
    double currY; 
    double currAngle;
    int currFG; /* Range: 0-15 */
    int currBG; /* Range: 0-7 */
    char currPattern; /* Default: '+' */
} Tracker;

/**
*  STRUCT: Command
*  PURPOSE: Takes two fields - command (function pointer) and value (void
*   pointer). 'command' will be defined as a function that returns void and 
*   takes a void*. The void* pointer will be cast according to the line from 
*   file that we read.
*  HOW IT WORKS: 
*  HOW IT RELATES: 
**/
typedef struct
{
    CmdFunc command;            /* Function pointer */
    char value[VAL_STR_LEN];    /* imported values from file */
} CmdStruct;

#include "utility.h" /* Included below Tracker declaration to avoid errors */
#include "effects.h"

#endif
