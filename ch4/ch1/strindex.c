#include <stdio.h>

int strindex(char s[], char t[]) // char *s, char *t 사용
{
	int i, j, k;
	for (i = 0; s[i] != '\0'; i++)
	{
		for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
			;
		if (k>0 && t[k] == '\0')
			return i;
	}
	return -1;
}
