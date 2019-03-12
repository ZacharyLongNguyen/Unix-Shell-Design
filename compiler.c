#include <stdio.h>
#include <string.h>

int main() {
	printf("Hello world!\n");
	char str1[20];
	char str2[20] = "exit";
	while(1) {
		printf("command> ");
		scanf("%s", str1);
		int exiting = strcmp(str1, str2);
		if(exiting == 0) {
			return(0);
		}
		printf("Inserted command: %s\n", str1);
		//hello my love
		//stfu omar
		//suck dick darren, Love you too.
	}
	return(0);
}
