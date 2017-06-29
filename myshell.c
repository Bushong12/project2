#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

int main (int argc, char *argv[]) {
    while (1) {
	char command[4097];
	char *words[101];
	printf("myshell> ");
	fflush(stdout);
	if (fgets(command, 4097, stdin)!= NULL) {

	    // accept empty lines
	    if (!strcmp(command, "\n")) {
		continue;
	    }

    	    // parse the input
    	    int nwords = 0;
	    char *token; 
	    token = strtok(command, " \t\n");
    	    while (token != NULL) {
		words[nwords] = token;
		token = strtok(NULL, " \t\n");
		nwords++;
	    }
	    words[nwords] = NULL;
	    if (words[0] == NULL) { // prevent it from segfaulting when spaces are typed
		continue;
	    }

	    // run the appropriate command
    	    if (!strcmp(words[0], "start")) {

		// check usage
		if (words[1] == NULL) {
		    printf("%s: Incorrect arguments: usage: start <command>\n", argv[0]);
		    continue;
		}

		// use fork and execvp
	    	int rc = fork();
    		if (rc < 0) {	// fork failed; exit
		    fprintf(stderr, "fork failed\n");
		    exit(1);
    		}
    		else if(rc == 0) {	// child (new process)
	    	    char *myargs[100];
		    myargs[0] = words[1];			// program to run
		    int i = 1;
		    while (words[i + 1] != 0) {
			myargs[i] = words[i + 1];
			i++;
		    }
		    myargs[i] = NULL;				// terminate with NULL
		    printf("%s: process %d started\n", argv[0], (int) getpid());
		    int success = execvp(myargs[0], myargs);	// runs program
		    if (success == -1) {
			printf("%s: couldn't run specified command: %s\n", argv[0], strerror(errno));
		    }
	        }
	    }

	    else if (!strcmp(words[0], "wait")) {
		// use wait
		int status = 0;
		int wc = wait(&status);
		if (WIFEXITED(status) && wc != -1) { // child terminated normally
		    printf("%s: process %d exited normally with status %d\n", argv[0], wc, WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status)){ // child terminated by signal
		    printf("%s: process %d exited abnormally with signal %d: %s\n", argv[0], wc, WTERMSIG(status), strsignal(WTERMSIG(status)));
		}
		else { // no children
		    printf("%s: no processes left\n", argv[0]);
		}
	    }

	    else if (!strcmp(words[0], "run")) {
		// use waitpid
	    	int rc = fork();
    		if (rc < 0) {	// fork failed; exit
		    fprintf(stderr, "fork failed\n");
		    exit(1);
    		}
    		else if(rc == 0) {	// child (new process)
	    	    char *myargs[100];
		    myargs[0] = words[1];			// program to run
		    int i = 1;
		    while (words[i + 1] != 0) {
			myargs[i] = words[i + 1];
			i++;
		    }
		    myargs[i] = NULL;				// terminate with NULL
		    int success = execvp(myargs[0], myargs);	// runs program
		    if (success == -1) {
			printf("%s: couldn't run specified command: %s\n", argv[0], strerror(errno));
		    }
	        }
 	        else {
		    int status = 0;
		    waitpid(rc, &status, 0);
		    if (WIFEXITED(status)) { // terminated normally
		    	printf("%s: process %d exited normally with status %d\n", argv[0], rc, WEXITSTATUS(status));
		    }
		    else if (WIFSIGNALED(status)) { // terminated by signal
			printf("%s: process %d exited abnormally with signal %d: %s\n", argv[0], rc, WTERMSIG(status), strsignal(WTERMSIG(status)));
		    }
	        }
	    }

	    else if (!strcmp(words[0], "kill")) {
		// use kill
		if (words[2] != NULL || !words[1]) {
		    printf("%s: Incorrect arguments: usage: kill <PID>\n", argv[0]);
		    continue;
		}
		int success = kill(atoi(words[1]), SIGKILL);
		if (success == -1) {
		    printf("%s: Failed to kill process %d: %s\n", argv[0], atoi(words[1]), strerror(errno));
		}
		else {
		    printf("%s: process %d killed\n", argv[0], atoi(words[1]));
		}	
	    }

	    else if (!strcmp(words[0], "stop")) {
		// use kill
		if (words[2] != NULL || !words[1]) {
		    printf("%s: Incorrect arguments: usage: stop <PID>\n", argv[0]);
		    continue;
		}
		int success = kill(atoi(words[1]), SIGSTOP);
		if (success == -1) {
		    printf("%s: Failed to stop process %d: %s\n", argv[0], atoi(words[1]), strerror(errno));
		}
		else {
		    printf("%s: process %d stopped\n", argv[0], atoi(words[1]));
		}
	    }

	    else if (!strcmp(words[0], "continue")) {
		// use kill
		if (words[2] != NULL || !words[1]) {
		    printf("%s: Incorrect arguments: usage: continue <PID>\n", argv[0]);
		    continue;
		}
		int success = kill(atoi(words[1]), SIGCONT);
		if (success == -1) {
		    printf("%s: Failed to continue process %d: %s\n", argv[0], atoi(words[1]), strerror(errno));
		}
		else {
		    printf("%s: process %d continued\n", argv[0], atoi(words[1]));
		}
	    }

	    else if (!strcmp(words[0], "quit") | !strcmp(words[0], "exit") | !strcmp(words[0], "\0")) {
		return 0;
	    }

	    else {
		printf("%s: unknown command: %s\n", argv[0], words[0]);
	    }
	}
    }
    return 0;
}
