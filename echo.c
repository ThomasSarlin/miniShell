/* echo.c
 * Thomas Sarlin
 * Laboration 3 : Systemnära programmering, HT-18
 * Responsible for the echo command
 */
#include <stdio.h>
#include <stdlib.h>
#include "echo.h"
/**
 * Name: echo
 * Purpose: extracts information from command and prints the 
 * information accordingly.
 * Parameters:  echo command
 * */

void echo(command com){
	switch(checkInput(com)){
		case 1:
			fileToFile(com);
			break;
		case 2:
			fileToEcho(com);
			break;
		case 3:
			comToFile(com);
			break;
		default:
			defaultEcho(com);
			break;
	}
}

/**
 * Name: checkInput
 * Purpose: checks in and out files from command
 * Parameters:  echo command
 * Return values: 1 if both in/out files existst
 * 				, 2 with inile
 *				, 3 if outfile exists
 *				, 0 if no redirections.
 * */
int checkInput(command com){
	int result =0; 
    if(com.infile!=NULL && com.outfile!=NULL)
    	result=1;
    else if(com.infile!=NULL && com.outfile==NULL)
    	result=2;              
    else if(com.infile==NULL && com.outfile!=NULL)
		result=3;	
	return result;
}
/**
 * Name: fileToFile
 * Purpose: prints from file to another file.
 * Parameters: echo command
 * comment: exit 1 if files doesn't exists or can't 
 *			be created.
 * */
void fileToFile(command com){
	FILE *infile,*outfile;
	char c;
	if((infile=fopen(com.infile,"r"))==NULL){
		perror(com.infile);
		exit(1);
	}
	if((outfile=fopen(com.outfile,"w"))==NULL){
		perror(com.outfile);
		exit(1);
	}
	while((c= getc(infile))!=EOF)
		putc(c,outfile);
	
	fclose(outfile);
	fclose(infile);
}
/**
 * Name: fileToEcho
 * Purpose: prints file to stdout.
 * Parameters:  echo command
 * Comment: exit(1) if infile does not exists.
 * */
void fileToEcho(command com){
	FILE *infile;
	char c;
	if((infile=fopen(com.infile,"r"))==NULL){
		perror(com.infile);
		exit(1);
	}
	while((c= getc(infile))!=EOF)
		printf("%c",c);
	
	fclose(infile);
}
/**
 * Name: comToFile
 * Purpose: prints command to file
 * Parameters:  echo command.
 * Comment: exit(1) if file does not exist.
 */
void comToFile(command com){
	int i=1;
	FILE *outfile;
	outfile=fopen(com.outfile,"w");
	while(*(com.argv+i)!=NULL){
		fputs((*(com.argv+i)),outfile);
		(i<com.argc-1)?putc(' ',outfile):putc('\n',outfile);
		i++;
	}
	
	fclose(outfile);
}
/**
 * Name: defaultEcho
 * Purpose: prints command to stdout.
 * Parameters:  echo command
 * */
void defaultEcho(command com){
	int i=1;
	while((*(com.argv+i))!=NULL){
		printf("%s",(*(com.argv+i)));
		(i<com.argc-1)?printf(" "):printf("\n");
		i++;
	}
}

