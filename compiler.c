#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>

extern FILE *stderr;
char ** parser(char *);
int main() {
	/*
		TODO:
		-Implement cd and path command
		-Implement already existing programs
		-Add error stuff
		-Implement redirection
		-Implement parallel commands
		-From Larkin: the 'cd' command should call the chdir() function, where the input is what comes after
		 the cd command
	*/
	printf("MemeShell> ");
	char *str1 = NULL;
	char **args;
	char *dir = "";
	char *path1 = (char*)malloc(sizeof(char)*15);
	char *path2 = (char*)malloc(sizeof(char)*20);
	strcpy(path1, "/bin/");
	strcpy(path2, "/usr/bin/");
	size_t linesize = 0; // number of elements with elements being of a certain byte size
	ssize_t linelen, pathlen; // byte size of each element, or negative error value
	while((linelen = getline(&str1, &linesize, stdin)) != -1) { // user input and input length
		//str1 = strtok(str1, " \n"); // string for command
		//dir = strtok(NULL, " \n"); // string for directory
		//printf("%s \n", str1); // just for testing
		//printf("%s \n", dir); // just for testing
		/*if (dir == NULL) {
			dir = "(null)";
			if (strncmp("exit", str1, 4) == 0) { // check if input = "exit", return 0 if true
				exit(0);
			}
		}*/
		if(strncmp("exit", str1, 4) == 0) {
			exit(0);
		}
		else if (strncmp("cd", str1, 2) == 0) { //checks if cd is input
			dir = strtok(str1, " \n");
			dir = strtok (NULL, " ");
			dir[strlen(dir) - 1] = '\0'; //Remove the end line character at the end of dir
			}
		else if (strncmp("path", str1, 4) == 0) {
			//if input is path
			//Need to implement this
			printf("path\n");
		}
		else { //The input is already an existing function, or doesn't exist
			//pathlen = linelen - 1;
			//char **args = parser(str1); //Places arguments after command into args char
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
		//This is only for testing, and should be removed once the assignment is working
		//printf("Input command: ");
		//fwrite(str1, linelen, 1, stdout); // rewrites the input line
		//printf("\n");
		printf("MemeShell%s> ", dir);
	}
	free(str1); // deallocates memory from str1
	free(dir); // deallocates memory from dir
	char error_message[30] = "An error has occurred\n";
	write(STDERR_FILENO, error_message, strlen(error_message));
}

/*
char ** parser (char *input) {
	input = strtok(input, " \n");
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
}*/

