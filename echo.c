#include <stdio.h>
#include <stdlib.h>
#include "echo.h"

void echo(command com){
	switch(checkInput(com)){
		case 0:
			fileToFile(com);
			break;
		case 1:
			fileToEcho(com);
			break;
		case 2:
			comToFile(com);
			break;
		default:
			defaultEcho(com);
			break;
	}
}

int checkInput(command com){
	int result =-1; 
        if(com.infile!=NULL && com.outfile!=NULL){
        	result=0;
	}
        else if(com.infile!=NULL && com.outfile==NULL){
        	result=1;              
	}
        else if(com.infile==NULL && com.outfile!=NULL){
		result=2;
	}	
	return result;
}
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
void defaultEcho(command com){
	int i=1;
	while((*(com.argv+i))!=NULL){
		printf("%s",(*(com.argv+i)));
		(i<com.argc-1)?printf(" "):printf("\n");
		i++;
	}
}

