/**
* cd.c
* Thomas Sarlin
* Laboration 3: Systemnära programmering, HT-18
* Responsible for changing directory
*/

#include <stdio.h>
#include <unistd.h>
#include "cd.h"
#include "parser.h"
void cd(char* dir){
	if(chdir(dir))perror(dir);
}
