/* mish.h
 * Thomas Sarlin
 * Laboration 3 : Systemnära programmering, HT-18
 * Responsible for running the program mish
 */

/**
 * Name: userLoop
 * Purpose: reads input from the user with stdin
 * Parameters:  -Array av typen command struct enligt parser.h 
 * 		med information om de commandon som ska köras
 *		-antalet kommandon som användaren har angivit.
 * Return values: 1 on error, 0 on success.
 * */

int userLoop(void);


/**
 * Name: runCommand
 * Purpose: executes commandos from the user.
 * Parameters:  -Array av typen command struct enligt parser.h 
 * 		med information om de commandon som ska köras
 *		-antalet kommandon som användaren har angivit.
 * Return values: void
 * */

void runCommand(command[],int);
/**
 * Name: sysprint
 * Purpose: stderr print for mish command row.
 * Parameters:  void 
 * Return values: void
 * */

void sysprint(void);

/**
 * Name: checkFunction
 * Purpose: checks if the argument is internal or external
 * Parameters:  first argument of command
 * Return values: 0 if function is external, 1 if echo, 2 for cd
 * Comment: should not be called if there are no arguments.
 * */

int checkFunction(char*);

/**
 * Name: sighandler
 * Purpose: Ingnoring ctrl+c and instead of closing the program
 *  the prompt will be reprinted, propsing the user to enter a vaild
 *  commmand. 
 * Parameters: signal
 *  */
void sighandler(int);
