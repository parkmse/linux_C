#include <stdio.h>

int main(void)
{
	extern int i = 10;
	static int j = 20;
	int r;

	if ( i>j )
		r i - j;
	else if (i<j)
		r = j - i;
	else 
		r = 0;
	return r;
}
