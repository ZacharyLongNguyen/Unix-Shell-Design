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
	char **args;
	char **dir = malloc(8*sizeof(char*));
	char *path1 = (char*)malloc(sizeof(char)*15);
	char *path2 = (char*)malloc(sizeof(char)*20);
	strcpy(path1, "/bin/");
	strcpy(path2, "/usr/bin/");
	char *defaultPath = malloc(sizeof(char*));
	strcpy(defaultPath, "/bin/");
	dir[0] = defaultPath;//Sets default path
	size_t linesize = 0; // number of elements with elements being of a certain byte size
	ssize_t linelen, pathlen; // byte size of each element, or negative error value
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
				int cdcheck = chdir(currentDir); //Checks to make sure the default address is correct
				if(cdcheck < 0) 
					printf("Bad address for cd\n");
			
			}
			else {
				chdir(args[1]);
				dir = args[1];
			}
		}
		else if (strncmp("path", str1, 4) == 0) {
			//if input is path
			//Need to implement this
			printf("path\n");
		}
		else { //The input is already an existing function, or doesn't exist
			//pathlen = linelen - 1;
			//char **args = parser(str1); //Places arguments after command into args char
			args = parser(str1);
			strncat(path1, str1,pathlen); //
			strncat(path2, str1,pathlen);
			if(access(path1, X_OK) == 0) {
				//printf("Command exists in path1");
				//The 0 in the following line needs to get arguments from the parser!
				/*int runcheck = fork();
				if(runcheck < 0) {
					printf("Function call failed. Exiting child.");
					exit(0);
				}*/
				/*else if(runcheck == 0) {
					execv(path1,
				}*/
				execv(path1, 0);
			}
			else if(access(path2, X_OK) == 0) {
				//printf("Command exists in path2");
				//The 0 in the following line are arguments from the parser
				execv(path2, 0);
			}
		}
		printf("MemeShell%s> ", dir);
	}
	free(str1); // deallocates memory from str1
	free(dir); // deallocates memory from dir
	char error_message[30] = "An error has occurred\n";
	write(STDERR_FILENO, error_message, strlen(error_message));
}

char ** parser (char *input) {
	input = strtok(input, "\n");
	char *parsed;
	char **args = malloc(8*sizeof(char *));
	int argSize = 0;
	parsed = strtok(input, " ");
	while(parsed != NULL) {
		args[argSize] = parsed;
		argSize++;
		parsed = strtok(NULL, " ");
	}
	args[argSize] = NULL;
	return args;
}

