# project2
cse30341 project 2: processes and the shell (2/10/2017)

Project Description:
You will write a program called myshell which is capable of executing, managing, and monitoring user level programs. This program will be similar in purpose and design to everyday shells like bash or tcsh, although the syntax will be slightly different. myshell will be invoked without any arguments, and will support several different commands.

Your program should print out a prompt like myshell> when it is ready to accept input. It must read a line of input, accepting several possible commands. The start command will start another program with command line arguments, print out the process number of the running program, and then accept another line of input.
For example: Note that emacs will take over the console. This is OK and expected behavior if you are not sitting directly at the desktop of one of the machines in Fitzpatrick. Try to think of other commands that might exhibit behavior that do not take over the console.

The wait command takes no arguments, and causes the shell to wait until a process exits. When this happens, indicate whether the exit was normal or abnormal, along with the exit code or signal number and name, respectively. If there are no processes to wait for, print an appropriate message and then accept another line of input. 
The run command combines the behavior of start and wait. run should start a program, possibly with command line arguments, wait for that particular process to finish, and print the exit status. 
The kill, stop, and continue commands take a process ID as an argument, and send the SIGKILL, SIGSTOP, and SIGCONT signals, respectively, to the indicated processes. Note that a process that is killed still requires a wait in order to collect the exit status.
After each command completes, your program must continue to print a prompt and accept another line of input. The shell should exit with status zero if the command is quit or exit or the input reaches end-of-file. If the user types a blank line, simply print another prompt and accept a new line of input. If the user types any other command, the shell should print a reasonable error message.
Your shell must accept inputs lines of up to 4096 characters, and must handle up to 100 distinct words on a line. 
