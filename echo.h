/* echo.c
 * Thomas Sarlin
 * Laboration 3 : Systemnära programmering, HT-18
 * Responsible for the echo command
 */

#include "parser.h"
/**
 * Name: echo
 * Purpose: extracts information from command and prints the 
 * information accordingly.
 * Parameters:  echo command
 * */
void echo(command);
/**
 * Name: checkInput
 * Purpose: checks in and out files from command
 * Parameters:  echo command
 * Return values: 1 if both in/out files existst
 * 				, 2 with inile
 *				, 3 if outfile exists
 *				, 0 if no redirections.
 * */
int checkInput(command);
/**
 * Name: fileToFile
 * Purpose: prints from file to another file.
 * Parameters: echo command
 * comment: exit 1 if files doesn't exists or can't 
 *			be created.
 * */
void fileToFile(command);
/**
 * Name: fileToEcho
 * Purpose: prints file to stdout.
 * Parameters:  echo command
 * Comment: exit(1) if infile does not exists.
 * */
void fileToEcho(command);
/**
 * Name: comToFile
 * Purpose: prints command to file
 * Parameters:  echo command.
 * Comment: exit(1) if file does not exist.
 */
void comToFile(command);
/**
 * Name: defaultEcho
 * Purpose: prints command to stdout.
 * Parameters:  echo command
 * */
void defaultEcho(command);
