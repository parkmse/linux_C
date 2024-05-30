#include <stdio.h>
#include <string.h>

int main(void)
{
	char *s1 = "1234512345";
	char *s2 = "3";

	printf("%d\n", (int)strspn(s1, s2));

	return 0;
}
