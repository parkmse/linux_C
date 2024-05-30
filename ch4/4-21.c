#include <stdio.h>

void a(void)
{
	static int i = 10;
	printf("%d\n", i++);
}
int main(void)
{
	for(int j = 0; j<3 ; j++)
		a();
	return 0;
}

