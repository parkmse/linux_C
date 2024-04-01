#include <stdio.h>

int main(void)
{
	int i = 0X0F; // 2진수로 0000 1111임.
	int j = 0X14; // 2진수로 0001 0100임.

	printf("i & j = %X\n", i & j);
	printf("i | j = %X\n", i | j);
	printf("i ^ j = %X\n", i ^ j);
	printf("~(i | j) = %X\n", ~(i | j));
	printf("i<<2 = %X\n", i<<2);
	printf("i>>3 = %X\n", i>>3);

	return 0;
}
