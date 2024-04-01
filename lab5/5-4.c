#include <stdio.h>

void b(int *p) //int pointer를 인자로 받는 함수 b
{
	printf("%d %d %d\n", p[0], p[-1], p[-2]); // 배열의 마지막 요소부터 3개 요소 출력
	return;
}

int main(void)
{
	int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	int n = (int)(sizeof(a)/sizeof(int)); // 배열 요소 갯수
	for(int i =0; i<n; i++)
		printf("%d ", a[i]);
	putchar('\n');

	b(a+n-1); // 배열의 마지막 요소의 주소를 b에게 전달

	return 0;
}
