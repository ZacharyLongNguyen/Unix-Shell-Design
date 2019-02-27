#include <stdio.h>

int main() {
	printf("Hello world!\n");
	char str1[20];
	while(1) {
		scanf("%s", str1);
		printf("Inserted command: %s\n", str1);
	}
	return 0;
}
