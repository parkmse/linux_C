#include <stdio.h>
#define MAXLINE 1000

int mygetline(char line[], int max); //mygetline 사용, (char*, int)사용
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";

int main()
{
	char line[MAXLINE];
	int found = 0;

	while (mygetline(line, MAXLINE) > 0)
		if (strindex(line, pattern) >= 0) {
			printf("%s", line);
			found ++;
		}
	return found;
}

