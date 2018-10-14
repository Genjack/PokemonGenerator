/* Name: Tim J. Dempsey
   Student ID: 19390664
   Unit and Time: UCP, Tuesdays @ 4pm
   Contents: Header file for main.c, UCP Assignment 2018 S2.

   This file contains header declarations for C89 functionality, including:
   > stdio, stdlib, string.h;
   > STRUCT Tracker, Command;
   > INT VAL_STR_LEN;
*/

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

/*#define VAL_STR_LEN 4  Allows for 3 digits plus null term (i.e. 360) */

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


/*****************************************************************************
* FUNCTION POINTER: CmdFunc
* PURPOSE:
*    This function pointer is designed to be able to point to all of the 
*    functions related to commands, i.e. setBG/FG, draw, move, update, so that
*    when reading the file, I only have to check which command the line holds
*    once.
* HOW IT WORKS:
*    When the file is read, the first string is parsed for a command. 
*    Depending on which command it is (determined with more if statements than
*    a poorly thought-out conspiracy theory), the function pointer is given
*    the memory address of the relevant function. When the list is read, it 
*    just calls the function that each pointer points to.
* HOW IT RELATES:
*    It's set in file.c, and used in utility.c.
**/
typedef void (*CmdFunc)(char*, Tracker*); /*type name is 'CmdFunc' */
/* Declaration example: CmdFunc command = &function; */

/*****************************************************************************
*  STRUCT: Command
*  PURPOSE: Takes two fields - command (function pointer) and value (void
*    pointer). 'command' will be defined as a function that returns void and 
*    takes a void*. The void* pointer will be cast according to the line from 
*    file that we read.
*  HOW IT WORKS: 
*    Firstly, it's declared below CmdFunc because it references CmdFunc. It 
*    consists of a CmdFunc pointer and a char*, which together will be able to
*    hold a valid line of information from an input file. The CmdFunc pointer
*    takes the char* with it when it goes to do its duty.
*  HOW IT RELATES: 
*    Ties the file reading and the list reading together, by translating the
*    input file into two distinct values that can be read from the list.
**/
typedef struct
{
    CmdFunc command;            /* Function pointer */
    char* value;    /* imported values from file */
} CmdStruct;


/****** Both header files are below Tracker declaration to avoid errors. *****/
#include "utility.h" 
#include "file.h"

/*****************************************************************************
*  FUNCTION: main
*  PURPOSE:
*    main() is the first point of call for the program, and acts like a flow
*    of events. It calls all the required functions to complete the drawing
*    of the input file, and cleans up at the end. 
*  HOW IT WORKS: 
*    main takes in the input file as argv[1], and if supplied, opens a FILE*
*    for parsing it. From there, it creates a linked list, checks the length
*    of the file, and passes the information into the list. If successful, it
*    creates a default Tracker*, and reads the list node-by-node, before
*    freeing all memory and closing the file.
*  HOW IT RELATES: 
*    Links all files and functions together into a flow of events.
**/


/*****************************************************************************
*  FUNCTION: printDash
*  PURPOSE: Prints "---" to logfile at the start of each program instance.
*  HOW IT WORKS: 
*    main() calls it - it uses the same FILE* ('graphics.log) to append. 
*  HOW IT RELATES: 
*    Separates all program logfile instances.
**/
void printDashes();

#endif
