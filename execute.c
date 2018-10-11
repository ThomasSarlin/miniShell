/* external.c
 * Thomas Sarlin
 * Laboration 3 : Systemnära programmering, HT-18
 * Responsible for external commands
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Duplicate a pipe to a standard I/O file descriptor
 * Arguments:	pip	the pipe
 *		end	tells which end of the pipe shold be dup'ed; it can be
 *			one of READ_END or WRITE_END
 *		destfd	the standard I/O file descriptor to be replaced
 * Returns:	-1 on error, else destfd
 */

int dupPipe(int pip[2],int end, int destfd){
	int pipe = dup2(pip[end],destfd);
	return pipe;
}

/* Redirect a standard I/O file descriptor to a file
 * Arguments:	filename	the file to/from which the standard I/O file
 * 				descriptor should be redirected
 * 		flags	indicates whether the file should be opened for reading
 * 			or writing
 * 		destfd	the standard I/O file descriptor which shall be
 *			redirected
 * Returns:	-1 on error, else destfd
 */

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
