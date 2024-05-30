#include <stdio.h>
extern void bar(void);

int main(void)
{
	printf("foo print\n");
	bar();
	return 0;
}
