#include <stdio.h>
#include <string.h>

int main(void)
{
	char s[] = " Y Baek: 010 6277:CS professor";
	char *ptr;

	ptr = strtok(s, ":");
	while (ptr != NULL) {
		printf("%s\n", ptr);
		ptr = strtok(NULL, ":");
	}

	return 0;
}
