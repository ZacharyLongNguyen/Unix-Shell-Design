#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>

extern FILE *stderr;
char ** parser(char *);
char *currentDir;
int main() {
	/*
		TODO:
		-Implement path command
		-Implement already existing programs
		-Implement redirection
		-Implement parallel commands
	*/
	char buff[1000];
	currentDir = getcwd(buff, sizeof(buff));
	printf("MemeShell> ");
	char *str1 = NULL;
	char **args = malloc(10*sizeof(char*));
	char **paths = malloc(10*sizeof(char *));
	char **dir;
	dir[0] = "";
	pid_t pid;
	//strcpy(paths[0], "/bin");
	int pathcount = 0;
	char *defaultPath = malloc(sizeof(char*));
	strcpy(defaultPath, "/bin/");
	paths[0] = defaultPath;
	dir[0] = defaultPath;//Sets default path
	size_t linesize = 0; // number of elements with elements being of a certain byte size
	ssize_t linelen;
	while((linelen = getline(&str1, &linesize, stdin)) != -1) { // user input and input length
		//If the input is exit, exit, regardless of what is passed
		if(strncmp("exit", str1, 4) == 0) {
			exit(0);
		}
		else if (strncmp("cd", str1, 2) == 0) { //checks if cd is input
			args = parser(str1);
			if(args[2] != NULL) //Check if there is more than one input for cd
				printf("Too many arguments passed for cd \n");
			else if(args[1] == NULL) { //Check if the user only input 'cd'
				//If so, change back to default directory
				int cdcheck = chdir(currentDir);
				if(cdcheck < 0) 
					printf("Bad address for cd\n");
			
			}
			else {
				chdir(args[1]);
				dir[0] = args[1];
			}
		}
		else if (strncmp("path", str1, 4) == 0) {
			//if input is path
			//Need to implement this
			args = parser(str1);
			//Checks if only path is input
			if(args[1] == NULL) {
				paths[0] = NULL;
			}		
			else {
				int count = 1;
				while(args[count] != NULL) { 
					strcpy(paths[count - 1], args[count]);
					count++;
				}
			}
		}
		else { //The input is already an existing function, or doesn't exist
			//We need to fork, and let the child run the process
			if(paths[0] == NULL)
				printf("Invalid path, no external commands can be run\n");
			else {
				args = parser(str1);
				pid = fork();
				for(int i = 0; i < pathcount - 1; i++) {
					//strcat(paths[i], args[0]);
					printf("Checking if path exists\n");
					if(access(paths[i], X_OK) == 0) {
						printf("Command exists in path %d\n", i);
						break;
					}
				}
			}
		}
		printf("MemeShell%s> ", dir[0]);
	}
	free(str1); // deallocates memory from str1
	free(dir); // deallocates memory from dir
	char error_message[30] = "An error has occurred\n";
	write(STDERR_FILENO, error_message, strlen(error_message));
}

char ** parser (char *input) {
	input = strtok(input, "\n");
	char *parsed;
	//Creates args, which is an array that stores the command at args[0], and all input arguments in the following indexes
	char **args = malloc(8*sizeof(char *));
	int argSize = 0;
	parsed = strtok(input, " ");
	while(parsed != NULL) { //Loop places the command and each input into args
		args[argSize] = parsed;
		argSize++;
		parsed = strtok(NULL, " ");
	}
	//Make the last index NULL so it can not go past that index
	args[argSize] = NULL;
	return args;
}

