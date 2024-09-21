#include <stdio.h>

char msg [] = "Hello, World";

void greet() {
	printf("%s\n", msg);
}

int main(void) {
	greet();
	return 0;
}
