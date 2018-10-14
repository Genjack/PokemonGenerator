/* Name: Tim J. Dempsey
   Student ID: 19390664
   Unit and Time: UCP, Tuesdays @ 4pm
   Tutors: Rayden and Elliot

   UCP ASSIGNMENT - FILE.H
   Contents: This is the header file for file.c, containing the function
   declarations for the following methods:

    > readInFile( FILE*, LinkedList* );
*/

#ifndef FILE_H
#define FILE_H

#include "linked_list.h"
#include "main.h"
#include "effects.h" /* For setFgColour(int) and setBgColour(int) */
#include "utility.h" /* For moveCursor */

#define CMD_STR_LEN 8 /* PATTERN = 7 + 1('\0') = longest valid string */

#define FALSE 0
#define TRUE !FALSE

#define VALID TRUE
#define NOT_VALID FALSE

/* FUNCTION DECLARATIONS */

/**
* FUNCTION: readInFile
* IMPORTS: File* - the file to read in, hopefully containing valid commands.
*          LinkedList* - Pointer to a linked list to store structs.
* PURPOSE: 
*    This is a key method that reads in the file and makes the necessary
*    calls to storage and other methods so that the draw and move operations
*    can be initiated.
* HOW IT WORKS: 
*    Works inside a for loop, defined with the imported int as a boundary. Each
*    loop, a CmdStruct is malloced, and the line is read. All content is
*    validated, and if valid, the struct's function pointer is set to point to 
*    the relevant function, while the char* is set to the value of the command.
*    Returns an integer representing a success code - if -1, it's failed, if 0
*    it's all good.
**/
int readInFile( FILE*, LinkedList* );

int checkWordValidity( FILE* );

/** 
* FUNCTION: toUpperCase
* PURPOSE:
*   Ensure that all valid commands from file are formatted in upper case to 
*   avoid errors and promote usability.
* HOW IT WORKS:
*   Takes a char pointer, which points at an array of chars; iterates over each
*   character, and if the ASCII value of the character falls within the lower
*   case range, it subtracts 32 from the value, which converts the character to
*   upper case.
* HOW IT RELATES:
*   Struggles; upper case characters can be pretty stuck up. Also, it fits in by
*   ensuring that any case-insensitivity in the file is not an issue. Will be 
*   called by the main.c file to sanitise the data after file read.
**/
void toUpperCase( char* );

/**
*  FUNCTION: validateColour
*  IMPORTS: char* - the parsed value of the FG/BG command.
*           int - Minimum range of FG/BG, 0.
*           int - Maximum range of FG/BG, 15 or 7 respectively.
*  PURPOSE: 
*    To check that the imported char* can be successfully converted to an int.
*  HOW IT WORKS:
*    Uses strtol() to check that the value can indeed be converted to an
*    integer; if not, it returns a success value of -1.
*  HOW IT RELATES:
*    There is a specific colour range allowed for printing to terminal - this 
*    ensures that the program continues smoothly.
**/
int validateColour( char*, int, int );

/**
*  FUNCTION: validateReal
*  IMPORTS: char* - the parsed value of the real number as a string.
*  PURPOSE: 
*    To check that the imported char* can be successfully converted to a real.
*  HOW IT WORKS:
*    Uses strtod() to check that the value can indeed be converted to a
*    real; if not, it returns a success value of -1.
*  HOW IT RELATES:
*    The real numbers are very important in determining angles and distances
*    when drawing - validation here is vital.
**/
int validateReal( char* );

/**
*  FUNCTION: validateChar
*  IMPORTS: char* - the parsed value of the real number as a string.
*  PURPOSE: 
*    To check that the imported char* is just a char, and no longer.
*  HOW IT WORKS:
*    Uses strlen() to check the length of the char* - if it isn't 1, then it 
*    means that the pattern is certainly invalid.
*  HOW IT RELATES:
*    Another brick in the wall of validation. Essentially, the length of the
*    char* is all that matters here, because any char can be used if it's a 
*    printable character.
**/
int validateChar( char* );

/**
*  FUNCTION: printLog
*  IMPORTS: double - real value of initial position of cursor on x-axis.
*           double - real value of initial position of cursor on y-axis.
*           Tracker* - Pointer to the Tracker struct.
*           char* - string representing the command (MOVE or DRAW).
*  PURPOSE: 
*    To print out the command to either a log file or terminal in a highly
*    formatted manner.
*  HOW IT WORKS:
*    printLog() is called from within either the moveCursor() or drawLine() 
*    functions, and uses the coordinates given to chart the movements of the
*    cursor. If DEBUG is not defined, the results are only printed to a
*    logfile, which is created once and then appended to each time. If DEBUG
*    is defined, it also prints the results to terminal.  
*  HOW IT RELATES:
*    This function allows the user to view their coordinate movements each
*    time a move or draw command is given, and helps to give a better sense of
*    what the program is doing at each step.    
**/
void printLog( double, double, Tracker*, char* );

#endif
