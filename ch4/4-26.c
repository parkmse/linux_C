#include <stdio.h>
void printd(int n)
{
	if (n<0)
	{
		putchar('-');
		n= -n;
	}
	if (n/10)
		printd(n/10);
	putchar(n%10+'0');
}
int main()
{
	int x = '123';
	printf("%c\n",printd(x));
	return printd;
}
