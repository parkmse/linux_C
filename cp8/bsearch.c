#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *p, const void *q)
{
	int i = *(const int *)p;
	int j = *(const int *)q;

	return (i-j);
}
	
int main(void)
{
	int a[] = {32, 11, 97, 42, 21, 70, 56, 67, 88};

	int num = sizeof(a) / sizeof(int);
	int i;

	for (i = 0; i < num; i++)
		printf("%d ", a[i]);
	printf("\n");
	
	qsort(a, num, sizeof(int), compare);

	for (i = 0; i < num; i++)
		printf("%d ", a[i]);
	printf("\n");

	int *found;
	int key = 42;
	if ((found = bsearch(&key, a, num, sizeof(int), compare)) != NULL)
		printf("Found key is %d.\n", *found);
	else
		printf("There is no %d in List.\n", key);

	key = 13;
	if ((found = bsearch(&key, a, num, sizeof(int), compare)) != NULL)
		printf("Found key is %d\n.", *found);
	else
		printf("There is no %d in List.\n", key);

	return 0;
}

