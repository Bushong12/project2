#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {	// fork failed; exit
	fprintf(stderr, "fork failed\n");
	exit(1);
    }
    else if(rc == 0) {	// child (new process)
	char *myargs[4];
	myargs[0] = strdup("cp");	// program: "cp" (copy)
	myargs[1] = argv[1];		// input file
	myargs[2] = strdup("CloneFile");// argument: copy of the file
	myargs[3] = NULL;		// terminate
	execvp(myargs[0], myargs);	// runs word count
    }
    else {
	int wc = wait(NULL);
	char *myargs[4];
        myargs[0] = strdup("md5sum");	// program: "md5sum"
	myargs[1] = argv[1];		// input file
	myargs[2] = strdup("CloneFile");// argument: copy of input file
	myargs[3] = NULL;		// terminate
        execvp(myargs[0], myargs);
    }
    return 0;
}
