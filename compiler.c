#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>

int main() {
	printf("compiler> ");
	char *str1 = NULL;
	size_t linesize = 0; // number of elements with elements being of a certain byte size
	ssize_t linelen; // byte size of each element, or negative error value
	while((linelen = getline(&str1, &linesize, stdin)) != -1) { // user input and input length
		//strsep(&str1, " ");
		if (strncmp("exit", str1, 4) == 0) { // check if input = "exit", return 0 if true
			exit(0);
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
		//hello my love
		//stfu omar
		//suck dick darren, Love you too.
	}
	free(str1); // deallocates memory from str1
	if(ferror(stdin)) { // checks if there is an error, returns 0 if no error
		err(1, "getline"); // displays an error message with where the error is
	}
}
