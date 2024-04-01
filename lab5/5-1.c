#include <stdio.h>

int main(void)
{
	int a[] = {1, 2, 3, 4, 5};
	int *p = a; // 포인터 p 선언, a[0]주소 할당
	int i;

	for ( i = 0; i<5; i++) 
		printf("%2d", a[i]); // 배열 a 모든 요소 출력
	putchar('\n');
	i = 0;

	while(i<5)
	{
		printf("%2d", *(p++)); // 포인터 p가 가리키는 값 출력, p값 1 증가
	i++;
	}
	putchar('\n');
	return 0;
}

