#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int dupPipe(int pip[2],int end, int destfd){
	int pipe = dup2(pip[end],destfd);
	close(pip[end]);
	return pipe;
}


int redirect(char *filename, int flags, int desfd){
	char *flag =(flags==1)?"w":"r";
	FILE *filefd;
	int newfd=-1;
	if((filefd = fopen(filename,flag))==NULL){
		perror(filename);
	}
	else
		newfd=dup2(fileno(filefd),desfd);
	fclose(filefd);
	return newfd;
}
