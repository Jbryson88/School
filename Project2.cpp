// Write a C++ program that is able to use system call EXEC to execute a command

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
	// Declare necessary variables;
    char *command;
    char *arg[10];
    char *token;
    int i = 0;
    int status;
    pid_t pid;

	// Get path data
    cout << "Enter the command: ";
    cin.getline(command, 100);

// Parse path data into a 2-d character array so that each entry of the array is a path.  Hint: you may use strtok function to complete this task.
    token = strtok(command, " ");
    while (token != NULL)
    {
        arg[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    arg[i] = NULL;

    // Create a child process using fork() and execute the command using execvp() in the child process.
    pid = fork();
    if (pid == 0)
    {
        execvp(arg[0], arg);
    }
    else
    {
        waitpid(pid, &status, 0);
    }

    return 0;

}


	for(; ;) { //accept user’s command until the user quit
		// Print shell prompt
        cout << "myshell> ";
        cin.getline(command, 100);

		// Read input 
        token = strtok(command, " ");
        while (token != NULL)
        {
            arg[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        arg[i] = NULL;

        // Parse input into command and arguments
        if (strcmp(arg[0], "quit") == 0)
        {
            break;
        }

		// Compare the input with “quit” or “exit”
        // If the input is “quit” or “exit”, terminate the shell
        // Otherwise, create a child process using fork() and execute the command using execvp() in the child process.
        pid = fork();
        if (pid == 0)
        {
            execvp(arg[0], arg);
        }
        else
        {
            waitpid(pid, &status, 0);
        }
    }
		//if yes, and then terminate the program
        //if no, then create a child process using fork() and execute the command using execvp() in the child process.
    return 0;

		else {
			// Call fork to create a child process
            			pid = fork();
			if (pid == 0) { //child process
				// Call execvp to execute the command
				execvp(arg[0], arg);
			}
			else { //parent process
				// Call waitpid to wait for the child process to finish
				waitpid(pid, &status, 0);
			}

        } 
			if (strcmp(arg[0], "quit") == 0) {
                execvp(arg[0], arg);
            }
            else { //parent process
                // Call waitpid to wait for the child process to finish
                waitpid(pid, &status, 0);
            }   
			{
				for(path 1 to path n)
				{
					// Make arguments for execl using strcpy and strcat 
                    					strcpy(path, arg[0]);
					strcat(path, arg[1]);
					// Call execl to execute the command
					execl(path, arg[0], arg[1], NULL);
				}
					// Call execl(path/cmd, cmd, argu1, …, 0);
                    execl(path, arg[0], arg[1], NULL);
				}
				// No success, print no such a command
                cout << "No such a command" << endl;
			else (pid == 0) { //child process
            				// Call waitpid to wait for the child process to finish
				waitpid(pid, &status, 0);
		
			         // Call wait function to wait the child process’ termination
        wait(&status);
	//end of infinite loop
    

	exit(0);
    };
 


