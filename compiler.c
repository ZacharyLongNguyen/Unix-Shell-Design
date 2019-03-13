#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>

int main() {
	/*
		TODO:
		-Implement cd and path command
		-Implement parser
		-Implement already existing programs
	*/
	printf("compiler> ");
	char *str1 = NULL;
	char *path1 = (char*)malloc(sizeof(char)*15);
	char *path2 = (char*)malloc(sizeof(char)*20);
	char *parser = NULL;
	strcpy(path1, "/bin/");
	strcpy(path2, "/usr/bin/");
	size_t linesize = 0; // number of elements with elements being of a certain byte size
	ssize_t linelen, pathlen; // byte size of each element, or negative error value
	while((linelen = getline(&str1, &linesize, stdin)) != -1) { // user input and input length
		//strsep(&str1, " ");
		if (strncmp("exit", str1, 4) == 0) { // check if input = "exit", return 0 if true
			exit(0);
		}
		else if (strncmp("cd", str1, 2) == 0) {
			//if cd is input
			//Need to implement this
			printf("cd");
		}
		else if (strncmp("path", str1, 4) == 0) {
			//if input is path
			//Need to implement this
			printf("path");
		}
		pathlen = linelen - 1;
		strncat(path1, str1,pathlen);
		strncat(path2, str1,pathlen);
		if(access(path1, X_OK) == 0) {
			//printf("Command exists in path1");
			//The 0 in the following line needs to get arguments from the parser!
			execv(path1, 0);
		}
		else if(access(path2, X_OK) == 0) {
			//printf("Command exists in path2");
			//The 0 in the following line are arguments from the parser
			execv(path2, 0);
		}
		printf("Input command: ");
		fwrite(str1, linelen, 1, stdout); // rewrites the input line
		/*if (strncmp("fork", str1, 4) {
			int rc = fork();
			if (rc < 0) { // fork fails
				printf("Fork failed\n");
				exit(1);
			}
			else if (rc == 0) {
				*/
		printf("compiler> ");
	}
	free(str1); // deallocates memory from str1
	if(ferror(stdin)) { // checks if there is an error, returns 0 if no error
		err(1, "getline"); // displays an error message with where the error is
	}
}
